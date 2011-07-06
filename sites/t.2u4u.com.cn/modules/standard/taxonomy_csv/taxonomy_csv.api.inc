<?php
// $Id: taxonomy_csv.api.inc,v 1.1.2.7 2010/01/13 17:43:18 danielkm Exp $

/**
 * @file
 * This Api allows to use taxonomy_csv import/export functions from modules.
 *
 * Functions sets:
 * 1a. Prepare and import a vocabulary      : taxonomy_csv_vocabulary_import
 * 1b. Prepare and export a vocabulary      : taxonomy_csv_vocabulary_export
 * 2a. Prepare and import a line            : taxonomy_csv_line_import
 * 2b. Prepare and export a line from a term: taxonomy_csv_line_export
 * 3. Prepare and import a term             : taxonomy_csv_term_import
 * 4. Errors helpers
 * 5. Infos and log messages
 *
 *
 * Structure of import Api:
 * -  1. Batch prepare import of file or text
 * -  2. Process import line by line (see below)
 * -  3. Evaluate vocabulary and finish process
 *
 * Process import structure (line by line import from a batch set):
 * - 1. Validate line
 *     1. Clean input line
 *     2. Check line items
 * - 2. Prepare to process items matching import type (eventual loop)
 * - 3. Process import
 *     1. Find previous or existing term (see below)
 *     2. Update or create term
 *     3. Cache term
 *
 * Find a term before update or create it:
 * - 1. In previous imported
 *     1. In parent if structure
 *     2. In whole cache in all cases
 *     3. In extended cache if related (internal use only)
 * - 2. In existing terms of the vocabulary (except ignore all)
 *     1. In parent if structure
 *     2. In whole vocabulary in all cases
 *     3. In all vocabularies if related (internal use only)
 *
 *
 * Structure of export Api:
 * - 1. Batch prepare of vocabulary
 * - 2. Export depending on format
 *
 *
 * To add a new csv scheme, need:
 * - a define without space,
 * - items in _taxonomy_csv_info_lists,
 * - items in taxonomy_csv.js and taxonomy_csv.css,
 * - a description in forms (taxonomy_csv.module),
 * - an advanced help.
 * - a case in _taxonomy_csv_check_items(),
 * - a case in taxonomy_csv_import_line_items(),
 * - eventually specific options.
 * - a case in taxonomy_csv_export_line_items() if possible,
 *
 *
 * To use as an Api, file need to be invoked as a dependency, an external module
 * or an internal include. Example use:
 * @code
 * // Invoke taxonomy_csv.api if not included in module.info or enabled.
 * $taxonomy_csv_path = drupal_get_path('module', 'taxonomy_csv');
 * require_once("$taxonomy_csv_path/taxonomy_csv.api.inc");
 *
 * $csv_lines = '"Europe", "France", "Paris"';
 * $result = taxonomy_csv_vocabulary_import(
 *   array(
 *    'source_choice'  => 'text',
 *    'text'           => $csv_lines,
 *    'import_format'  => 'tree_structure',
 *    'existing_items' => 'update_replace',
 * ));
 * @endcode
 */

/**
 * Available import/export schemas.
 */
define('TAXONOMY_CSV_FORMAT_ALONE_TERMS',       'alone_terms');
define('TAXONOMY_CSV_FORMAT_FIELDS_LINKS',      'fields_links');
define('TAXONOMY_CSV_FORMAT_FLAT',              'flat');
define('TAXONOMY_CSV_FORMAT_TREE_STRUCTURE',    'tree_structure');
define('TAXONOMY_CSV_FORMAT_POLYHIERARCHY',     'polyhierarchy');
define('TAXONOMY_CSV_FORMAT_PARENTS',           'parents');
define('TAXONOMY_CSV_FORMAT_CHILDREN',          'children');
define('TAXONOMY_CSV_FORMAT_FIELDS',            'fields');
define('TAXONOMY_CSV_FORMAT_RELATIONS',         'relations');
define('TAXONOMY_CSV_FORMAT_DESCRIPTIONS',      'descriptions');
define('TAXONOMY_CSV_FORMAT_WEIGHTS',           'weights');
define('TAXONOMY_CSV_FORMAT_SYNONYMS',          'synonyms');
define('TAXONOMY_CSV_FORMAT_TAXONOMY_MANAGER',  'taxonomy_manager');

/**
 * Available import options.
 */
define('TAXONOMY_CSV_EXISTING_UPDATE',          'update');
define('TAXONOMY_CSV_EXISTING_UPDATE_MERGE',    'update_merge');
define('TAXONOMY_CSV_EXISTING_UPDATE_REPLACE',  'update_replace');
define('TAXONOMY_CSV_EXISTING_IGNORE',          'ignore');
define('TAXONOMY_CSV_EXISTING_IGNORE_CREATE',   'ignore_create');
define('TAXONOMY_CSV_EXISTING_IGNORE_ALL',      'ignore_all');
define('TAXONOMY_CSV_EXISTING_IGNORE_PREVIOUS', 'ignore_previous');

/**
 * List of watchdog options.
 */
define('TAXONOMY_CSV_WATCHDOG_ERROR',   3); // Stop import process.
define('TAXONOMY_CSV_WATCHDOG_WARNING', 4); // Stop line process and go next.
define('TAXONOMY_CSV_WATCHDOG_NOTICE',  5); // Continue current line process.
define('TAXONOMY_CSV_WATCHDOG_INFO',    6); // Successfully processed.
define('TAXONOMY_CSV_WATCHDOG_DEBUG',   7); // Internal use only.
define('TAXONOMY_CSV_WATCHDOG_NONE',    9); // Internal use only.

/**
 * Information about import process. Use too default Drupal constants:
 *   SAVED_NEW     = 1
 *   SAVED_UPDATED = 2
 * Possibly use of:
 *   SAVED_DELETED = 3
 */
define('TAXONOMY_CSV_ERROR',       0);
define('TAXONOMY_CSV_NEW_UPDATED', 4);
define('TAXONOMY_CSV_UNCHANGED',   5);

/**
 * @defgroup taxonomy_csv_vocabulary Import/export a vocabulary
 * @{
 * Functions allowing import of a vocabulary into a new or an existing one and
 * export of a vocabulary to a file.
 */

/**
 * Prepare the import of a vocabulary.
 * If not used in a form, don't forget to use batch_process().
 *
 * @param $options
 *   Array of options:
 *     source_choice  : 'path', 'url' or 'text'
 *     path           : path to local csv file
 *     url            : url to distant or local csv file
 *     file           : object file if file is already uploaded
 *     text           : csv text to import
 *     import_format  : see _taxonomy_csv_info_lists('list_import_format')
 *     delimiter      : 1 character csv delimiter (default: ",")
 *     enclosure      : 0 or 1 character csv enclosure (default: none or '"')
 *     vocabulary_target: 'autocreate' (default), 'duplicate' or 'existing'
 *     vocabulary_id  : vocabulary id to duplicate or to import into
 *     existing_items : see _taxonomy_csv_info_lists('list_import_option')
 *     internal_cache : boolean. use (default) or not internal cache
 *     hierarchy_check: boolean. check (default) or not vocabulary hierarchy
 *     hierarchy_level: if not hierarchy check, set hierarchy level (0, 1 or 2)
 *     line_checks    : boolean. check (default) or not format of lines
 *     utf8_check     : boolean. check (default) or not utf8 format
 *     result_stats   : boolean. Display (default) or not stats
 *     result_terms   : boolean. Display (default) or not list of imported terms
 *     result_level   : Log: 'none', 'warnings' (default), 'notices' or 'infos'
 *     result_type    : Display of log: 'by_message' (default) or 'by_line'
 *     // Specific to relations import:
 *     relations_create_subrelations: boolean.
 *     relations_all_vocabularies   : boolean.
 *   Needed options are source_choice, path or url or text, import_format
 *   and existing_items. Other options have default values.
 * @return
 *   Array of errors or nothing (batch process to execute).
 */
function taxonomy_csv_vocabulary_import($options) {
  // Check and eventually update options.
  $result = _taxonomy_csv_vocabulary_import_check_options($options);
  if (count($result)) {
    return $result;
  }

  // Remove useless option, because text is saved.
  if ($options['source_choice'] == 'text') {
    $options['text'] = '';
  }

  // Prepare vocabularies.
  // With some formats, vocabularies are created during import.
  if (!in_array($options['import_format'], array(
      TAXONOMY_CSV_FORMAT_FIELDS_LINKS,
    ))) {
    // User choose to autocreate or duplicate a vocabulary.
    switch ($options['vocabulary_target']) {
      case 'autocreate':
        $new_vocabulary = taxonomy_csv_vocabulary_create(($options['source_choice'] != 'text') ? $options['file']->filename : '');
        $options['vocabulary_id'] = $new_vocabulary['vid'];
        break;

      case 'duplicate':
        $new_vocabulary = taxonomy_csv_vocabulary_duplicate($options['vocabulary_id']);
        $options['vocabulary_id'] = $new_vocabulary['vid'];
        break;
    }
    $options['vocabulary'] = taxonomy_vocabulary_load($options['vocabulary_id']);
  }

  // Prepare import batch.
  $batch = array(
    'title'            => ($options['source_choice'] != 'text') ?
        t('Importing terms from CSV file "%filename"...', array('%filename' => $options['file']->filename)) :
        t('Importing terms from text...'),
    'init_message'     => t('Starting uploading of datas...'),
    'progress_message' => '',
    'error_message'    => t('An error occurred during the import.'),
    'finished'         => '_taxonomy_csv_vocabulary_import_finished',
    'file'             => dirname(drupal_get_filename('module', 'taxonomy_csv')) .'/taxonomy_csv.api.inc',
    'progressive'      => TRUE,
    'operations'       => array(
      0 => array('_taxonomy_csv_vocabulary_import_process', array($options)),
    ),
  );

  batch_set($batch);
}

/**
 * Validate options of imported vocabulary or line.
 *
 * @param $options
 *   Array of options.
 * @return
 *   Array of messages errors if any.
 *   By reference options are cleaned and completed.
 */
function _taxonomy_csv_vocabulary_import_check_options(&$options) {
  $messages = array();

  // Set default value for unset options.
  foreach (array(
      'delimiter'          => ',',
      'enclosure'          => '',
      'vocabulary_target'  => 'autocreate',
      'internal_cache'     => TRUE,
      'hierarchy_check'    => TRUE,
      'line_checks'        => TRUE,
      'utf8_check'         => TRUE,
      'result_stats'       => 'result_stats',
      'result_terms'       => 'result_terms',
      'result_level'       => 'notices',
      'result_type'        => 'by_message',
      // Default options of specific imports.
      'relations_create_subrelations' => FALSE,
      'relations_all_vocabularies'    => FALSE,
    ) as $key => $value) {
    if (!isset($options[$key])) {
      $options[$key] = $value;
    }
  }

  // Check if there is write access and prepare file.
  switch ($options['source_choice']) {
    case 'path':
    case 'url':
      // Upload if not already uploaded.
      if (!isset($options['file'])) {
        // Upload from a path.
        if ($options['source_choice'] == 'path') {
          $options['file'] = file_save_upload($options['path']);
        }
        // Upload from an url.
        else {
          $filename = file_save_data(
            file_get_contents($options['url']),
            basename($options['url']),
            'FILE_EXISTS_RENAME');
          $options['file'] = new stdClass();
          $options['file']->filename = basename($filename);
          $options['file']->filepath = $filename;
          $options['file']->filesize = filesize($filename);
        }
      }

      if (!$options['file']) {
        $messages['path'] = t("You choose to import a taxonomy by a file, but you don't set its name or its size is greater than the server's limit of !max_size.", array('!max_size' => format_size(parse_size(ini_get('upload_max_filesize')))));
      }
      elseif (!$options['file']->filesize) {
        $messages['path'] = t('Size of your file is null.');
      }
      break;

    case 'text':
      if (empty($options['text'])) {
        $messages['text'] = t('You choose to import a taxonomy by a text, but the text is empty.');
      }
      elseif (!isset($options['file'])) {
        // Prepare import by text: save text as a temp file to simplify process
        // and avoid memory congestion.
        $filename = file_save_data(
          $options['text'],
          'taxo_csv',
          'FILE_EXISTS_RENAME');
        $options['file'] = new stdClass();
        $options['file']->filename = basename($filename);
        $options['file']->filepath = $filename;
        $options['file']->filesize = filesize($filename);

        if (!$filename) {
          $messages['text'] = t('Import by text needs access to temp directory. Import failed.');
        }
      }
      break;

    default:
      $messages['source_choice'] = t('Source choice should be "path", "url" or "text".');
  }

  // Delimiter or enclosure greater than one character are useless with fgetcsv.
  if (drupal_strlen($options['delimiter']) != 1) {
    $messages['delimiter'] = t('Delimiter should be a one character string.');
  }
  if (drupal_strlen($options['enclosure']) == 0) {
    // With fgetcsv, empty enclosure bugs, so use default quote enclosure.
    $options['enclosure'] = '"';
  }
  elseif (drupal_strlen($options['enclosure']) > 1) {
    $messages['enclosure'] = t('Enclosure lenght cannot be greater than one character.');
  }
  if ($options['delimiter'] == $options['enclosure']) {
    $messages['delimiter'] = t('Delimiter and enclosure cannot be same character.');
  }

  if (isset($options['file'])) {
    // Calculates number of lines to be imported.
    // Automatically detects line endings.
    ini_set('auto_detect_line_endings', '1');
    $handle = fopen($options['file']->filepath, 'r');
    $lines_count = 0;
    while (fgetcsv($handle, 32768, $options['delimiter'], $options['enclosure'])) {
      $lines_count++;
    }
    fclose($handle);
    $options['total_lines'] = $lines_count;
    if (!$options['total_lines']) {
      $messages['total_lines'] = t('No term to import. Import finished.');
    }
  }

  if (!in_array($options['vocabulary_target'], array(
      'autocreate',
      'duplicate',
      'existing',
    ))) {
    $messages['vocabulary_target'] = t('Destination target should be "autocreate", "duplicate" or "existing".');
  }

  if ($options['vocabulary_target'] == 'duplicate'
      || $options['vocabulary_target'] == 'existing') {
    $list_vocabularies = taxonomy_get_vocabularies();
    if (!isset($list_vocabularies[$options['vocabulary_id']])) {
      $messages['vocabulary_id'] = t("You choose to use an existing vocabulary, but you haven't choose it.");
    }
  }

  $list_import_format = _taxonomy_csv_info_lists('list_import_format');
  $list_import_option = _taxonomy_csv_info_lists('list_import_option');
  $list_import_format_allowed_import_option = _taxonomy_csv_info_lists('list_import_format_allowed_import_option');
  if (!array_key_exists($options['import_format'], $list_import_format)) {
    $messages['import_format'] = t('Source content "!import_format" is not managed.', array(
      '!import_format' => $list_import_format[$options['import_format']]
    ));
  }
  elseif (!in_array($options['existing_items'], $list_import_format_allowed_import_option[$options['import_format']])) {
    $messages['existing_items'] = t('Import option "%existing_items" cannot be used with source content "!import_format".', array(
      '%existing_items' => $list_import_option[$options['existing_items']],
      '!import_format'  => $list_import_format[$options['import_format']],
    ));
  }

  if (!$options['existing_items']) {
    $messages['existing_items'] = t('Please set what will become existing terms.');
  }
  elseif (!array_key_exists($options['existing_items'], $list_import_option)) {
    $messages['existing_items'] = t('Import option "!existing_items" is not managed.', array(
      '!existing_items' => $list_import_option[$options['existing_items']]
    ));
  }

  if ($options['hierarchy_check']
      && ($options['hierarchy_level'] < 0 || $options['hierarchy_level'] > 2)) {
    $messages['hierarchy_level'] = t('You need to set hierarchy level if hierarchy check of vocabulary is disabled.');
  }

  return $messages;
}

/**
 * Batch process of vocabulary import.
 *
 * @param $options
 *   Array of batch options.
 * @param &$context
 *   Batch context to keep results and messages.
 * @return
 *   NULL because use of &$context.
 */
