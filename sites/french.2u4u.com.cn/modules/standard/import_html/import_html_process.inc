<?php
// $Id: import_html_process.inc,v 1.5.4.17 2009/10/06 14:09:02 dman Exp $
/**
 * @file Actual routines for importing files.
 *
 *
 * @ingroup import_html Import HTML
 * @author Dan Morrison http://coders.co.nz/
 *
 */

module_load_include('inc', 'import_html', 'coders_php_library/debug');
module_load_include('inc', 'import_html', 'coders_php_library/xml-transform');
module_load_include('inc', 'import_html', 'coders_php_library/file-routines');

/**
 * Files have been selected, set them up for processing
 *
 * @param $file_list
 *   an  array of simple file paths, probably selected from the file_list form
 * @param $context
 *   A set of parameters, similar to the import_html profile, possibly from
 *   the list_filesystem form. Should contain the base path that the
 *   submitted files are relative to.
 * Note that context is NOT a full profile.
 *
 * @return A result set of nodes
 */
function import_html_import_files($file_list, $context) {
  drupal_set_message(t('Processing %count files! Using %profile_id configuration settings.', array('%count' => count($file_list), '%profile_id' => $context['profile_id'])));

#  dsm(count($file_list) ." files to go on");
#  dsm($file_list);
#  dsm(array('Context' => $context));

  if ( empty($file_list)) {
    drupal_set_message(__FUNCTION__ .' '. t("No Files Selected. Nothing to import"), 'error');
    return;
  }

  // TODO see what we can do about clearing out our memory

  $results = array();
  foreach ($file_list as $list_index => $rel_path) {
    if (! empty($rel_path)) {
      $file_results = import_html_import_file($rel_path, $context);
      if (! $file_results) {
        drupal_set_message(t('
          Failed to get any results from the attempted analysis of %rel_path.
          The source file path was probably unavailable or incorrect.',
          array('%rel_path' => $rel_path)), 'error');
        continue;
      }
      // Result of importing a file MAY be more than one node,
      // unlikely as it may be for XHTML, but is possible for XML extension
      import_html_debug_code("Result of processing file $rel_path", $file_results, WATCHDOG_DEBUG);
      foreach ($file_results as $node) {
        unset($node->file_data); // discard debug logs, try to save space.
        $results[] = $node;
      }
    }
    else {
      // Probably a folder path item
      // One day may support these as recursive
      drupal_set_message(__FUNCTION__ ." Strange, the input array element in the submitted file list had no path for item $list_index", 'warning');
      #dpm($file_list);
    }
  }
  // This isn't happening correctly until I visit admin?
  menu_rebuild();

  return $results;
}


/**
 * Given a html file, prepare all the node info we can get out of it.
 *
 * This func mainly prepares the paths and relative links. Data extraction happens in _import_html_process_html_page()
 *
 * It does submit and save the node to the database.
 *
 * @param $context
 *   describes the context this function was called in. It should contain
 * 'profile_id' and 'source_siteroot'. Also 'form_id'
 *
 * @return array that may contain more than one node (in extreme cases)
 */
