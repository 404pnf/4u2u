<?php
// $Id: fast_gallery.admin.inc,v 1.17.2.18 2010/08/28 09:29:57 rapsli Exp $ 

/**
 * @file 
 * This is the general administration stuff
 */

/**
 * This is the form definition for a single row 
 * @param $key
 * @param $chid
 * @param $value
 * @param $title
 * @param $size
 * @param $alias
 * @return unknown_type
 */
function _fast_gallery_gallery_form($key, $chid = NULL, $value = '', $title = '', $size = 10, $alias = '') {
  $form = array(
    '#tree' => TRUE,
  );
  // We'll manually set the #parents property of these fields so that
  // their values appear in the $form_state['values']['choice'] array.
  $form['chid'] = array(
    '#type' => 'value',
    '#value' => $chid,
    '#parents' => array('a_gallery', $key, 'chid'),
  );

  $form['fg_path'] = array(
    '#type' => 'textfield',
    '#default_value' => $value,
    '#size' => 30,
    '#parents' => array('a_gallery', $key, 'fg_path'),
  );

  $form['fg_alias'] = array(
    '#type' => 'textfield',
    '#default_value' => $alias,
    '#size' => 30,
    '#parents' => array('a_gallery', $key, 'fg_alias'),
  );

  $form['fg_title'] = array(
    '#type' => 'textfield',
    '#default_value' => $title,
    '#size' => 30,
    '#parents' => array('a_gallery', $key, 'fg_title'),
  );

  /*$form['weight'] = array(
   '#type' => 'weight',
   '#default_value' => $weight,
   '#delta' => $size,
   '#parents' => array('a_gallery', $key, 'weight'),
   );*/

  return $form;
}

/**
 * Callback function for admin settings
 */