function _taxonomy_csv_vocabulary_import_process($options, &$context) {
  $first = FALSE;

  // First callback.
  if (empty($context['sandbox'])) {
    // Remember options as batch_set can't use form_storage.
    // It allows too that first line in result is numbered 1 and not 0.
    $context['results'][0] = $options;

    $first = TRUE;

    // Automatically detect line endings.
    ini_set('auto_detect_line_endings', '1');

    // Initialize some variables.
    $context['results'][0]['current_line'] = 0;
    $context['results'][0]['worst_line'] = 0;
    $context['results'][0]['worst_message'] = 999;
    $context['results'][0]['handle'] = fopen($options['file']->filepath, 'r');
    $context['sandbox']['handle_pointer'] = 0;
    $context['sandbox']['max'] = $options['total_lines'];
    $context['sandbox']['previous_items'] = array(
      'name' => array(),
      'tid'  => array(),
    );

    // Enable or disable cache.
    $result = _taxonomy_csv_term_cache($options['internal_cache'], 'use_cache');
  }
  elseif (!is_resource($context['results'][0]['handle'])) {
    // Recall file and set pointer in case of memory or time out.
    $context['results'][0]['handle'] = fopen($options['file']->filepath, 'r');
    fseek($context['results'][0]['handle'], $context['sandbox']['handle_pointer']);

    // Reload internal static cache if it has been removed during a long batch.
    if ($options['internal_cache']
        && isset($context['results'][0]['imported_terms'])
        && (_taxonomy_csv_term_cache('', 'count') == 0)) {
      $result = _taxonomy_csv_term_cache($context['results'][0]['imported_terms'], 'set_cache');
    }
  }

  // Load and process one line.
  $worst_line     = &$context['results'][0]['worst_line'];
  $worst_message  = &$context['results'][0]['worst_message'];
  $handle         = &$context['results'][0]['handle'];
  $line_number    = &$context['results'][0]['current_line'];
  $previous_items = &$context['sandbox']['previous_items'];
  $line = fgetcsv($handle, 32768, $options['delimiter'], $options['enclosure']);
  if ($line) {
    $line_number++;

    // Remember pointer in case of memory or time out.
    $context['sandbox']['handle_pointer']  = ftell($handle);

    // Skip eventual UTF-8 byte order mark.
    if ($first) {
      if (strncmp($line[0], "\xEF\xBB\xBF", 3) === 0) {
        $line[0] = substr($line[0], 3);
        $first = FALSE;
      }
    }

    // Process import of current line.
    $result = taxonomy_csv_line_import($line, $options, $previous_items);

    // Remember processed line.
    $previous_items['name'] = $result['name'];
    $previous_items['tid']  = $result['tid'];

    // Remember worst message of imported lines.
    $worst_message_new = _taxonomy_csv_message_get_worst_message($result['msg']);
    if ($worst_message_new < $worst_message) {
      $worst_message = $worst_message_new;
      $worst_line    = $line_number;
    };

    if ($options['internal_cache']) {
      // Remember only wanted logs.
      switch ($options['result_level']) {
        case 'none':
          break;
        case 'warnings':
          $list_messages = array();
          foreach ($result['msg'] as $value) {
            foreach ($value as $msg) {
              if (_taxonomy_csv_message_get_level($msg) <= TAXONOMY_CSV_WATCHDOG_WARNING) {
                $list_messages[$msg] = $msg;
              }
            }
          }
          if (count($list_messages)) {
            sort($list_messages);
            $context['results'][$line_number] = $list_messages;
          }
          break;
        case 'notices':
          $list_messages = array();
          foreach ($result['msg'] as $value) {
            foreach ($value as $msg) {
              if (_taxonomy_csv_message_get_level($msg) <= TAXONOMY_CSV_WATCHDOG_NOTICE) {
                $list_messages[$msg] = $msg;
              }
            }
          }
          sort($list_messages);
          $context['results'][$line_number] = $list_messages;
          break;
        case 'infos':
          $list_messages = array();
          foreach ($result['msg'] as $value) {
            foreach ($value as $msg) {
              $list_messages[$msg] = $msg;
            }
          }
          sort($list_messages);
          $context['results'][$line_number] = $list_messages;
          break;
        case 'full':
          $context['results'][$line_number] = $result;
          break;
      }

      // Save static cache to keep infos about process in case of batch timeout.
      $context['results'][0]['imported_terms'] =& _taxonomy_csv_term_cache('', 'dump');
    }

    // Inform about progress.
    $context['message'] = t('Line !line_number of !total_lines processed: !line', array(
      '!line_number' => $line_number,
      '!total_lines' => $options['total_lines'],
      '!line'        => implode(', ', $line),
    ));

    // Check worst message of imported lines and update progress.
    if (_taxonomy_csv_message_get_level($worst_message) > TAXONOMY_CSV_WATCHDOG_ERROR) {
      $context['finished'] = $line_number / $context['sandbox']['max'];
    }
    else {
      $context['finished'] = 1;
      if ($options['internal_cache']) {
        $result = _taxonomy_csv_term_cache('', 'clear');
      }
    }
  }
  // With some formats, remember vocabularies to be checked.
  if (in_array($options['import_format'], array(
      TAXONOMY_CSV_FORMAT_FIELDS_LINKS,
    ))) {
    $context['results'][0]['last_items'] = $previous_items;
  }
}

/**
 * Callback for finished batch import and display result informations.
 */
function _taxonomy_csv_vocabulary_import_finished($success, $results, $operations) {
  // $results[0] is used to save options and some infos (imported terms), as
  // batch process can't use $form_state.
  $options = &$results[0];
  unset($results[0]);

  // Close imported file.
  if ($options['handle']) {
    fclose($options['handle']);
  }

  // Clear internal cache.
  if ($options['internal_cache']) {
    $result = _taxonomy_csv_term_cache('', 'clear');
  }

  // Display general info.
  drupal_set_message(_taxonomy_csv_info_chosen_options($options), 'status');

  // Check and info on used or created vocabularies.
  // With some formats, multiple vocabularies can be created.
  $vocabularies = (in_array($options['import_format'], array(
        TAXONOMY_CSV_FORMAT_FIELDS_LINKS,
      ))) ?
      $options['last_items']['tid']['vocabulary'] :
      array($options['vocabulary_id']);
  $message = t('!count used or created.', array('!count' => format_plural(count($vocabularies), 'A vocabulary has been', '@count vocabularies have been')));
  drupal_set_message($message, 'status');
  foreach ($vocabularies as $vocabulary_id) {
    // Check and update hierarchy of vocabularies.
    $vocabulary = taxonomy_vocabulary_load($vocabulary_id);
    $new_hierarchy[$vocabulary_id] = ($options['hierarchy_check']) ?
        taxonomy_csv_vocabulary_check_hierarchy($vocabulary_id) :
        taxonomy_csv_vocabulary_check_hierarchy($vocabulary_id, $options['hierarchy_level']);

    // Display general info about vocabulary.
    $message = (in_array($options['import_format'], array(
          TAXONOMY_CSV_FORMAT_FIELDS_LINKS,
        ))) ?
        t('Vocabulary "%vocabulary_name" has been used or created.', array('%vocabulary_name' => $vocabulary->name)) :
        _taxonomy_csv_info_vocabulary_destination($vocabulary, $options['vocabulary_target']);
    $message .=  '<br />';
    $message .= _taxonomy_csv_info_vocabulary_result($vocabulary, $options['vocabulary_target'], $new_hierarchy[$vocabulary_id]) .'<br />';
    if (!$options['hierarchy_check']) {
      $message .= t('Hierarchy level has been manually set.') .'<br />';
    }
    drupal_set_message($message, 'status');
  }

  // Prepare batch result message.
  if (!$success) {
    $message = t('Importation failed');
    $message .= '<br />'. t('This issue is related to import process or to size import and probably not to content.');
    if ($options['current_line'] == $options['total_lines']) {
      $message .= '<br />'. t('Import process was successful, but the evaluation of hierarchy level has failed, because it is highly memory consumming. You need to change its value with default Drupal functions or set it in Tweaks section of Taxonomy csv.') .' '. t('This problem can be caused too by a high log level. You can reduce it in advanced options.');
    }
    else {
      $message .= '<br />'. t('Import process was successful until the line !line_count of a total of !total_lines. You can first check your file on this line and check file uploading.', array(
        '!line_count'  => $options['current_line'],
        '!total_lines' => $options['total_lines'],
      ));
    }
    $message .= '<br />'. t('You can reduce log level or disable internal cache to avoid this error.');
    $message .= '<br />'. t('You can reinstall module from a fresh release or submit an issue on <a href="!link">Taxonomy CSV import/export module</a>.', array(
      '!link' => url('http://drupal.org/project/issues/taxonomy_csv/'),
    ));

    drupal_set_message($message, 'error');
  }
  else {
    // Short summary information.
    switch (_taxonomy_csv_message_get_level($options['worst_message'])) {
      case TAXONOMY_CSV_WATCHDOG_ERROR:
        drupal_set_message(t('Errors have been reported during import process. Process failed at line !line_number with error: !message', array(
          '!line_number' => $options['worst_line'],
          '!message'     => _taxonomy_csv_info_result_text($options['worst_message']),
        )), 'error');
        break;
      case TAXONOMY_CSV_WATCHDOG_WARNING:
        drupal_set_message(t('Warnings have been reported during import process (bad formatted lines). First line skipped is line !line_number with message: !message', array(
          '!line_number' => $options['worst_line'],
          '!message'     => _taxonomy_csv_info_result_text($options['worst_message']),
        )), 'error');
        break;
      case TAXONOMY_CSV_WATCHDOG_NOTICE:
        drupal_set_message(t('Notices have been reported during import process (bad formatted or empty lines). Lines processed. First notice on line !line_number with message: !message', array(
          '!line_number' => $options['worst_line'],
          '!message'     => _taxonomy_csv_info_result_text($options['worst_message']),
        )), 'warning');
        break;
      case TAXONOMY_CSV_WATCHDOG_INFO:
      default:
        drupal_set_message(t('No error, warnings or notices have been reported during import process.'), 'status');
        break;
    }

    if (!$options['line_checks']) {
      drupal_set_message(t('Line checks have been disabled. Some warnings and notices may have not been reported.'), 'warning');
    }

    if (!$options['internal_cache']) {
      drupal_set_message(t('No more information about process because internal cache is disabled.'), 'notice');
    }
    else {
      // Display stats and eventually lists about imported terms.
      if ($options['result_stats'] || $options['result_terms']) {
        if (isset($options['imported_terms'])) {
          if ($options['result_terms']) {
            drupal_set_message(_taxonomy_csv_info_terms_stats($options['imported_terms'], 'full'), 'status');
          }
          elseif ($options['result_stats']) {
            drupal_set_message(_taxonomy_csv_info_terms_stats($options['imported_terms'], 'stats'), 'status');
          }
        }
        else {
          drupal_set_message(t('No term was imported.'), 'warning');
        }
      }

      // Display detailled result of import.
      if ($options['result_level'] != 'none') {
        if (count($results)) {
          drupal_set_message(t('Available informations about lines import.'));
          call_user_func("_taxonomy_csv_info_result_{$options['result_type']}", $results, $options['result_level']);
        }
        else {
          drupal_set_message(t('No more information reported about lines import.'));
        }
      }
    }
  }
}

/**
 * Prepare the export of a vocabulary.
 * If not used in a form, don't forget to use batch_process().
 *
 * @param $options
 *   Array of options:
 *     export_format: see _taxonomy_csv_info_lists('list_export_format')
 *     vocabulary_id: vocabulary id to export (default: 0, which means all)
 *     delimiter    : one character csv delimiter (default: ",")
 *     enclosure    : zero or one character csv enclosure (default: "")
 *     line_ending  : 'Unix' (default), 'Mac' or 'Microsoft DOS'
 *     order        : order of terms: 'name' (default), 'tid' or 'weight'
 *     Specific to fields_links:
 *     fields_links_terms_ids : 'name_if_needed' (default), 'name' or 'tid'
 *     fields_links_vocabularies_ids : 'none' (default), 'name' or 'vid'
 *   Only export_format is needed. Other options have default values.
 * @return
 *   Array of errors or nothing (batch process to execute).
 */
function taxonomy_csv_vocabulary_export($options) {
  // Check and eventually update options.
  $result = _taxonomy_csv_vocabulary_export_check_options($options);
  if (count($result)) {
    return $result;
  }

  // Csv variables.
  $options['separator']   = $options['enclosure'] . $options['delimiter'] . $options['enclosure'];
  $line_ending = array(
    'Unix'             => "\n",
    'Mac'              => "\r",
    'Microsoft DOS'    => "\r\n",
  );
  $options['end_of_line'] = $line_ending[$options['line_ending']];

  // Prepare export batch.
  $batch = array(
    'title'            => t('Exporting terms to CSV file...'),
    'init_message'     => t('Starting downloading of datas...'),
    'progress_message' => '',
    'error_message'    => t('An error occurred during the export.'),
    'finished'         => '_taxonomy_csv_vocabulary_export_finished',
    'file'             => dirname(drupal_get_filename('module', 'taxonomy_csv')) .'/taxonomy_csv.api.inc',
    'progressive'      => TRUE,
    'operations'       => array(
        0 => array('_taxonomy_csv_vocabulary_export_process', array($options))
    ),
  );

  batch_set($batch);
}

/**
 * Validate options of exported vocabulary or line.
 *
 * @param $options
 *   Array of options.
 * @return
 *   Array of messages errors if any.
 *   By reference options are cleaned and completed.
 */
function _taxonomy_csv_vocabulary_export_check_options(&$options) {
  $messages = array();

  // Set default value for unset options.
  foreach (array(
      'vocabulary_id'                 => 0,
      'delimiter'                     => ',',
      'enclosure'                     => '',
      'line_ending'                   => 'Unix',
      'order'                         => 'name',
      // Default options of specific imports.
      'fields_links_terms_ids'        => 'name_if_needed',
      'fields_links_vocabularies_ids' => 'none',
    ) as $key => $value) {
    if (!isset($options[$key])) {
      $options[$key] = $value;
    }
  }

  // Check if there is write access and prepare file (first time only).
  if (!isset($options['file'])) {
    // Set filename.
    if ($options['vocabulary_id']) {
      $vocabulary = taxonomy_vocabulary_load($options['vocabulary_id']);
      $vocabulary_name = $vocabulary->name;
    }
    else {
      $vocabulary_name = t('Taxonomy');
    }
    // Create file.
    $filename = file_save_data(
      '',
      "$vocabulary_name.csv",
      'FILE_EXISTS_RENAME');
    if (!$filename) {
      $messages['file'] = t('Export needs access to temp directory. Export failed.');
    }
    else {
      $options['file'] = new stdClass();
      $options['file']->filename = basename($filename);
      $options['file']->filepath = $filename;
      $options['file']->filesize = filesize($filename);
    }
  }

  $list_export_format = _taxonomy_csv_info_lists('list_export_format');
  if (!array_key_exists($options['export_format'], $list_export_format)) {
    $messages['export_format'] = t('Export format "!export_format" is not managed.', array(
      '!export_format' => $list_export_format[$options['export_format']],
    ));
  }

  $list_vocabularies = taxonomy_get_vocabularies();
  if (!$list_vocabularies) {
    $messages['vocabulary_id'] = t('No vocabulary to export.');
  }
  elseif ($options['vocabulary_id']) {
    if (!isset($list_vocabularies[$options['vocabulary_id']])) {
      $messages['vocabulary_id'] = t("You choose to export a vocabulary, but it doesn't exist.");
    }
  }

  // Delimiter and enclosure greater than one character are forbidden.
  if (drupal_strlen($options['delimiter']) != 1) {
    $messages['delimiter'] = t('Delimiter should be a one character string.');
  }
  if (drupal_strlen($options['enclosure']) > 1) {
    $messages['enclosure'] = t('Enclosure lenght cannot be greater than one character.');
  }
  if ($options['delimiter'] == $options['enclosure']) {
    $messages['delimiter'] = t('Delimiter and enclosure cannot be same character.');
  }

  if (!in_array($options['line_ending'], array(
      'Unix',
      'Mac',
      'Microsoft DOS',
    ))) {
    $messages['line_ending'] = t('Line ending should be "Unix", "Mac" or "Microsoft DOS".');
  }

  if (!in_array($options['order'], array(
      'name',
      'tid',
      'weight',
    ))) {
    $messages['order'] = t('Order should be "name", "tid" or "weight".');
  }

  if (!in_array($options['fields_links_terms_ids'], array(
      'name_if_needed',
      'name',
      'tid',
    ))) {
    $messages['fields_links_terms_ids'] = t('Terms identifiants should be "name_if_needed", "name" or "tid".');
  }

  if (!in_array($options['fields_links_vocabularies_ids'], array(
      'none',
      'name',
      'vid',
    ))) {
    $messages['fields_links_vocabularies_ids'] = t('Vocabularies identifiants should be "none", "name" or "vid".');
  }

  // When multiple vocabularies are exported, names or tids are always needed.
  if ($options['fields_links_vocabularies_ids'] == 'none') {
    if ($options['vocabulary_id'] == 0) {
      $options['fields_links_vocabularies_ids'] = 'name';
    }
    else {
      // Check if all related terms are related to main vocabulary.
      // @todo Currently, check is made for each term in line_export.
    }
  }

  // Calculates number of terms to be exported.
  $sql = "
    SELECT COUNT(*)
    FROM {term_data}
  ";
  $args = array();
  if ($options['vocabulary_id']) {
    $sql .= ' WHERE vid = %d';
    $args[] = $options['vocabulary_id'];
  }
  $options['total_terms'] = array_shift(db_fetch_array(db_query($sql, $args)));
  if (!$options['total_terms']) {
    $message['vocabulary_id'] = t('No term to export. Export finished.');
  }

  return $messages;
}

/**
 * Batch process of vocabulary export.
 *
 * @param $options
 *   Array of batch options.
 * @param &$context
 *   Batch context to keep results and messages.
 * @return
 *   NULL because use of &$context.
 */