function import_html_import_file($rel_path, $context) {

  // Read the profile id and use that as a context for all settings
  $profile = import_html_profile($context['profile_id']);

  $source_siteroot = $context['source_siteroot'];
  $dest_root = ensure_trailing_slash($profile['file_storage_path']);
  $is_remote = valid_url($source_siteroot, TRUE);

  import_html_debug(
    "<strong>Importing</strong> '%rel_path'",
    array('%rel_path' => $rel_path),
    WATCHDOG_NOTICE
  );

  $source_path = $source_siteroot . $rel_path;
  $save_as = safe_filepath_from_url($rel_path);
  $dest_path = preg_replace("|/+|", "/", $dest_root . $save_as);

  // Handle URLS/Folders with training slash
  if (preg_match("|/$|", $rel_path)) {
    // Handle trailing slashes differently at home and away
    if ($is_remote) {
      // It's remote
      $default_documents = split(",", $profile['default_document']);
      // need a dummy filename if retrieving default docs.
      $dest_path .= trim(array_shift($default_documents));;
    }
    else {
      return; //skip local directories altogether (their contents is selected individually)
    }
  }

  $file = array(
    'source' => $source_path,
    'dest' => $dest_path,
    'rel_path' => $rel_path,
  );
  // Handle files that are resources.
  // Copy them into the files folder and return
  $checkfile = is_local($source_path) ? $source_path : $dest_path;
  // can't use mime detection on remote lookups yet
  if (import_html_guess_file_class($checkfile) != 'html') {
    // non-page resource - what sort of processing can I do here?

    import_html_debug(
      "I think (due to file suffix '%doctype')
        that '%source' is not a html page I can process.<br/>
        It's just been copied into '!dest'.",
      array(
        '%source' => basename($source_path),
        '!dest' => l($dest_path, $dest_path),
        '%doctype' => import_html_guess_file_class($checkfile),
      ),
      WATCHDOG_NOTICE
    );

    import_html_get_raw_file_local($source_path, $dest_path, $is_remote);
    $file['type'] = 'resource';
    $file['path'] = $dest_path;
    $files[] = $file;
    return $files;
  }


  // Compare the alias path of this new page with what we've already got
  $new_path = _import_html_calc_path($rel_path);
  if (($normal_path = drupal_get_normal_path($new_path)) != $new_path) {
    // We recognise that alias, thus an item already exists in that path.
    if ($profile['handle_duplicates'] == IMPORT_HTML_SKIP) {

      import_html_debug(
        "We already have '%new_path' in the system as '%normal_path'.
          According to import_html settings, this import is being skipped",
        array(
          '%new_path' => $new_path,
          '%normal_path' => $normal_path,
        ),
        WATCHDOG_INFO
      );

      return;
    }
    import_html_debug(
      "We already have '%new_path' in the system as '%normal_path'.
        Overwriting/updating it with the new import",
      array(
        '%new_path' => $new_path,
        '%normal_path' => $normal_path,
      ),
      WATCHDOG_INFO
    );
  }

  // Minor clean-up. Helps recover from crashes and prevents files getting renamed into file-01.etc
  if ( is_file($dest_path) && ! $profile['keep_temp_files']) {
    unlink($dest_path);
  }

  // TODO
  // Resolve issue when there is a file called the same name as a folder
  // eg spidering off another Drupal site, /node is a PAGE with content, but /node/1 is also.
  // ??
  // forcably add a suffix to otherwise unsuffixed stuff?
  // is it a problem from wget?

  if (! is_file($dest_path) || ! $profile['keep_temp_files']) {
    if (!import_html_get_raw_file_local($source_path, $dest_path, $is_remote)) {

      import_html_debug(
        "Failed to fetch a copy of %source_path into %dest_path",
        array('%dest_path' => $dest_path, '%source_path' => $source_path),
        WATCHDOG_ERROR
      );

      return FALSE;
    }

    import_html_debug(
      "Fetched a %persistant local copy to %dest_path",
      array(
        '%dest_path' => $dest_path,
        '%persistant' => ($profile['keep_temp_files'] ? 'persistant' : 'temporary')
      )
    );

  }
  else {
    import_html_debug(
      "Local copy exists at %dest_path",
      array('%dest_path' => $dest_path)
    );
  }

  if ($is_remote) {
    // Importing a remote file - as for demo
    // relinking will happen to point back at where it came from, not here
    // TODO need yet another parameter to indicate this, the path to neighbours
    # $rel_path = $source_path;
    // that worked, but created some odd paths in places when using a prefix.
    // Resources and cross-links were found, but local alias was wrong

    import_html_debug("Relinking this source will point back to the original URL context!");
  }
  // We have a local copy now.
  // $node initialized and processed HERE. Produces a node OBJECT
  //
  #dpm(get_defined_vars());

  $nodes = import_html_process_html_page($dest_path, $rel_path, $profile);

  // At this point, the node(s) are full of data, but not yet saved.

  // On rare occasions, (using xt:document) the processing can produce an ARRAY of nodes that need saving.
  // So we always work with $nodes as an array of nodes. Almost always just one.

  if (!$nodes) {
    import_html_debug(
      "Failed to process a node out of file '%rel_path'",
      array('%rel_path' => $rel_path),
      WATCHDOG_ERROR
    );
    return FALSE;
  }

  // We can immediately discard the source file -
  // it should have been a temp copy made by import_html_get_raw_file_local() above
  if ( file_exists($dest_path) && ! $profile['keep_temp_files']) {
    unlink($dest_path);
  }

  // Almost trivial loop (probably over 1 item)
  foreach ($nodes as $node) {
    // The node data object has been initialized
    // It may contain heaps of extra junk set in via a random absorbtion of elements in the XML import.
    // They will get ignored if not recognised.
    import_html_debug(
      "Processed page to extract content. Title: <strong>'%title'</strong> ",
      array('%title' => $node->title),
      WATCHDOG_INFO
    );

    // If it's overwriting an existing path, merge values
    $node = import_html_merge_over_existing_node($node, $profile);

    if (empty($node->body)) {
      form_set_error('body', t("No body content found in this node"));
    }

    // Finished prep, now save

    // 'prepare' occasionally ensures that some required fields are filled in
    // depending on enabled modules. Maybe.
    // node_invoke_nodeapi($node, 'prepare');

    // I really should VALIDATE now!
    // but what to do with errors?
    // path_nodeapi complains if I try to validate before I know my nid. Is that correct?
    // node_invoke_nodeapi($node, 'validate');

    // Submit doesn't actually save, it just fills in extra fields
    $node = node_submit($node);


    if ($context['form_id'] == 'import_html_demo_form') {
      // DO NOT actually save stuff to the database
      $file['node'] = $node;
    }
    else {

      if ($errors = form_get_errors()) {

        import_html_debug(
          "Import of '%rel_path' did not quite validate. I'm not sure how to recover from that problem. <br/>!errors",
          array(
            '%rel_path' => $file['rel_path'],
            '!errors' => join(',<br/> ', $errors),
          ),
          WATCHDOG_ERROR
        );
        // TODO This is not very helpful in bulk mode.
        // what can I do now?
      }

      else {

        if (! empty($node->nid)) {

          import_html_debug(
            "!node_link Exists, updating it with content from %source_path.",
            array(
              '!node_link' => l('node '. $node->nid, 'node/'. $node->nid),
              '%source_path' => $source_path
            ),
            WATCHDOG_INFO
          );
          node_save($node);
          module_invoke_all('import_html_after_save', $profile, $node);

        }
        else {

          import_html_debug(
            "Inserting New Node !node_link with content from %source_path",
            array('%source_path' => $source_path, '!node_link' => l($node->path, $node->path)),
            WATCHDOG_INFO
          );
          #dpm($node);
          node_save($node);

          // Had to wait until I had an ID to do this
          // These callbacks add the aliases and menus
          module_invoke_all('import_html_after_save', $profile, $node);
          // note, navigation items only gets set up on first import.
          // After that you are on your own
        }
      } // Finished updating database


      #// Keep a copy for auditing (maybe not if memory gets heavy)
      $mini_node = (object) array();
      foreach (array('title', 'nid', 'path') as $att) {
        $mini_node->$att = $node->$att;
      }
      $file['node'] = $mini_node;

      import_html_debug(
        "<strong>Imported Node</strong> !node_link with content from %source_path . [mem: %memory]",
        array(
          '%source_path' => $source_path,
          '!node_link' => l($node->title, 'node/' . $node->nid),
          # Node path is usually right, but we will actually let the system figure that out - path may be off!
          #'!node_link' => l($node->title, $node->path),
          '%memory' => format_size(memory_get_usage()) .'/'. format_size(memory_get_peak_usage()),
        ),
        WATCHDOG_NOTICE
      );

    } // Looped over all nodes from file
    $files[] = $file;
  } // Looped over all files

  return $files;
}

/**
 * Big brother to import_html_import_file
 *
 * Recursively imports ALL FILES in a given folder and returns a result array
 *
 * This does this immediately in normal flow, and really should be done in
 * batch. Try not to do this directly a lot.
 */
