<?php
// $Id: swftools.admin.inc,v 1.1.2.2 2010/04/08 23:46:02 stuartgreenfield Exp $

// Load core module
module_load_include('inc', 'swftools', 'includes/swftools.core');

define('SWFTOOLS_ADMIN_STORE', 1);
define('SWFTOOLS_ADMIN_RETRIEVE', 0);

function swftools_admin_embed_form() {

  // Get array of options that will be used for form elements
  $swf_options = _swftools_options();

  // See if colorpicker 2 is loaded
  $colorfield = function_exists('colorpicker_2_or_later') ? 'colorpicker_textfield' : 'textfield';
  
  // Add admin css
  drupal_add_css(drupal_get_path('module', 'swftools') . '/swftools.admin.css', 'module', 'all', FALSE);
  
  // Initialise array to hold the form
  $form = array();
  
  // Start a fieldset to hold the embedding methods
  $form['swftools_method'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Embedding'),
    '#description' => t('Flash content can be embedded on a page directly, using &lt;object&gt; tags, or
                         JavaScript can be used to dynamically replace content on the page with the Flash
                         movie. SWF Tools supports direct embedding without installing any additional
                         modules, but JavaScript methods require that the supporting module is enabled, and
                         may require a JavaScript library to be downloaded. JavaScript interaction between
                         the page and the Flash movie is possible with both direct embedding and
                         JavaScript methods. Note that the direct embedding method does not support the Flash
                         express install feature.
                         ',
                         array('%library' => SWFTOOLS_LIBRARIES)
                       ),
  );

  // Get the available embedding methods
  $methods = swftools_get_methods('swftools_embed_method');
  
  // Build array of options ready for the selector
  if (count($methods)) {
    
    foreach ($methods AS $method => $info) {

      // Assume method is not private and that it has no accompanying library
      $info += array(
        'private' => FALSE,
        'library' => '',
      );
      
      // Only show this method as an embedding method if it is not a private method
      if (!$info['private']) {

        // Start with the name of the player
        $swf_embed_methods[$method] = $info['title'];
        
        // If the required shared file is missing add a message explaining
        if ($info['library'] && !file_exists($info['library'])) {

          // Only set a form error if the error is OTHER THAN SWF Object2 as
          // the SWF Object 2 module can access the remote library
          if ($info['name'] != 'swfobject2_replace') {
          
            // Set an error on the form so the field set expands and highlights the error
            form_set_error('swftools_embed_method', t('The shared file for @method is missing.', array('@method' => $info['title'])));

          }

          // Add missing message to the form
          // TODO: Could make a customised message for SWF Object 2 missing
          $swf_embed_methods[$method] = $swf_embed_methods[$method] . ' - <span class="error">Missing '. $info['library'] .'</span>';
          
          // If download data is available then add a download link
          if ($info['download']) {
            $swf_embed_methods[$method] = $swf_embed_methods[$method] . ' - ' . l(t('Download here'), $info['download']);
          }
        }
      }
    }
  }

  $form['swftools_method']['swftools_embed_method'] = array(
    '#type' => 'radios',
    '#title' => t('Embedding method'),
    '#default_value' => variable_get('swftools_embed_method', 'swftools_direct'),
    '#options' => $swf_embed_methods,
  );

  $form['swftools_method']['swftools_always_add_js'] = array(
    '#type' => 'radios',
    '#title' => t('Add JavaScript to all pages'),
    '#default_value' => variable_get('swftools_always_add_js', SWFTOOLS_ALWAYS_ADD_JS),
    '#options' => array(
      0 => t('Disabled'),    
      1 => t('Enabled (recommended)'),
      
    ),
    '#description' => t('Modules such as filters result in caching of the mark up generated
                         to display Flash content. In these cases SWF Tools will not be
                         triggered to add the necessary JavaScript to the page and the Flash
                         content will not display. Normally you should leave this setting
                         enabled. Setting it to disabled may prevent content from appearing.
                         '),
  );

  $form['swftools_method']['swftools_javascript_location'] = array(
    '#type' => 'radios',
    '#title' => t('JavaScript placement'),
    '#default_value' => variable_get('swftools_javascript_location', SWFTOOLS_JAVASCRIPT_INLINE),
    '#options' => array(
      SWFTOOLS_JAVASCRIPT_INLINE => t('Body'),    
      SWFTOOLS_JAVASCRIPT_HEADER => t('Header'),
    ),
    '#description' => t('Scripts to activate JavaScript embedding can be placed in line with
                         the page markup, or placed in the page header. If you are using the
                         input filter to generate content you should <em>not</em> put the
                         JavaScript in the header as it will not be cached and the content
                         will not display. If you are using CCK then script can safely be
                         placed in the page header if you prefer to avoid mixing JavaScript
                         within the page body.
                         '),
  );
  
  $form['swftools_method']['swftools_html_alt'] = array(
    '#type' => 'textarea',
    '#title' => t('HTML alternative'),
    '#default_value' => variable_get('swftools_html_alt', SWFTOOLS_DEFAULT_HTML_ALT),
    '#description' => t('Enter the default HTML that will appear if the Flash
                         content cannot be embedded.'),
  );
  
  // Only display parameters if main SWF Tools module is present
  if (defined('SWFTOOLS_INSTALLED')) {

    // Get current params defaults
    $params = _swftools_params();
  
    // Convert true/false back to 1/0
    swftools_admin_boolean_settings($params, SWFTOOLS_ADMIN_RETRIEVE);
    
    $form['swftools_params'] = array(
      '#type' => 'fieldset',
      '#title' => t('Embedding parameters'),
      '#description' => t('<p>These parameters determine various aspects of how the embedded Flash movie will be displayed, and how
                           the page can interact with it. These are the default settings that will be used if specific settings are
                           not provided when the content is being rendered.</p>
                           <p>Refer to !technote for more details about each setting.</p>',
                           array('!technote' => l('Adobe technote 12701', 'http://kb.adobe.com/selfservice/viewContent.do?externalId=tn_12701'))),
      '#tree' => TRUE,
    );
  
    $form['swftools_params']['version'] = array(
      '#type' => 'textfield',
      '#size' => '5',
      '#title' => 'Flash version',
      '#default_value' => $params['version'],
    );
    
    $form['swftools_params']['play'] = array(
      '#type' => 'checkbox',
      '#title' => t('<strong>Play immediately</strong> (play)'),
      '#default_value' => $params['play'],
    );
  
    $form['swftools_params']['loop'] = array(
      '#type' => 'checkbox',
      '#title' => t('<strong>Loop movie</strong> (loop)'),
      '#default_value' => $params['loop'],
    );
  
    $form['swftools_params']['menu'] = array(
      '#type' => 'checkbox',
      '#title' => t('<strong>Full menu</strong> (menu)'),
      '#default_value' => $params['menu'],
    );
  
    $form['swftools_params']['allowfullscreen'] = array(
      '#type' => 'checkbox',
      '#title' => t('<strong>Allow full screen mode</strong> (allowfullscreen)'),
      '#default_value' => $params['allowfullscreen'],
    );
    
    $form['swftools_params']['swliveconnect'] = array(
      '#type' => 'checkbox',
      '#title' => t('<strong>Load Java</strong> (swliveconnect)'),
      '#default_value' => $params['swliveconnect'],
    );
  
    $form['swftools_params']['bgcolor'] = array(
      '#type'  => $colorfield,
      '#title' => t('Background color <span class="weight-normal">(bgcolor)</span>'),
      '#size'  => 7,
      '#maxlength' => 7,
      '#default_value' => $params['bgcolor'],
      '#description' => t('Hexadecimal background color in the form #RRGGBB.'),
    );
  
    $form['swftools_params']['quality'] = array(
      '#type' => 'select',
      '#title' => t('Quality') . ' <span class="weight-normal">(quality)</span>',
      '#default_value' => $params['quality'],
      '#options' => $swf_options['quality'],
    );
  
    $form['swftools_params']['scale'] = array(
      '#type' => 'select',
      '#title' => t('Scale') . ' <span class="weight-normal">(scale)</span>',
      '#default_value' => $params['scale'],
      '#options' => $swf_options['scale'],
    );
  
    $form['swftools_params']['wmode'] = array(
      '#type' => 'select',
      '#title' => t('Window mode') . ' <span class="weight-normal">(wmode)</span>',
      '#default_value' => $params['wmode'],
      '#options' => $swf_options['wmode'],
    );
  
    $form['swftools_params']['align'] = array(
      '#type' => 'select',
      '#title' => t('Align') . ' <span class="weight-normal">(align)</span>',
      '#default_value' => $params['align'],
      '#options' => $swf_options['align'],
    );
  
    $form['swftools_params']['salign'] = array(
      '#type' => 'select',
      '#title' => t('salign') . ' <span class="weight-normal">(salign)</span>',
      '#default_value' => $params['salign'],
      '#options' => $swf_options['salign'],
    );
    
    $form['swftools_params']['allowscriptaccess'] = array(
      '#type' => 'select',
      '#options' => $swf_options['allowscriptaccess'],
      '#title' => t('Allow script access') . ' <span class="weight-normal">(allowscriptaccess)</span>',
      '#default_value' => $params['allowscriptaccess'],
    );

    // Add custom form handler to convert 1/0 to true/false
    $form['#submit'][] = 'swftools_admin_embed_submit';
    
  }
  
  // Add custom form handler to flush cache upon submit
  $form['#submit'][] = 'swftools_admin_settings_submit';
    
  // Return the form
  return system_settings_form($form);

}


function swftools_admin_handling_form() {

  $form = array();

  $form['swftools_files'] = array(
    '#type'  => 'fieldset',
    '#title' => t('File locations'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $current_path = variable_get('swftools_media_url', $GLOBALS['base_url'] . '/' . file_create_path(''));

  // Misname the variable with '_dummy' so that it is not saved!
  $form['swftools_files']['swftools_media_url_dummy'] = array(
    '#type' => 'textfield',
    '#title' => t('Media directory url'),
    '#default_value' => $current_path,
    '#disabled' => TRUE,
    '#description' => t("This helps swftools identify the server where your media files are located.
                         You cannot change it here, as changing it has the potential to break existing
                         content. You can set this on the &#36;conf array in your settings.php file.
                         For example: <pre>
  &#36;conf = array(
    'swftools_media_url' => 'http://anothersite.com/media', // No trailing slashes!
  );</pre>               Leaving this value unset in your settings.php file will
                         persuade SWF Tools to check for the existence of your
                         media files, as they are automatically assumed to be
                         on the local server."),
  );

  $form['swftools_files']['swftools_check_media'] = array(
    '#type' => 'radios',
    '#title' => t('File checking'),
    '#options' => array(
      1 => t('Enabled - check that local files exist.'),
      0 => t('Disabled - do not check that local files exist.'),
    ),
    '#default_value' => variable_get('swftools_check_media', TRUE),
    '#description' => t('This option will cause SWF Tools to check that requested local
                         media files exist, and issue a warning if they do not. If this
                         option is set to do not check then the mark up will be placed on
                         the page irrespective of whether the file is actually present.'),
  );

  // Get handling form by calling the profile form with no profile setting
  $form += swftools_handling_profile_form();
  
  // Make handlers collapsible
  $form['swftools_handlers'] += array(
    '#type'  => 'fieldset',
    '#title' => t('File handling'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Choose how different file types are handled.'),
  );
    
  $form['swftools_private'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Private file system'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  // Allow SWF Tools to grant access to non-uploaded files
  $form['swftools_private']['swftools_grant_access_to_private_files'] = array(
    '#type' => 'radios',
    '#title' => t('Access to supported private files'),
    '#options' => array(
      1 => t('Enabled'),
      0 => t('Disabled'),
    ),
    '#default_value' => variable_get('swftools_grant_access_to_private_files', SWFTOOLS_PRIVATE_ACCESS_DENIED),
    '#description' => t('If using a private file system then SWF Tools is unable to
                         access files that are not uploaded via a file module that
                         supports a private file system. For example, SWF Tools will
                         be unable to access files that were manually uploaded via FTP.
                         Enabling this setting will allow SWF Tools to grant access
                         to files with extensions defined by the next setting.
                         Note - if another module <em>denies</em> access then access
                         to the file will not be granted. SWF Tools itself does not
                         deny access to any file.
                         '),
  );

  // Should SWF Tools allow access to private files?
  $form['swftools_private']['swftools_grant_access_extensions'] = array(
    '#type' => 'textfield',
    '#title' => t('Extensions that SWF Tools will allow access to'),
    '#default_value' => variable_get('swftools_grant_access_extensions', SWFTOOLS_PRIVATE_ACCESS_ALLOWED_EXTENSIONS),
    '#maxlength' => 255,
    '#description' => t('Under a private file system SWF Tools will grant access to files
                         with extensions in this list. Separate extensions with a space
                         and do not include the leading dot. Although any extension can be
                         added to this list, only <em>swf flv xml mp3 jpg jpeg</em> and
                         <em>png</em> will return the correct headers.'),
  );

  // Get current mime type array
  $mime_types = _swftools_mime_types();
  
  // $mime_types are stored as an array where key is the extension, and value is the mime type
  $defaults = array();
  
  // Turn each key/value pair in to a string
  foreach ($mime_types as $extension => $type) {
    $defaults[] = $extension . ' ' . $type;
  }

  // Implode the resulting array to create a single string for presenation
  $defaults = implode("\n", $defaults);

  // Put text area on the page
  $form['swftools_private']['swftools_mime_types_input'] = array(
    '#type' => 'textarea',
    '#title' => t('Mime types'),
    '#default_value' => $defaults,
    '#description' => t('Enter a list of additional extensions that SWF Tools should recognise. Put each extension on a separate line, with the
                         extension first, followed by a space, and then the mime type for that type of file.'),
  );

  $form['swftools_advanced'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Advanced settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  
  // Enable SWF Tools cache?
  $form['swftools_advanced']['swftools_cache'] = array(
    '#type' => 'radios',
    '#title' => t('SWF Tools cache'),
    '#options' => array(
      CACHE_NORMAL => t('Enabled (recommended)'),
      CACHE_DISABLED => t('Disabled'),
    ),
    '#default_value' => variable_get('swftools_cache', CACHE_NORMAL),
    '#description' => t('During site development it can be helpful to disable the cache and
                         force content to be regenerated on every page call. Note that content
                         being generated via an input filter is always cached by the input filter
                         itself and disabling the SWF Tools cache will not stop the filter cache.
                         Even when the SWF Tools cache is disabled it will continue to store content
                         to allow features such as serving content from %path to function.', array('%path' => base_path() . 'swftools/html/nn')),
  );
  
  
  // Allow SWF Tools to grant access to content from the cache?
  $form['swftools_advanced']['swftools_grant_access_to_cache'] = array(
    '#type' => 'radios',
    '#title' => t('Allow cached content to be served'),
    '#options' => array(
      1 => t('Enabled'),
      0 => t('Disabled'),
    ),
    '#default_value' => variable_get('swftools_grant_access_to_cache', 0),
    '#description' => t('SWF Tools stores generated content in its own cache. You can simplify
                         the use of features like LightBox by allowing access to content directly
                         from the cache via the path %path, where %cid is the 32 character cid of
                         the content. SWF Tools will serve a basic page with nothing but the flash
                         content. The only access control is that the user has the %access permission.
                         ', array('%path' => base_path() . 'swftools/html/nn', '%cid' => 'nn', '%access' => 'access content')),
  );

  // Get available actions - this is just a list of available actions and descriptions about them
  $actions = swftools_get_actions();
  
  // Get the array of actions, keyed on extension
  $_extensions = _swftools_actions();
  
  // Turn it around to we are organised by action
  foreach ($_extensions as $extension => $action) {
    $extensions[$action][] = $extension;
  }
    
  // Make extensions an array
  $form['swftools_advanced']['swftools_extensions'] = array(
    '#tree' => TRUE,
  );
  
  // Put each option on the form to let the user assign extensions to each available action
  foreach ($actions as $action => $info) {
    
    // Only output single file handlers (list handlers handle collections of single files of the same type)
    if(substr($action, -5) != '_list') {
    
      // Place an option on the page
      $form['swftools_advanced']['swftools_extensions'][$action] = array(
        '#type' => 'textfield',
        '#title' => t('Extensions to associate with ' . $info['#type']),
        '#default_value' => isset($extensions[$action]) ? implode(' ', $extensions[$action]) : '',
        '#description' => t('Enter a list of extensions, separated by spaces, that SWF Tools should associate with ' . $info['#description'] . '.'),
        '#weight' => 1 + $info['#weight'] / 10,      
      );
    
    }
   
  }
  
  // Add custom form handler to flush cache upon submit
  $form['#submit'][] = 'swftools_admin_settings_submit';
  
  // Add custom handler to process extension handling
  $form['#submit'][] = 'swftools_admin_extensions_submit';
  
  // Add custom handler to process extension handling
  $form['#submit'][] = 'swftools_admin_mime_type_submit';
  
  // Return finished form
  return system_settings_form($form);

}


function _swftools_admin_file_handling_options($action, $description, $profile = '') {
  
  // Initialise list of methods
  $list = array();

  // Obtain list of available methods
  $methods = swftools_get_methods($action);

  if (count($methods)) {
    foreach ($methods AS $method => $info) {

      if ($info['library'] && !file_exists($info['library'])) {
        $list[$method] = $info['title'] . ' - <span class="error">Missing '. $info['library'] .'</span>';
        if (isset($info['donwload']) && $info['download']) {
          $list[$method] = $list[$method] . ' - ' . l(t('Download here'), $info['download']);
        }
      }
      else {
        $list[$method] = $info['title'];
      }
    }
  }

  // If there are no handlers reporting then return now
  if (!$list) {
    return;
  }
  
  // Sort the list of methods
  asort($list);

  // None is always an option so add this at the top of the list, unless 'swf'
  if ($action != 'swf') {
    $list = array(t('None')) + $list;
  }

  // Determine the appropriate default based on $action
  $default = swftools_get_player($action, $profile);

  // swftools_get_player() returns FALSE for nothing configured, change to 0
  if (!$default) {
    $default = 0;
  }

  return array(
    '#type' => 'radios',
    '#title' => t('Default player for ' . $description),
    '#default_value' => $default,
    '#options' => $list,
  );

}


/**
 * flashvar and param option arrays. These are used for options settings in the
 * configuration screen and also as a lookup (particularly 'bool') to output the correct value for to html.
 *
 */
function _swftools_options() {
  // cache output each request
  static $swf_options = array();
  if (!count($swf_options)) {
    $swf_options['quality'] = array('low' => 'low', 'autolow' => 'autolow', 'medium' => 'medium', 'high' => 'high', 'autohigh' => 'autohigh', 'best' => 'best', );
    $swf_options['wmode'] = array('window' => 'window',  'opaque' => 'opaque',   'transparent' => 'transparent', );
    $swf_options['scale'] = array('showall' => 'showall', 'noborder' => 'noborder', 'exactfit' => 'exactfit', );
    $swf_options['align'] = array('default' => 'centered', 'l' => 'left', 'r' => 'right', 't' => 'top', 'b' => 'bottom', );
    $swf_options['salign'] = array('l' => 'left', 'r' => 'right', 't' => 'top', 'b' => 'bottom', 'tl' => 'top left', 'tr' => 'top right', 'bl' => 'bottom left', 'br' => 'bottom right', );
    $swf_options['bool'] = array('default' => 'default', 'true' => 'true', 'false' => 'false');
    $swf_options['allowscriptaccess'] = array('always' => 'always', 'sameDomain' => 'sameDomain', 'never' => 'never');
  }
  return $swf_options;
}


/**
 * Menu callback: Settings form for configuring CCK playlist fallbacks.
 */
function swftools_admin_cck_form() {
  
  // Get a list of all content types in use
  $content_types = content_types();
  
  // Get a list of all the CCK fields that are in use
  $fields = content_fields();
  
  // Get a list of all field types (this contains the list of formatters)
  $field_types = _content_field_types();

  // Put a description on the page
  $form['description'] = array(
    '#value' => '<p>' . t('For content that is being formatted as an SWF Tools playlist you can specify an alternate format that should be used if a
                           single file is passed to the playlist function. For example, display a single image as a regular image instead of placing
                           it in a slideshow.') . '</p>',
  );
  
  // Initialise an empty array 
  $swftools_types = array();
  
  // Discover what field types are supporting SWF Tools formatters
  foreach ($field_types as $type => $data) {
    if (isset($data['formatters']['swftools_playlist'])) {
      $swftools_types[] = $type;
    }
  }
  
  // Sort the list of types ready for output
  asort($swftools_types);
  
  // If the array is empty no field type is supporting the playlist formatter
  if (!$swftools_types) {

    // Just return an informative message
    $form['no fields'] = array(
      '#value' => '<p>' . t('No CCK fields that support SWF Tools playlists have been created.') . '</p>',
    );    
  }
  
  else {
  
    // Iterate over types that support SWF Tools formatters
    foreach ($swftools_types as $swftools_type) {
    
      // Add descriptive message
      $form['filefields'] = array(
        '#value' => '<p>' . t('Content types that contain fields that have been configured to be formatted as an
                             SWF Tools playlist are listed below.') . '</p>',
      );    
      
      // Initialise an array to hold formatters
      $options = array();
      
      // Collect all the available formatters
      foreach ($field_types[$swftools_type]['formatters'] as $formatter_name => $formatter_info) {
        $options[$formatter_name] = $formatter_info['label'];
      }
    
      // Add hidden as an optional formatter
      $options['hidden'] = t('<Hidden>');
      
      // Cycle through each content type
      foreach ($content_types as $type => $type_info) {
    
        // See if fields are in use on this type
        if (isset($type_info['fields'])) {
          
          // If fields are in use then cycle through them
          foreach ($type_info['fields'] as $field => $field_info) {
            
            // If field is a filefield type then we might be interested in it
            if ($field_info['type'] == $swftools_type) {
              
              // See if either of the teaser or body are set to be a playlist
              if ($field_info['display_settings']['teaser']['format'] == 'swftools_playlist' || $field_info['display_settings']['full']['format'] == 'swftools_playlist') {
    
                // If they are then create a form entry in the form swftools_{type}_{field}
                $form['swftools_' . $type . '_' . $field] = array(
                  '#title' => check_plain($type_info['name'] . ' - ' . $field_info['widget']['label']),
                  '#type' => 'select',
                  '#options' => $options,
                  '#default_value' => variable_get('swftools_' . $type . '_' . $field ,'swftools_playlist'),
                );
                
              }
            }
          }
        }
      }
    }
  }

  // Add custom form handler to flush cache upon submit
  $form['#submit'][] = 'swftools_admin_settings_submit';
  
  // Return a system settings form
  return system_settings_form($form);
  
}


/**
 * Convert 1/0 to true/false, or vice versa.
 * 
 * The settings form stores 1/0 for checkboxes, but flash wants to
 * use true/false in its configuration string. This function will
 * convert the appropriate options in the settings between the two.
 * 
 * @param $settings
 *   An array of embedding configuration configuration parameters.
 * @param $mode
 *   SWFTOOLS_ADMIN_STORE: convert 1/0 to true/false
 *   SWFTOOLS_ADMIN_RETRIEVE: convert true/false to 1/0
 * @return
 *   Nothing - the array is passed by reference.
 */
function swftools_admin_boolean_settings(&$settings, $mode) {
  
  // Encode the following parameters to yes/no
  $encode = array(
    'play',
    'menu',
    'loop',
    'allowfullscreen',
    'swliveconnect',
  );
  
  // Build the map to either encode or decode
  $map = array(
    SWFTOOLS_ADMIN_RETRIEVE => array(
      'true' => 1,
      'false' => 0,
    ),
    SWFTOOLS_ADMIN_STORE => array(
      0 => 'false',
      1 => 'true',
    ),
  );

  // Iterate over these settings encoding them, skipping settings that are not present
  foreach ($encode as $parameter) {
    $settings[$parameter] = $map[$mode][$settings[$parameter]];
  }
  
}


/**
 * Custom form handler to encode checkboxes to true/false.
 */
function swftools_admin_embed_submit($form, &$form_state, $decode = FALSE) {
  
  // Convert 1/0 to true/false
  swftools_admin_boolean_settings($form_state['values']['swftools_params'], SWFTOOLS_ADMIN_STORE);
  
}


/**
 * Returns a form definition for the profile file handling page.
 */
function swftools_handling_profile_form($profile = '') {
  
  // Get available actions from a fresh copy
  $actions = swftools_get_actions(TRUE);
  
  // Put each option on the form
  foreach ($actions as $action => $info) {
    if ($form_element = _swftools_admin_file_handling_options($action, $info['#description'], $profile)) {
      $form['swftools_handlers'][$action] = $form_element;
    }
  }
  
  // Initialise tree as we want to store arrays
  $form['swftools_handlers']['#tree'] = TRUE;
  
  // Return finished form
  return $form;

}


/**
 * Explodes a string of file extensions and converts them back in to an array.
 * 
 * On the admin page we show the user a list of actions and allow them to
 * associate extensions with each one. But when it comes to generating content
 * we will have the extension and we need to discover the action.
 * 
 * What we do in this submit handler is crunch the settings array so it is
 * available with extensions as key under the variable swftools_actions. So
 * we actually store this data twice, 
 */
function swftools_admin_extensions_submit($form, &$form_state) {
  
  // Explode the separate list back to an array of strings
  foreach ($form_state['values']['swftools_extensions'] as $action => $extensions) {

    // Explode in to separate pieces
    $temp = explode(' ', $extensions);
    
    // Trim white space
    $temp = array_map('trim', $temp);
    
    // Unset empty elements
    $temp = array_filter($temp);

    // Store the result
    $form_state['values']['swftools_extensions'][$action] = $temp;
  
  }

  // For use in a page it's easier to have things organised by extension
  $actions = array();
  
  foreach($form_state['values']['swftools_extensions'] as $key => $data) {
    $actions += array_fill_keys($data, $key);
  }
  
  $form_state['values']['swftools_actions'] = $actions;
  
}


/**
 * Explodes a string of file extensions and converts them back in to an array.
 */
function swftools_admin_mime_type_submit($form, &$form_state) {
  
  // Explode the separate list back to an array of strings
  $temp = explode("\n", $form_state['values']['swftools_mime_types_input']);

  // Now create the array of mime types
  $mime_types = array();
  
  // Iterate over each piece
  foreach ($temp as $setting) {

    // Explode each item again
    $setting = explode(' ', $setting);
    
    // Only valid if we have two pieces
    if (count($setting) == 2) {
    
      // Trim white space
      $setting = array_map('trim', $setting);
      
      // Store the result
      $mime_types[$setting[0]] = $setting[1];
      
    }
    
  }
  
  // Store the result as a new variable
  $form_state['values']['swftools_mime_types'] = $mime_types;
  
}