function _taxonomy_csv_vocabulary_export_process($options, &$context) {
  // First callback.
  if (empty($context['sandbox'])) {
    // Remember options as batch_set can't use form_storage.
    // It allows too that first line in result is numbered 1 and not 0.
    $context['results'][0] = $options;

    // Initialize some variables.
    $context['results'][0]['current_term'] = 0;
    $context['results'][0]['current_name'] = '';
    $context['results'][0]['worst_term'] = 0;
    $context['results'][0]['worst_name'] = '';
    $context['results'][0]['worst_message'] = 999;
    // No pointer because new line is appended to file.
    $context['results'][0]['handle'] = fopen($options['file']->filepath, 'a+');
    $context['sandbox']['max'] = $options['total_terms'];

    // Prepare terms to be exported.
    $sql = "
      SELECT *
      FROM {term_data}
    ";
    $args = array();
    if ($options['vocabulary_id']) {
      $sql .= ' WHERE vid = %d';
      $args[] = $options['vocabulary_id'];
    }
    // Use descendant order, because array_pop is used (quicker than shift).
    $sql .= ' ORDER BY %s DESC';
    $args[] = $options['order'];
    $result = db_query($sql, $args);
    while ($term = db_fetch_array($result)) {
      $context['sandbox']['terms'][] = $term;
    }

    // Prepare list of duplicate terms for fields_links export.
    $context['results'][0]['duplicate_terms'] = array();
    $sql = '
      SELECT t1.tid, t1.name
      FROM {term_data} t1
      LEFT OUTER JOIN {term_data} t2 ON t1.tid != t2.tid AND LOWER(t1.name) = LOWER(t2.name)
      WHERE t2.tid IS NOT NULL
    ';
    $args = array();
    if ($options['vocabulary_id']) {
      $sql .= ' AND t1.vid = %d';
      $args[] = $options['vocabulary_id'];
    }
    $sql .= '
      ORDER BY {t1.tid} ASC
    ';
    $result = db_query($sql, $args);
    while ($term = db_fetch_object($result)) {
      $context['results'][0]['duplicate_terms'][$term->tid] = $term->name;
    }
  }
  elseif (!is_resource($context['results'][0]['handle'])) {
    // Reopen file in case of memory out.
    $context['results'][0]['handle'] = fopen($options['file']->filepath, 'a+');
  }

  // Load and process one term.
  $worst_term      = &$context['results'][0]['worst_term'];
  $worst_name      = &$context['results'][0]['worst_name'];
  $worst_message   = &$context['results'][0]['worst_message'];
  $handle          = &$context['results'][0]['handle'];
  $duplicate_terms = &$context['results'][0]['duplicate_terms'];
  $term_number     = &$context['results'][0]['current_term'];
  $current_name    = &$context['results'][0]['current_name'];
  $term = array_pop($context['sandbox']['terms']);
  if ($term) {
    $term_number++;

    // Remember current name in case of error.
    $current_name = $term['name'];

    // Process export of current term.
    $result = taxonomy_csv_line_export($term, $options, $duplicate_terms);

    // Check if separator, enclosure or line ending exist in line.
    $check_line = implode('', $result['line']);
    if ((strpos($check_line, $options['separator']) !== FALSE)
        || (($options['enclosure'] != '')
          && (strpos($check_line, $options['enclosure']) !== FALSE))
        || (($options['enclosure'] == '')
          && (strpos($check_line, $options['end_of_line']) !== FALSE))) {
      $result['msg'][] = array(313); // Error delimiter or enclosure.
    }

    // Save line to file.
    $line = $options['enclosure'] . implode($options['separator'], $result['line']) . $options['enclosure'] . $options['end_of_line'];
    if (fwrite($handle, $line) === FALSE) {
      $result['msg'][] = array(312); // Unable to write to file.
    }

    // Remember worst message of exported terms.
    $worst_message_new = _taxonomy_csv_message_get_worst_message($result['msg']);
    if ($worst_message_new < $worst_message) {
      $worst_term    = $term_number;
      $worst_name    = $current_name;
      $worst_message = $worst_message_new;
    };

    // Inform about progress.
    $context['message'] = t('Term !term_number of !total_terms processed: %term', array(
      '!term_number' => $term_number,
      '!total_terms' => $options['total_terms'],
      '%term'        => $current_name,
    ));

    // Check worst message of exported lines and update progress.
    if (_taxonomy_csv_message_get_level($worst_message) > TAXONOMY_CSV_WATCHDOG_ERROR) {
      $context['finished'] = $term_number / $context['sandbox']['max'];
    }
    else {
      $context['finished'] = 1;
    }
  }
}

/**
 * Callback for finished batch export and display result informations.
 */
function _taxonomy_csv_vocabulary_export_finished($success, $results, $operations) {
  $options = &$results[0];
  unset($results[0]);

  // Close exported file.
  if ($options['handle']) {
    fclose($options['handle']);
  }

  // General infos.
  $message = t('!term_count / !total_terms terms of chosen vocabularies have been exported to file !file (!filesize KB). Click on link to view it or right click to download it.', array(
    '!term_count'  => $options['current_term'],
    '!total_terms' => $options['total_terms'],
    '!file'        => l($options['file']->filename, file_create_url($options['file']->filepath)),
    '!filesize'    => number_format(filesize($options['file']->filepath) / 1000, 1),
  )) .'<br />';
  // Main check of end process.
  $status = (($options['current_term'] == $options['total_terms']) && ($options['current_term'] > 0)) ? 'status' : 'error';
  drupal_set_message($message, $status);

  // Infos on duplicate term names.
  $duplicate_count = count($options['duplicate_terms']);
  // If there are duplicate term names, display them.
  if ($duplicate_count) {
    $message = t('!count duplicate term names have been found. Error can occur when you will import this list, except if you choose "fields and links" export format or import option "ignore existing items".', array('!count' => $duplicate_count)) .'<br />'.
    t('List of duplicate term names:') .'<br />"'.
    implode('", "', array_keys(array_flip($options['duplicate_terms']))) .'"';
    $status = 'warning';
  }
  else {
    // No duplicate term names.
    $message = t('No duplicate term name has been found.');
    $status = 'status';
  }
  drupal_set_message($message, $status);

  // Prepare batch result message.
  if (!$success) {
    $message = t('Exportation failed');
    $message .= '<br />'. t('This issue is related to export process and may be caused by a memory overrun of the database.');
    if ($options['current_term'] == $options['total_terms']) {
      $message .= '<br />'. t('All terms were exported, but a unknown error appears after the end of process.');
    }
    else {
      $message .= '<br />'. t('Export process was successful until the term !term_count (%term_name) of a total of !total_terms.', array(
        '!term_count'  => $options['current_term'],
        '%term_name'   => $options['current_name'],
        '!total_terms' => $options['total_terms'],
      ));
    }
    $message .= '<br />'. t('You can reinstall module from a fresh release or submit an issue on <a href="!link">Taxonomy CSV import/export module</a>.', array(
      '!link' => url('http://drupal.org/project/issues/taxonomy_csv/'),
    ));

    drupal_set_message($message, 'error');
  }
  else {
    // Short summary information.
    switch (_taxonomy_csv_message_get_level($options['worst_message'])) {
      case TAXONOMY_CSV_WATCHDOG_ERROR:
        drupal_set_message(t('Errors have been reported during export process. Process failed at term !worst_count (%worst_name) with error: !message', array(
          '!worst_count' => $options['worst_term'],
          '%worst_name'  => $options['worst_name'],
          '!message'     => _taxonomy_csv_info_result_text($options['worst_message']),
        )), 'error');
        break;
      case TAXONOMY_CSV_WATCHDOG_WARNING:
        drupal_set_message(t('Warnings have been reported during export process (bad formatted terms). First term skipped is term !worst_count (%worst_name) with message: !message', array(
          '!worst_count' => $options['worst_term'],
          '%worst_name'  => $options['worst_name'],
          '!message'     => _taxonomy_csv_info_result_text($options['worst_message']),
        )), 'error');
        break;
      case TAXONOMY_CSV_WATCHDOG_NOTICE:
        drupal_set_message(t('Notices have been reported during export process (bad formatted or empty terms). Terms processed. First notice on term !worst_count (%worst_name) with message: !message', array(
          '!worst_count' => $options['worst_term'],
          '%worst_name'  => $options['worst_name'],
          '!message'     => _taxonomy_csv_info_result_text($options['worst_message']),
        )), 'warning');
        break;
      case TAXONOMY_CSV_WATCHDOG_INFO:
      default:
        drupal_set_message(t('No error, warnings or notices have been reported during export process.'), 'status');
        break;
    }
  }
}

/**
 * Creates vocabulary by its name and returns an array with vid and name.
 */
function taxonomy_csv_vocabulary_create($vocabulary_name = '') {
  // Create an empty vocabulary. Relations and hierarchy are updated later.
  $vocabulary = array(
    'name'         => _taxonomy_csv_vocabulary_create_name($vocabulary_name),
    'description'  => t('Auto created vocabulary by taxonomy_csv module'),
    'help'         => '',
    'relations'    => TRUE,
    'hierarchy'    => 2,
    'multiple'     => TRUE,
    'required'     => FALSE,
    'tags'         => FALSE,
    'module'       => 'taxonomy',
    'weight'       => 0,
    'nodes'        => array(),
  );

  taxonomy_save_vocabulary($vocabulary);

  return array(
    'vid' => taxonomy_csv_vocabulary_get_id($vocabulary['name']),
    'name' => $vocabulary['name'],
  );
}

/**
 * Duplicates a vocabulary by its vid and returns an array with vid and name.
 * If not exist, creates an empty vocabulary.
 */
function taxonomy_csv_vocabulary_duplicate($vocabulary_id) {
  $original_vocabulary = taxonomy_vocabulary_load($vocabulary_id);
  if ($original_vocabulary) {
    // Creates an unused name.
    // Check if name begins with 'Copy of #name' in order to serialize name.
    $name = t('Copy of [!vocabulary_name]', array('!vocabulary_name' => $original_vocabulary->name));
    $name = _taxonomy_csv_vocabulary_create_name((strpos($original_vocabulary->name, $name) === FALSE) ? $name : $original_vocabulary->name);

    // Duplicate original vocabulary. Relations and hierarchy are updated later.
    $duplicated_vocabulary = array(
      'name'         => $name,
      'description'  => $original_vocabulary->description,
      'help'         => $original_vocabulary->help,
      'relations'    => $original_vocabulary->relations,
      'hierarchy'    => $original_vocabulary->hierarchy,
      'multiple'     => $original_vocabulary->multiple,
      'required'     => $original_vocabulary->required,
      'tags'         => $original_vocabulary->tags,
      'module'       => $original_vocabulary->module,
      'weight'       => $original_vocabulary->weight,
      'nodes'        => array(),
    );

    taxonomy_save_vocabulary($duplicated_vocabulary);

    $duplicated_vocabulary['vid'] = taxonomy_csv_vocabulary_get_id($duplicated_vocabulary['name']);

    // Get all terms and attributes of original vocabulary
    // and copy them in the new one in two steps.
    $original_terms = taxonomy_get_tree($original_vocabulary->vid);

    // First step: copy each term except relations and parents.
    $duplicated_terms = array();
    foreach ($original_terms as $original_term) {
      $duplicated_terms[$original_term->tid] = array(
        'vid'         => $duplicated_vocabulary['vid'],
        'name'        => $original_term->name,
        'description' => $original_term->description,
        'weight'      => $original_term->weight,
        'synonyms'    => taxonomy_get_synonyms($original_term->tid),
      );
      taxonomy_csv_term_save($duplicated_terms[$original_term->tid]);

      // Complete term with its tid for next step.
      $duplicated_terms[$original_term->tid]['tid'] = db_last_insert_id('term_data', 'tid');
    }

    // Second step: update duplicated terms with parents and relations.
    foreach ($original_terms as $original_term) {
      $duplicated_terms[$original_term->tid]['parent'] = array();
      foreach ($original_term->parents as $original_parent_term_id) {
        $duplicated_terms[$original_term->tid]['parent'][] = $duplicated_terms[$original_parent_term_id]['tid'];
      }

      $duplicated_terms[$original_term->tid]['relations'] = array();
      $original_related_terms = taxonomy_get_related($original_term->tid);
      foreach ($original_related_terms as $original_related_term) {
        $duplicated_terms[$original_term->tid]['relations'][] = $duplicated_terms[$original_related_term->tid]['tid'];
      }

      taxonomy_csv_term_save($duplicated_terms[$original_term->tid]);
    }

    return array(
      'vid'  => $duplicated_vocabulary['vid'],
      'name' => $duplicated_vocabulary['name'],
    );
  }
  else {
    return taxonomy_csv_vocabulary_create();
  }
}

/**
 * Helper to create an unused vocabulary name from a string.
 */
function _taxonomy_csv_vocabulary_create_name($vocabulary_name = '') {
  $name = eregi_replace('.csv', '', trim(basename(strval($vocabulary_name))));
  $vocabulary_check_name = (drupal_strlen($name) > 0) ? $name : t('Auto created vocabulary');

  // Limits to 250 characters.
  $vocabulary_check_name = drupal_substr($vocabulary_check_name, 0, 250);

  // Invent a unused vocabulary name.
  if (!taxonomy_csv_vocabulary_get_id($vocabulary_check_name)) {
    $new_vocabulary_name = $vocabulary_check_name;
  }
  else {
    for ($i = 2; taxonomy_csv_vocabulary_get_id("$vocabulary_check_name $i"); $i++) {
    }
    $new_vocabulary_name = "$vocabulary_check_name $i";
  }

  return $new_vocabulary_name;
}

/**
 * Static check and update hierarchy flag of a given vocabulary.
 * If hierarchy is set, simply update it without check.
 *
 * Drupal update hierarchy function works only dynamically.
 *
 * @param $vid
 *   The vocabulary id to update.
 * @param $hierarchy
 *   Optional. The hierarchy level to set (0, 1 or 2).
 * @return
 *   Updated hierarchy level or FALSE if not exist.
 */
function taxonomy_csv_vocabulary_check_hierarchy($vid, $hierarchy_level = FALSE) {
  $vocabulary = taxonomy_vocabulary_load($vid);

  if ($vocabulary) {
    if ($hierarchy_level !== FALSE) {
      // Set hierarchy_level without check vocabulary.
      $hierarchy = $hierarchy_level;
    }
    else {
      $tree = taxonomy_get_tree($vocabulary->vid);
      $hierarchy = 0;
      foreach ($tree as $term) {
        // Check current term's parent count.
        if (count($term->parents) > 1) {
          $hierarchy = 2;
          break;
        }
        // taxonomy.module l. 285 can't detect level 0 with '0 !== array_shift'.
        elseif (count($term->parents) == 1 && 0 != array_shift($term->parents)) {
          $hierarchy = 1;
        }
      }
    }
    // Update hierarchy if necessary.
    if ($hierarchy != $vocabulary->hierarchy) {
      $vocabulary->hierarchy = $hierarchy;
      $vocabulary = (array) $vocabulary;
      $result = taxonomy_save_vocabulary($vocabulary);
    }

    return $hierarchy;
  }
  return FALSE;
}

/**
 * Return vocabulary vid by its name or NULL if none.
 */
function taxonomy_csv_vocabulary_get_id($vocabulary_name) {
  if (is_string($vocabulary_name) && ($vocabularies = taxonomy_get_vocabularies())) {
    foreach ($vocabularies as $vocabulary) {
      if ($vocabulary_name == $vocabulary->name) {
        return $vocabulary->vid;
      }
    }
  }
}

/**
 * @} End of "defgroup taxonomy_csv_vocabulary".
 */

/**
 * @defgroup taxonomy_csv_line Import/export a line
 * @{
 * Functions allowing import of a line of terms or fields or export of a term to
 * a line.
 */

/**
 * Import a line that contains a term and other items matching the options.
 *
 * @param $line
 *   Array which contains items of a csv line.
 * @param $options
 *   Array of import options:
 *     import_format : see _taxonomy_csv_info_lists('list_import_format')
 *     vocabulary_id : vocabulary id to import into
 *     existing_items: see _taxonomy_csv_info_lists('list_import_option')
 *     line_checks   : boolean. Tweak to check (default) or not format of lines
 *     utf8_check    : boolean. Tweak to check (default) or not utf8 format
 *     // Specific to relations import:
 *     relations_create_subrelations: boolean.
 *     relations_all_vocabularies   : boolean.
 * @param $previous_items
 *   Optional. Cleaned and checked previous imported line names and tids array.
 *   Needed with some contents as one term array structure or Taxonomy manager.
 *   Specificities:
 *     taxonomy_manager:
 *       tid array is indexed with old tids.
 *     fields_links:
 *       'name' and 'tid' arrays contain sub-arrays 'vocabulary' and 'term' with
 *       imported identifiant as key and name or tid/vid as value in order to
 *       allow duplicate names import and use of number identifiants.
 * @return Result array:
 *   'name' => array of imported terms names,
 *   'tid'  => array of imported terms tids,
 *   'msg'  => messages arrays:
 *     term position => array of status messages of term,
 *     'line'        => array of status messages of line.
 */
function taxonomy_csv_line_import($line, $options, $previous_items = array()) {
  // Define default values.
  $line_messages = array();
  $items_messages = array();
  $result = array(
    'name' => array(),
    'tid'  => array(),
    'msg'  => array(),
  );

  if ($options['line_checks']) {
    // 1. Validate and clean line.
    $line = _taxonomy_csv_line_import_clean(
      $line,
      $options['utf8_check'],
      $line_messages);
    // Check if an error occurs and if line is not empty.
    if (!_taxonomy_csv_message_warning($line_messages)
        && ((count($line_messages) == 0) || ($line_messages[0] != 696))) {

      // 2. Check items of line.
      $line = _taxonomy_csv_line_import_check(
        $line,
        $options,
        $previous_items,
        $items_messages);
      $line_messages = array_merge($line_messages, $items_messages);
      if (!_taxonomy_csv_message_warning($items_messages)) {

        // 3. Process import items with full checked line.
        $result = _taxonomy_csv_line_import_process(
          $line,
          $options,
          $previous_items);
        // Add line level message of bad or successful import.
        $line_messages[] = (_taxonomy_csv_message_warning($result, 'line')) ? 499 : 699;
      }
    }
  }
  else {
    // No checks, so directly import line.
    $result = _taxonomy_csv_line_import_process(
      array_values(array_map('trim', $line)),
      $options,
      $previous_items);
    // Add line level message of bad or successful import.
    $line_messages[] = (_taxonomy_csv_message_warning($result, 'line')) ? 499 : 699;
  }

  // Keep previous items in case of an empty or an unprocessed line.
  if (count($result['name']) == 0) {
    $result['name'] = $previous_items['name'];
    $result['tid']  = $previous_items['tid'];
  }

  // Remember line level messages.
  $result['msg'] += array('line' => $line_messages);

  return $result;
}