function import_html_import_directory($rel_path, $context) {
  // Read the profile id and use that as a context for all settings
  $profile = import_html_profile($context['profile_id']);
  $source_siteroot = $context['source_siteroot'];
  import_html_debug(
    "<strong>Importing Directory</strong> '%rel_path'",
    array('%rel_path' => $rel_path),
    WATCHDOG_INFO
  );
  $source_path = $source_siteroot . $rel_path;
  $results = array();
  if (is_dir($source_path)) {
    // will scan and queue ALL sub-contents of this folder
    $dir_structure = file_scan_directory(trim_trailing_slash($source_path), ".*");
    foreach ($dir_structure as $filepath => $file) {
      // We have the full path, but need to knock it back to the rel path
      // before handing off to the normal file import
      $file_rel_path = str_replace($source_siteroot, '', $filepath);
      import_html_import_file($file_rel_path, $context);
    }
  }
  return $results;
}


/**
 * Carefully fetch a (potentially remote?) file and save it nearby
 */
function import_html_get_raw_file_local($source_path, $dest_path, $host) {
  mkdirs(dirname($dest_path), FILE_CREATE_DIRECTORY);
  if (! mkdirs(dirname($dest_path)) ) {
    trigger_error("Failed to create directory for $dest_path Might be permissions.", E_USER_ERROR);
  }
  $debug_info = array(
    '%source' => $source_path,
    '%dest' => $dest_path,
  );

  import_html_debug(
    "Fetching content from %location '<a href='!realpath'>%source_path</a>' now. Saving temp file locally as %dest_path",
    array(
      '%source_path' => $source_path,
      '%dest_path' =>  $dest_path,
      '%location' => empty($host) ? 'local' : $host,
      '!realpath' => (empty($host) ? 'file://' : '') . realpath($source_path),
    ),
    WATCHDOG_INFO
  );

  $orig_path = $source_path;

  if ($host) {
    // It's remote. Trust PHP5 and allor_url_fopen is available
    if (!copy($source_path, $dest_path)) {
      import_html_debug(
        "Remote file copy from %source to %dest failed",
        $debug_info,
        WATCHDOG_ERROR
      );
      return FALSE;
    }
  }
  else {
    // local copy
    if (realpath($source_path) == realpath($dest_path)) {
      import_html_debug(
        "Copying between identical source and destination, %source = %dest , importing file in-place.",
        $debug_info
      );
      return TRUE;
    };

    if (!copy($source_path, $dest_path)) {
      import_html_debug(
        'Local file copy failed (%source_path to %dest_path).
        Source %orig_path is <pre>!source_stat</pre>
        Dest folder %dest_path is <pre>!dest_stat</pre>
        ',
        array(
          '%source_path' => $source_path,
          '%dest_path' => $dest_path,
          '!source_stat' => print_r(stat($source_path), 1),
          '!dest_stat' => print_r(stat($dest_path), 1),
        ),
        WATCHDOG_ERROR
      );

      return FALSE;
    }
  }
  import_html_debug(
    "Copied import file from %source_path to %dest_path",
    $debug_info
  );
  return TRUE;
}


/**
 * Analyse a source page and create a node definition from it.
 *
 * Most of the processing magic is in here.
 * The $node handle may be provided initialized with some pre-set values.
 * The $node may come in as an array or an object.
 * Internally we should continue using the object methods.
 *
 * This processing is still in the 'validate' phase, so should
 * not cause anything to happen, just configure the node object
 *
 * @param $path/$node
 *   the file (or object) to read the data from. If it's a string, it's taken
 * to be the filename, if an object, it's the node. A node should contain a -
 * >body (or ->raw_html) and a - >path at least.
 * @param $rel_path
 *   Where this html page was found, relative to its own server root. This is
 * used to rewrite its urls. If the path is a directory, it should end with a
 * slash. ( /a/path/ == /a/path/index.html != /a/path )
 * @param $profile
 *   The  settings for this import process.
 *
 * @return array containing the new node object as the first item. Some
 * processes may return multiple nodes
 */
