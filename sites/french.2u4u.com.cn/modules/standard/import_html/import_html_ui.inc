<?php
// $Id: import_html_ui.inc,v 1.11.4.21 2009/10/06 14:09:02 dman Exp $
/**
 * @file
 * Forms and UI functions for import_html.
 *
 * The bulk is made up of the multistep import_html_prcess_form.
 * This is made up of conditional includes of the per-stage subforms, and their
 * respctive submit handlers.
 *
 * TODO ajaxify?
 *
 * @ingroup import_html Import HTML
 * @author Dan Morrison http://coders.co.nz/
 */


module_load_include('inc', 'import_html', 'import_html_process');


///////////////////////////////////////////
// SETTINGS and PROFILES

/**
 * Display the import_html options and settings.
 *
 * Settings menu callback
 *
 * Display the default profile
 */
function import_html_admin_settings($form_state) {

  $form = array();
  // Check htmltidy is present and correct
  module_load_include('inc', 'import_html', 'coders_php_library/tidy-functions');
  $form['HTMLTidy'] = html_tidy_settings($form_state);

  // Warn about known problem with open_basedir
  if ($open_basedir = ini_get('open_basedir')) {
    $form['open_basedir']=array(
      '#value' => t("
        <p><strong>Warning:</strong>
        This server has open_basedir restrictions set [%open_basedir].
        It's possible that external source directories may be inaccessible,
        or that access to htmlTidy may be restricted.
        <a href='%help_url'>Check the help for more details</a>.</p>
      ",
      array(
        '%open_basedir' => $open_basedir,
        '%help_url' => url('admin/help/import_html', array('fragment' => 'open_basedir')))
      )
    );
  }

  // Warn, fix a known problem with large batch jobs.
  import_html_check_max_allowed_packet();

  $profile_id = import_html_current_profile_id();
  $form['default_profile'] = import_html_profile_settings($form_state, $profile_id);
  $form['#submit'][] = 'import_html_profile_settings_submit';
  $form['#validate'][] = 'import_html_profile_settings_validate';


  $form['import_html_proceed'] = array(
    '#type' => 'submit',
    '#value' => t("Proceed to import"),
    '#submit' => array('import_html_goto_process'),
    '#prefix' => '<br/>',
    #'#attributes' => array('style' => 'font-size:2em;'),
    '#attributes' => array('style' => 'font-size:2em; height:2.4em; margin-top:0em'),
  );

  // Links to other profiles
  $form['other_profiles'] = array(
    '#type' => 'markup',
    '#value' => '<h3>'. t('Other Profiles:') .'</h3>'. import_html_profiles_page(),
  );

  return $form;
}

/**
 * Small submit handler to redirect to the process form - just so we get a
 * button
 */
function import_html_goto_process() {
  drupal_goto(IMPORT_HTML_ADMIN_PATH .'/import_site');
}

/**
 * This function attempts to analyse and repair your MySQL config.
 * It is highly likely the ability to do this will be restricted on shared
 * hosts, but try anyway.
 *
 * This change will go away next time the MySQL gets reset, but that's OK.
 */
function import_html_check_max_allowed_packet() {
  // Warn about known problem with max_allowed_packet

  $sql = "SHOW VARIABLES WHERE Variable_name = 'max_allowed_packet' ";
  $result = @db_query($sql);
  if ($row = db_fetch_array($result)) {
    if ($row['Value'] >= (IMPORT_HTML_REQUIRED_MAX_ALLOWED_PACKET * 1024 *1024)) {
      return TRUE;
    }
  }

  // Try to set it (I don't know what permissions are required to allow this, but it worked for me.
  $result = @db_query("SET GLOBAL max_allowed_packet = %d * 1024 * 1024", IMPORT_HTML_REQUIRED_MAX_ALLOWED_PACKET);
  // Check again (may have failed)
  $result = @db_query($sql);
  if ($row = db_fetch_array($result)) {
    if ($row['Value'] >= (IMPORT_HTML_REQUIRED_MAX_ALLOWED_PACKET * 1024 *1024)) {
      drupal_set_message(t("Adjusted max_allowed_packet on this MySQL server. Large batches should be OK now."));
      return TRUE;
    }
  }

  drupal_set_message(t("
    <p><strong>Warning:</strong> This server has the
    database max_allowed_packet limited to %max_allowed_packet .
    Due to a limitation of the batch process, this is likely to cause
    problems on huge imports (several thousands of pages at once).<br/>
    If you <em>can</em>, please increase it in your database config (my.cnf).
    At least %required_allowed_packet is recommmended.
    See !doc_link,
    If you can't, then set the advanced option '<b>Recursion behaviour</b>' to
    '<b>recurse after</b>' and try to import your site only a few thousand
    pages at a time.</p>",
    array(
      '%max_allowed_packet' => format_size($row['Value']),
      '%required_allowed_packet' => format_size(IMPORT_HTML_REQUIRED_MAX_ALLOWED_PACKET * 1024 *1024),
      '!doc_link' => l('MySQL docs', 'http://dev.mysql.com/doc/refman/5.1/en/packet-too-large.html'),
    )
  ), 'warning');
  return FALSE;
}


/**
 * Page to display a list of current profiles, or to edit a named one
 */
function import_html_profiles_page($profile_id = NULL) {
  if (!$profile_id) {
    // Just return links to all other profiles
    $import_html_profiles = variable_get('import_html_profiles', array());
    $links = array();
    foreach ($import_html_profiles as $profile_id => $profile) {
      $links[] = array(
        'title' => $profile_id,
        'href' => IMPORT_HTML_ADMIN_PATH .'/profile/'. $profile_id,
      );
    }
    $links[] = array(
      'title' => t('New'),
      'href' => IMPORT_HTML_ADMIN_PATH .'/profile/'.'new',
    );
    return theme('links', $links);
  }
  // Else, render this given profile
  return drupal_get_form('import_html_profile_settings', $profile_id);
}


/**
 * An import_html profile settings form.
 *
 * TODO get the contrib modules to provide their own settings forms via hook
 *
 */