/**
 * Helper function to clean an imported line.
 *
 * @param $line
 *   Array of items to be processed.
 * @param $utf8_check
 *   Optional. Enable (default) or not conversion to utf8.
 * @param &$messages
 *   Optional. By reference array of messages codes to be returned.
 * @return Array of cleaned imported line.
 */
function _taxonomy_csv_line_import_clean($line, $utf8_check = TRUE, &$messages = array()) {
  $cleaned_line = array();

  // Example: string "Term 1".
  if (!is_array($line)) {
    $messages[] = 310; // Error not a line array.
  }
  // Example: " " or unrecognized line.
  elseif ((count($line) == 0)
      || empty($line)
      || ((count($line) == 1) && (trim($line[0]) == ''))) {
    $messages[] = 696; // Info empty line.
  }
  else {
    $cleaned_line = $line;

    // @todo To simplify.
    // Convert each item of the line to UTF-8.
    // Convert can be bypassed. See http://drupal.org/node/364832.
    if ($utf8_check) {
      if (function_exists('mb_detect_encoding')) {
        foreach ($line as $key => $item) {
          $enc = mb_detect_encoding($item, 'UTF-8, ISO-8859-1, ISO-8859-15', TRUE);
          if ($enc != 'UTF-8') {
            if (FALSE === $cleaned_line[$key] = drupal_convert_to_utf8($item, $enc)) {
              $messages[] = 320; // Error convert.
            }
          }
        }
      }
      else {
        $messages[] = 320; // Error convert.
      }
    }
    // If convert is bypassed, check if text is already utf-8 encoded.
    else {
      foreach ($line as $item) {
        if (!drupal_validate_utf8($item)) {
          $messages[] = 321; // Error validate.
        }
      }
    }

    // Trim and check empty line: useful for some non-Ascii lines.
    $line = array_map('trim', $cleaned_line);

    // @todo To simplify.
    // Example: " , , ".
    $test_line = array_unique($line);
    if (count($test_line) == 1 && in_array('', $test_line)) {
      $messages[] = 491; // Warning no item.
    }
    else {
      $cleaned_line = array_values($line);
    }
  }

  return $cleaned_line;
}

/**
 * Helper function to validate an imported line.
 *
 * @param $line
 *   Array of items from a cleaned line.
 * @param $options
 *   Array of available options. See taxonomy_csv_line_import.
 * @param $previous_items
 *   Optional. Cleaned and checked previous imported line names and tids array.
 *   Needed with some contents as one term array structure or Taxonomy manager.
 *   Specificities:
 *     taxonomy_manager:
 *       tid array is indexed with old tids.
 *     fields_links:
 *       'name' and 'tid' arrays contain sub-arrays 'vocabulary' and 'term' with
 *       imported identifiant as key and name or tid/vid as value in order to
 *       allow duplicate names import and use of number identifiants.
 * @param &$messages
 *   Optional. By reference array of messages codes to be returned.
 * @return Array of checked items of imported line.
 */
function _taxonomy_csv_line_import_check($line, $options, $previous_items = array(), &$messages = array()) {
  $checked_items = array();

  // Simplify used options.
  $existing_items = &$options['existing_items'];

  // No input check because line and previous line are already checked.
  // @todo A php callback function may be used to simplify checking.
  switch ($options['import_format']) {
    case TAXONOMY_CSV_FORMAT_ALONE_TERMS:
      // Checks empty first column.
      // Example: ", Item 1, Item 2"
      if (empty($line[0])) {
        $messages[] = 480; // Warning no first column.
        break;
      }
      if (count($line) > 1) {
        $messages[] = 501; // Notice too many items.
      }
      $checked_items = array($line[0]);
      break;

    case TAXONOMY_CSV_FORMAT_FIELDS_LINKS:
      if (empty($line[0])) {
        $messages[] = 464; // Warning no name.
        break;
      }
      // Complete $line for easier check.
      $line = array_pad($line, 9, '');
      // Example: "Term, 1, voc, Description, 0, No,..."
      foreach (array(4, 5, 6, 7, 8) as $key) {
        if (!empty($line[$key]) && !is_numeric($line[$key])) {
          $messages[] = 451; // Warning not a number.
          break 2;
        }
      }
      // Check count of items.
      $links_count = $line[5] + $line[6] + $line[7] + $line[8];
      if (count($line) < (9 + $links_count)) {
        $messages[] = 430; // Warning some empty items.
        break;
      }
      // Check vocabularies of related terms. If empty, use of main term vid.
      if (count($line) < (9 + $links_count + $line[8])) {
        $messages[] = 639; // Info some empty vocabulary related items.
        $line = array_pad($line, 9 + $links_count + $line[8], '');
      }
      elseif (count($line) > (9 + $links_count + $line[8])) {
        $messages[] = 434; // Warning too many items.
        break;
      }
      // Example: "Term, 1, voc, Description, 0, 1, 2, 3, 4, item, , item 2..."
      $imported_items = array_map('strval', array_slice($line, 9, $links_count));
      foreach ($imported_items as $key => $value) {
        if (empty($value)) {
          $messages[] = 430; // Warning some empty items.
          break 2;
        }
      }
      // Check and remove duplicate synonyms.
      $synonyms = array_slice($line, 9, $line[5]);
      $unique_synonyms = array_unique($synonyms);
      if (count($unique_synonyms) < (count($synonyms))) {
        $messages[] = 535; // Notice duplicate items (removed).
        $line[5] = count($unique_synonyms);
        $line = array_merge(array_slice($line, 0, 9), $unique_synonyms, array_slice($line, 9 + count($synonyms)));
      }
      // Check and remove duplicate parents.
      $parents = array_slice($line, 9 + $line[5], $line[6]);
      $unique_parents = array_unique($parents);
      if (count($unique_parents) < (count($parents))) {
        $messages[] = 536; // Notice duplicate items (removed).
        $line[6] = count($unique_parents);
        $line = array_merge(array_slice($line, 0, 9 + $line[5]), $unique_parents, array_slice($line, 9 + $line[5] + count($parents)));
      }
      // Check and remove duplicate children.
      $children = array_slice($line, 9 + $line[5] + $line[6], $line[7]);
      $unique_children = array_unique($children);
      if (count($unique_children) < (count($children))) {
        $messages[] = 537; // Notice duplicate children (removed).
        $line[7] = count($unique_children);
        $line = array_merge(array_slice($line, 0, 9 + $line[5] + $line[6]), $unique_children, array_slice($line, 9 + $line[5] + $line[6] + count($children)));
      }
      // Check and remove duplicate related.
      $related = array_slice($line, 9 + $line[5] + $line[6] + $line[7], $line[8]);
      $unique_related = array_unique($related);
      if (count($unique_related) < (count($related))) {
        $messages[] = 538; // Notice duplicate related (removed).
        $line[8] = count($unique_related);
        $line = array_merge(array_slice($line, 0, 9 + $line[5]) + $line[6] + $line[7], $unique_related, array_slice($line, 9 + $line[5] + $line[6] + $line[7] + count($related)));
      }
      // Example: "Term, 1, voc, Description, 0, 1, 2, 3, 4, item 1, item 1..."
      $imported_items = array_slice($line, 9, $line[5] + $line[6] + $line[7] + $line[8]);
      $imported_unique_items = array_unique($imported_items);
      if (count($imported_unique_items) < (count($imported_items))) {
        $messages[] = 532; // Notice duplicate items (allowed).
      }
      // Example: "Name, 1, voc, Description, 0, 1, 2, 3, 4, Name, item 1..."
      if (in_array($line[0], $imported_unique_items)) {
        $messages[] = 433; // Warning name and some items are same.
        break;
      }
      $checked_items = $line;
      break;

    case TAXONOMY_CSV_FORMAT_FLAT:
      if (count($checked_items) == 0) {
        $messages[] = 491; // Warning no item.
        break;
      }
      $checked_items = array_unique(array_filter($line));
      if (count($checked_items) < count($line)) {
        $messages[] = 531; // Notice duplicates, which are removed.
      }
      break;

    case TAXONOMY_CSV_FORMAT_TREE_STRUCTURE:
    case TAXONOMY_CSV_FORMAT_POLYHIERARCHY:
      // Check last empty column before first item with previous imported items.
      for ($first_non_empty = 0; ($first_non_empty < count($line)) && (empty($line[$first_non_empty])); $first_non_empty++) {
      }
      // Example: Previous line("Term 1,Item 2") ; Current line(",,,Item4")
      if ($first_non_empty && (!isset($previous_items['name'][$first_non_empty - 1]))) {
        $messages[] = 410; // Warning impossible to get parent.
        break;
      }
      // Example: Previous line("Term 1,Item 2") ; Current line(",,,Item4")
      // "0" value are lost, but that is not important for a taxonomy.
      $imported_items = array_filter(array_slice($line, $first_non_empty));
      if (count($imported_items) == 0) {
        $messages[] = 491; // Warning no item.
        break;
      }
      if (count($imported_items) < (count($line) - $first_non_empty)) {
        $messages[] = 510; // Notice empty items.
      }
      if (count(array_unique($imported_items)) < count($imported_items)) {
        $messages[] = 632; // Info duplicates (not removed).
      }
      if ($first_non_empty == 0) {
        $checked_items = $imported_items;
      }
      else {
        $checked_items = array_merge(array_fill(0, $first_non_empty, ''), $imported_items);
      }
      break;

    case TAXONOMY_CSV_FORMAT_PARENTS:
    case TAXONOMY_CSV_FORMAT_CHILDREN:
    case TAXONOMY_CSV_FORMAT_RELATIONS:
    case TAXONOMY_CSV_FORMAT_SYNONYMS:
      if (empty($line[0])) {
        $messages[] = 480; // Warning no first column.
        break;
      }
      // Example: "Term,Item 1,,Item 2"
      $imported_items = array_map('strval', array_slice($line, 1));
      foreach ($imported_items as $key => $value) {
        if ($value == '') {
          unset($imported_items[$key]);
          $messages[] = 530; // Notice some empty items.
        }
      }
      // Example: "Term,Item 1,Item 2,Item 1"
      $imported_unique_items = array_unique($imported_items);
      if (count($imported_unique_items) < (count($imported_items))) {
        $messages[] = 531; // Notice duplicates, which are removed.
      }
      // Example: "Term,Item 1,Term,Item 2"
      $checked_items = array_unique(array_merge(array($line[0]), $imported_unique_items));
      if (count($checked_items) <= count($imported_unique_items)) {
        $messages[] = 533; // Notice name and some items are same, so removed.
      }
      // Example: "Term"
      if ((count($checked_items) == 1)
          && ($existing_items == TAXONOMY_CSV_EXISTING_UPDATE_REPLACE)) {
        $messages[] = 580; // Notice remove items.
      }
      break;

    case TAXONOMY_CSV_FORMAT_FIELDS:
      if (empty($line[0])) {
        $messages[] = 480; // Warning no first column.
      }
      elseif (count($line) == 1) {
        $messages[] = 510; // Notice empty items.
        if ($existing_items == TAXONOMY_CSV_EXISTING_UPDATE_REPLACE) {
          $messages[] = 580; // Notice remove items.
        }
        $checked_items = array($line[0], 0);
      }
      elseif (!is_numeric($line[1]) && !is_int($line[1]) && $line[1]) {
        $messages[] = 450; // Warning weight is not a number.
      }
      elseif (count($line) <= 3) {
        $checked_items = $line;
      }
      else {
        // Example: "Term,Item 1,,Item 2"
        // "0" value is lost, but this is not important for a taxonomy.
        $imported_items = array_filter(array_slice($line, 3));
        if (count($imported_items) < (count($line) - 3)) {
          $messages[] = 530; // Notice some empty items.
        }
        // Example: "Term,Item 1,Item 2,Item 1"
        $imported_unique_items = array_unique($imported_items);
        if (count($imported_unique_items) < (count($imported_items))) {
          $messages[] = 531; // Notice duplicates, which are removed.
        }
        // Example: "Term,Item 1,Term,Item 2"
        $temp_checked_items = array_unique(array_merge(array($line[0]), $imported_unique_items));
        if (count($temp_checked_items) <= count($imported_unique_items)) {
          $messages[] = 533; // Notice name and some items are same, so removed.
        }
        $checked_items = array_merge(array_slice($line, 0, 3), array_slice($temp_checked_items, 1));
      }
      break;

    case TAXONOMY_CSV_FORMAT_DESCRIPTIONS:
      if (empty($line[0])) {
        $messages[] = 480; // Warning no first column.
        break;
      }
      if ((count($line) == 1)
          && ($existing_items == TAXONOMY_CSV_EXISTING_UPDATE_REPLACE)) {
        $messages[] = 580; // Notice remove items.
        $checked_items = array($line[0], '');
      }
      else {
        if (count($line) > 2) {
          $messages[] = 541; // Notice too many items.
        }
        $checked_items = array($line[0], $line[1]);
      }
      break;

    case TAXONOMY_CSV_FORMAT_WEIGHTS:
      if (empty($line[0])) {
        $messages[] = 480; // Warning no first column.
        break;
      }
      if ((count($line) > 1) && !is_numeric($line[1]) && !is_int($line[1]) && $line[1]) {
        $messages[] = 450; // Warning weight is not a number.
        break;
      }
      if ((count($line) == 1) && ($existing_items == TAXONOMY_CSV_EXISTING_UPDATE_REPLACE)) {
        $messages[] = 580; // Notice remove items.
        $checked_items = array($line[0], 0);
      }
      else {
        if (count($line) > 2) {
          $messages[] = 541; // Notice too many items.
        }
        $checked_items = array($line[0], intval($line[1]));
      }
      break;

    case TAXONOMY_CSV_FORMAT_TAXONOMY_MANAGER:
      $checked_items = $line;
      if (empty($line[0])) {
        $messages[] = 550; // Notice no first column.
      }
      if (count($line) < 4) {
        $messages[] = 450; // Warning some items lacks.
        break;
      }
      if (empty($line[1]) || empty($line[2])
          || ($line[1] == 0) || ($line[2] == '')) {
        $messages[] = 481; // Warning no item in second or third column.
        break;
      }
      if (count($line) == 4) {
        $messages[] = 551; // Notice root term.
        $checked_items[] = 0;
      }
      foreach ($checked_items as $key => $value) {
        if (($key != 2) && ($key != 3) && !is_numeric($value)) {
          $messages[] = 451; // Warning not a number.
          break 2;
        }
      }
      $list_parents = array_unique(array_slice($checked_items, 4));
      sort($list_parents);
      if (count($list_parents) != count(array_slice($checked_items, 4))) {
        $messages[] = 531; // Notice duplicates, which are removed.
      }
      foreach ($list_parents as $value) {
        if ($value == $checked_items[1]) {
          $messages[] = 452; // Warning a term can't be a parent of itself.
          break 2;
        }
      }
      $checked_items = array_merge(array_slice($checked_items, 0, 4), $list_parents);
      if (($list_parents[0] === 0) && (count($list_parents) > 1)) {
        $messages[] = 453; // Warning: root term has a parent.
        break;
      }
      // $previous_items keys contain all previous lines source tid.
      if (isset($previous_items['tid'][$checked_items[1]])) {
        $messages[] = 552; // Notice: term has been already imported.
      }
      foreach ($list_parents as $value) {
        if (($value != 0) && !isset($previous_items['tid'][$value])) {
          $messages[] = 352; // Error: parent tid hasn't been already imported.
          break;
        }
      }
      break;

    default:
      $messages[] = 306; // Error unknown source content.
  }

  return array_values($checked_items);
}

/**
 * Helper function to process import items.
 *
 * @param $line
 *   Array which contains items of a cleaned and checked csv line.
 * @param $options
 *   Array of import options:
 *     import_format  : see _taxonomy_csv_info_lists('list_import_format')
 *     vocabulary_id  : vocabulary id to import into
 *     existing_items : see _taxonomy_csv_info_lists('list_import_option')
 *     // Specific to relations import:
 *     relations_create_subrelations: boolean.
 *     relations_all_vocabularies   : boolean.
 * @param $previous_items
 *   Optional. Cleaned and checked previous imported line names and tids array.
 *   Needed with some contents as one term array structure or Taxonomy manager.
 *   Specificities:
 *     taxonomy_manager:
 *       tid array is indexed with old tids.
 *     fields_links:
 *       'name' and 'tid' arrays contain sub-arrays 'vocabulary' and 'term' with
 *       imported identifiant as key and name or tid/vid as value in order to
 *       allow duplicate names import and use of number identifiants.
 * @return Result array:
 *   'name' => array of imported terms names,
 *   'tid'  => array of imported terms tids,
 *   'msg'  => messages arrays:
 *     term position => array of status messages of term.
 */