function import_html_process_html_page($path, $rel_path, $profile) {
  if (!init_xsl()) {
    trigger_error("Sorry, with no XML support there will be no content scanning AT ALL. Aborting process. See the import_html_help.htm for info on enabling XML under PHP.", E_USER_ERROR);
    return;
  }
  import_html_debug_code("The import profile settings being used to import_html_process_html_page($rel_path)", $profile);

  if (is_string($path)) {
    // read from file

    import_html_debug(
      "Processing file as HTML page.
        Full file path: %path , will be imported as a relative path
        under the current section.
        Relative-path is: %rel_path",
        array('%path' => $path, '%rel_path' => $rel_path),
        WATCHDOG_INFO
    );

    if (! file_exists($path)) {
      trigger_error("Path '$path' was not found. This should have been a local copy of the file being imported, but the paths may be wrong somehow. Abject failure processing $rel_path");
    }

    /*
     * Trying to parse pure XML first is causing problems
     * Either I want everything to be html, (always tidy)
     * or I allow for exsl:document blocks (which can't be tidied)
     * Option for now is try to parse, and only tidy if that fails.
     *
     */
     // temporarily ignore parser errors (catch?)
    set_error_handler('stfu');
    $xmldoc = parse_in_xml_file($path, $profile['force_tidy']);
    restore_error_handler();

    if (! $xmldoc && $profile['force_tidy'] ) {
      import_html_debug(
        "%path was not tidy enough - running tidy over it now so I can parse it.",
        array('%path' => $path, '%rel_path' => $rel_path)
      );
      // If a raw XML parse failed,
      // tell parse_in_xml_file() to use htmlTidy before it begins
      // TODO - add a flag to skip this double-processing, (parsing twice) it may be a bit slow if it's not often used
      $xmldoc = parse_in_xml_file($path, TRUE);
    }
    #import_html_debug_code("Finished reading from file:", xml_tostring($xmldoc));
    $source_node = new stdClass();
  }
  else {
    // We may have passed in a source-node object where the path was expected instead.
    // A bit of a sneak. The given node has the source HTML in $node->raw_html
    if (is_object($path)) {
      $source_node = $path;
      $path = $source_node->path;
      if (! $source_node->raw_html) {
        trigger_error(t("import_html_process_html_page alled with no HTML source to analyse"), E_USER_ERROR);
      }
      import_html_debug("Processing page source, ". strlen($source_node->raw_html) ." chars long", array());
      import_html_debug_code("Raw source", $source_node->raw_html);

      $xmldoc = parse_in_xml_string($source_node->raw_html, $profile['force_tidy']);
    }
  }

  if (!$xmldoc) {
    // parsing failed
    import_html_debug("Import_HTML failed to initialize or parse XMLdoc input", array(), WATCHDOG_ERROR);
    return FALSE;
  }

  import_html_debug_code("PARSED XML $path . XHTML", xml_tostring($xmldoc));

  // Start massaging the XML

  if ($profile['rewrite_links']) {
    // use XSL to rewrite links to fit into Drupal
    $xmldoc = import_html_rewrite_links($xmldoc, $rel_path, $profile);
  }
  if ($profile['strip_tables']) {
    $xmldoc = import_html_strip_tables($xmldoc);
  }
  if ($profile['strip_scripts']) {
    $xmldoc = import_html_strip_scripts($xmldoc);
  }

  // Debug trace data
  if (import_html_variable('debug_level')) {
    $source_node->file_data['after_rewriting'] = xml_tostring($xmldoc);
  }

  // Import content as node.
  // Translate the source text to the known tidy simple, tagged HTML structure now
  $parameters = array(
    'xmlid' => TRUE,
    'xsl_path' => $profile['translation_template'],
  );
  if ( !empty($profile['content_tag_id'])) {
    $parameters['contentid'] = $profile['content_tag_id'];
  }

  if ($xsldoc = _import_html_get_xsl_doc($profile['translation_template'])) {
    // for info only:
    $xml_top = $xmldoc->firstChild;
    $xsl_top = $xsldoc->firstChild;
    import_html_debug("
      Using XSL translation template to extract semantic content.
      Will search for body content labelled '". $parameters['contentid']
      ."' in the source.
      Active XML Namespaces are
      {$xml_top->nodeName} : {$xml_top->namespaceURI} -
      {$xsl_top->nodeName} : {$xsl_top->namespaceURI}  \n"
      , array());
    $importxml = xmldoc_plus_xsldoc($xmldoc, $xsldoc, $parameters);
    import_html_debug("Transform Successful. TRANSLATED from messy source into a pure xhtml page to import");
  }
  else {
    trigger_error("Failed to initialize XSLdoc", E_USER_WARNING);
  }

  if (! $importxml) {
    trigger_error("Nothing useful extracted via XML from that content", E_USER_WARNING);
    return FALSE;
  }

  $xmldoc = parse_in_xml_string($importxml, FALSE);

  // Allow one source document to produce multiple nodes
  $nodes = array();
  // If the process has resulted in xt:document blocks, each block
  // is a new item.
  // Either there is a html element in the input ... or many of them.

  $html_elements = xml_getelementsbytagname($xmldoc, 'html');
  import_html_debug("Found ". count($html_elements) ." html elements in source doc");

  // Probably only one, but we'll iterate over an array of one then
  foreach ($html_elements as $html_element) {

    import_html_debug_code('XML simple XHTML source ready to have its semantics extracted', xml_toString($xmldoc));

    ////////////////////////////////////
    // Do most of the content logic:
    //
    $node = import_html_xhtml_to_node($html_element, $source_node, $profile);
    //
    ////////////////////////////////////

    // The rest is housekeeping or generic:
    //

    // Set what we want the alias to be.
    if (empty($node->path)) {
      $node->path = _import_html_calc_path($rel_path);
      $node->old_path = _import_html_calc_path($rel_path, TRUE);
    }

    // May need extra care when creating multiples.
    // Invent new paths for the new documents if the exsl:document didn't define them
    if (isset($nodes[$node->path])) {
      // already using this path, extend a new one
      $node->path .= '/'. import_html_check_name(!empty($node->label)?$node->label:$node->title);
    }

    $node->title = import_html_guess_document_title($node);
    $node->status = $profile['import_status'];
    $node->promote = $profile['import_promote'];


    $nodes[$node->path] = $node;

    import_html_debug("Path to save this page as is %path", array('%path' => $path));
  }

  return $nodes;
}



/**
 * From a given XML document, create a node structure
 * with all useful parameters set.
 * A shell node object may be passed in with some values already set. The data
 * extracted from the XHTML structure will be layered onto that.
 *
 * Here is where we map HTML info to node data, like H1 -> $node->title
 * TODO tidy this up with a lookup table or something
 *
 * node may have defined its own $node->type even
 *
 * Called by
 * @see import_html_process_html_page()
 *
 * THIS IS THE ENGINE OF IMPORT_HTML
 *
 * @param $datadoc
 *   An XML document containing the whole source data
 * @param $node
 *   A   partial node object, ready to have other bits added to it. It should be
 * already filled out with the most important information - like $node->path
 * @param $profile
 *   A   set of settings and preferences for the import_html process currently
 * underway. May include some context information like paths.
 *
 */
function import_html_xhtml_to_node($datadoc, $node, $profile) {
  import_html_debug("Importing from XML object to node object");

  $node = $node ? $node : new stdClass();
  $node->type = (!empty($node->type) && is_string($node->type)) ? $node->type : $profile['content_type'];

  // debug notes/trace logs. Can be removed
  if (import_html_variable('debug_level')) {
    $node->file_data['raw_xhtml'] = xml_toString($datadoc);
  }


  // Now read the input into node structure
  //
  // Absorb the most generic bits first. Later processes may overwrite them more accurately.

  // This initial import is a totally generic catch-all.
  import_html_absorb_all_tagged_elements($node, $datadoc);

  //
  // Get all metas as properties
  //
  $head_element = xml_getelementsbytagname($datadoc, 'head', TRUE);

  // Allow ALL values I find (some may get lost later)
  import_html_absorb_metas($node, $head_element, 'meta', 'name', 'content');
  import_html_absorb_metas($node, $head_element, 'link', 'rel', 'href');

  // If there are any other things to come from HTML into $node, let me know now!
  // Loop over a buch of hook-like per-module extensions
  // MENU, PATH, TAXONOMY, CCK all add values in their own callbacks in import_html_modules.inc
  // Also the core node elements - body, title, teaser get set in a 'core' callback

  import_html_include_add_on_module_handlers();
  module_invoke_all('import_html', $profile, $node, $datadoc);

  // 'content' is now a reserved word in Drupal5
  // If I have a string there, the body cannot be rendered right later
  unset($node->content);

  // The preferred filter 'format' of this body is none - not even line breaks
  $node->format = import_html_get_preferred_filter();

  import_html_debug_code(
    "After absorbing absolutely everything I could find,
    the node object now contains the following blocks and bits:",
    $node
  );

  return $node;
}