function import_html_profile_settings(&$form_state, $profile_id) {

  $profile = import_html_profile($profile_id);
  if (! $profile) {
    // Fill in defaults (should only be needed first time, if that
    $profile = import_html_profile_defaults();
  }

  $form = array();
  if ($profile_id != 'new') {
    $form['summary'] = array('#value' => import_html_profile_summary($profile));
  }
  $form['profile_id'] = array(
    '#title' => t("Profile ID"),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => $profile_id,
  );
  if ($profile_id != 'new') {
    $form['profile_id']['#default_value'] = $profile_id;
    // It used to be that disabling this worked.
    // Now doing so messes with validations
    $form['profile_id']['#disabled'] = TRUE;
    $form['profile_id']['#required'] = FALSE;
  }

  $form['extraction'] = array(
    '#type' => 'fieldset',
    '#title' => t('Import and Content Analysis Options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['extraction'][] = array(
    '#value' => '<p>'. t("How the content is extracted from the source documents.") .'</p>',
  );

  // This is abstracted so it can be re-used in other places (wrapper.module)
  $form['extraction']['translation_template'] = import_html_template_selector($profile['translation_template']);

  $form['extraction']['content_tag_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Content Tag ID'),
    '#default_value' => $profile['content_tag_id'],
    '#size' => 20,
    '#maxlength' => 100,
    '#description' => t("
      If your source document is structured well enough to have the actual
      content in a named div or something (&lt;div id='main'&gt;...content )
      what is that name?
      <br/>
      The default template will search for 'main', 'copy', 'story', 'text', and
      'bodyCopy'. If your input uses another label, set it here.
      <br/>
      This only takes effect if the selected XSL template uses this parameter,
      and may be overridden or ignored by custom templates.
    "),
  );

  $form['extraction']['content_type'] = array(
    '#type' => 'select',
    '#title' => t("Node Type for new pages"),
    '#options' => node_get_types('names'),
    '#default_value' => $profile['content_type'],
    '#description' => t("
      Note, if importing into a CCK content type, or anything that doesn't
      store its body in the node 'body', some customization will have to be
      done on your XSL template.
    ")
  );

  // Just a select, the filter radios are much to bulky for here.
  $form['extraction']['preferred_filter'] = array(
    '#type' => 'select',
    '#title' => t("Default Input Filter"),
    '#default_value' => $profile['preferred_filter'],
    '#options' => import_html_get_preferred_filter(TRUE),
    '#description' => t("
      After importing HTML, the end result may still have a standard Drupal
      filter applied to it internally.
      Use 'Unfiltered HTML' if you want the content verbatim.
      'Full HTML' <em>may</em> be correct here, although it may create
      unwanted hard breaks if the input is already word-wrapped internally.
      Modify only if you want to strip the source right down, execute php,
      or do other filter magic on the input.
    "),
  );

  $form['extraction']['default_document'] = array(
    '#type' => 'textfield',
    '#title' => t("Default Document"),
    '#default_value' => $profile['default_document'],
    '#size' => 40,
    '#maxlength' => 40,
    '#description' => t("
      What is the default document name for pages served in directories on
      the current site (index.htm, index.html, default.asp, index.php)?
      When documents of this name are imported, they can be given both
      the old name (my/dir/index.htm) and a friendly directory name (my/dir) .
      When the navigation menu is built, this file is served when the
      directory link is clicked.
      This should end up emulating normal website navigation behaviour.
      <br/>
      May be a comma-separated list, the first option is the default.
    "),
  );


  $form['extraction']['file_exclusions'] = array(
    '#type' => 'textarea',
    '#title' => t("File Exclusion Pattern"),
    '#default_value' => $profile['file_exclusions'],
    '#description' => t("
      When listing files to import, some sources should probably be left behind.
      Enter a set of regular expressions to check against the file <b>path</b>
      that should <em>not</em> show up on the import screen.
      <ul><li>
      <code>^_</code> = begins with '_'
      </li><li>
      <code>/_</code> = in a dir that begins with '_'
      </li><li>
      <code>CVS/?</code> = called CVS, or has CVS in the path
      </li></ul>
    "),
  );

  $form['extraction']['strip_tables'] = array(
    '#type' => 'checkbox',
    '#title' => t("Remove table markup"),
    '#return_value' => TRUE,
    '#default_value' => $profile['strip_tables'],
    '#description' => t("
      A common task when updating old sites is removing the
      legacy formatting tables. While we are going through the
      pages, this process can do it all for you.
      Beware - enabling this will remove ALL tables, so don't
      try it if there are genuine data tables you wish to retain!
    "),
  );
  $form['extraction']['strip_scripts'] = array(
    '#type' => 'checkbox',
    '#title' => t("Remove old javascripts"),
    '#return_value' => TRUE,
    '#default_value' => $profile['strip_scripts'],
    '#description' => t("
      There are many reasons why importing old inline javascripts
      may be a bad idea. Doing so will remove some functionality
      but also clean up some crap. Up to you.
    "),
  );
  $form['extraction']['force_tidy'] = array(
    '#type' => 'checkbox',
    '#title' => t("Force HTML Tidy-up"),
    '#return_value' => TRUE,
    '#default_value' => $profile['force_tidy'],
    '#description' => t("
      Run HTML Tidy with all strict options over the input before
      parsing it as XML. Normally you want this on BUT turn it off
      if trying to read from non-HTML sources (like arbitrary XML)
      or it will mutilate it.
      <br/>
      Instead of using HTML input, you can feed in any <b>valid</b> XML
      and use XSL template to massage it into simple XHTML.
      But in that case disable this option and do NOT use HTML tidy.
    "),
  );

  $form['replication'] = array(
    '#type' => 'fieldset',
    '#title' => t("Replication Options"),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['replication'][] = array(
    '#value' => '<p>'. t("How and where the imported content is reproduced on this site.") .'</p>',
  );

  if (!module_exists('path')) {
    drupal_set_message(t("The <b>path</b> module is not enabled! If you try to import pages without paths, I can do it, but links won't work and you'll find it hard to find the pages again.'"), 'error');
  }

  $form['replication']['trim_suffixes'] = array(
    '#type' => 'checkbox',
    '#title' => t("Trim Suffixes"),
    '#return_value' => TRUE,
    '#default_value' => $profile['trim_suffixes'],
    '#description' => t("
      When importing files, new url_aliases will be generated based on the
      old path. Optionally, the new primary alias can have the suffix
      chopped of. So <code>old/path/file.htm</code> wil be accessed as just
      <code>old/path/file</code> and <code>old/section/index.htm</code>
      will become <code>old/section</code>.
      Uncheck this if you do NOT want this tidy behaviour.
      <br/>Note, this aliasing is needed to detect when an import is
      <em>replacing</em> a previously imported page. Disabling it may
      cause you to end up with duplicates if importing the same file again.
      <br/>This just defines the name given to the page, it does not
      automatically update any links <em>to</em> the page (see below) .
    "),
  );

  $form['replication']['legacy_aliases'] = array(
    '#type' => 'checkbox',
    '#title' => t("Legacy Aliases"),
    '#return_value' => TRUE,
    '#default_value' => $profile['legacy_aliases'],
    '#description' => t("
      Optionally, a secondary alias can be made that DOES have the old
      full suffix. This supports old links and hrefs.
      <b>The new node may end up with two aliases</b> (thats OK) but the tidy
      one will be used internally by default.
      Uncheck this if you do NOT want old URL support.
      <br/>
      These two options are independant of each other. If both are off
      the new page will have no url_alias.
    "),
  );

  $form['replication']['relink_files'] = array(
    '#type' => 'checkbox',
    '#title' => t("Try to Relink Files by discarding suffixes"),
    '#return_value' => TRUE,
    '#default_value' => $profile['relink_files'],
    '#description' => t("
      <b>If</b> you choose not to support the Legacy Aliases suffixes
      on your new pages, <em>existing embedded links to those pages will break</em>.
      This includes inline links from within the content we are importing.
      <br/>If a page linked to /home/about.htm and you have renamed it
      to home/about, without legacy support, the old link will be broken.
      This tool is a batch job process, not an entire site spider and
      relinker.
      <br/>
      <b>But</b> if you understand exactly what is going on,
      you can choose to try and rewrite all local links to their shortname
      equivalent (basically dropping off the suffixes of linked files)
      during import.
      This will convert any existing <code>href=\"local/path/file.htm\"</code>
      into just <code>href=\"local/path/file\"</code>. Use with care, but
      this option plus \"Trim Suffixes\" should be able to work together to
      rename all files. You\'ll want to run a link checker afterwards!
    "),
  );

  $form['replication']['allow_bad_urls'] = array(
    '#type' => 'checkbox',
    '#title' => t("Allow bad URLs and filenames"),
    '#return_value' => TRUE,
    '#default_value' => $profile['allow_bad_urls'],
    '#description' => t("
      It's bad mojo to have spaces or non-alphanumeric characters
      in your filenames and in your URLs. Normally I try to fix this
      by replacing potentially damaging characters with an underscore.
      If, however you have to support legacy stuff like
      'Random filename #3 - & about what?.pdf' then we can try to leave them alone.
      May not always work the way you expect.
    "),
  );

  $form['replication']['file_storage_path'] = array(
    '#type' => 'textfield',
    '#title' => t("Extra File Storage Path"),
    '#default_value' => $profile['file_storage_path'],
    '#description' => t("
      Where, beneath siteroot, should extra imported <strong>files</strong>
      be stored. Images and suchlike will be put into a heirachy mirroring
      their old location, but all under this directory.
      <br/>
      Effectively, this moves file storage towards the Drupal CMS way of
      storing user files, although it does not enter them as 'attachments'.
    "),
    '#after_build' => array('system_check_directory'), // this works for the core, try it myself
    // beware - system_check_directory() actually silently modifies the value and strips the training slash
  );
  $form['replication']['rewrite_links'] = array(
    '#type' => 'checkbox',
    '#title' => t("Relink references to resources to the new file storage location"),
    '#return_value' => TRUE,
    '#default_value' => $profile['rewrite_links'],
    '#description' => t("
      As the actual files are being stored elsewhere, the HTML links need to be
      rewritten to allow for that. This should be on by default.
      Turn off only if you are intending to re-create a
      messy site with files in old places and have set the file storage path to blank.
      See the transformation file
      <code>rewrite_href_and_src.xsl</code> for fine-tuning if there is trouble.
      <small>Only relative and site-relative links are rewritten.
      Hard-coded, fully-justified (external) URLS are not messed with,
      even if they used to resolve to the same host.</small>
    ")
  );

  $form['replication']['import_site_prefix'] = array(
    '#type' => 'textfield',
    '#title' => t("Import Site Prefix"),
    '#default_value' => ensure_trailing_slash($profile['import_site_prefix']),
    '#size' => 20,
    '#maxlength' => 100,
    '#description' => t("
      Where, beneath siteroot, should extra imported <strong>pages</strong>
      <em>appear to be</em> served from?
      This is a prefix that is applied to the generated URL-aliases.
      <br/>
      If you wish to keep the imported
      pages separate from the main site, setting this value to look like a
      subdirectory will make the imported site act like it's in a subsection.
      Otherwise leave it blank and new page URLs will be added under the top
      level navigation.
    "),
  );

  $vocabs = taxonomy_get_vocabularies();
  $freetagging_vocabs = array(0 => t('<none>'));
  foreach ($vocabs as $vid => $vocab) {
    if ($vocab->tags) {
      $freetagging_vocabs[$vid] = $vocab->name;
    }
  }

  $form['replication']['freetag_vocab'] = array(
    '#title' => t('Absorb keywords as tags'),
    '#type' => 'select',
    '#options' => $freetagging_vocabs,
    '#default_value' => $profile['freetag_vocab'],
    '#description' => t("
       If chosen, any <b>meta keywords</b> or <b>dc:Subject</b> tags
       found in the source will be added as terms in the given vocabulary.
       Works best with <em>freetagging vocabularies</em> that are associated
       with the import node type.
    "),
  );

  // Even more settings. These ones are able to be overridden during the process also,
  // so they are often slightly more transient preferences
  $form['replication']['subsettings'] = import_html_subsettings_form($profile);

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t("Advanced Import Tuning"),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['advanced']["help"] = array(
   '#value' => '<p>'. t("How to handle problems when importing") .'</p>',
  );

  $form['advanced']['handle_duplicates'] = array(
    '#type' => 'select',
    '#title' => t("Duplicate Handling"),
    '#default_value' => $profile['handle_duplicates'],
    '#options' => array(IMPORT_HTML_MERGE => 'overwrite/merge' , IMPORT_HTML_SKIP => 'skip'),
    '#description' => t("
      If attempting to import a file into a path that already exists
      in the system (such as by repeating an import process), do what?
    "),
  );

  $form['advanced']['handle_no_title'] = array(
    '#type' => 'select',
    '#title' => t("No Title"),
    '#default_value' => $profile['handle_no_title'],
    '#options' => array(
      IMPORT_HTML_GUESS => 'use the document path',
      IMPORT_HTML_SKIP => 'skip, do not import',
      IMPORT_HTML_DEFAULT => 'set to a placeholder value'
    ),
    '#description' => t("
      If parsing the input document fails to return any title at all, do what?"
    ),
  );

  $form['advanced']['recursion_behaviour'] = array(
    '#type' => 'select',
    '#title' => t("Recursion behaviour"),
    '#default_value' => $profile['recursion_behaviour'],
    '#options' => array(
      IMPORT_HTML_GLOB_BEFORE => IMPORT_HTML_GLOB_BEFORE,
      IMPORT_HTML_RECURSE_AFTER => IMPORT_HTML_RECURSE_AFTER,
    ),
    '#description' => t("
      Very advanced option for mega-sites and batch processes.
      <br/>
      When selecting subdirectories, and there are too many items to display in the UI,
      you can choose to import everything under a given path.
      When using this option, we can either scan those directories <em>before</em>
      or <em>during</em> the process.
      <br/>
      Scanning and queuing everything first is more predictable, but may result in
      a huge list being loaded into memory first.
      <br/>
      Noting the directories to recurse into and only scanning them when it's time
      <em>may</em> be easier on the memory for gigantic sites. The batch job will
      keep extending until it is done.
      <br/>I don't know which is better. The first is easy, but I'd recommend the second for
      tens of thousands of pages.
    "),
  );

  $form['advanced']['debug_level'] = array(
    '#type' => 'select',
    '#title' => t("Debug Level"),
    '#default_value' => $profile['debug_level'],
    '#options' => array(0, 1, 2, 3),
    '#description' => t("
      To trace and test the import process, increasing the debug level here
      will produce a huge amount of process tracing,
      including dumps of the raw versions of the input files
      as it gets massaged into the end result.
      <br/>
      Note that enabling debug can itself introduce errors as the trace logs
      and pretty-printer can cause memory overages.
    "),
  );
  $form['advanced']['keep_temp_files'] = array(
    '#type' => 'checkbox',
    '#title' => t("Keep Temp Files"),
    '#return_value' => TRUE,
    '#default_value' => $profile['keep_temp_files'],
    '#description' => t("
      When processing, files are copied temporarily into a temp directory.
      These are usually deleted immediately after tidying and parsing,
      but if you want to trace problems, enable this option and check the
      files/import directory.
    "),
  );


  $form['advanced']['import_html_other_logic'] = array(
    '#value' => t("<p>
       Other logic, like whether to use the TITLE tag or the H1 tag found in a
       file is defined in the XSL template, which you can tune yourself.
       </p>"
    ),
  );

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save Settings'),
  );
  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete Profile'),
    '#submit' => array('import_html_form_settings_delete'),
  );
//  $form['#redirect'] = IMPORT_HTML_ADMIN_PATH .'/profile';

  return $form;
}

/**
 * Returns a text summary of all the current settings
 */
function import_html_profile_summary($profile) {
  $dest_file_root = url($profile['file_storage_path'], array('absolute' => TRUE));
  $dest_virtual_path = url($profile['import_site_prefix'], array('absolute' => TRUE));

  // D6 Menus are tricky
  $menu_parent = menu_get_item($profile['menu_parent_id']);
  list($menu_name, $mlid) = explode(':', $profile['menu_parent_id'] );
  if ($mlid) {
    $menu = menu_link_load($mlid);
    // TODO
  }
  else {
    $menu = menu_load($menu_name);
    $menu_title = $menu['title'];
  }

  if (function_exists('dpm') && ($profile['debug_level'] > 0)) {
    dpm($profile);
  }

  $import_categories = array();
  foreach ((array)$profile['import_category'] as $tid) {
    if ($term = taxonomy_get_term($tid)) {
      $import_categories[$tid] = $term->name;
    }
  }


  $substitutions = array(
      '%import_html_source_siteroot' => variable_get('import_html_source_siteroot', "/var/www/htdocs/") ,
      '%import_html_current_subsection' => variable_get('import_html_current_subsection', ""),
      '!dest_virtual_path' => l($dest_virtual_path, $dest_virtual_path ),
      '!dest_file_root' => l($dest_file_root, $dest_file_root),
      '!settings_url' => url(IMPORT_HTML_ADMIN_PATH .'/settings'),
      '!translation_template' => l(basename($profile['translation_template']), $profile['translation_template']),
      '%default_document' => $profile['default_document'],
      '%create_menus' => $profile['create_menus']?'will':'will not',
      '%menu_parent_name' => $menu_title,
      '%content_type' => $profile['content_type'],
      '%import_site_prefix' => $profile['import_site_prefix'],
      '%import_status' => $profile['import_status']?'will':'will not',
      '%import_promote' => $profile['import_promote']?'will':'will not',
      '%import_categories' => join($import_categories, ', '),
    );

  $summary = array();
  $summary[] = t("
      Source files will be scanned from
      <br/><code>%import_html_source_siteroot%import_html_current_subsection</code>
    ", $substitutions);
  $summary[] = t("
    Pages will be re-created underneath
    <br/><code>!dest_virtual_path%import_html_current_subsection</code>
    <br> as <strong>%content_type</strong> type nodes.", $substitutions);

  $summary[] = t("
    Import template for semantic data extraction is <code>!translation_template</code>
    ", $substitutions);

  $summary[] = $profile['rewrite_links']
    ? t("Links found within the sources <b>will</b> be rewritten to try and allow for the new paths")
    : t("Links from within the imported pages will <b>not</b> be rewritten, and may get lost.");

  if ($profile['strip_scripts'])
    $summary[] = t("All script tags found in the source will be discarded");
  else
    $summary[] = t("Script tags in the source will be left as-is (likely to break)");

  $summary[] = t("Non-page files imported will be saved beneath <code>!dest_file_root %import_html_current_subsection</code> ", $substitutions);

  $summary[] = t("Default document <code>%default_document</code> will be used to represent folders.", $substitutions);

  $summary[] = t("New pages %create_menus be added to the menu underneath %menu_parent_name.", $substitutions);
  if ($profile['menu_parent_id'] == 1) {
    $summary[] = t("<strong>Warning:</strong> The parent menu is set to the default 'Navigation' menu. This is OK, but will place new pages directly into the top of your menu which can be messy. You may instead wish to create a unique menu holder or menu item and use that as the import menu root instead. 'Primary Links' is also a good choice.", $substitutions);
  }
  $summary[] = t("Imported pages %import_status be published by default and %import_promote be promoted to the front page.", $substitutions);

  if (! empty($import_categories)) {
    $summary[] = t("ALL imported pages will be tagged with the terms: (%import_categories)", $substitutions);
  }

  $output = t("<p>These preferences and more are changeable <a href='!settings_url'>in the settings</a>.</p>", $substitutions);

  $title = t('%profile_label import profile:', array('%profile_label' => $profile['profile_id']));
  return theme('box', $title, theme("item_list", $summary) . $output );
}



/**
 * Returns a widget for selecting an import template from the ones provided by
 * import_html
 */
function import_html_template_selector($current_template) {
    $templates = file_scan_directory(drupal_get_path('module', 'import_html') .'/templates', '.xsl', array('.', '..'), 0, TRUE);
    $options = array_map(
      create_function('$o', 'return $o->name;'),
      $templates
    );
    if (! $current_template) {
      $current_template = drupal_get_path('module', 'import_html') ."/templates/html2simplehtml.xsl";
    }

    return array(
      '#type'    => 'select',
      '#title'   => t('Import template to use'),
      '#options' => $options,
      '#default_value' => $current_template,
      '#prefix'  => '<div id="import-template-selector" class="sub-option">',
      '#suffix'  => '</div>',
      '#description' => t("
        This file must be a valid XSL Template that can convert from your source
        HTML to the simplified semantic XHTML schema (see docs and examples).
        Templates should be placed in the import_html module <code>/templates/</code> directory.
        <br/>
        Sample import templates can be found in %module_dir.
      ", array('%module_dir' => drupal_get_path('module', 'import_html') .'/templates' )),
    );
}

/**
 * FAPI callback
 */
function import_html_profile_settings_validate($form, &$form_state) {
  // Initializing the XSL doc just to check is inefficient, but this is just a config screen.
  if (!_import_html_get_xsl_doc($form_state['values']['translation_template'])) {
    form_set_error("import_html_translation_template", "XSL File unable to be parsed");
  }
}

/**
 * FAPI callback
 */
function import_html_profile_settings_submit($form, &$form_state) {
  if ($form_state['values']['profile_id'] == 'new') {
    drupal_set_message(t('Not saving details called "new"', array()));
    return;
  }
  // trivial tidy-up, not worth complaining about
  $form_state['values']['file_storage_path'] = ensure_trailing_slash($form_state['values']['file_storage_path']);

  // Save only the variables I care about
  $keys = array_keys(import_html_profile_defaults());
  foreach ($keys as $key) {
    // It's possible that some values are not relevant if modules (path/taxonomy) are not enabled
    if ( isset($form_state['values'][$key]) ) {
      $profile[$key] = $form_state['values'][$key];
    }
  }

  // Save it as a blob
  import_html_profile($form_state['values']['profile_id'], $profile);
  drupal_set_message(t('%profile_id Profile Updated', array('%profile_id' => $form_state['values']['profile_id'])));
}

/**
 * Form button handler
 */
function import_html_profile_settings_delete($form, &$form_state) {
  import_html_profile($form_state['values']['profile_id'], FALSE);
  drupal_set_message(t('%profile_id Profile Deleted', array('%profile_id' => $form_state['values']['profile_id'])));
  return;
}


/**
 * This is a subset of the general settings - these options are also reproduced
 * on later action pages where they can be tweaked closer to the action. So
 * the form is saved in a block of its own.
 *
 * These options may be a little different occur per-pass, eg if importing
 * different directories within a global profile.
 */
function import_html_subsettings_form($profile) {
  $form=array();

  // Taxonomy box:
  // note, this doesn't show up for vocabs with only one term. Sorta annoying'
  if ($taxonomy = module_invoke('taxonomy', 'form_all', 1)) {
    $form['import_category'] = array(
      '#type' => 'select',
      '#title' => t('Add imported nodes to the following category(s)'),
      '#default_value' => $profile['import_category'],
      '#prefix' => '<div class="criterion">',
      '#size' => 10,
      '#suffix' => '</div>',
      '#options' => $taxonomy,
      '#multiple' => TRUE,
    );
  }
  else {
    $form['import_category'] = array(
      '#value' => t("<p><b>Taxonomy:</b> There are no vocabularies available to tag the imported content with. <a href='!add_vocab'>Create one</a> if you like.</p>", array('!add_vocab' => url('admin/content/taxonomy'))),
    );
  }

  // Status selection:
  $form['import_status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Imported nodes are Published?'),
    '#default_value' => $profile['import_status'],
    '#description' => t("
      Sets the node status.  Check to have nodes published.
    "),
  );

  // promote selection:  added by L0rne
  $form['import_promote'] = array(
    '#type' => 'checkbox',
    '#title' => t('Imported Nodes are Promoted to front page?'),
    '#default_value' => $profile['import_promote'],
    '#description' => t("
      Sets whether or not imported nodes are promoted to the front page.
    "),
  );

  global $user;
  $form['import_user'] = array(
    '#type' => 'textfield',
    '#title' => t('User to create nodes as'),
    '#maxlength' => 60,
    '#autocomplete_path' => 'user/autocomplete',
    '#default_value' => $profile['import_user'],
  );

  if (module_exists('menu')) {
    $form["create_menus"] = array(
      '#type' => 'checkbox',
      '#title' => t("Add each page to menu"),
      '#return_value' => TRUE,
      '#default_value' => $profile['create_menus'],
      '#description' => t( 'requires menu.module'. (module_exists('menu')?'(installed)':' (Which is NOT available)')),
    );
    // Retrieve a select list of the entire menu tree
    $menu_parent_options = menu_parent_options(menu_get_menus(), array('mlid' => 0));

    $form["menu_parent_id"] = array(
      '#type' => 'select',
      '#title' => t('Menu Parent'),
      '#default_value' => $profile['menu_parent_id'],
      '#options' => $menu_parent_options,
      '#description' => t("
        Where in the menu system should the new heirachy
        of pages be built?
        <br/>
        If you leave this as 'Navigation' the new pages
        may start to collide with your Admin menus,
        so consider making a placeholder menu first.
      "),
    );
  }
  else {
    $form["create_menus"] = array(
      '#type' => 'markup',
      '#value' => t("
        Menu is not enabled, so the heirachical structure
        of the imported files will NOT be retained.
      "),
      '#description' => t("
        <p>If you enable the menu.module,
        the structure of the imported files can be imported as well.</p>
        <p>Note, that in order for this to work, all the apparent parents
        of a page must have menu items as well. If importing a subsection,
        Placeholders for the higher sections will be created, but they may be
        hollow shells.</p>
      ")
    );
  }
  return $form;
}


function import_html_subsettings_submit($form, &$form_state) {
  // Handle incidental settings when submitted from other pages - like during the
  // import process.

  $profile = import_html_profile($form_state['values']['profile_id']);
  $variables = array(
    'import_html_source_siteroot',
    'import_html_current_subsection',
    'import_site_prefix',
    'import_category',
    'import_status',
    'import_promote',
    'import_user',
    'create_menus',
    'menu_parent_id',
  );
  foreach ($variables as $v) {
   if (isset($form_state['values'][$v]) && ($profile[$v] != $form_state['values'][$v])) {
    $profile[$v] = $form_state['values'][$v];
   }
  }

  import_html_profile($form_state['values']['profile_id'] , $profile);
}

function import_html_profile_switcher_submit($form, &$form_state) {
  import_html_current_profile_id($form_state['values']['profile_id']);
}



///////////////////////////////////////////
// IMPORT PROCESS
///////////////////////////////////////////

/**
 * A multi-part 'wizard' style form.
 * Step 1 - intro and set parameters
 * Step 2 - display files and select them
 * - submit that to run the import
 * Step 3 - display summary of results.
 *
 * Parameters and return as per usual with FAPI
 */
function import_html_process_form(&$form_state) {
  $form = array();
  $steps = 3;

  // Initialize multistep
  // D6 multistep example from
  // http://www.andrewyager.com/content/view/51/27/
  if (empty($form_state['storage']['step'])) {
    // we are coming in without a step, so default to step 1
    $form_state['storage']['step'] = 1;
  }

  $form['title'] = array('#value' => t('<h3>Step %step of %steps</h3>', array('%step' => $form_state['storage']['step'], '%steps' => $steps)));

  $profile_id = isset($form_state['values']['profile_id']) ? $form_state['values']['profile_id'] : import_html_current_profile_id();
  $profile = import_html_profile($profile_id);
  // Display this on every page - help knowing just what's happening
  $form['profile_info'] = array(
    '#value' => '<h4>'. t("Using %profile_id profile", array('%profile_id' => $profile_id)) .'</h4>',
  );
  $form['profile_id'] = array('#type' => 'hidden', '#default_value' => $profile_id);


  // Note the current context and state info as the rendering functiona and submit process needs to know
  if (isset($form_state['values'])) {
    $form['source_siteroot'] = array( '#type' => 'hidden', '#default_value' => $form_state['values']['source_siteroot']);
    $form['current_subsection'] = array( '#type' => 'hidden', '#default_value' => $form_state['values']['current_subsection']);
  }

/*
@dpm(array(
  'Asked for the process form. profile is ' => $profile,
  'Current step is ' => $form_state['storage']['step'],
  'Current submission is ' => $form_state['values'],
  'Current POST is ' => $_POST,
  'Last time we were here, saved submission was ' => $form_state['storage']['values'][ $form_state['storage']['step'] ],
  )
);
*/

  // retrieve the last submitted values from storage to re-populate this form
  if ( isset($form_state['storage']['values'][ $form_state['storage']['step'] ])) {
    $form_state['values'] = array_merge($form_state['storage']['values'][ $form_state['storage']['step'] ], $form_state['values']);
  }

  if (! isset($profile['source_siteroot']) ) {
    $profile['source_siteroot'] = variable_get('import_html_source_siteroot', '/var/www/old');
  }
  if (! isset($profile['current_subsection']) ) {
    $profile['current_subsection'] = variable_get('import_html_current_subsection', '');
  }

  switch ($form_state['storage']['step']) {

    case 1:
      // Display current options and path prior to filesystem scan
      $form['step1'] = import_html_select_source_form($form_state, $profile);

      $import_html_profiles = variable_get('import_html_profiles', array());
      $profile_options = array_combine(array_keys($import_html_profiles), array_keys($import_html_profiles));
      $form['profile_id'] = array(
        '#type' => 'select',
        '#title' => 'Import settings profile',
        '#options' => $profile_options,
        '#default_value' => $profile_id,
      );
      $form['#submit'][] = 'import_html_profile_switcher_submit';


      // Also allow last-minute or transient profile settings adjustments
      $form['import_html_settings'] = import_html_subsettings_form($profile);
      $form['import_html_settings']['#type'] = 'fieldset';
      $form['import_html_settings']['#title'] = t("More Settings");
      $form['import_html_settings']['#collapsible'] = TRUE;
      $form['import_html_settings']['#collapsed'] = TRUE;

      $form['summary'] = array('#value' => import_html_profile_summary($profile) ) ;

      if (!module_exists('path')) {
        drupal_set_message(t("The <b>path</b> module is not enabled! If you try to import pages without paths, I can do it, but links won't work and you'll find it hard to find the pages again.'"), 'warning');
      }
    break;

    case 2:

      // Create the file selection form - list all files
      $form['step2'] = import_html_list_filesystem($form_state['values'], $profile);

      $form['action'] = array(
        '#value' => '<p>'. t("Either run the import now, or queue the selected files for processing later - may be required for large jobs") .'</p>',
      );

      // If these buttons are to do their thing and ALSO make an effect on the multistep
      // and proceed, they need to have both behaviours attached as #submit actions.
      $form['import'] = array(
        '#type' => 'submit',
        '#value' => t('Import Files'),
        '#submit' => array(
          'import_html_import_files_submit',
          'import_html_process_form_next_button_submit',
        )
      );
      $form['batch'] = array(
        '#type' => 'submit',
        '#value' => t('Batch Process Files'),
        '#submit' => array(
          'import_html_batch_import_files_submit',
          'import_html_process_form_next_button_submit'
        ),
      );

    break;

    case 3:
      // Files have been selected and submitted.

      // To keep the state information fresh, (forward/back testing)
      // Make a quiet note of the recently selected checkboxes
      $import_files = (array)$form_state['values']['file_rel_path'];
      $selected_files = array_filter($import_files);
      $form['file_rel_path'] = array(
        '#type' => 'item',
        '#tree' => TRUE,
      );
      foreach ($selected_files as $selected) {
        $form['file_rel_path'][$selected] = array(
          '#type' => 'hidden',
          '#value' => $selected,
        );
      }

      // Display recent logged results
      $form['results'] = array(
        '#value' => import_html_results(WATCHDOG_NOTICE),
      );

    break;
  }


  // Show step buttons.
  if ($form_state['storage']['step'] > 1) {
    $form['previous'] = array(
      '#type' => 'submit',
      '#value' => t('<< Previous'),
      '#submit' => array('import_html_process_form_previous_button_submit'),
    );
  }
  if ($form_state['storage']['step'] < $steps-1) {
    $form['next'] = array(
      '#type' => 'submit',
      '#value' => t('Next >>'),
      '#submit' => array('import_html_process_form_next_button_submit'),
    );
  }
  return $form;

}

/**
 * Handle each step of the import process
 * - by passing the form submit down to per-page handlers
 * , actually subforms with their own identity.
 */
function import_html_process_form_validate($form, &$form_state) {
  // Massage the input to be forgiving and figure what we really mean
  // Note these transient settings as variables.
  // It's more convenient if they are remembered like this
  if ( isset($form_state['values']['source_siteroot']) ) {
    $form_state['values']['source_siteroot'] = ensure_trailing_slash(foreslash($form_state['values']['source_siteroot'])); // win32 safe.
    variable_set('import_html_source_siteroot', $form_state['values']['source_siteroot']);
  }
  if ( isset($form_state['values']['current_subsection']) ) {
    $current_subsection = ensure_trailing_slash($form_state['values']['current_subsection']);
    $current_subsection = ltrim($current_subsection, '/');
    $form_state['values']['current_subsection'] = $current_subsection;
    variable_set('import_html_current_subsection', $current_subsection);
  }
  // Other actual validation is handled by individual #element_validate calls
  // @see import_html_source_siteroot_validate()
}

/**
 * This function probably never runs. Remove it when all is well with the
 * multistep.
 *
 * Action buttons within import_html_process_form have their own handlers!
 *
 * The actual process that runs at the end of this form is
 * @see import_html_import_files_submit()
 */
function import_html_process_form_submit($form, &$form_state) {
  // I don't do anything useful.
}

/**
 * Button press handler function.
 * Stand-alone way of working with a multistep form.
 */
function import_html_process_form_next_button_submit($form, &$form_state) {
  // Multistep: save the values for the current submitted step into the storage array
  $form_state['storage']['values'][$form_state['storage']['step']] = $form_state['values'];
  $form_state['storage']['step']++;
  //  Multistep: Tell Drupal we are redrawing the same form
  $form_state['rebuild'] = TRUE;
  // do other things the form may have been expecting to happen
  foreach ((array) $form['#submit'] as $submit_func) {
    $submit_func($form, $form_state);
  }
}
function import_html_process_form_previous_button_submit($form, &$form_state) {
  // Multistep: save the values for the current submitted step into the storage array
  $form_state['storage']['values'][$form_state['storage']['step']] = $form_state['values'];
  $form_state['storage']['step']--;
  //  Multistep: Tell Drupal we are redrawing the same form
  $form_state['rebuild'] = TRUE;
}


function import_html_select_source_form(&$form_state, $profile) {
  $form = array();

  $form['help'] = array('#type' => 'markup', '#value' => t("<p>
      For an intro, try <a href='!demo_link'>a quick demo</a>.
    </p><p>
      The source website files must be directly available to this server.
      This process will NOT yet import the structure of a client website on a remote server,
      or spider all the resources of a remote site.
    </p><p>
      <b>Note</b> Big sites <i>will</i> take a long time to process,
      and processing may timeout.
      You can either increase the php timeout value and wait around,
      or just do sections at a time by using the subsection parameter above.
    </p>",
    array(
      '!demo_link' => url(IMPORT_HTML_ADMIN_PATH .'/demo'),
    )
  ));


  $form['htmlsource'] = array(
    '#type' => 'fieldset',
    '#title' => t("Select HTML file source"),
  );

  $form['htmlsource']['source_siteroot'] = array(
    '#type' => 'textfield',
    '#title' => t("Site Root on the Server"),
    '#default_value' => $profile['source_siteroot'],
    '#description' => t("
      Where to read from.
      <br/><b>If the files are on the server</b> (local to Drupal)
      Enter the absolute or drupal-root-relative location of the site to import.
      You must have access permissions.
      Relative paths and aliases will be calculated from here.
      <br/>eg: <code>/var/www/old_site/htdocs</code>, or <code>sites/default/files/copy-of-old-site</code>
    "),
    '#element_validate' => array('import_html_validate_trailing_slash', 'import_html_source_siteroot_validate'),
  );

  $form['htmlsource']['current_subsection'] = array(
    '#type' => 'textfield',
    '#title' => t("Subsection to list"),
    '#default_value' => $profile['current_subsection'],
    '#size' => 20,
    '#description' => t("
      For large sites, its more convenient to just list and process sections.
      If a subdirectory is specified, only that will be displayed."
    ),
    '#element_validate' => array('import_html_validate_trailing_slash'),
  );

  // Set a callback so these settings get saved generically, persistantly
  $form['#submit'][] = 'import_html_subsettings_submit';

  return $form;
}

/**
 * Check the submitted source path and subsection are valid
 *
 * A FAPI #element_validate callback invoked on $form['source_siteroot']
 *
 * http://api.drupal.org/api/file/developer/topics/forms_api_reference. html#element_validate
 *
 * NOTE- use
 * form_error($element, $message)
 * not
 * form_set_error($element_name, message)
 */
function import_html_source_siteroot_validate($element, &$form_state) {
  $working_path = ensure_trailing_slash($form_state['values']['source_siteroot']) . $form_state['values']['current_subsection'];
  if (! is_dir($working_path)) {
    form_error($element, t("Directory %dir does not exist or is unreadable.", array('%dir' => $working_path)));
    return ;
  }
}

/**
 * Form element validator. Ensure the value ends with /
 */
function import_html_validate_trailing_slash($element, &$form_state) {
  form_set_value($element, ensure_trailing_slash($element['#value']), $form_state);
}


/**
 * Given a local filepath, display all the files I can find in it.
 *
 * Exclude hidden files and directories ( starting with "." or "_" ) .
 * Guess what type of content they are
 * (html, resources like images and styles or other)
 * based on suffix.
 * Enable handy multi-selections to enhance the form
 *
 * A form api form def used in step 2 of import_html_page()
 *
 * @param  $form_values array including 'source_siteroot' and
 * 'current_subsection'
 *
 * @param $profile array including file exclusion patterns and scanning rules
 *
 * @return Drupal form
 */
function import_html_list_filesystem($form_values, $profile, $max_depth = 0) {

  // Paranoia.
  if (empty($form_values['source_siteroot'])) {
    trigger_error('import_html_list_filesystem called without a valid source_siteroot path. args were: '. print_r($form_values, 1), E_USER_WARNING);
    return NULL;
  }

  $source_siteroot = $form_values['source_siteroot'];
  $current_subsection = $form_values['current_subsection'];

  drupal_set_message(t("
    Listing contents of %source_siteroot %current_subsection ; %max_depth
  ", array(
    '%source_siteroot'  => $source_siteroot,
    '%current_subsection' => empty($current_subsection) ? '' : '['. $current_subsection .']',
    '%max_depth' => empty($max_depth) ? 'recursive' : 'maximum recursion depth:'. $max_depth,
    )
  ));
  $working_path = $source_siteroot . $current_subsection;
  $form = array();

  if (! $max_depth) $max_depth = 4;
  $dir_structure = import_html_file_scan_directory(trim_trailing_slash($working_path), ".*", array('.', '..', 'CVS'), 0, TRUE, 'filename', 0, 1, $max_depth);
  $count_files = count($dir_structure);

  // If there are too many files than can reasonably be shown, need to reduce the recursion depth
  if ($count_files > IMPORT_HTML_MAX_FILE_LISTING_COUNT) {
    $max_depth --;
    if ($max_depth < 1) {
      // Way too many items to list
      drupal_set_message(t("
        Too many items to list in the folder structure at this level.
        You must just select the folder and hope it works.
      "), 'warning');

      $count_files = count(file_scan_directory(trim_trailing_slash($working_path), ".*"));
      $dir_structure = array( $working_path => (object)array(
        'filename' => $working_path,
        'basename' => basename($working_path) ,
        'child_count' => $count_files,
      ));
    }
    else {
      // Call myself with a new depth limit.
      drupal_set_message(t("Too many items ($count_files) found. Reducing recursion depth and trying again"));
      // RECURSION HERE
      return import_html_list_filesystem($form_values, $profile, $max_depth);
    }
  }
  if ($max_depth != 4) {
    drupal_set_message(t("
      Because this file listing contains more than %max files,
      it is unreasonable to show all files in a browser treeview.
      The recursion depth is therefore being reduced to %max_depth.
      Content below that level can be selected in bulk
      by selecting the appropriate parent directory.
      You may also try changing the 'current subsection'
      to be more specific and just show files at that level.
    ", array(
      '%max' => IMPORT_HTML_MAX_FILE_LISTING_COUNT,
      '%count' => $count_files,
      '%max_depth' => $max_depth,
      )
    ));
  }

  // file_scan_directory returns a flat array. Convert it into a tree structure, then render it.
  $tree = import_html_sort_list_into_tree($dir_structure, $source_siteroot, $profile['file_exclusions']);

  // Note the current context and state info as the rendering functiona and submit process needs to know
  $form['file_count'] = array( '#type' => 'value', '#value' => count($dir_structure));

  $dest_file_root = url($profile['file_storage_path'], array('absolute' => TRUE));
  $dest_virtual_path = url($profile['import_site_prefix'], array('absolute' => TRUE));

  // UI thingie. Actual goodies get added in script client-side
  // @see filetype_selectors.js
  $form['selectors'] = array(
    '#weight' => -2,
    '#value' => "<p id='import-html-selectors'>Select files to import<br/></p>",
  );

  // Need to convert the sructured tree into a structured form
  $tree_form = _import_html_tree_to_form($tree, "", "/", $form_values);

  $form['filesystem'] = $tree_form;
  $form['#theme'] = 'import_html_list_filesystem_tree';

  return $form;
}



/**
 * The 'import files' button was pressed on the 'select files' form.
 * Go do it!
 *
 */
function import_html_import_files_submit($form, $form_state) {

  variable_set('import_html_last_import_timestamp', time());

  $import_files = isset($form_state['values']['file_rel_path']) ? (array)$form_state['values']['file_rel_path'] : arrray();
  // All the checkboxes returned as keys, but only those selected need be processed.
  $selected_files = array_filter($import_files);

  // Glob out the recursive folders now.
  // This will create a huge list, but at least we know what we are doing.
  // globbing later may be lighter for batch jobs, but is unpredictable.
  $import_dirs = isset($form_state['values']['file_rel_dir']) ? (array)$form_state['values']['file_rel_dir'] : array();
  $selected_dirs = array_filter($import_dirs);
  $files_in_dirs = import_html_scan_rel_dir($selected_dirs, $form_state['values']);
  if (! empty($files_in_dirs)) {
    drupal_set_message("Globbed an additional ". count($files_in_dirs) ." files from ". count($selected_dirs) ." subdirectories");
    $selected_files = array_merge($selected_files, $files_in_dirs);
  }

  $results = array();

  if (count($selected_files)) {
    $results = import_html_import_files($selected_files, $form_state['values']);
  }
  else {
    drupal_set_message(t("No files or folders selected for import"));
  }

  drupal_set_message(t("Imported %count items", array('%count' => count($results))));
  return $results;
}

/**
 * A successor to import_html_import_files_submit.
 *
 * Does the same thing, using the Drupal batch process.
 */
function import_html_batch_import_files_submit($form, $form_state) {
  variable_set('import_html_last_import_timestamp', time());

  $profile_id = $form_state['values']['profile_id'];
  $profile = import_html_profile($profile_id);

  $import_files = (array)@$form_state['values']['file_rel_path'];
  $selected_files = array_filter($import_files);

  $import_dirs = (array)@$form_state['values']['file_rel_dir'];
  $selected_dirs = array_filter($import_dirs);

  // Data from this submission that the batch process will need to know
  // Keep it simple - this data gets passed around a bit
  $context = array(
    'profile_id' => $form_state['values']['profile_id'],
    'source_siteroot' => $form_state['values']['source_siteroot'],
    'form_id' => $form_state['values']['form_id'],
  );

  // Substitutions used for messages
  $info = array(
    '%count_files' => count($selected_files),
    '%count_dirs'  => count($selected_dirs),
    '!context'     => print_r($context, 1),
  );

  if ($profile['recursion_behaviour'] == IMPORT_HTML_GLOB_BEFORE) {
    // Glob out the recursive folders now.
    // This will create a huge list, but at least we know what we are doing.
    // globbing later may be lighter for batch jobs, but is unpredictable.
    // TODO look at queuing dirs
    $files_in_dirs = import_html_scan_rel_dir($selected_dirs, $form_state['values']);
    $info['%count_globbed_files'] = count($files_in_dirs);
    if (! empty($files_in_dirs)) {
      drupal_set_message(t("Globbed an aditional %count_globbed_files files from %count_dirs subdirectories", $info));
      $selected_files = array_merge($selected_files, $files_in_dirs);
    }
  }

  import_html_debug("Queuing Batch process of %count_files selected files, %count_dirs dirs", $info, WATCHDOG_INFO );

  if (!empty($selected_files)) {
    $batch_instructions = import_html_import_files_batch_instructions($selected_files, $context, 'import_html_import_file_batch_job');
    batch_set($batch_instructions);
  }

  if (($profile['recursion_behaviour'] == IMPORT_HTML_RECURSE_AFTER) && !empty($selected_dirs)) {
    // Also batch queue folders - individual batches
    $batch_instructions = import_html_import_files_batch_instructions($selected_dirs, $context, 'import_html_import_directory_batch_job');
    batch_set($batch_instructions);
  }

  import_html_debug("Batch process (%count_dirs dirs, %count_files files) items) is queued", $info, WATCHDOG_INFO);
}



/**
 * From a flat list of file defs, build a tree structure, and annotate it like
 * the forms API does.
 *
 * @param $dir_structure list of file names and file details, as returned from
 * file_scan_directory.
 *
 * @return an array structure that is almost, but not quite a FAPI form
 * definition.
 */
function import_html_sort_list_into_tree($dir_structure, $source_siteroot, $file_exclusions = "^_\nCVS\n^\\.") {

  $ex = trim(preg_replace('|\r|', "", $file_exclusions));
  $exclusions = explode("\n", $ex);

  $tree = array();
  $count = 0;
  foreach ($dir_structure as $file_path => $file_info) {
    $rel_path = substr($file_path, strlen($source_siteroot));

    // skip if it's a hidden/excluded file
    foreach ($exclusions as $regexp) {
      if (preg_match('|'. $regexp .'|', $rel_path)) continue 2;
    }

    $ancestors = preg_split("/[\/\:]+/", $rel_path);
    $twig = & $tree; // find the current twig, starting from the top
    $path = '';
    while ($dad = array_shift($ancestors)) {
      // walk down the path
      if (!array_key_exists($dad, $twig)) {
        // add new branch
        $twig['#type'] = 'tree_branch';
        $twig['#value']= $path;
        $twig['#description']= "";
        $twig['#filename']   = $source_siteroot . $path;

        $twig[$dad] = array();
        $count++;
      }
      $path .= $dad .'/';
      $twig = & $twig[$dad];
    }
    $twig['#type']       = is_dir($file_path) ? 'tree_branch' : 'tree_item';
    $twig['#description']= $file_info->basename;
    $twig['#filename']   = $file_path;
    $twig['#value']      = $rel_path;

    // Misc data that MAY have been set when we scanned.
    if (! empty($file_info->child_count)) {
      $twig['#description'] = $file_info->child_count ." items";
    }
  }
  return $tree;
}


/**
 * Recursive form construction function to format a tree-like structure
 * of heirarchical filenames into a Form API nested tree of checkboxes.
 *
 * The function is self-referentially recursive - depth-first formatting of a tree menu.
 *
 * @param $tree array The tree layout so far;
 * @param $name string The human name of the item were are adding right now
 * @param $prefix string The path so far;
 *
 * @return form object
 */
function _import_html_tree_to_form($tree, $name, $prefix = "", $form_values ) {
  $path = (($prefix != "/") ? $prefix ."/" : "") . $name;
  $id = "ID_" . preg_replace("/[^\w]/", "", $path);
  // $id is a safe name - a unique id derived from the item path
  // -- OK, these are becoming stupidly long - any reason not to just use a counter?

  // Although the form is presented in a tree, the form values are to come back in a list.
  //
  // To sorta-but-not-really 'tree' and allow multiple values for identically named checkboxes,
  // we keep a running list of numbers.
  // We cheat by setting the '#parents' manually before rendering, and using a counter of our own
  static $checkbox_count;


  $element = array();

  if ($tree['#type'] == 'tree_branch') {
    // tree_branch is our own pseudo form element item
    // I wanted to re-use 'fieldset' and just render it specially myself
    // but that was not over-ridable.
    // This element uses theme_tree_branch() when it is encountered in drupal_render

    $element = array(
      '#type'          => 'tree_branch',
      '#title'         => $tree['#value'],
      '#attributes'    => array('class' => 'tree-branch'),
      '#theme'         => 'tree_branch',
      '#description'   => isset($tree['#description']) ? $tree['#description'] : '',
    );

    // checkbox toggle for the children of this item
    //
    // If this was a folder that displays children,
    // the children will be submitted as individual entries in the UI
    // this means that we can ignore its state for the purposes of importing,
    // otherwise we would queue both the folder (recursive) and its children (individuals)
    // which would produce double-ups
    // Give the checkbox a different form element name.
    $checkbox_name = element_children($tree) ? 'file_rel_dir_ui_only' : 'file_rel_dir';
    $element['file_rel_dir'] = array(
      '#type'         => 'checkbox',
      '#id'           => "${id}-toggle",
      '#item-type'    => 'container',
      '#return_value' => $tree['#value'],
      '#default_value' => @$form_values['file_rel_dir'][$tree['#value']],
      '#attributes'   => array('class' => "tree-branch-toggle"),
      // Need to allow multiples, but they are essentially flat, not tree-d
      '#parents'      => array($checkbox_name, $tree['#value']),
    );
  }
  else {
    // Normal file
    $element = array(
      '#type'          => 'checkbox',
      '#title'         => $tree['#description'],
      '#theme'         => 'import_html_filesystem_tree_item',
      '#id'            => "${id}-checkbox",
      '#attributes'    => array('class' => 'tree-leaf-toggle'),
      '#default_value' => @$form_values['file_rel_path'][$tree['#value']],
      '#return_value'  => $tree['#value'],
      // Need to allow multiples, but they are essentially flat, not tree-d
      '#parents' => array('file_rel_path', $tree['#value']),
    );
  }
  $item_type = ($tree['#type'] == 'tree_branch') ? "container" : import_html_guess_file_class($tree['#filename']);

  // special case:  if name is blank (we are at root) show the working dir
  if (! $tree['#value']) {
    $item_type = 'tree-root';
    $element['#title'] = $form_values['source_siteroot'];
  }

  $element['#item-type'] = $item_type; // made-up attribute to pass to theme
  $element['#item-path'] = $item_type; // made-up attribute to pass to theme
  $element['#attributes']['class'] .= ' '. $item_type;


  // Construct the content

  if (element_children($tree)) {
    // This node has content to be recursed into. Add it as a child
    ksort($tree);
    $element['children'] = array();
    // Just a container array. Themed later
    $element['children']['#id'] = "${id}-content";
    $element['children']['#attributes']['class'] = "tree-content";
    foreach ($tree as $twigname => $twig) {
      if (element_property($twigname)) continue;
      $element['children']['file_rel_path'][] = _import_html_tree_to_form($twig, $twigname, $path, $form_values);
    }
  }
  return $element;
}

/**
 * Main filesystem select container
 */
function theme_import_html_list_filesystem_tree($element) {
  drupal_add_js(drupal_get_path('module', 'import_html') .'/toggle_treeview.js');
  drupal_add_css(drupal_get_path('module', 'import_html') .'/treeview.css');
  drupal_add_js(drupal_get_path('module', 'import_html') .'/filetype_selectors.js');
  return drupal_render($element);
}

/**
 * Basically the theme_checkbox, but without form-item div cruft.
 *
 * Does have some extra css classes though.
 *
 * @return HTML containing a form checkbox
 */
function theme_import_html_filesystem_tree_item($element) {
  $checked = $element['#value'] ? ' checked="checked" ' : ' ';
  $atts = drupal_attributes($element['#attributes']);
  $checkbox = "<input type='checkbox' name='{$element['#name']}' id='{$element['#id']}' value='{$element['#return_value']}' $checked $atts />";

  $label_atts = array(
    'class' => $element['#item-type'] .'-item file-label',
    'title' => $element['#return_value'],
    'for' => $element['#id'],
  );

  $checkbox = '<label '. drupal_attributes($label_atts) .'>'. $checkbox .' '. $element['#title'] .'</label>';
  return $checkbox;
}




/**
 * filesystem tree container is a fieldset, contains one toggle checkbox and a collection of 'children'
 * If you want the normal rendering back (description, value) put it in yourself.
 */
function theme_tree_branch($element) {
  $toggle_button = $element['file_rel_dir'];
  $checked = $toggle_button['#value'] ? ' checked="checked" ' : ' ';
  $atts = drupal_attributes($toggle_button['#attributes']);
  $item_checkbox = "<input type='checkbox' name='{$toggle_button['#name']}' id='{$toggle_button['#id']}' value='{$toggle_button['#return_value']}' $checked $atts />";
  $item = "<label>$item_checkbox {$element['#title']}</label>";

  $children = empty($element['children']) ? '' :
    '<div'. drupal_attributes($element['children']['#attributes']) .'>'
    . drupal_render($element['children'] )
    .'</div>'
    ;

  return
    '<fieldset'. drupal_attributes($element['#attributes']) .'>'
  ."<legend class=\"{$element['#item-type']}-label\">{$item}</legend>"
  . (isset($element['#description']) && $element['#description'] ? '<div class="description">'. $element['#description'] .'</div>' : '')
  . $children
  . (isset($element['#value']) ? $element['#value'] : '')
  ."</fieldset>\n";

}

/**
 * Return a table listing the results from the watchdog.
 */
function import_html_results($severity = WATCHDOG_INFO) {
  $last_import_timestamp = variable_get('import_html_last_import_timestamp', 0);

  $output = "Results from the last import process - ". format_date($last_import_timestamp);

  // We will use the watchdog to do most of our logging - but then have to retrieve it ourself as the watchdog reports are tedious.
  // Code adapted from dblog.admin.inc
  $filter = array(
    'where' => "(w.type = '%s') AND (w.timestamp >= %d) AND (w.severity <= %d)",
    'args' => array('Import HTML', $last_import_timestamp, $severity),
  );

  $sql = "SELECT w.wid, w.uid, w.severity, w.type, w.timestamp, w.message, w.variables, w.link FROM {watchdog} w ";
  $header = array(
    t('Message'),
  );
  $classes = array(
    WATCHDOG_DEBUG    => 'dblog-debug',
    WATCHDOG_INFO     => 'dblog-info',
    WATCHDOG_NOTICE   => 'dblog-notice',
    WATCHDOG_WARNING  => 'dblog-warning',
    WATCHDOG_ERROR    => 'dblog-error',
    WATCHDOG_CRITICAL => 'dblog-critical',
    WATCHDOG_ALERT    => 'dblog-alert',
    WATCHDOG_EMERG    => 'dblog-emerg',
  );

  $tablesort = "";#tablesort_sql($header);
  $result = pager_query($sql ." WHERE ". $filter['where'] . $tablesort, 100, 0, NULL, $filter['args']);

  while ($dblog = db_fetch_object($result)) {
    $rows[] = array('data' =>
      array(
        array( 'data' => t($dblog->message, unserialize($dblog->variables)), 'class' => 'message'),
        $dblog->link,
      ),
      // Attributes for tr
      'class' => "dblog-". preg_replace('/[^a-z]/i', '-', $dblog->type) .' '. $classes[$dblog->severity]
    );
  }

  if (!$rows) {
    $rows[] = array(array('data' => t('No log messages available.'), 'colspan' => 6));
  }

  $output .= theme('table', $header, $rows, array('id' => 'import-html-dblog'));
  $output .= theme('pager', NULL, 50, 0);
  drupal_add_css(drupal_get_path('module', 'import_html') .'/import_html-dblog.css');

  return $output;


}

/////////////////////////////////////////////
// DEMO
/////////////////////////////////////////////



/**
 * Show an interface to import just one file
 */
function import_html_demo_form() {
  $form = array();

  $form = array(
   '#method' => 'post',
  );

  $form['Select'] = array(
    '#type' => 'fieldset',
    '#title' => t("Select HTML file source"),
  );
  $form['Select']['source_url'] = array(
    '#type' => 'textfield',
    '#title' => t("URL to import"),
    '#default_value' => '',
    '#maxlength' => 240,
    '#description' => t("
        Local file paths are OK, although you may have to use the
        <kbd>file://</kbd> syntax on them, depending on your system.
    "),
  );
  $import_html_profiles = variable_get('import_html_profiles', array());
  $profile_options = array_combine(array_keys($import_html_profiles), array_keys($import_html_profiles));
  $form['profile_id'] = array(
    '#type' => 'select',
    '#title' => "Import Profile",
    '#options' => $profile_options,
  );

  $form[] = array(
    '#type' => 'submit',
    '#value' => t("Preview"),
  );
  return $form;
}

//TODO: fix handler errors
/**
 * Submit handler for import_html_demo_form
 * @param $form_id
 *   a form_id
 * @param $form_values
 *   posted form values typically passed in by submit handler, but also can be from $_POST.
 *   should contain
 *     ('file_rel_path' array)
 *     relative to the submitted 'source_siteroot' (no trailing slash) .
 *     Rel paths here begin with slashes.
 */
function import_html_demo_form_submit($form, &$form_state) {
  switch ($form_state['values']['form_id']) {
    case 'import_html_demo_form':
      // Bulk imports come with context paths which are used for structure
      // Over-ride (fudge) those inputs for the demo
      $source_path = foreslash( $form_state['values']['source_url'] );

      $url_parts = parse_url($source_path);

      // divide the path into two halves (avoiding glue_url()) to provide a context and a rel_path
      $split_at = strrpos($source_path, $url_parts['path']) +1;

      $form_state['values']['source_siteroot'] = substr($source_path, 0, $split_at);
      $rel_path = substr($source_path, $split_at);

      // Grab the current default settings.
      $context = import_html_profile();

      $import_files = array($rel_path);
      $files = import_html_import_files($import_files, $form_state['values']);

      // Take the resulting node definition from the processed array and display it in a node edit form
      // as if it were an existing node.

      if (is_array($files) && ($file = array_shift($files)) ) {
        if (empty($file['node'])) {
          drupal_set_message(t("Looks like processing %path didn't return any valid node.", array('%path' => $url_parts['path'])), 'error');
          break;
        }
        $node = $file['node'];

        // Dummy up a node edit form
        module_load_include('inc', 'node', 'node.pages');

        // Setting NODE_BUILD_PREVIEW should prevent the theme etc from borking because the node has no nid.
        $node->build_mode = NODE_BUILD_PREVIEW;

        // Previewing alters $node so it needs to be cloned.
        $cloned_node = drupal_clone($node);

        // Unset this because the 'trimmed version' is unhelpful
        $cloned_node->teaser = trim($cloned_node->body);

        $output = theme('node_preview', $cloned_node);

        if (function_exists('dpm') && ($context['debug_level'] > 0)) {
          dpm($node);
        }

        $form_id = $node->type .'_node_form';
        $output .= drupal_get_form($form_id, $node);

        // Note there is also a hook in import_html_form_alter that adjusts this page_node_form and makes it work.
        print theme('page', $output);
      }
      else {
        print theme('page', t("For whatever reason, the request to %rel_path on %source_siteroot) failed to return a result. You'll have to enable debugging to find out why.", array('%rel_path' => $rel_path, '%source_siteroot' => $source_siteroot)) );
      }
      break;

    case 'page_node_form':
      drupal_execute('page_node_form', $form_state['values']);
      break;
  }
}