function _taxonomy_csv_line_import_process($line, $options, $previous_items = array()) {
  // Define default values.
  $result = array(
    'name' => array(),
    'tid'  => array(),
    'msg'  => array(),
  );

  // Only count check because function variables are already checked.
  if (count($line)) {
    switch ($options['import_format']) {
      case TAXONOMY_CSV_FORMAT_ALONE_TERMS:
      case TAXONOMY_CSV_FORMAT_FIELDS:
      case TAXONOMY_CSV_FORMAT_DESCRIPTIONS:
      case TAXONOMY_CSV_FORMAT_WEIGHTS:
      case TAXONOMY_CSV_FORMAT_SYNONYMS:
        $term = array(
          'name' => $line[0],
          'vid'  => $options['vocabulary_id'],
        );
        switch ($options['import_format']) {
          case TAXONOMY_CSV_FORMAT_FIELDS:
            $term['weight']      = $line[1];
            $term['description'] = $line[2];
            $term['synonyms']    = array_slice($line, 3);
            break;

          case TAXONOMY_CSV_FORMAT_DESCRIPTIONS:
            $term['description'] = $line[1];
            break;

          case TAXONOMY_CSV_FORMAT_WEIGHTS:
            $term['weight'] = $line[1];
            break;

          case TAXONOMY_CSV_FORMAT_SYNONYMS:
            $term['synonyms'] = array_slice($line, 1);
            break;
        }
        // Import term then store result. No check because only one term.
        $current_result = taxonomy_csv_term_import($term, $options['existing_items']);
        $result['name'][] = $current_result['name'];
        $result['tid'][]  = $current_result['tid'];
        $result['msg'][]  = $current_result['msg'];
        break;

      case TAXONOMY_CSV_FORMAT_FIELDS_LINKS:
        // 1. Keep previous imported vocabularies and terms.
        $result['name'] = $previous_items['name'];
        $result['tid']  = $previous_items['tid'];

        // 2. Define main term to be imported.
        $term = array(
          'name'        => $line[0],
          'description' => $line[3],
          'weight'      => $line[4],
          'synonyms'    => array_slice($line, 9, $line[5]),
          'parent'      => array(),
          'relations'   => array(),
        );

        // 3. Prepare links. Zero character ids have been already removed.
        $parents_names  = array_slice($line, 9 + $line[5], $line[6]);
        $children_names = array_slice($line, 9 + $line[5] + $line[6], $line[7]);
        $related_names  = array_slice($line, 9 + $line[5] + $line[6] + $line[7], $line[8]);
        $related_vocs   = array_slice($line, 9 + $line[5] + $line[6] + $line[7] + $line[8], $line[8]);

        // 4. Check if main and related vocabularies are already in memory.
        $vocabularies = array_unique(array_merge(array($line[2]), $related_vocs));
        foreach ($vocabularies as $id) {
          // Empty vocabulary identifiant is saved too.
          // Vocabulary is unknown.
          if (!isset($result['name']['vocabulary'][$id])) {
            $vid = taxonomy_csv_vocabulary_get_id($id);
            // Vocabulary exists.
            if ($vid) {
              $vocabulary['name'] = $id;
              $vocabulary['vid']  = $vid;
            }
            // Vocabulary doesn't exist.
            else {
              $vocabulary = taxonomy_csv_vocabulary_create($id);
              $result['msg'][] = array(610); // Info new vocabulary.
            }
            // Remember imported vocabulary.
            $result['name']['vocabulary'][$id] = $vocabulary['name'];
            $result['tid']['vocabulary'][$id]  = $vocabulary['vid'];
          }
        }
        // Update main term with vocabulary id.
        $term['vid'] = $vid = $result['tid']['vocabulary'][$line[2]];

        // 5. Import each parent and check result.
        $tids = array();
        foreach ($parents_names as $key => $id) {
          // Check if term is already imported.
          if (!isset($result['name']['term'][$id])) {
            $current_result = taxonomy_csv_term_import(
              array(
                'name' => $id,
                'vid'  => $vid,
              ),
              $options['existing_items']);
            $result['name']['term'][$id] = $current_result['name'];
            $result['tid']['term'][$id]  = $current_result['tid'];
            $result['msg'][]             = $current_result['msg'];
            if (_taxonomy_csv_message_warning($current_result['msg'])) {
              break 2;
            }
          }
          $tids[] = $result['tid']['term'][$id];
        }
        // Update main term with parents ids.
        $term['parent'] = $tids;

        // 6. Import each related term and check result.
        $tids = array();
        foreach ($related_names as $key => $id) {
          // Check if term is already imported or not.
          if (isset($result['name']['term'][$id])) {
            // Check vocabulary: need update if it changes (by line approach).
            $temp_term       = taxonomy_csv_term_get($result['tid']['term'][$id]);
            $temp_vocabulary = ($related_vocs[$key] == '') ?
                // There is no vocabulary identifiant, so use main term vid.
                $vid :
                // There is a vocabulary identifiant.
                $result['tid']['vocabulary'][$related_vocs[$key]];
            // Vocabulary change is unadvised if term has links, but possible.
            if ($temp_term['vid'] != $temp_vocabulary) {
              $current_result = taxonomy_csv_term_import(
                array(
                  'name' => $result['name']['term'][$id],
                  'vid'  => $temp_vocabulary,
                ),
                $options['existing_items']);
              $result['name']['term'][$id] = $current_result['name'];
              $result['tid']['term'][$id]  = $current_result['tid'];
              $result['msg'][]             = $current_result['msg'];
              if (_taxonomy_csv_message_warning($current_result['msg'])) {
                break 2;
              }
              $result['msg'][] = array(511); // Notice: Update not recommended.
            }
          }
          else {
            $current_result = taxonomy_csv_term_import(
              array(
                'name' => $id,
                'vid'  => ($related_vocs[$key] == '') ?
                    // There is no vocabulary identifiant, so use main term vid.
                    $vid :
                    // There is a vocabulary identifiant.
                    $result['tid']['vocabulary'][$related_vocs[$key]],
              ),
              $options['existing_items']);
            $result['name']['term'][$id] = $current_result['name'];
            $result['tid']['term'][$id]  = $current_result['tid'];
            $result['msg'][]             = $current_result['msg'];
            if (_taxonomy_csv_message_warning($current_result['msg'])) {
              break 2;
            }
          }
          $tids[] = $result['tid']['term'][$id];
        }
        // Update main term with related ids.
        $term['relations'] = $tids;

        // 7. Import main term and check result.
        // If there is an identifiant, pre-import term.
        if ($line[1] != '') {
          // If term is already imported, simply update main term with tid.
          if (isset($result['name']['term'][$line[1]])) {
            $term['tid'] = $result['tid']['term'][$line[1]];
          }
          // Pre-import is needed only when name and identifiant are different.
          elseif (drupal_strtolower($line[0]) != drupal_strtolower($line[1])) {
            $current_result = taxonomy_csv_term_import(
              array(
                'name' => $term['name'],
                'vid'  => $term['vid'],
              ),
              TAXONOMY_CSV_EXISTING_IGNORE_CREATE);
            $result['name']['term'][$id] = $current_result['name'];
            $result['tid']['term'][$id]  = $current_result['tid'];
            $result['msg'][]             = $current_result['msg'];
            if (_taxonomy_csv_message_warning($current_result['msg'])) {
              break;
            }
            $term['tid'] = $current_result['tid'];
          }
        }
        // Import main term.
        $current_result = taxonomy_csv_term_import($term, $options['existing_items']);
        // Remember only if an identifiant is set.
        if ($line[1] != '') {
          $result['name']['term'][$line[1]] = $current_result['name'];
          $result['tid']['term'][$line[1]]  = $current_result['tid'];
        }
        $result['msg'][] = $current_result['msg'];
        if (_taxonomy_csv_message_warning($current_result['msg'])) {
          break;
        }

        // 8. Import each child with main term as parent and check result.
        $parent_tid = $current_result['tid'];
        $tids = array();
        foreach ($children_names as $key => $id) {
          // No check because parent is added even if term is already imported.
          $temp_term = array(
            'name' => $id,
            'vid'  => $vid,
            'parent' => array($parent_tid),
          );
          // Nevertheless, tid is needed if known in order to make an update.
          if (isset($result['name']['term'][$id])) {
            $temp_term['tid'] = $result['tid']['term'][$id];
          }
          // Import term then store and check result.
          // Don't check tid == parent_tid because duplicates have been removed.
          $current_result = taxonomy_csv_term_import(
            $temp_term,
            $options['existing_items']);
          $result['name']['term'][$id] = $current_result['name'];
          $result['tid']['term'][$id]  = $current_result['tid'];
          $result['msg'][]             = $current_result['msg'];
          if (_taxonomy_csv_message_warning($current_result['msg'])) {
            break 2;
          }
        }
        break;

      case TAXONOMY_CSV_FORMAT_FLAT:
        foreach ($line as $term_name) {
          $term = array(
            'name' => $term_name,
            'vid'  => $options['vocabulary_id'],
          );
          // Import term then store and check result.
          $current_result = taxonomy_csv_term_import($term, $options['existing_items']);
          $result['name'][] = $current_result['name'];
          $result['tid'][]  = $current_result['tid'];
          $result['msg'][]  = $current_result['msg'];
          if (_taxonomy_csv_message_warning($current_result['msg'])) {
            break;
          }
        }
        break;

      case TAXONOMY_CSV_FORMAT_TREE_STRUCTURE:
        // Same process, except when term is imported.
      case TAXONOMY_CSV_FORMAT_POLYHIERARCHY:
        // First, complete line with previous line.
        // Find first non empty item as line can be full, partial or one term.
        for ($first_non_empty = 0; ($first_non_empty < count($line)) && (empty($line[$first_non_empty])); $first_non_empty++) {
        }

        // Remove surabondant previous items and remember them for next line.
        if ($first_non_empty) {
          $result['name'] = $previous_items['name'] = array_slice($previous_items['name'], 0, $first_non_empty);
          $result['tid']  = $previous_items['tid']  = array_slice($previous_items['tid'], 0, $first_non_empty);
          foreach ($previous_items['tid'] as $key => $term) {
            $result['msg'][]  = array(683); // Previous line term.
          }
        }

        // Second, process import of new items.
        // Set root or previous ancestor name and id.
        $parent_name = ($first_non_empty == 0) ? '' : $previous_items['name'][$first_non_empty - 1];
        $parent_tid  = ($first_non_empty == 0) ? 0 : $previous_items['tid'][$first_non_empty - 1];

        for ($c = $first_non_empty; $c < count($line); $c++) {
          $term = array(
            'name'   => $line[$c],
            'vid'    => $options['vocabulary_id'],
            // Need an array in case of multiple parent.
            'parent' => array($parent_tid),
          );

          // Import term then store and check result.
          switch ($options['import_format']) {
            case TAXONOMY_CSV_FORMAT_TREE_STRUCTURE:
              // With TAXONOMY_CSV_EXISTING_IGNORE_CREATE, parent terms (so all
              // terms but the last on this line) are always updated because
              // they are successive parents of a child.
              $current_result = ($options['existing_items'] == TAXONOMY_CSV_EXISTING_IGNORE_CREATE && ($c < count($line) - 1)) ?
                  taxonomy_csv_term_import($term, TAXONOMY_CSV_EXISTING_IGNORE_PREVIOUS, FALSE, $parent_tid) :
                  taxonomy_csv_term_import($term, $options['existing_items'], FALSE, $parent_tid);
              break;

            case TAXONOMY_CSV_FORMAT_POLYHIERARCHY:
              // Check direct duplicates: in Drupal, a term can't be its parent.
              $current_result = ($term['name'] == $parent_name) ?
                  taxonomy_csv_term_import($term, $options['existing_items'], FALSE, $parent_tid) :
                  taxonomy_csv_term_import($term, $options['existing_items'], FALSE, NULL);
              break;
          }
          $result['name'][] = $current_result['name'];
          $result['tid'][]  = $current_result['tid'];
          $result['msg'][]  = $current_result['msg'];
          if (_taxonomy_csv_message_warning($current_result['msg'])) {
            break;
          }

          $parent_name = $current_result['name'];
          $parent_tid  = $current_result['tid'];
        }
        break;

      case TAXONOMY_CSV_FORMAT_PARENTS:
        // First, import parents using a recursive call and check result.
        if (count($line) > 1) {
          $options_temp = $options;
          $options_temp['import_format'] = TAXONOMY_CSV_FORMAT_FLAT;
          $result = _taxonomy_csv_line_import_process(array_slice($line, 1), $options_temp);
          if (_taxonomy_csv_message_warning($result, 'line')) {
            break;
          }
        }

        // Second, import main term and store result.
        // Don't check tid == parent_tid because duplicates have been removed.
        $term = array(
          'name'   => $line[0],
          'vid'    => $options['vocabulary_id'],
          'parent' => $result['tid'],
        );
        $current_result = taxonomy_csv_term_import($term, $options['existing_items']);
        // No check because only one term.
        // Use array_unshift in order to keep $line order of items.
        array_unshift($result['name'], $current_result['name']);
        array_unshift($result['tid'], $current_result['tid']);
        array_unshift($result['msg'], $current_result['msg']);
        break;

      case TAXONOMY_CSV_FORMAT_CHILDREN:
        // First, import main term then store and check result.
        $options_temp = $options;
        $options_temp['import_format'] = TAXONOMY_CSV_FORMAT_ALONE_TERMS;
        $result = _taxonomy_csv_line_import_process(array($line[0]), $options_temp);
        if (_taxonomy_csv_message_warning($result, 'line')) {
          break;
        }
        // Remember tid of main term.
        $parent_tid = $result['tid'][0];

        // Second, import children.
        foreach (array_slice($line, 1) as $value) {
          $term = array(
            'name'   => $value,
            'vid'    => $options['vocabulary_id'],
            'parent' => array($parent_tid),
          );

          // Import term then store and check result.
          // Don't check tid == parent_tid because duplicates have been removed.
          $current_result = taxonomy_csv_term_import($term, $options['existing_items']);
          $result['name'][] = $current_result['name'];
          $result['tid'][]  = $current_result['tid'];
          $result['msg'][]  = $current_result['msg'];
          if (_taxonomy_csv_message_warning($current_result['msg'])) {
            break;
          }
        }
        break;

      case TAXONOMY_CSV_FORMAT_RELATIONS:
        // Each related term should exist before first column term can be
        // related to it (need of its tid). Next, process relations and
        // eventually subrelations.
        // So with a line A,B,C,D,E..., creates A, BA, CA(B), DA(BC), EA(BCD)...
        // as it's the fatest way to create one or all relations even if items
        // don't exist.
        // As use of name is only for first column, need to keep previous tids
        // matching names in $previous_relations ([name] <=> [tid]).
        $previous_relations = array();
        foreach ($line as $key => $term) {
          $term = array(
            'name'      => $line[$key],
            'vid'       => $options['vocabulary_id'],
            'relations' => array_slice($previous_relations, 0, ($options['relations_create_subrelations']) ? $key : $key != 0),
          );

          // @todo Set an 'ignore all' option.
          // For second and next terms, update merge related terms in order to
          // keep previous relations, as option is only for the first column term.
          $current_term_import_option = ($key == 0) ? $options['existing_items'] : TAXONOMY_CSV_EXISTING_UPDATE_MERGE;

          $current_result = taxonomy_csv_term_import($term, $current_term_import_option, $options['relations_all_vocabularies'], NULL);
          $result['name'][] = $current_result['name'];
          $result['tid'][]  = $current_result['tid'];
          $result['msg'][]  = $current_result['msg'];
          if (_taxonomy_csv_message_warning($current_result['msg'])) {
            break;
          }

          $previous_relations[$current_result['name']] = $current_result['tid'];
        }
        break;

      case TAXONOMY_CSV_FORMAT_TAXONOMY_MANAGER:
        $term = array(
          'name'        => $line[2],
          'vid'         => $options['vocabulary_id'],
        );
        if ($line[3]) {
          $term['description'] = $line[3];
        }

        // Complete with parents except root. All parents are already checked.
        $list_parents = array_slice($line, 4);
        if ($list_parents[0] != 0) {
          foreach ($list_parents as $value) {
            $term['parent'][] = $previous_items['tid'][$value];
          }
        }

        // Use tid if term is already imported.
        if (isset($previous_items['tid'][$line[1]])) {
          $term['tid'] = $previous_items['tid'][$line[1]];
        }
        else {
          // No tid is given, so it's always a new term.
          $options['existing_items'] = TAXONOMY_CSV_EXISTING_IGNORE_CREATE;
        }

        // Import term then store result. No check because only one term.
        $current_result = taxonomy_csv_term_import($term, $options['existing_items']);
        // Keep old index (names and tids).
        $result = $previous_items;
        $result['name'][$line[1]] = $current_result['name'];
        $result['tid'][$line[1]]  = $current_result['tid'];
        $result['msg'][$line[1]]  = $current_result['msg'];
        break;

      default:
        $result['msg'][] = array(306); // Error unknown import format.
    }
  }
  else {
    $result['msg'][] = array(685); // No term to process.
  }

  return $result;
}

/**
 * Export a term to a line matching the options.
 *
 * @param $term
 *   Term array (name, tid, vid, description, weight) to export.
 * @param $options
 *   Array of export options:
 *     export_format : see _taxonomy_csv_info_lists('list_export_format')
 *     Specific to fields_links:
 *     fields_links_terms_ids : 'name_if_needed' (default), 'name' or 'tid'
 *     fields_links_vocabularies_ids : 'none' (default), 'name' or 'vid'
 * @param $duplicate_terms
 *   Optional. Array of duplicate terms names indexed by tid.
 *   Duplicate terms are managed only with fields_links.
 * @return Result array:
 *   'line' => array of exported items,
 *   'msg'  => array of messages arrays.
 */