/**
 * Import ALL tagged classes and IDs as node attributes.
 *
 * If the input has ANY id or classes at all, grab that info and apply it to
 * this object. Assume anything important enough to have a label is important
 * enough to remember.
 *
 * This will probably produce a very cloggy node, filled with trash, Possibly
 * even some arrays where there shouldn't be. But any unrecognised property
 * names will be discarded on save, leaving only the serializable values. This
 * approach will allow arbitrary data to come and go in the future.
 *
 */
function import_html_absorb_all_tagged_elements(&$node, $datadoc) {

  foreach (array('id', 'class') as $attribute_label) {

    import_html_debug(
      "Absorbing all elements with an %attribute_label
      as incidental data blobs (possibly html) into node structure",
      array('%attribute_label' => $attribute_label)
    );
    $found_elements = xml_query($datadoc, './/*[@'. $attribute_label .']');

    // I now have a collection of tagged nodes.
    foreach ($found_elements as $found_element) {

      $attribute_value = xml_getattribute($found_element, $attribute_label);
      // if it was a class, it may be multiple!
      // Usually just one however...
      $keys = explode(' ', $attribute_value);
      // debug("Found an node with $attribute_label of ".print_r($keys, 1) , 3);

      foreach ($keys as $key) {
        // Found 'something' labelled 'something'
        if (! trim($key)) continue;

        // Allow HTML though. Sometimes this will not be right...
        // TODO, figure it out?
        $value = xml_tostring($found_element, TRUE);
        if (! trim($value)) continue;

        // The value just gets absorbed
        import_html_debug(
          "Found an unexpected tagged value - %key ,
            Absorbing it into the node as a default text/html value",
          array('%key' => $key)
        );

        // Set it onto the node,
        // If it's a class, carefully combine to preserve pre-existing arrays
        if ( $attribute_label == 'class') {
          import_html_absorb_properties($node, $key, $value);
        }
        else {
          // but if it's an ID, there can be only one, just set it
          $node->$key = $value;
        }
      } // each multiple key
    } // each found element
  } // each attribute type
}

/**
 * Scan a given dom object for metas of a certain persuasion, and add all found
 * key-values to the $node.
 *
 * Supports different metas, like
 * <meta name="key" content="value" />
 * or
 * <rel type="top" href="url" />
 *
 * import_html_absorb_metas($node, $htmlnode, 'meta', 'name', 'content');
 * import_html_absorb_metas($node, $htmlnode, 'rel', 'type', 'href');
 *
 * ...
 * .. would result in :
 *
 * $node->key='value';
 * $node->top='url';
 *
 *
 */
function import_html_absorb_metas(&$node, $xml_element, $tagname, $keyname, $valname) {

  import_html_debug(
    "Absorbing the '%valname' of '%tagname's with a '%keyname'
      from source doc into node structure",
    array(
      '%valname' => $valname,
      '%tagname' => $tagname,
      '%keyname' => $keyname,
    )
  );

  $metas = xml_getelementsbytagname($xml_element, $tagname);
  foreach ($metas as $meta) {
    if (empty($meta)) continue;
    $key = xml_getattribute($meta, $keyname);
    $value = xml_getattribute($meta, $valname);
    if ($key && $value) {
      import_html_absorb_properties($node, $key, $value);
      if (module_exists('nodewords')) {
        $node->nodewords[strtolower($key)] = $value;
      }
    }
    else{
      import_html_debug(
        "When absorbing '%valname' from '%tagname's with a '%keyname' from source doc,
        (%key='%value') had a null value. Not a great problem, just letting you know.",
        array(
          '%valname' => $valname,
          '%tagname' => $tagname,
          '%keyname' => $keyname,
          '%key' => $key,
          '%value' => $value,
        ),
        WATCHDOG_INFO
      );
    }
  }
}


/**
 * Set the given property on the given object,
 * allowing multiple values to expand into arrays.
 *
 * Happens automatically IFF more than one key match is found. Deal with that
 * yourself.
 */
function import_html_absorb_properties(&$node, $key, $value) {
  if (!$key) {
    debug("Odd, when absorbing properties, value:'$value' is a value for what key? The calling function passed a null key to be absorbed.");
    return;
  }
  if (!$value) {
    debug("Odd, when absorbing properties, '$key' had a null value. This is probably not an error.", 2);
    return;
  }

  // Auto-expand into arrays - most metas can legally have duplicates
  if ( ! isset($node->$key) ) {
    $node->$key = $value;
  }
  else if ( is_array($node->$key) ) {
    $a = $node->$key; $a[] = $value; $node->$key = $a;
  }
  else { $node->$key = array($node->$key, $value); }
}

/**
 * Include what we can find in the /modules directory.
 * Only once.
 */
function import_html_include_add_on_module_handlers() {
  static $done;
  if ($done) return;
  // Scan add-on dir and include all bits found there
  $inc_files = file_scan_directory(drupal_get_path('module', 'import_html') .'/modules', ".*.inc", array('.', '..', 'CVS')) ;
  foreach ($inc_files as $inc_path) {
    include_once($inc_path->filename);
  }
  $done = TRUE;
}

/**
 * Ensure the node has a valid title.
 * If none is set, fill in a default.
 */