function fast_gallery_general_settings_form() {
  $gallery_default = variable_get('fg_galleries', array());

  // Add a wrapper for the choices and more button.
  $form['gallery_wrapper'] = array(
    '#tree' => FALSE,
    '#weight' => -4,
    '#prefix' => '<div class="clearfix" id="fg-galleries-wrapper">',
    '#suffix' => '</div>',
  );

  // Container for just the poll choices.
  $form['gallery_wrapper']['a_gallery'] = array(
    '#prefix' => '<div id="fg-gallery">',
    '#suffix' => '</div>',
    '#theme' => 'fg_multiple_galleries',
  );

  // Add the current choices to the form.
  $delta = 0;
  $weight = 0;
  if (!isset($form_state['values']['a_gallery'])) {
    $gallery_count = 1;
  }
  else {
    $gallery_count = sizeof($form_state['values']['a_gallery']);
    $ar_galleries = $form_state['values']['a_gallery'];
  }

  if (isset($gallery_default)) {
    $delta = count($gallery_default);
    $weight = -$delta;
    foreach ($gallery_default as $gid => $gal) {
      $key = 'chid:'. $gid;
      $form['gallery_wrapper']['a_gallery'][$key] = _fast_gallery_gallery_form($key, $gid, $gal['fg_path'], $gal['fg_title'], $gallery_count, $gal['fg_alias']);
    }
  }
  

  $key = 'new:'. ($delta);
  $form['gallery_wrapper']['a_gallery'][$key] = _fast_gallery_gallery_form($key, NULL, '', '', $gallery_count, '');

  // We name our button 'poll_more' to avoid conflicts with other modules using
  // AJAX-enabled buttons with the id 'more'.
  //TODO: this still needs some work....
  /*$form['gallery_wrapper']['fg_more'] = array(
    '#type' => 'submit',
    '#value' => t('Add gallery'),
    '#description' => t("If the amount of boxes above isn't enough, click here to add more choices."),
    '#weight' => 1,
    '#submit' => array(''), // If no javascript action.
    '#ajax' => array(
      'callback' => 'fast_gallery_ajax_handler',
      'wrapper' => 'fg-gallery',
      'method' => 'replace',
      'effect' => 'fade',
  ),
  );*/

  $form['fg_setup'] = array(
    '#type' => 'fieldset',
    '#title' => t('Setup'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $engines = module_invoke_all('fast_gallery_info');
  
  $ar_engines = array();
  foreach ($engines['storageengine'] as $engine) {
    $ar_engines[$engine['key']] = $engine['name'];
  }
  
  $form['fg_setup']['fg_storage_engine'] = array(
    '#type' => 'select',
    '#title' => t('Storage engine'),
    '#default_value' => variable_get('fg_storage_engine', FG_DEFAULT_STORAGE_ENGINE),
    '#options' => $ar_engines,
    '#description' => t('So far only default storage engine is implemented!'),
  );

  /*
  $js_framework_options = array();
  $js_framework_options['none'] = t('<none>');
  $js_framework_default = 'none';
  if (module_exists('thickbox')) {
    //$js_framework_options['thickbox'] = t('Thickbox');
  }
  if (module_exists('lightbox2')) {
    $js_framework_default = 'lightbox_no_slideshow';
    $js_framework_options['lightbox_no_slideshow'] = t('Lightbox2 (no slideshow)');
    $js_framework_options['lightbox_with_slideshow'] = t('Lightbox2 (with slideshow)');
  }

  $form['fg_setup']['fast_gallery_js_framework'] = array(
    '#type' => 'select',
    '#title' => t('Choose your Javascript framework'),
    '#options' => $js_framework_options,
    '#default_value' => variable_get('fast_gallery_js_framework', $js_framework_default),
    '#description' => t('Thickbox (not yet implemented) and Lightbox are the two options for displaying images.'),
  );
  */
  
  //TODO: this needs to be finished
  $modules = module_invoke_all('fast_gallery_info');
  foreach ($modules['presentation'] as $item) {
    $pres_options[$item['key']] = $item['name'];
  }
  $default_presentation = variable_get('fast_gallery_presentation', '');
  $form['fg_setup']['fast_gallery_presentation'] = array(
    '#type' => 'select',
    '#title' => t('How would you like to present your gallery?'),
    '#options' => $pres_options,
    '#default_value' => $default_presentation['key'],
    '#description' => t('Thickbox (not yet implemented) and Lightbox are the two options for displaying images.'),
  );
  
  // giving some Imagecache preset options
  if (module_exists('imagecache')) {
    $presets = imagecache_presets();
    $options = array();
    foreach ($presets as $preset) {
      $options[$preset['presetname']] = $preset['presetname'];
    }
    $form['fg_setup']['fast_gallery_ic_thumb'] = array(
      '#type' => 'select', 
      '#title' => t('Imagecache preset for thumbnails'),
      '#options' => $options,
      '#default_value' => variable_get('fast_gallery_ic_thumb', ''),
    );
    $form['fg_setup']['fast_gallery_ic_full'] = array(
      '#type' => 'select', 
      '#title' => t('Imagecache preset for full view'),
      '#options' => $options,
      '#default_value' => variable_get('fast_gallery_ic_full', ''),
    );
  }
  else {
    $form['fg_setup']['fg_imagecache'] = array(
      '#value' => t('Install imagecache to have more options'),
    );
  }
  
  $form['fg_setup']['fast_gallery_cron'] = array(
    '#type' => 'checkbox', 
    '#title' => t('Rescan on cron'),
    '#default_value' => variable_get('fast_gallery_cron', ''),
    '#description' => t('if checked fast gallery will rescan on every cron run if there are new images.'),
  );
  $form['fg_setup']['fg_folder_cache'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Gallery Cache'),
    '#default_value' => variable_get('fg_folder_cache', FALSE),
    '#description' => t('If checked, the galleries will be cached. Cached will be cleared upon recreation of the gallery.'),
  );
  
  $options = array(
    '<none>' => '<none>',
    'object_name' => 'object_name',
    'caption' => 'caption',
    'creation_date' => 'creation_date',
    'author' => 'author',
    'by_line' => 'by_line',
    'filename' => 'filename',
  );
  
  $form['fg_setup']['fg_iptc_settings'] = array(
    '#type' => 'select',
    '#title' => t('Thumbnail title'),
    '#options' => $options,
    '#default_value' => variable_get('fg_iptc_settings', '<none>'),
    '#description' => t('These are IPTC fields. They will be used as thumbnail subtitle. Incase you selected want to display a IPTC field, but it is not defined in the picture, it will just return the filename instead.'),
  );
  
  $form['fg_setup']['fg_iptc_settings_title'] = array(
    '#type' => 'select',
    '#title' => t('Image title'),
    '#options' => $options,
    '#default_value' => variable_get('fg_iptc_settings_title', '<none>'),
    '#description' => t('These are IPTC fields. They will be used as title in lightbox.'),
  );

  $ic_link = l('Imagecache', 'admin/build/imagecache');
  $form['fast_gallery_operations'] = array(
    '#type' => 'fieldset',
    '#title' => t('Operations'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => FALSE,
    '#description' => t('Remember to first click Save Settings (if you made any changes) before performing the below operations. Clear the database whenever you change the gallery path. Rescan the database whenever you add images, delete images, move images, or restructure the hierarchy.  Flush Internal Cache to delete 
      and force recaching of Internal Cache thumbnails aswell as the {cache_fast_gallery} db table. If you are using Imagecache, you need to flush 
      thumbnails on the Imagecache settings page: ') . $ic_link ,
  );

  $form['fast_gallery_operations']['fast_gallery_clear'] = array(
    '#type' => 'button',
    '#value' => t('Clear DB'),
    '#ahah' => array(
      'path' => 'fast_gallery/ajax/clear-db',
      'method' => 'replace',
      'effect' => 'fade',
      'wrapper' => 'attach-wrapper',
    )
  );

  $form['fast_gallery_operations']['fast_gallery_rescan'] = array(
    '#type' => 'button',
    '#value' => t('Rescan'),
    '#ahah' => array(
      'path' => 'fast_gallery/ajax/rescan',
      'method' => 'replace',
      'effect' => 'fade',
      'wrapper' => 'attach-wrapper',
    )
  );

  $form['fast_gallery_operations']['fast_gallery_flush_thumbs'] = array(
    '#type' => 'button',
    '#value' => t('Flush Internal Cache'),
    '#ahah' => array(
      'path' => 'fast_gallery/ajax/flush-thumbs',
      'method' => 'replace',
      'effect' => 'fade',
      'wrapper' => 'attach-wrapper',
    )
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}

/**
 * validation function for the settinsg form
 * @param $form
 * @param $form_state
 */
function fast_gallery_general_settings_form_validate($form, &$form_state) {
  foreach ($form_state['values']['a_gallery'] as $key => $gallery) {
    $path = $gallery['fg_path'];

    //incase we have a path -> check if it's valid
    if (!is_dir($path) && $path != '') {
      form_error($form['gallery_wrapper']['a_gallery'][$key]['fg_path'], t('This path does not exist.'));
    }

    // check if the alias doesn't contain special chars
    preg_match("/ /", $gallery['fg_alias'], $matches);
    if (count($matches) > 0) {
      form_error($form['gallery_wrapper']['a_gallery'][$key]['fg_alias'], t('Please make sure that this is a valid URL alias.'));
    }
    
    //incase there's a path make sure the path ends with a slash
    if ($path != '') {
      $last_token = substr($path, -1);
      if ($last_token != '/') {
        $path .= '/';
        $form_state['values']['a_gallery'][$key]['fg_path'] = $path;
      }
    }

    //incase there's a path -> check if there's an alias
    if ($form_state['values']['a_gallery'][$key]['fg_alias'] == '' && $form_state['values']['a_gallery'][$key]['fg_path'] != '') {
      form_error($form['gallery_wrapper']['a_gallery'][$key]['fg_alias'], t('Please enter an alias'));
    }
  }
}

/**
 * submitting the form making sure we save all the relevant information
 * @param $form
 * @param $form_state
 * @return unknown_type
 */
function fast_gallery_general_settings_form_submit($form, &$form_state) {  
  $ar_galleries = array();
  foreach ($form_state['values']['a_gallery'] as $gallery) {
    if ($gallery['fg_path'] != '') {
      $ar_galleries[$gallery['fg_path']] = $gallery;
    }
  }
  variable_set('fg_galleries', $ar_galleries); //save the galleries
  
  $engines = module_invoke_all('fast_gallery_info');
  variable_set('fg_storage_engine', $engines['storageengine'][$form_state['values']['fg_storage_engine']]); //save the storageengine
  variable_set('fast_gallery_presentation', $engines['presentation'][$form_state['values']['fast_gallery_presentation']]);
  
  variable_set('fast_gallery_ic_thumb', $form_state['values']['fast_gallery_ic_thumb']);
  variable_set('fast_gallery_ic_full', $form_state['values']['fast_gallery_ic_full']);
  variable_set('fast_gallery_cron', $form_state['values']['fast_gallery_cron']);
  variable_set('fast_gallery_js_framework', $form_state['values']['fast_gallery_js_framework']);
  variable_set('fg_folder_cache', $form_state['values']['fg_folder_cache']);
  variable_set('fg_iptc_settings', $form_state['values']['fg_iptc_settings']);
  variable_set('fg_iptc_settings_title', $form_state['values']['fg_iptc_settings_title']);
  
  fast_gallery_flush_caches();
  menu_rebuild();//prepare the paths for newly built galleries
  
  $fg = fast_gallery_get_FastGallery();
  $fg->rescanGallery();
}

/**
 * Ajax handler when hitting some of the buttons or editing image names
 * @param $form
 * @param $form_state
 */
function fast_gallery_ajax_handler($op) {
  $fg = fast_gallery_get_FastGallery();

  switch ($op) {
    case 'flush-thumbs': //clear cache
      $cache = fast_gallery_get_cache();
      fast_gallery_flush_caches();
      $cache->flushThumbs();
      print drupal_to_js(array('status' => TRUE, 'data' => theme('status_messages')));
      exit;
    case 'rescan': //reindex images
      $fg->rescanGallery();
      print drupal_to_js(array('status' => TRUE, 'data' => theme('status_messages')));
      exit;
    case 'clear-db': //clear db
      $fg->clearDb();
      print drupal_to_js(array('status' => TRUE, 'data' => theme('status_messages')));
      exit;
    case 'edit-fg-more':
      $choice_form = $form['gallery_wrapper']['a_gallery'];
      return $choice_form;
      break;
    case 'edit-imagename':
      $error = true;
      $key = variable_get('fg_iptc_settings', '');
      if ($key != '' && $key != 'filename') {
        $image = new FGImage($_POST["data"]);
        $error = ! $image->setIptc($key, $_POST["new_value"]);
      }
      print drupal_to_js( array(
        "is_error"	=> $error,
        "error_text"	=> "Name not based on an IPTC Tag",
        "html"		=> $error ? $_POST["orig_value"] : $_POST["new_value"],
      ) );
      break;
  }
}

/**
 * theming the form for adding new galleries
 * @param $key
 * @param $chid
 * @param $value
 * @param $votes
 * @param $weight
 * @param $size
 * @return string
 */
function theme_fg_multiple_galleries($form) {
  $delta = 0;
  $rows = array();
  $headers = array(
  //  '',
    t('Path to Gallery'),
    t('Path Alias'),
    t('Title of Gallery'),
  //t('Weight'),
  );

  foreach (element_children($form) as $key) {
    $delta++;

    // Build the table row.
    $row = array(
      'data' => array(
        drupal_render($form[$key]['fg_path']),
        drupal_render($form[$key]['fg_alias']),
        drupal_render($form[$key]['fg_title']),
      ),
    );

    // Add any additional classes set on the row.
    if (!empty($form[$key]['#attributes']['class'])) {
      $row['class'] = array_merge($row['class'], $form[$key]['#attributes']['class']);
    }

    $rows[] = $row;
  }

  $output = theme('table', $headers, $rows);
 
  return $output;
}