function taxonomy_csv_line_export($term, $options, $duplicate_terms = array()) {
  // Define default values.
  $result = array(
    'line' => array(),
    'msg'  => array(),
  );

  // Only count check because term and options are already checked.
  if (count($term)) {
    switch ($options['export_format']) {
      case TAXONOMY_CSV_FORMAT_ALONE_TERMS:
        $result['line'] = array(
          $term['name'],
        );
        break;

      case TAXONOMY_CSV_FORMAT_FIELDS_LINKS:
        // Prepare identifiants of main term and links.
        // Check if each term is a duplicate, because identifiants are names,
        // except for duplicate terms. For them, tid is appended to name.
        $terms['main']      = array((object) $term);
        $terms['parent']    = taxonomy_get_parents($term['tid']);
        $terms['children']  = taxonomy_get_children($term['tid']);
        $terms['relations'] = taxonomy_get_related($term['tid']);
        foreach (array(
            'main',
            'parent',
            'children',
            'relations',
          ) as $link) {
          $ids[$link] = array();
          foreach ($terms[$link] as $item) {
            // Option is to use term id.
            if ($options['fields_links_terms_ids'] == 'tid') {
              $ids[$link][] = $item->tid;
            }
            // If another option, identifiant depends on duplicate names.
            // Term name is a duplicate, so append tid to name.
            elseif (isset($duplicate_terms[$item->tid])) {
              $ids[$link][] = $item->name .' '. $item->tid;
            }
            // Not duplicate, so use name or eventually nothing for main term.
            else {
              $ids[$link][] = $item->name;
            }
          }
        }

        // Prepare synonyms.
        $synonyms = taxonomy_get_synonyms($term['tid']);

        // Prepare main term vocabulary identifiant.
        // Vocabulary identifiant depends on fields_links_vocabularies_ids.
        $vocabulary = taxonomy_vocabulary_load($term['vid']);
        $vocabulary_id = ($options['fields_links_vocabularies_ids'] == 'none') ?
            // Don't set vocabulary.
            '' :
            // Use name or vid.
            $vocabulary->$options['fields_links_vocabularies_ids'];
        // Prepare vocabularies identifiants of related terms.
        $related_vocs = array();
        // Option 'none' is impossible with multiple vocabularies, so use name.
        $vocabulary_option = ($options['fields_links_vocabularies_ids'] == 'none') ?
            'name' :
            $options['fields_links_vocabularies_ids'];
        foreach ($terms['relations'] as $item) {
          // Check if related term vocabulary is main term vocabulary.
          $vocabulary = taxonomy_vocabulary_load($item->vid);
          $related_vocs[] = ($item->vid == $term['vid']) ?
              // Same vocabularies, so use same identifiant.
              $vocabulary_id :
              // Different vocabularies, so use name or vid.
              $vocabulary->$vocabulary_option;
        }

        $result['line'] = array_merge(
          array(
            $term['name'],
            // Main term identifiant: use tid, name or nothing.
            (($options['fields_links_terms_ids'] == 'name_if_needed') && ($term['name'] == $ids['main'][0])) ?
                // Choice is name_if_needed and name is not a duplicate.
                '' :
                // Previously set identifiant.
                $ids['main'][0],
            $vocabulary_id,
            $term['description'],
            $term['weight'],
            count($synonyms),
            count($ids['parent']),
            count($ids['children']),
            count($ids['relations']),
          ),
          $synonyms,
          $ids['parent'],
          $ids['children'],
          $ids['relations'],
          $related_vocs
        );
        break;

      case TAXONOMY_CSV_FORMAT_PARENTS:
        $result['line'] = array_merge(
          array(
            $term['name'],
          ),
          taxonomy_csv_term_get_parents_names($term['tid'])
        );
        break;

      case TAXONOMY_CSV_FORMAT_CHILDREN:
        $result['line'] = array_merge(
          array(
            $term['name'],
          ),
          taxonomy_csv_term_get_children_names($term['tid'])
        );
        break;

      case TAXONOMY_CSV_FORMAT_RELATIONS:
        $result['line'] = array_merge(
          array(
            $term['name'],
          ),
          taxonomy_csv_term_get_related_names($term['tid'])
        );
        break;

      case TAXONOMY_CSV_FORMAT_FIELDS:
        $result['line'] = array_merge(
          array(
            $term['name'],
            $term['weight'],
            $term['description'],
          ),
          taxonomy_get_synonyms($term['tid'])
        );
        break;

      case TAXONOMY_CSV_FORMAT_DESCRIPTIONS:
        $result['line'] = array(
          $term['name'],
          $term['description'],
        );
        break;

      case TAXONOMY_CSV_FORMAT_WEIGHTS:
        $result['line'] = array(
          $term['name'],
          $term['weight'],
        );
        break;

      case TAXONOMY_CSV_FORMAT_SYNONYMS:
        $result['line'] = array_merge(
          array(
            $term['name'],
          ),
          taxonomy_get_synonyms($term['tid'])
        );
        break;

      default:
        $result['msg'][] = array(307); // Error unknown export format.
    }
  }
  else {
    $result['msg'][] = array(685); // No term to process.
  }

  return $result;
}

/**
 * @} End of "defgroup taxonomy_csv_line".
 */

/**
 * @defgroup taxonomy_csv_term Import/export a term
 * @{
 * Functions allowing import/export of a term.
 */

/**
 * Update or create a term with the given name in the given vocabulary and
 * given parent.
 *
 * @param $term
 *   A term array to import. Term is an array containing:
 *     'name'        => term name string,
 *   and eventually, matching options:
 *     'tid'         => term id,
 *     'vid'         => the vocabulary id where to import,
 *     'parent'      => array of first level parent tids,
 *     'relations'   => array of related tids,
 *     'synonyms'    => array of synonyms terms names strings,
 *     'description' => description string,
 *     'weight'      => weight integer,
 * @param $existing_items
 *   Optional. Type of import on existing terms. Default to ignore and create.
 * @param $all_vocabularies
 *   Optional. Boolean. Search in all vocabularies
 *   or only in $term['vid'] vocabulary (default), which need to be set.
 * @param $parent_tid
 *   Optional. Boolean. Restrict search in parent ($term['parent'][0] and next).
 *   Useful for structure. Default to NULL (search in whole vocabulary).
 * @return array
 *    'name' => term name,
 *    'tid'  => term id,
 *    'msg'  => messages array.
 */
function taxonomy_csv_term_import($term, $existing_items = TAXONOMY_CSV_EXISTING_IGNORE_CREATE, $all_vocabularies = FALSE, $parent_tid = NULL) {
  $messages = array();
  if ($term) {
    // Set default term to update.
    $term_to_update = array(
      'name'        => '',
      'tid'         => 0,
      'vid'         => 0,
      'parent'      => array(),
      'relations'   => array(),
      'synonyms'    => array(),
      'description' => '',
      'weight'      => 0,
    );

    switch ($existing_items) {
      case TAXONOMY_CSV_EXISTING_UPDATE:
        // When no difference between update/merge and update/replace.
      case TAXONOMY_CSV_EXISTING_UPDATE_MERGE:
        $existing_term = _taxonomy_csv_term_find_existing($term, $all_vocabularies, $parent_tid);
        if ($existing_term) {
          $term_to_update = $existing_term;
          // Get name is not case sensitive and a name can be updated.
          if (isset($term['name'])) {
            $existing_term['name'] = $term['name'];
          }
          if (isset($term['vid'])) {
            $existing_term['vid'] = $term['vid'];
          }
          if (isset($term['parent'])) {
            $existing_term['parent'] = array_unique(array_merge($existing_term['parent'], $term['parent']));
          }
          if (isset($term['relations'])) {
            $existing_term['relations'] = array_unique(array_merge($existing_term['relations'], $term['relations']));
          }
          if (isset($term['synonyms'])) {
            $existing_term['synonyms'] = array_unique(array_merge($existing_term['synonyms'], $term['synonyms']));
          }
          if (isset($term['description'])) {
            $i = trim($existing_term['description']);
            $existing_term['description'] = (($i == '') || ($i == $term['description'])) ?
                $term['description'] :
                $i ."\n". $term['description'];
          }
          // Weight is always replaced as it is a simple number.
          if (isset($term['weight'])) {
            $existing_term['weight'] = $term['weight'];
          }
          $term = $existing_term;
        }
        break;

      case TAXONOMY_CSV_EXISTING_IGNORE_PREVIOUS:
        // Doesn't ignore, but use previous parents.
      case TAXONOMY_CSV_EXISTING_UPDATE_REPLACE:
        $existing_term = _taxonomy_csv_term_find_existing($term, $all_vocabularies, $parent_tid);
        if ($existing_term) {
          $term_to_update = $existing_term;
          foreach (array(
              'name',
              'vid',
              'parent',
              'relations',
              'synonyms',
              'description',
              'weight',
            ) as $key) {
            if (array_key_exists($key, $term)) {
              $existing_term[$key] = $term[$key];
            }
          }
          $term = $existing_term;
        }
        break;

      case TAXONOMY_CSV_EXISTING_IGNORE:
        // When no difference between ignore/create and ignore/all.
      case TAXONOMY_CSV_EXISTING_IGNORE_CREATE:
        break;

      case TAXONOMY_CSV_EXISTING_IGNORE_ALL:
        // Ignore even existing terms in additional columns.
        // @todo IGNORE_ALL
    }

    // If a term has no parent, it's a root term, so adds parent 0.
    if (!isset($term['parent'])
        || count($term['parent']) == 0) {
      $term['parent'] = array(0);
    }
    // If a term has a parent, it can't be a root term, so removes parent 0.
    elseif ((count($term['parent']) > 1)
        && in_array(0, $term['parent'])) {
      unset($term['parent'][array_search(0, $term['parent'])]);
    }

    // Check if term is really new in order to avoid a useless import.
    if ($term['name']           != $term_to_update['name']
        || $term['vid']         != $term_to_update['vid']
        || $term['parent']      != $term_to_update['parent']
        || $term['relations']   != $term_to_update['relations']
        || $term['synonyms']    != $term_to_update['synonyms']
        || $term['description'] != $term_to_update['description']
        || $term['weight']      != $term_to_update['weight']) {
      $result = taxonomy_csv_term_save($term);
      $messages[] = ($result == SAVED_NEW) ? 691 : 692; // Saved or updated.
    }
    else {
      $result = TAXONOMY_CSV_UNCHANGED;
      $messages[] = 695; // Unchanged term.
    }

    // Update cache with new or updated $term.
    if (_taxonomy_csv_term_cache($term, $result) === FALSE) {
      $messages[] = 392; // Cache problem.
    }
  }
  else {
    $messages[] = 391; // Error: not a term.
  }
  return array(
    'name' => $term['name'],
    'tid'  => $term['tid'],
    'msg'  => $messages,
  );
}

/**
 * Find an existing term in cache or in vocabularies by its tid, else in
 * vocabularies by its name.
 *
 * @param $term
 *   The term array to find.
 * @param $all_vocabularies
 *   Optional. Boolean. Search in all vocabularies
 *   or only in $term['vid'] vocabulary (default), which need to be set.
 * @param $parent_tid
 *   Optional. The direct parent term id.
 *   Useful for structure. Default to NULL (no parent restriction).
 * @return
 *   Found term array or empty array if not found.
 */
function _taxonomy_csv_term_find_existing($term, $all_vocabularies = FALSE, $parent_tid = NULL) {
  // Find existing term in cache. All terms with tid are cached and only them.
  if (!empty($term['tid'])) {
    return (_taxonomy_csv_term_cache('', 'cache_enabled') === TRUE) ?
      // Use cache. Return empty array if not cached.
      _taxonomy_csv_term_cache($term) :
      // No cache, so get from vocabularies.
      taxonomy_csv_term_get_full($term['tid']);
  }
  // If no tid, search in vocabularies.
  elseif (isset($term['name'])) {
    return taxonomy_csv_term_find($term['name'], ($all_vocabularies) ? NULL : $term['vid'], $parent_tid);
  }
  // ERROR: no tid neither name.
  return FALSE;
}

/**
 * Find or save an existing term in the imported terms cache, by its tid.
 *
 * @param $term
 *   The term array to get or save. Need only the term['tid'] to get it.
 *   If $process_type is 'set_cache', array of terms arrays with 'st' (status).
 *   If $process_type is 'use_cache', boolean.
 * @param $process_type
 *   Optional. Process type:
 *   'get'          : find a cached imported term (default)
 *   SAVED_NEW      : update the static cache with the given term as created
 *   SAVED_UPDATED  : update the static cache with the given term as updated
 *   TAXONOMY_CSV_UNCHANGED: update the cache with the given term as unchanged
 *   'count'        : count cached terms
 *   'set_cache'    : set cache
 *   'dump'         : return all the cache
 *   'clear'        : clear cache
 *   'use_cache'    : use cache if $term is TRUE or disable it if $term is FALSE
 *   'cache_enabled': inform if cache is used
 * @return
 *   get: Found term array or FALSE if error.
 *   Always TRUE if cache is not set, except when process_type is cache_enabled.
 */
function &_taxonomy_csv_term_cache($term, $process_type = 'get') {
  // Notice: Need to return something, because it's a by reference function.
  // Furthermore, only variable references should be returned by reference.
  // Options all_vocabularies and parent_tid aren't used as currently, import
  // process is always the same.

  // Enable or disable cache.
  static $use_cache = TRUE;

  // Each full term array is cached by its tid with its status.
  static $imported_cache = array();

  // Cache enabled.
  if ($use_cache) {
    switch ($process_type) {
      // @todo Update cached relateds when relateds are updated. Or use handles.
      case 'get':
        if (isset($imported_cache[$term['tid']])) {
          $result = $imported_cache[$term['tid']];
          // Complete term links with empty array in order to return full term.
          if (!isset($result['synonyms'])) {
            $result['synonyms'] = array();
          }
          // Empty parent is a root parent.
          if (!isset($result['parent'])) {
            $result['parent'] = array(0);
          }
          // Currently, as to make a relation influes on two terms, cached term
          // may not be up to date. So, update returned result when get. Cache
          // is not updated, because it's useless when get and can lost status.
          $result['relations'] = taxonomy_csv_term_get_related_tids($result['tid']);
          // Remove status, not needed to get term.
          unset($result['st']);
          return $result;
        }
        // Else.
        $result = array();
        return $result;

      case SAVED_NEW:
        if ((isset($term['tid'])) && ($term['tid'] != 0)) {
          if (!isset($imported_cache[$term['tid']])) {
            $imported_cache[$term['tid']] = $term;
            $imported_cache[$term['tid']]['st'] = SAVED_NEW;
            $result = TRUE;
            return $result;
          }
          // Already cached and user wants again to create it.
          $imported_cache[$term['tid']] = $term;
          $imported_cache[$term['tid']]['st'] = TAXONOMY_CSV_ERROR;
        }
        // Else.
        $result = FALSE;
        return $result;

      case SAVED_UPDATED:
        // 'update updated'
        if ((isset($term['tid'])) && ($term['tid'] != 0)) {
          if (!isset($imported_cache[$term['tid']])) {
            $imported_cache[$term['tid']] = $term;
            $imported_cache[$term['tid']]['st'] = SAVED_UPDATED;
            $result = TRUE;
            return $result;
          }
          // Else.
          switch ($imported_cache[$term['tid']]['st']) {
            case SAVED_NEW:
            case TAXONOMY_CSV_NEW_UPDATED:
              // Unchange status but update term.
              $imported_cache[$term['tid']] = $term;
              $imported_cache[$term['tid']]['st'] = TAXONOMY_CSV_NEW_UPDATED;
              $result = TRUE;
              return $result;

            case SAVED_UPDATED:
            case TAXONOMY_CSV_UNCHANGED:
              // Unchange status whether previous status was, but update term.
              $imported_cache[$term['tid']] = $term;
              $imported_cache[$term['tid']]['st'] = SAVED_UPDATED;
              $result = TRUE;
              return $result;
          }
          // Default.
          $imported_cache[$term['tid']] = $term;
          $imported_cache[$term['tid']]['st'] = TAXONOMY_CSV_ERROR;
        }
        // Else.
        $result = FALSE;
        return $result;

      case TAXONOMY_CSV_UNCHANGED:
        if ((isset($term['tid'])) && ($term['tid'] != 0)) {
          if (!isset($imported_cache[$term['tid']])) {
            $imported_cache[$term['tid']] = $term;
            $imported_cache[$term['tid']]['st'] = TAXONOMY_CSV_UNCHANGED;
          }
          $result = TRUE;
          return $result;
        }
        // Else.
        $result = FALSE;
        return $result;

      case 'count':
        $result = count($imported_cache);
        return $result;

      case 'set_cache':
        $imported_cache = $term;
        $use_cache = TRUE;
        return $use_cache;

      case 'dump':
        return $imported_cache;

      case 'clear':
        $imported_cache = array();
        return $imported_cache;

      case 'use_cache':
        $use_cache = $term;
        return $use_cache;

      case 'cache_enabled':
        $result = TRUE;
        return $result;
    }
  }
  // Cache disabled.
  else {
    // Always return TRUE except when command is to know if cache is used.
    $result = ($process_type == 'cache_enabled') ?
        FALSE :
        TRUE;
    return $result;
  }
  // process_type error.
  $result = FALSE;
  return $result;
}

/**
 * Get a base term by its id.
 *
 * Memory overflow can occur with static cache of taxonomy_get_term function.
 *
 * @param $tid
 *   The term id to get.
 * @return
 *   Found base term array or empty array.
 */
function taxonomy_csv_term_get($tid) {
  return db_fetch_array(db_query('SELECT * FROM {term_data} WHERE tid = %d', $tid));
}

/**
 * Get a full term by its id.
 *
 * @param $tid
 *   The term id to get.
 * @return
 *   Found term array as describe in taxonomy_csv_term_import or an empty array.
 */