function import_html_guess_document_title($node) {
  if (empty($node->title) ) {
    import_html_debug(
      "Failed to extract a useful title for this node, falling back to a default value.",
      array(),
      WATCHDOG_NOTICE
    );
    switch (import_html_variable('handle_no_title')) {
      case IMPORT_HTML_GUESS :
        return import_html_guess_label('', $node->path);
        break;
      case IMPORT_HTML_DEFAULT :
        return 'Untitled Document';
        break;
    }
  }
  return $node->title;
}

/**
 * Create a human-readable string from a filename or similar, by replacing
 * underscores with spaces, removing suffix etc.
 */
function import_html_guess_label($title, $path) {
  $label = $title;
  // Need to beware of stupid long titles - they can't fit in breadcrumbs and menus
  if (strlen($title) > IMPORT_HTML_MAX_LABEL_LENGTH || empty($title) ) {
    $path_bits = split('/', $path);
    $label = array_pop($path_bits);
    if (!$label) {
      // it had a trailing slash
      $label = array_pop($path_bits);
    }
    $label = preg_replace('/\?.*$/', '?', $label); // messiness from mirrored URLs with args in
    // TODO maybe adjust this title-munging algoritm to make better guesses
    $label = str_replace('_', ' ', $label);
    $label = (strstr($label, '.')) ? substr($label, 0, strrpos($label, ".")) : $label;
  }
  return $label;
}


/**
 * Return the nice path alias of an imported page.
 *
 * Simplify a legacy URL path into something better looking.
 */
function _import_html_calc_path($rel_path, $leave_suffix = FALSE) {
  $path = import_html_variable('import_site_prefix') . preg_replace('|^/|', '', $rel_path);
  $path = preg_replace('| |', '%20', $path); // URLs should NOT have spaces, but old sites may have done this

  if ($leave_suffix) {
    return $path;
  }

  if (import_html_variable('trim_suffixes')) {
    // Simplify the URL if possible by trimming the suffix and 'index'
    // but remember the original path somewhere, we'ill need to link it forward
    // once the new node is established.

    // To be clever, special-case the 'index.html' files to be
    // linked to their parent directories.
    // Trailing slash is tricky.
    // /this/path is a whole navigation level above
    // /this/path/ and will resolve relative links differently!
    // We need to actually redirect, not just alias any links like that
    $default_documents = split(",", import_html_variable('default_document'));
    $trimmed_path = $path;
    foreach ($default_documents as $default_document) {
      $trimmed_path = preg_replace('|/('. trim($default_document) .')$|', "", $trimmed_path);
    }
    if ($trimmed_path != $path) {
      import_html_debug(
        "It's an index page, so we will refer to $path as $trimmed_path",
        array('%path' => $path, '%trimmed_path' => $trimmed_path),
        WATCHDOG_INFO
      );
      $path = $trimmed_path;
    }
    else {
      // No change, Chop suffix instead.
      // Take care - don't break a path like
      // /path/site-mirror/drupal.org/about
      // incorrectly. So make sure that we split off the basename, chop its suffix, then glue it back onto the dirname
      // $path = (! empty($path) ? dirname($path) .'/' : '') . preg_replace('|\.[^\.]+$|', "", basename($path));
      // Alternatively - avoid matching bacl up the tree
      $path = preg_replace('|([^/]*)\.[^\.]+$|', '$1', $path);
    }
  }

  return $path;
}

/**
 * Find and initialize the transformation template.
 *
 * Includes caching retrieval for a bit of speed-up over bulks.
 *
 * @return XML Document
 */
function _import_html_get_xsl_doc($xslfile) {
  static $xsldocs;
  if (isset($xsldocs[$xslfile])) {
    return $xsldocs[$xslfile];
  }

  // Check if and where filepath can be found
  // Search first under full path, then module dir, then under files dir
  $xslfilepath = $xslfile;
  if (!file_exists($xslfilepath)) {
    $xslfilepath = drupal_get_path('module', 'import_html') ."/$xslfile";
  }
  if (!file_exists($xslfilepath)) {
    $xslfilepath = file_directory_path() ."/$xslfile";
  }

  if (file_exists($xslfilepath)) {
    import_html_debug("Loading Transformation Stylesheet from $xslfilepath");
    $xsldoc = parse_in_xml_file($xslfilepath, FALSE);
    $xsldocs[$xslfile] = $xsldoc;
  }
  else {
    trigger_error("Unable to locate the Transformation Stylesheet '$xslfile' ", E_USER_WARNING);
    $xsldocs[$xslfile] = FALSE;
    return FALSE;
  }
  return $xsldoc;
}

/**
 * Run the url-rewrite XSL over the source document
 * TODO allow for the non-base version of Drupal links
 *
 * The relative links need to be converted into path-to- top and back down
 * again. Relative references just cannot be maintained.
 *
 * @return an XML doc again
 */
function import_html_rewrite_links($xmldoc, $rel_path, $profile) {
  static $rewrite_xsldoc; // memo this to speed up bulk imports
  static $xslfilepath;
  if (!$rewrite_xsldoc) {
    $xslfilepath = drupal_get_path('module', 'import_html') ."/rewrite_href_and_src.xsl";
    $rewrite_xsldoc = parse_in_xml_file($xslfilepath, FALSE);
  }

  import_html_debug("Rewriting links for a file called '$rel_path'. dirname($rel_path) is ". dirname($rel_path));
  import_html_debug_code("import_html profile settings used for rewriting", $profile);

  // dirname('/ok.htm') returns '\'; No idea why, may only happen at root level on Win
  // !! B-X

  // $rel_base is the path from the import root to the current page dir
  // I want a trailing slash, but not a leading one for the next concatenation
  // dirname('/a/dir/') returns '/a' - which is not what I want
  $rel_dir = preg_match('|/$|', $rel_path) ? $rel_path : dirname($rel_path);
  $rel_base = ensure_trailing_slash($rel_dir);

  $site_root = url('');
  $path_to_import_top = url( ensure_trailing_slash($profile['import_site_prefix']) );
  $site_root = $path_to_import_top;

  // if we are re-writing thing/index.htm to thing - our links will resolve differently!
  // either too high for thing, or too low for the thing/index.htm alias.
  $href_base = url( ensure_trailing_slash($profile['import_site_prefix']) . $rel_base);

  // Create the prefix for resource sources
  // Is url() OK for files with unclean urls? - NO. Neither is file_create_url
  $src_root = base_path() . ensure_trailing_slash($profile['file_storage_path']);

  $src_base = ensure_trailing_slash($src_root) . (($rel_base == '/') ? '' : $rel_base);

  // Or not, if we are still linking to full URLs (demo or partial import)
  if (valid_url($rel_path, TRUE)) {
    // it's remote!
    $url_parts = parse_url($rel_path);
    $path_to_import_top = $rel_path;
    $site_root = 'http://'. $url_parts['host'] .'/';
    $src_root = $site_root;
    $src_base = $rel_path;
  }
  $src_base = str_replace('/./', '/', $src_base);
  $href_base = str_replace('/./', '/', $href_base);


  import_html_debug("
    <b>Rewrite patterns:</b>
    Path to the top of this (relative) server is $site_root .
    Path to top of the prefixed section
    ({$profile['import_site_prefix']})
    from here ($rel_path)
    to our import base
    ({$profile['import_site_prefix']})
    would be '$path_to_import_top'.
    Path to a relative <em>neighbour</em> of this page would be
    ($href_base)
    or to find the base for <em>relative</em> resource files over in
    the file storage area
    ({$profile['file_storage_path']})
    would be '$src_base' ",
    array(),
    WATCHDOG_DEBUG
  );


  $parameters = array(
    // These parameters tell the rewriter what to prepend to the links.
    // They are instructions how this page will find its missing bretheren
    // when we put it where we put it.
    // Images and Pages may end up in different places.
    'site_root'      => $site_root,
    'src_root'       => $src_root,
    'src_base'       => $src_base,
    'href_base'      => $href_base,
    'replace_suffix' => $profile['relink_files'],
    'new_suffix'     => '',
    'xsl_path'       => $xslfilepath,
    'strip_scripts'  => $profile['strip_scripts'],
  );
  import_html_debug("
    XSL for URL rewrites loaded OK.
    HTML links for files that were under '$rel_base' will be made relative to '"
    . $parameters['href_base'] ."' (for pages) and '". $parameters['src_base'] ."' (for resources) "
    . ( $parameters['strip_scripts'] ? 'All inline script blocks will be discarded from the source.'. $parameters['strip_scripts'] : '')
    ,
    array(),
    WATCHDOG_DEBUG
  );
  #debug_code(xml_tostring($rewrite_xsldoc), 4, "PARSED XSL $xslfilepath . XSL");

  $rewritten = xmldoc_plus_xsldoc($xmldoc, $rewrite_xsldoc, $parameters);

  // collapse dir-up "../" paths. To tricky for XSL. Hope it doesn't break anything
  $rewritten = preg_replace('|/[^\.][^/\s"\'>]*/\.\./|', '/', $rewritten);

  import_html_debug_code("The source after URL rewriting . XHTML (string)", $rewritten);

  $xmldoc = parse_in_xml_string($rewritten, FALSE);
  if (empty($xmldoc)) {
    trigger_error("Failed to rewrite links into a valid XML file", E_USER_WARNING);
    return FALSE;
  }

  return $xmldoc;
}

/**
 * Run the strip_tables XSL over the source document
 *
 * @return an XML doc again
 */
function import_html_strip_tables($xmldoc) {
  static $strip_tables_xsldoc; // memo this to speed up bulk imports
  if (!$strip_tables_xsldoc) {
    $xslfilepath = drupal_get_path('module', 'import_html') ."/strip_tables.xsl";
    $strip_tables_xsldoc = parse_in_xml_file($xslfilepath, FALSE);
  }

  $parameters = array();
  $rewritten = xmldoc_plus_xsldoc($xmldoc, $strip_tables_xsldoc, $parameters);

  // Normalize space to clean up the gaps
  $rewritten = preg_replace("/\\s*\\n\\s*/", "\n", $rewritten);

  #debug_code( $rewritten , 3, "The source after stripping tables . XHTML (string)");
  $xmldoc = parse_in_xml_string($rewritten, FALSE);
  if (!$xmldoc) {
    trigger_error("Failed to strip tables and end up with a valid XML file", E_USER_WARNING);
    return FALSE;
  }

  return $xmldoc;
}

/**
 * @see import_html_strip_tables
 */
function import_html_strip_scripts($xmldoc) {
  static $strip_scripts_xsldoc, $xslfilepath; // memo this to speed up bulk imports
  if (!$strip_scripts_xsldoc) {
    $xslfilepath = drupal_get_path('module', 'import_html') ."/strip_scripts.xsl";
    $strip_scripts_xsldoc = parse_in_xml_file($xslfilepath, FALSE);
  }
  $parameters = array(
    'xsl_path' => $xslfilepath,
  );
  $rewritten = xmldoc_plus_xsldoc($xmldoc, $strip_scripts_xsldoc, $parameters);

  $xmldoc = parse_in_xml_string($rewritten, FALSE);
  if (!$xmldoc) {
    trigger_error("Failed to strip tables and end up with a valid XML file", E_USER_WARNING);
    return FALSE;
  }
  return $xmldoc;
}




/**
 * Ensure a sting is able to be used as an XML, CSS or Javascript ID.
 * Basically strip out all non-alpha-numerics
 * http://www.w3.org/TR/REC-xml/#NT-Name
 * @see form_clean_id() - which should have done this
 */
function import_html_check_name($name) {
  return preg_replace('|[^a-zA-Z0-9_]+|', '_', $name);
}



/**
 * Avoid double-ups, if the path already exists, UPDATE the existing node.
 * Can't have two content nodes claiming the same path or it won't validate.
 * Plus, we want to retain any info that's been added via drupal. Probably.
 *
 * @param $node
 *   partially  created node from import. Key lookup on $node->path
 * @param $profile
 *  May  contain some rules for conflict resolution - which values to keep,
 * which to over-write.
 *
 * @return $node
 *   possibly with pre-existing values blended in. Importantly - the nid
 */