function taxonomy_csv_term_get_full($tid) {
  $term = taxonomy_csv_term_get($tid);
  if ($term) {
    $term['parent']    = taxonomy_csv_term_get_parents_tids($term['tid']);
    $term['relations'] = taxonomy_csv_term_get_related_tids($term['tid']);
    $term['synonyms']  = taxonomy_get_synonyms($term['tid']);
  };
  return $term;
}

/**
 * Find, by its name, the first existing term in a given vocabulary and a given
 * parent.
 *
 * @param $name
 *   The name string to find.
 * @param $vid
 *   Optional. The vocabulary id where to search if any. Default to NULL (all).
 * @param $parent_tid
 *   Optional. The direct parent term id if any. Default to NULL (none).
 * @return
 *   Found term array as describe in taxonomy_csv_term_import or an empty array.
 */
function taxonomy_csv_term_find($name, $vid = NULL, $parent_tid = NULL) {
  $name = drupal_strtolower(trim($name));

  if (drupal_strlen($name)) {
    $sql = "
      SELECT t.*, h.parent
      FROM {term_data} t
      INNER JOIN {term_hierarchy} h ON t.tid = h.tid
      WHERE '%s' LIKE LOWER(t.name)
    ";
    $args = array($name);

    if ($vid) {
      $sql .= ' AND t.vid = %d';
      $args[] = $vid;
    }

    if ($parent_tid) {
      $sql .= ' AND h.parent = %d';
      $args[] = $parent_tid;
    }

    $sql .= ' ORDER BY t.tid ASC LIMIT 1';

    $result = db_query($sql, $args);
    $term   = db_fetch_array($result);

    if ($term) {
      $term['parent']    = taxonomy_csv_term_get_parents_tids($term['tid']);
      $term['relations'] = taxonomy_csv_term_get_related_tids($term['tid']);
      $term['synonyms']  = taxonomy_get_synonyms($term['tid']);

      return $term;
    }
  }
  return array();
}

/**
 * Save a term array by reference.
 *
 * Drupal taxonomy_save_term use a text area format to import synonyms.
 * This helper convert a synonym array into a string before using it.
 *
 * @param $term
 *   A term array to save by reference. Term is an array containing:
 *     'name'        => term name string,
 *     'vid'         => the vocabulary id,
 *   and eventually:
 *     'tid'         => term id,
 *     'parent'      => array of first level parent tids,
 *     'relations'   => array of related tids,
 *     'synonyms'    => array of synonyms terms names strings,
 *     'description' => description string,
 *     'weight'      => weight integer,
 * @return
 *   Status value.
 */
function taxonomy_csv_term_save(&$term) {
  if (isset($term['synonyms'])) {
    $synonyms = $term['synonyms'];
    $term['synonyms'] = implode("\n", $term['synonyms']);
  }
  // Term is automaticaly updated, because it's used by reference.
  // Return either SAVED_NEW or SAVED_UPDATED.
  $result = taxonomy_save_term($term);

  // Keep synonyms as an array.
  if (isset($synonyms)) {
    $term['synonyms'] = $synonyms;
  }

  return $result;
}

/**
 * Return an array of all term links of one type from a term id.
 *
 * @param $tid
 *   Term id from which to get links.
 * @param $link
 *   String. Type of link terms to get: 'parent', 'children' or 'relations'.
 * @param $item
 *   Optional. String. Type of item to get, as 'tid' (default) or 'name'.
 * @return Result array of items.
 */
function taxonomy_csv_term_get_links_from_tid($tid, $link, $item = 'tid') {
  $items = array();
  $link_callback = array(
    'parent'    => 'taxonomy_get_parents',
    'children'  => 'taxonomy_get_children',
    'relations' => 'taxonomy_get_related',
  );
  if (isset($link_callback[$link])
      && !empty($tid)) {
    $terms = call_user_func($link_callback[$link], $tid);
    foreach ($terms as $term) {
      $items[] = $term->$item;
    }
  }
  return $items;
}

/**
 * Return an array of all parents term IDs of a given term ID.
 * If no parent, return array(0), because a term without parent is a root term.
 * If tid doesn't exist, return array(0) too (not checked).
 * Return empty array only if tid is not set.
 * Wrapper of taxonomy_csv_term_get_links_from_tid.
 * @todo To simplify as other wrappers.
 */
function taxonomy_csv_term_get_parents_tids($tid) {
  if (empty($tid)) {
    return array();
  }
  // Else.
  $result = taxonomy_csv_term_get_links_from_tid($tid, 'parent', 'tid');
  return ($result) ? $result : array(0);
}

/**
 * Return an array of all parents term names of a given term ID.
 * Wrapper of taxonomy_csv_term_get_links_from_tid.
 */
function taxonomy_csv_term_get_parents_names($tid) {
  return taxonomy_csv_term_get_links_from_tid($tid, 'parent', 'name');
}

/**
 * Return an array of all children term id of a given term ID.
 * Wrapper of taxonomy_csv_term_get_links_from_tid.
 */
function taxonomy_csv_term_get_children_tids($tid) {
  return taxonomy_csv_term_get_links_from_tid($tid, 'children', 'tid');
}

/**
 * Return an array of all children term names of a given term ID.
 * Wrapper of taxonomy_csv_term_get_links_from_tid.
 */
function taxonomy_csv_term_get_children_names($tid) {
  return taxonomy_csv_term_get_links_from_tid($tid, 'children', 'name');
}

/**
 * Return an array of all term IDs related to a given term ID.
 * Wrapper of taxonomy_csv_term_get_links_from_tid.
 */
function taxonomy_csv_term_get_related_tids($tid) {
  return taxonomy_csv_term_get_links_from_tid($tid, 'relations', 'tid');
}

/**
 * Return an array of all term names related to a given term ID.
 * Wrapper of taxonomy_csv_term_get_links_from_tid.
 */
function taxonomy_csv_term_get_related_names($tid) {
  return taxonomy_csv_term_get_links_from_tid($tid, 'relations', 'name');
}

/**
 * @} End of "defgroup taxonomy_csv_term".
 */

/**
 * @defgroup taxonomy_csv_message Messages helpers
 * @{
 * Functions managing import/export messages.
 */

/**
 * Helper to determine worst level of a result messages array.
 *
 * @param $messages
 *   Array of messages of an import line results.
 * @return worst message.
 */
function _taxonomy_csv_message_get_worst_message($messages) {
  if (is_array($messages)) {
    // @todo To simplify.
    $list_messages = array();
    foreach ($messages as $value) {
      foreach ($value as $msg) {
        $list_messages[$msg] = $msg;
      }
    }
    // Sort so first is the lowest.
    sort($list_messages);

    return (count($list_messages)) ? $list_messages[0] : 998;   // No message.
  }
  return 0;
}

/**
 * Helper to determine worst message level of a set of message codes.
 *
 * @param $messages
 *   Array of message code (000 to 999) or set of full results messages.
 * @param $type
 *   Type of messages array:
 *     'msg' (default), 'term', 'line', 'lines', 'results'.
 * @return
 *   Worst level (0 to 9).
 */
function _taxonomy_csv_message_get_worst_level($messages, $type = 'msg') {
  if (is_array($messages)) {
    switch ($type) {
      case 'msg':
        $list_messages = $messages;
        break;

      case 'term':
        if ($messages['msg']) {
          $list_messages = $messages['msg'];
        }
        else {
          return 0;
        }
        break;

      case 'line':
        if ($messages['msg']) {
          // Convert ['msg'][term serial]msg serial => code to array of codes.
          $list_messages = array();
          foreach ($messages['msg'] as $message_codes) {
            $list_messages = array_merge($list_messages, $message_codes);
          }
        }
        else {
          return 0;
        }
        break;

      case 'lines':
        $list_messages = array();
        foreach ($messages as $line) {
          $list_messages = array_merge($list_messages, $line);
        }
        break;

      case 'results':
        // Convert [line number]['line'/serial]['msg'][term serial]msg => code
        // to array of codes indexed by code.
        if ($messages) {
          $list_messages = array();
          foreach ($messages as $line_number => $operation) {
            foreach ($operation as $item) {
              foreach ($item['msg'] as $message_code) {
                $list_messages[$message_code] = $message_code;
              }
            }
          }
        }
        else {
          return 0;
        }
        break;

      default:
        return 0;
    }

    return count($list_messages) ?
        _taxonomy_csv_message_get_level(min($list_messages)) :
        TAXONOMY_CSV_WATCHDOG_NONE;
  }
  return 0;
}

/**
 * Returns a boolean when a set of message codes contains a warning or worst.
 *
 * @param $messages
 *   Array of message code (000 to 999) or set of full results messages.
 * @param $type
 *   Type of messages array:
 *     'msg' (default), 'term', 'line', 'lines', 'results'.
 * @return
 *   TRUE if warning or error, else FALSE.
 */
function _taxonomy_csv_message_warning($messages, $type = 'msg') {
  return (_taxonomy_csv_message_get_worst_level($messages, $type) <= TAXONOMY_CSV_WATCHDOG_WARNING);
}

/**
 * Helper to determine error level of a message code.
 *
 * @param $message_code
 *   Single message code (000 to 999).
 * @return
 *   Level (0 to 9).
 */
function _taxonomy_csv_message_get_level($message_code) {
  $result = intval($message_code / 100);
  return ($result >= TAXONOMY_CSV_WATCHDOG_ERROR && $result <= TAXONOMY_CSV_WATCHDOG_NONE) ? $result : TAXONOMY_CSV_WATCHDOG_ERROR;
}

/**
 * @} End of "defgroup taxonomy_csv_message".
 */

/**
 * @defgroup taxonomy_csv_info Informations helpers.
 * @{
 * Functions informing about import/export process.
 */

/**
 * Helper to remember some items.
 *
 * @param $list
 *   A string matching list to be returned:
 *     'list_import_format',
 *     'list_export_format',
 *     'list_import_option',
 *     'list_import_format_allowed_import_option',
 *     'hierarchy_text',
 * @return wanted content.
 */
function _taxonomy_csv_info_lists($list) {
  switch ($list) {
    case 'list_import_format':
      return array(
        TAXONOMY_CSV_FORMAT_ALONE_TERMS      => t('Term names (ignore additional columns)'),
        TAXONOMY_CSV_FORMAT_FIELDS_LINKS     => t('Full term fields and links'),
        TAXONOMY_CSV_FORMAT_FLAT             => t('Terms (flat vocabulary)'),
        TAXONOMY_CSV_FORMAT_TREE_STRUCTURE   => t('Hierarchical tree structure or one term by line structure'),
        TAXONOMY_CSV_FORMAT_POLYHIERARCHY    => t('Polyhierarchical structure'),
        TAXONOMY_CSV_FORMAT_PARENTS          => t('First level parents'),
        TAXONOMY_CSV_FORMAT_CHILDREN         => t('First level children'),
        TAXONOMY_CSV_FORMAT_RELATIONS        => t('Related terms'),
        TAXONOMY_CSV_FORMAT_FIELDS           => t('Full term definitions'),
        TAXONOMY_CSV_FORMAT_DESCRIPTIONS     => t('Term descriptions'),
        TAXONOMY_CSV_FORMAT_WEIGHTS          => t('Term weights'),
        TAXONOMY_CSV_FORMAT_SYNONYMS         => t('Synonyms terms'),
        TAXONOMY_CSV_FORMAT_TAXONOMY_MANAGER => t('Taxonomy manager'),
      );

    case 'list_export_format':
      return array(
        TAXONOMY_CSV_FORMAT_ALONE_TERMS      => t('Term names'),
        TAXONOMY_CSV_FORMAT_FIELDS_LINKS     => t('Full term fields and links'),
        TAXONOMY_CSV_FORMAT_PARENTS          => t('First level parents'),
        TAXONOMY_CSV_FORMAT_CHILDREN         => t('First level children'),
        TAXONOMY_CSV_FORMAT_RELATIONS        => t('Related terms'),
        TAXONOMY_CSV_FORMAT_FIELDS           => t('Full term definitions'),
        TAXONOMY_CSV_FORMAT_DESCRIPTIONS     => t('Term descriptions'),
        TAXONOMY_CSV_FORMAT_WEIGHTS          => t('Term weights'),
        TAXONOMY_CSV_FORMAT_SYNONYMS         => t('Synonyms terms'),
      );

    case 'list_import_option':
      return array(
        TAXONOMY_CSV_EXISTING_UPDATE         => t('Update existing term'),
        TAXONOMY_CSV_EXISTING_UPDATE_MERGE   => t('Update (merge) existing term and items if exist else create'),
        TAXONOMY_CSV_EXISTING_UPDATE_REPLACE => t('Update (replace) existing term and items if exist else create'),
        TAXONOMY_CSV_EXISTING_IGNORE         => t('Duplicate existing term'),
        TAXONOMY_CSV_EXISTING_IGNORE_CREATE  => t('Ignore existing term and create a new term'),
        TAXONOMY_CSV_EXISTING_IGNORE_ALL     => t('Ignore existing term and create a new term for each term on the line'),
      );

    case 'list_import_format_allowed_import_option':
      return array(
        TAXONOMY_CSV_FORMAT_ALONE_TERMS      => array(
          TAXONOMY_CSV_EXISTING_UPDATE,
          TAXONOMY_CSV_EXISTING_IGNORE,
        ),
        TAXONOMY_CSV_FORMAT_FIELDS_LINKS     => array(
          TAXONOMY_CSV_EXISTING_UPDATE_MERGE,
        ),
        TAXONOMY_CSV_FORMAT_FLAT             => array(
          TAXONOMY_CSV_EXISTING_UPDATE,
          TAXONOMY_CSV_EXISTING_IGNORE,
        ),
        TAXONOMY_CSV_FORMAT_TREE_STRUCTURE   => array(
          TAXONOMY_CSV_EXISTING_UPDATE_REPLACE,
          TAXONOMY_CSV_EXISTING_IGNORE_CREATE,
//           TAXONOMY_CSV_EXISTING_IGNORE_ALL,
        ),
        TAXONOMY_CSV_FORMAT_POLYHIERARCHY    => array(
          TAXONOMY_CSV_EXISTING_UPDATE_MERGE,
        ),
        TAXONOMY_CSV_FORMAT_PARENTS          => array(
          TAXONOMY_CSV_EXISTING_UPDATE_MERGE,
          TAXONOMY_CSV_EXISTING_UPDATE_REPLACE,
          TAXONOMY_CSV_EXISTING_IGNORE_CREATE,
//           TAXONOMY_CSV_EXISTING_IGNORE_ALL,
        ),
        TAXONOMY_CSV_FORMAT_CHILDREN         => array(
          TAXONOMY_CSV_EXISTING_UPDATE_MERGE,
          TAXONOMY_CSV_EXISTING_UPDATE_REPLACE,
          TAXONOMY_CSV_EXISTING_IGNORE_CREATE,
//           TAXONOMY_CSV_EXISTING_IGNORE_ALL,
        ),
        TAXONOMY_CSV_FORMAT_RELATIONS        => array(
          TAXONOMY_CSV_EXISTING_UPDATE_MERGE,
          TAXONOMY_CSV_EXISTING_UPDATE_REPLACE,
          TAXONOMY_CSV_EXISTING_IGNORE_CREATE,
//           TAXONOMY_CSV_EXISTING_IGNORE_ALL,
        ),
        TAXONOMY_CSV_FORMAT_FIELDS           => array(
          TAXONOMY_CSV_EXISTING_UPDATE_MERGE,
          TAXONOMY_CSV_EXISTING_UPDATE_REPLACE,
          TAXONOMY_CSV_EXISTING_IGNORE_CREATE,
        ),
        TAXONOMY_CSV_FORMAT_DESCRIPTIONS     => array(
          TAXONOMY_CSV_EXISTING_UPDATE_MERGE,
          TAXONOMY_CSV_EXISTING_UPDATE_REPLACE,
          TAXONOMY_CSV_EXISTING_IGNORE_CREATE,
        ),
        TAXONOMY_CSV_FORMAT_WEIGHTS          => array(
          TAXONOMY_CSV_EXISTING_UPDATE_MERGE,
          TAXONOMY_CSV_EXISTING_IGNORE_CREATE,
        ),
        TAXONOMY_CSV_FORMAT_SYNONYMS         => array(
          TAXONOMY_CSV_EXISTING_UPDATE_MERGE,
          TAXONOMY_CSV_EXISTING_UPDATE_REPLACE,
          TAXONOMY_CSV_EXISTING_IGNORE_CREATE,
        ),
        TAXONOMY_CSV_FORMAT_TAXONOMY_MANAGER => array(
          TAXONOMY_CSV_EXISTING_UPDATE_MERGE,
          TAXONOMY_CSV_EXISTING_UPDATE_REPLACE,
          TAXONOMY_CSV_EXISTING_IGNORE_CREATE,
        ),
      );

    case 'hierarchy_text':
      return array(
        0 => t('no parent (flat)'),
        1 => t('single parent (tree)'),
        2 => t('multiple parents (polyhierarchy)'),
      );
  }
}

/**
 * Return formated list of options in order to inform user.
 */
function _taxonomy_csv_info_chosen_options($options) {
  // Local file, distant file or text.
  switch ($options['source_choice']) {
    case 'path':
      $message = t('File "%file" uploaded.', array(
        '%file' => $options['file']->filename));
      break;
    case 'url':
      $message = t('File "<a href="!url">%file</a>" uploaded from an url.', array(
        '!url'  => $options['url'],
        '%file' => basename($options['url'])));
      break;
    case 'text':
      $message = t('Import terms from text.');
      break;
  }

  // Content.
  $list = _taxonomy_csv_info_lists('list_import_format');
  $message .= '<br />'. t('Source content: "!import_format".', array(
    '!import_format' => $list[$options['import_format']],
  )) .'<br />';

  // Existing items.
  $list = _taxonomy_csv_info_lists('list_import_option');
  $message .= t('Existing terms choice: "!import_items".', array(
    '!import_items' => $list[$options['existing_items']],
  )) .'<br />';

  return $message;
}

/**
 * Return informations about destination vocabulary.
 */
function _taxonomy_csv_info_vocabulary_destination($vocabulary, $vocabulary_target) {
  // Destination vocabulary.
  $list_messages = array(
    'autocreate' => t('New vocabulary "%vocabulary_name" has been created.', array('%vocabulary_name' => $vocabulary->name)),
    'duplicate'  => t('Duplicate vocabulary "%vocabulary_name" has been created.', array('%vocabulary_name' => $vocabulary->name)),
    'existing'   => t('Terms are imported into existing vocabulary "%vocabulary_name".', array('%vocabulary_name' => $vocabulary->name)),
  );

  return $list_messages[$vocabulary_target];
}

/**
 * Return informations about result vocabulary.
 */
function _taxonomy_csv_info_vocabulary_result($vocabulary, $vocabulary_target, $new_hierarchy) {
  $message = '';

  // Level of vocabulary.
  $hierarchy_text = _taxonomy_csv_info_lists('hierarchy_text');
  if ($vocabulary_target != 'autocreate') {
    $message .= t('Old vocabulary hierarchy level was !level (!level_text).', array(
      '!level'      => $vocabulary->hierarchy,
      '!level_text' => $hierarchy_text[$vocabulary->hierarchy],
    )) .'<br />';
  }
  $message .= t('Vocabulary hierarchy level is !level (!level_text).', array(
    '!level'      => $new_hierarchy,
    '!level_text' => $hierarchy_text[$new_hierarchy],
  )) .'<br />';

  // Direct links to edit vocabulary and view terms.
  $message .= t('Properties can be edited at <a href="!vocabulary_edit_link">Administer > Content management > Taxonomy > edit vocabulary</a>.', array(
    '!vocabulary_edit_link' => url("admin/content/taxonomy/edit/vocabulary/$vocabulary->vid"),
  )) .'<br />';
  $message .= t('You can view terms at <a href="!vocabulary_list">Administer > Content management > Taxonomy > list terms</a>.', array(
    '!vocabulary_list' => url("admin/content/taxonomy/$vocabulary->vid"),
  )) .'<br />';
  if (module_exists('taxonomy_manager')) {
    $message .= t('It is recommended to use <a href="!link" title="Taxonomy manager module">Administer > Taxonomy manager > Vocabularies</a> with big taxonomies because a memory error can occur with default Drupal "List terms" menu.', array('!link' => url("admin/content/taxonomy_manager/voc/$vocabulary->vid")));
  }
  else {
    $message .= t('Warning: with default Drupal "List terms" function, a memory error can occurs with big taxonomies, so use another manager as <a href="!link" title="Taxonomy manager module">Taxonomy manager</a>.', array('!link' => url('http://drupal.org/project/taxonomy_manager')));
  }
  return $message;
}

/**
 * Helper to display basic statistics about created and updated terms.
 *
 * @param $imported_terms
 *   Array of imported terms arrays with 'tid', 'name' and 'st' (status).
 * @param $result_level
 *   Optional. Log level. Default to 'full'. Anything else is not full.
 * @return
 *   Statistics on imported terms (created and updated, updated, unchanged,
 *  created, error) with or without list of terms.
 */
function _taxonomy_csv_info_terms_stats(&$imported_terms, $result_level = 'full') {
  if (is_array($imported_terms)) {
    $stats_imported_terms = _taxonomy_csv_info_terms_stats_lists($imported_terms);

    $list_imported_text = array(
      TAXONOMY_CSV_NEW_UPDATED => t('Total created and updated terms'),
      SAVED_UPDATED            => t('Total updated existing terms'),
      TAXONOMY_CSV_UNCHANGED   => t('Total unchanged existing terms'),
      SAVED_NEW                => t('Total created terms'),
      TAXONOMY_CSV_ERROR       => t('Total processed import errors'),
    );

    $processed_message_text = '';
    foreach ($list_imported_text as $imported => $imported_text) {
      $processed_message_text .= "$imported_text : ". count($stats_imported_terms[$imported]) .'<br />';
      if ($stats_imported_terms[$imported]
          && ($result_level == 'full')) {
        $processed_message_text .= '"'. implode('", "', $stats_imported_terms[$imported]) .'".<br />';
      }
    }
    return $processed_message_text;
  }
}

/**
 * Helper to display basic statistics about created and updated terms.
 *
 * @param $imported_terms
 *   Array of imported terms arrays with 'tid', 'name' and 'st' (status).
 * @return
 *   Array of created and updated, updated, unchanged, created and error arrays
 *   of terms name.
 */
function _taxonomy_csv_info_terms_stats_lists(&$imported_terms) {
  if (is_array($imported_terms)) {
    $stats_imported_terms = array(
      TAXONOMY_CSV_NEW_UPDATED => array(),
      SAVED_UPDATED            => array(),
      TAXONOMY_CSV_UNCHANGED   => array(),
      SAVED_NEW                => array(),
      TAXONOMY_CSV_ERROR       => array(),
    );

    foreach ($imported_terms as $key => $term) {
      if (!isset($term['st'])) {
        $term['st'] = TAXONOMY_CSV_ERROR;
      }
      $stats_imported_terms[$term['st']][] = $term['name'];
    }
  return $stats_imported_terms;
  }
}

/**
 * Helper to display by line list of result messages.
 *
 * @param $messages_set
 *   Array of operation array of message codes.
 *   Message code is an integer between 000 and 999.
 * @param $result_level
 *   Optional. Level of messages to display: 'full' (default), 'infos',
 *   'notices' or 'warnings'.
 * @return
 *   Worst level (0 to 9).
 */
function _taxonomy_csv_info_result_by_line($messages_set, $result_level = 'full') {
  $list_messages = array();

  if (is_array($messages_set) && $messages_set) {
    // Prepare list of messages.
    switch ($result_level) {
      case 'full':
        // Convert [line number]['line'/serial]['msg'][message codes]
        //      to [line number][message codes].
        foreach ($messages_set as $line_number => $operation) {
          foreach ($operation as $item) {
            foreach ($item['msg'] as $message_code) {
              $list_messages[$line_number][] = $message_code;
            }
          }
        }
        break;

      case 'infos':
      case 'notices':
      case 'warnings':
        // Convert [line number][message codes]
        //      to [message codes][line number].
        foreach ($messages_set as $line_number => $operation) {
          foreach ($operation as $message_code) {
            $list_messages[$line_number][] = $message_code;
          }
        }
        break;

      default:
        return;
    }

    foreach ($list_messages as $line_number => $message_codes) {
      $processed_message_level = _taxonomy_csv_message_get_worst_level($message_codes);
      $processed_message_text  = t('Line #!line_number:', array('!line_number' => $line_number)) .'<br />';

      foreach ($message_codes as $message_code) {
        $processed_message_text .= _taxonomy_csv_info_result_text($message_code) .'<br />';
      }

      switch ($processed_message_level) {
        case TAXONOMY_CSV_WATCHDOG_ERROR:
        case TAXONOMY_CSV_WATCHDOG_WARNING:
          $status = 'error';
          break;
        case TAXONOMY_CSV_WATCHDOG_NOTICE:
          $status = 'warning';
          break;
        case TAXONOMY_CSV_WATCHDOG_INFO:
          $status = 'status';
          break;
      }

      drupal_set_message($processed_message_text, $status);
    }

    return _taxonomy_csv_message_get_worst_level($list_messages, 'lines');
  }
}

/**
 * Helper to display compact list of result messages.
 *
 * @param $messages_set
 *   Array of operation array of codes, except 691, 692 and 695.
 *   Message code is an integer between 000 and 999.
 * @param $result_level
 *   Optional. Level of messages to display: 'full' (default), 'infos',
 *   'notices' or 'warnings'.
 * @return
 *   Worst level (0 to 9).
 */
function _taxonomy_csv_info_result_by_message($messages_set, $result_level = 'full') {
  $list_messages = array();

  if (is_array($messages_set) && $messages_set) {
    // Prepare list of messages.
    switch ($result_level) {
      case 'full':
        // Convert [line number]['line'/serial]['msg'][message codes]
        //      to [message codes][line number].
        foreach ($messages_set as $line_number => $operation) {
          foreach ($operation as $item) {
            foreach ($item['msg'] as $message_code) {
              $list_messages[$message_code][] = $line_number;
            }
          }
        }
        break;

      case 'infos':
      case 'notices':
      case 'warnings':
        // Convert [line number][message codes]
        //      to [message codes][line number].
        foreach ($messages_set as $line_number => $operation) {
          foreach ($operation as $message_code) {
            $list_messages[$message_code][] = $line_number;
          }
        }
        break;

      default:
        return;
    }
    ksort($list_messages);

    foreach ($list_messages as $message_code => $line_numbers) {
      // Only show line level message with created, updated and unchanged terms.
      if (($message_code != 691) && ($message_code != 692) && ($message_code != 695)) {
        $processed_message_level = _taxonomy_csv_message_get_level($message_code);
        $processed_message_text  = _taxonomy_csv_info_result_text($message_code) .' '. t('Lines:') .'<br />'. implode(', ', $line_numbers) .'.';

      switch ($processed_message_level) {
        case TAXONOMY_CSV_WATCHDOG_ERROR:
        case TAXONOMY_CSV_WATCHDOG_WARNING:
          $status = 'error';
          break;
        case TAXONOMY_CSV_WATCHDOG_NOTICE:
          $status = 'warning';
          break;
        case TAXONOMY_CSV_WATCHDOG_INFO:
          $status = 'status';
          break;
      }

      drupal_set_message($processed_message_text, $status);
      }
    }

    return _taxonomy_csv_message_get_worst_level(array_keys($list_messages));
  }
}

/**
 * Helper to get text of a message with a message code.
 *
 * @param $message_code
 *   Message codes are integer between 000 and 999.
 * @return
 *   Message text string.
 */
function _taxonomy_csv_info_result_text($message_code) {
  // Static used only for performance reason.
  static $watchdog_messages;

  if (!isset($watchdog_messages)) {
    // This variables are used to simplify strings management and translation.
    $error   = ' '. t("Import process is stopped.");
    $warning = ' '. t("This line won't be processed.");
    $notice  = ' '. t("Line is processed.");

    $watchdog_messages = array(
      // Format: Level, Type of import, Serial.
        0 => t('Module error'),

      300 => t('ERROR'),
      305 => t('Error in options.'),
      306 => t('Unknown import format. Change "Source content" option.') . $error,
      307 => t('Unknown export format. Change "Export format" option.') . $error,
      310 => t("You choose to import a taxonomy by a file, but you don't set its name or its size is greater than the server's limit.") . $error,
      311 => t('Size of your file is null.') . $error,
      312 => t('Unable to write to file.') . $error,
      313 => t('Current line contains delimiter, enclosure or unprotected line ending. You need to change them if you want to import correctly a taxonomy.'),
      320 => t("Your file can't be converted to utf-8. Please install iconv, GNU recode or mbstring for PHP or convert your file to utf-8 and disable 'Enable utf-8 conversion' option.") . $error,
      321 => t('Despite your option, your file is not recognize as an UTF-8 encoded one. Convert it before submit it.') . $error,
      340 => t("Vocabulary doesn't exist."),
      352 => t("A parent tid is given, but it hasn't been imported in a previous line.") . $error,
      390 => t('No line to import. Please first check your file and file uploading, else reinstall module from a fresh release or submit an issue.') . $error,
      391 => t('No term to import. Please first check your file and file uploading, else reinstall module from a fresh release or submit an issue.') . $error,
      392 => t('Problem when caching imported term. Please first check your file and file uploading, else reinstall module from a fresh release or submit an issue.') . $error,
      399 => t("Module is not installed correctly. Please reinstall module from a fresh release or submit an issue."),

      400 => t('WARNING'),
      405 => t('Unmanaged option') . $warning,
      410 => t("Impossible to get parent of first item, because previous line has less parent(s). You may add one or more parents to current line or change lines order.") . $warning,
      430 => t('Line contains empty items.') . $warning,
      431 => t('Line contains duplicate items.') . $warning,
      433 => t("Line contains items matching term name. A term can't be synonym, related, parent or child of itself.") . $warning,
      434 => t('Line contains too many items.') . $warning,
      440 => t("Vocabulary doesn't exist. When you duplicate or import into an existing vocabulary, option 'vocabulary_id' should contains true vocabulary id.") . $warning,
      450 => t('Weight in second column is not an allowed number.') . $warning,
      451 => t('One or more items are not numbers.') . $warning,
      452 => t('A term cannot be a parent of itself.') . $warning,
      453 => t('A term has no semantic field parent.'),
      460 => t('Unknown predicate.') . $warning,
      461 => t('No subject.') . $warning,
      462 => t('No predicate.') . $warning,
      463 => t('No object.') . $warning,
      464 => t('No name.') . $warning,
      465 => t('More than three items.') . $warning,
      466 => t('Unmanaged predicate.') . $warning,
      467 => t('Each semantic field should be imported as "vocabulary" or "root_term".') . $warning,
      480 => t('No first column term to import. Empty first column is allowed only with structure or multiple terms import.') . $warning,
      481 => t('No item in second or third column.') . $warning,
      482 => t("Some items aren't present.") . $warning,
      483 => t('Term without name. Name is the only needed field.') . $warning,
      490 => t('No line to import.') . $warning,
      491 => t('No item to import.') . $warning,
      492 => t('Nothing to import.') . $warning,
      493 => t('Empty line.') . $warning,
      499 => t('Warnings have been reported on this line.'),

      500 => t('Notice'),
      501 => t('Too many items. Second and next columns will be ignored, as import choice is to ignore them.'),
      510 => t('Line contains empty items after first item to import. They will be ignored.'),
      511 => t('To change vocabulary of a term is not recommended.'),
      512 => t("Line contains items matching first column term. A term can't be related to itself and a synonym may be different to it.") .' '. t('Duplicates will be ignored.'),
      530 => t('Line contains empty items. They will be ignored.'),
      531 => t('Line contains duplicate items.') .' '. t('Duplicates will be ignored.'),
      532 => t('Line contains duplicate items.') .' '. t('Duplicates are allowed.'),
      533 => t("Line contains items matching term name. A term can't be related, parent, child or synonym to itself.") .' '. t('Duplicates will be ignored.'),
      535 => t('Line contains duplicate synonyms.') .' '. t('Duplicates will be ignored.'),
      536 => t('Line contains duplicate parents.') .' '. t('Duplicates will be ignored.'),
      537 => t('Line contains duplicate children.') .' '. t('Duplicates will be ignored.'),
      538 => t('Line contains duplicate related terms.') .' '. t('Duplicates will be ignored.'),
      541 => t('Too many items. Third and next columns will be ignored, as a term gets only one description and one weight.'),
      550 => t("No first column, but line can be processed."),
      551 => t('No parent, so it is a root term.'),
      552 => t('Term has been already imported in a previous line.'),
      553 => t('A semantic field cannot be related to terms.'),
      554 => t('A term has many parents and one is a semantic field, what is impossible.'),
      555 => t('A root term has a parent.') . $notice,
      557 => t('A term cannot be related to a semantic field'),
      558 => t('A semantic field cannot be a term synonym.'),
      559 => t('A term can have only one semantic field.'),
      561 => t('No subject.') . $notice,
      562 => t('No predicate.') . $notice,
      563 => t('No object.') . $notice,
      564 => t('Too many items. Fourth and next items will be ignored.') . $notice,
      565 => t('Some items are empty. Previous items will be used.') . $notice,
      580 => t('Be careful. This line has only one term and import choice is to replace existing items. So they will be removed.'),

      600 => t('Info'),
      605 => t('No error in options.'),
      610 => t('New vocabulary has been created.'),
      611 => t('A vocabulary has been duplicated.'),
      632 => t('Line contains duplicate items.') .' '. t('Duplicates are allowed.'),
      639 => t('Line contains empty vocabulary for related terms. They will be created in vocabulary of main term.'),
      640 => t('Vocabulary checked.'),
      662 => t('No predicate.'),
      683 => t('Use of a previous line term.'),
      685 => t('No term to process.'),
      691 => t('Saved new term.'),
      692 => t('Updated term.'),
      693 => t('Removed existing term.'),
      694 => t('Updated new term.'),
      695 => t('Unchanged term.'),
      696 => t('Empty line.'),
      697 => t('Command line.'),
      698 => t('Comment line.'),
      699 => t('Items of the line have been successfully imported.'),

      700 => t('Debug'),
      798 => t('Unreferenced debug code. Please reinstall module from a fresh release or submit an issue.'),
      799 => t('Unreferenced code.'),

      998 => t('No message.'),
      999 => t('No message.'),
    );
  }

  if (is_int($message_code) && ($message_code >= 0) && ($message_code <= 999)) {
    $message_title = intval($message_code / 100) * 100;
    $message_title = $watchdog_messages[(isset($watchdog_messages[$message_title])) ? $message_title : 700] .' : ';

    return $message_title . $watchdog_messages[(isset($watchdog_messages[$message_code])) ? $message_code : 798];
  }
  return "$watchdog_messages[799] : $message_code";
}

/**
 * @} End of "defgroup taxonomy_csv_info".
 */