function import_html_merge_over_existing_node($node, $profile) {
  $internal_link = drupal_get_normal_path($node->path);

  if ($internal_link != $node->path) {
    // Found an internal match, the alias is already asigned to a node
    // Merge info to avoid losing any Drupal-only info

    $probable_nid = array_pop(explode("/", $internal_link));
    if (! is_numeric($probable_nid)) {
      // This may happen if the menu builder has created a placeholder alias
      // pseudo-page, or the alias conflicts with an already-created system path.
      import_html_debug("
        When looking for an alias to '%nodepath',
        Found some pre-existing (non-node) content there.
        the internal link
        '%internal_link' - which was expected to return a nid.",
        array(
          '%nodepath' => $node->path,
          '%internal_link' => $internal_link,
        ),
        WATCHDOG_NOTICE
      );
      return $node;
    }
    $node->nid = $probable_nid;

    import_html_debug("
        Page path alias '%nodepath' already exists,
        It's already linked to node id '%nodenid'.
        This data import will <em>replace</em> that content,
        but try to keep any other values.
      ",
      array(
        '%nodepath' => $node->path,
        '%nodepath' => $node->nid,
      ),
      WATCHDOG_INFO
    );

    // Load existing item, layer changes on top of it
    $old_node = node_load($node->nid );

    // Paranoia
    if (empty($old_node)) {
      trigger_error("Something is seriously wrong, database may be out of sync. I found a reference to '{$node->nid}' when looking up existing aliases, but that is not loaded as a valid node. We'll proceed by making a new node, cannot merge with the allegedly pre-existing one.", E_USER_WARNING);
      return $node;
    }

    // It's tricky to handle merges for some complex modules.
    // Invoke a callback to let (for example) taxonomy figure out
    // how to blend an old node term list with a new node term list.
    module_invoke_all('import_html_node_merge', $old_node, $node, $profile);

    // Now do the rest by copying values as best we can
    foreach ($node as $key => $value) {
      // Do a deep merge
      if (is_array($value)) {
        // merge deeper sets, like taxonomy
        if (!@is_array($old_node->$key)) {
          $old_node->$key=array();
        }
        foreach ($value as $k => $v) {
          $old_node->{$key}[$k] = $v;
        }
      }
      else {
        $old_node-> $key = $value;
      }
    }
    $node = $old_node;
  }
  return $node;
}


/**
 * Utility function
 *
 * file_scan_directory() does not support max_depth.
 * I need it so my folder listings don't go insane when recursing
 *
 * This is a version of file_scan_directory that does respect max_depth
 * when recursing.
 * It also adds a filecount value to the returned item to assist feedback
 *
 * @see file_scan_directory.
 *
 */
function import_html_file_scan_directory($dir, $mask, $nomask = array('.', '..', 'CVS'), $callback = 0, $recurse = TRUE, $key = 'filename', $min_depth = 0, $depth = 0, $max_depth = NULL) {
  // If no max_depth is set, the normal recursed version is OK
  if (! isset($max_depth)) {
    return file_scan_directory($dir, $mask, $nomask, $callback, TRUE, $key, $min_depth, $depth);
  }

  $files = array();

  // Use file_scan_directory - non-recursive
  $files = file_scan_directory($dir, $mask, $nomask, $callback, FALSE, $key, $min_depth);

  foreach ($files as $filepath => $file) {
    if (is_dir($filepath)) {
      if ($depth < $max_depth) {
        $files = array_merge(import_html_file_scan_directory($filepath, $mask, $nomask, $callback, $recurse, $key, $min_depth, $depth + 1, $max_depth), $files);
      }

      // This may be intensive, but will help debugging
      $count_files = file_scan_directory($filepath, $mask);
      $files[$filepath]->child_count = count($count_files);
    }
  }

  return $files;
}

/**
 * Given a list of directories (relative to the working path)
 * Return a list of all files in them (relative to the working path)
 */
function import_html_scan_rel_dir($selected_dirs, $context) {
  $source_siteroot = $context['source_siteroot'];
  $files = array();
  foreach ($selected_dirs as $dir) {
    $working_path = $source_siteroot . $dir;
    $found_files = file_scan_directory($working_path, ".*");
    foreach ($found_files as $filepath => $file_data) {
      // strip them back to relative
      $files[] = str_replace($source_siteroot, '', $filepath);
    }
  }
  return $files;
}


/**
 * Tidy URLs before saving locally - for URL imports
 *
 * Squash/hash query strings, but don't discard them.
 * Do discard fragment ids
 *
 * Replace spaces and non-alphanumerics with underscore
 */
function safe_filepath_from_url($rel_path) {
  $save_as = preg_replace("|\?|", "%3f", $rel_path);
  $save_as = preg_replace("|\&|", "%26", $save_as);
  $save_as = preg_replace("|#.*|", "", $save_as);

  if (import_html_variable('allow_bad_urls')) {
    return $save_as;
  }

  $save_as = preg_replace("|[^A-Za-z0-9_\-~\./%]+|", "_", $save_as);
  return $save_as;
}

/**
 * http://nz2.php.net/manual/en/function.utf8-decode.php#85034
 */
function charset_decode_utf_8($string) {
  /* Only do the slow convert if there are 8-bit characters */
  /* avoid using 0xA0 (\240) in ereg ranges. RH73 does not like that */
  if (! ereg("[\200-\237]", $string) and ! ereg("[\241-\377]", $string)) {
    return $string;
  }

  // decode three byte unicode characters
  $string = preg_replace(
    "/([\340-\357])([\200-\277])([\200-\277])/e",
    "'&#'.((ord('\\1')-224)*4096 + (ord('\\2')-128)*64 + (ord('\\3')-128)).';'",
    $string
  );

  // decode two byte unicode characters
  $string = preg_replace(
    "/([\300-\337])([\200-\277])/e",
    "'&#'.((ord('\\1')-192)*64+(ord('\\2')-128)).';'",
    $string
  );

  return $string;
}


/**
 * dummy error handler
 * Used to shush DOM errors when we know the doc is probably invalid
 */
function stfu($err, $str) {
  # debug($str, 4);
};
