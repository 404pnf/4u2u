<?php
// $Id: swftools_flowplayer3.admin.inc,v 1.1.2.10 2010/04/04 23:36:21 stuartgreenfield Exp $

/**
 * Menu callback for the FlowPlayer3 settings form.
 */
function swftools_flowplayer3_admin_settings() {

  // Retrieve options needed to populate select elements
  $options = _swftools_flowplayer3_options();

  // Fetch form definition from the profile as our start point
  $form = swftools_flowplayer3_profile_form();
  
  // Player path
  $form['swftools_flowplayer3_files'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Player and plugin files'),
  );

  $form['swftools_flowplayer3_files']['swftools_flowplayer3_file'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('swftools_flowplayer3_file', SWFTOOLS_FLOWPLAYER3_FILE),
    '#title' => t('Player file'),
    '#description' => t('Specify the name of the player file - with FlowPlayer 3 this typically changes with each new release.'),
    '#size' => 50,
  );
  
  $form['swftools_flowplayer3_files']['swftools_flowplayer3_stream_plugin'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('swftools_flowplayer3_stream_plugin', SWFTOOLS_FLOWPLAYER3_STREAM_PLUGIN),
    '#title' => t('RTMP streaming plugin'),
    '#description' => t('Specify the name of the rtmp streaming plugin.'),
    '#size' => 50,
  );
  
  $form['swftools_flowplayer3_files']['swftools_flowplayer3_javascript'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('swftools_flowplayer3_javascript', SWFTOOLS_FLOWPLAYER3_JAVASCRIPT),
    '#title' => t('Embedding script'),
    '#description' => t('The path to the FlowPlayer3 embedding script, if FlowPlayer3 embedding is enabled. When downloaded from flowplayer.org the script file is in a subdirectory <em>example</em> so a relative path may be needed when setting this value.'),
    '#size' => 50,
  );
  
  $form['swftools_flowplayer3_files']['swftools_flowplayer3_playlist_javascript'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('swftools_flowplayer3_playlist_javascript', SWFTOOLS_FLOWPLAYER3_PLAYLIST_JAVASCRIPT),
    '#title' => t('Playlist script'),
    '#description' => t('The path to the FlowPlayer3 playlist script which is used to enable HTML playlists.'),
    '#size' => 50,
  );  
  
  $form['swftools_flowplayer3_files']['swftools_flowplayer3_controls'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('swftools_flowplayer3_controls', ''),
    '#title' => t('Controls'),
    '#description' => t('The path to the FlowPlayer3 controls plug-in. Leave blank to use the default.'),
    '#size' => 50,
  );

  $form['swftools_flowplayer3_files']['swftools_flowplayer3_product_key'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('swftools_flowplayer3_product_key', ''),
    '#title' => t('Product key'),
    '#description' => t('Enter your product key if you are using the commercial version of FlowPlayer 3.'),
    '#size' => 50,
  );
  
  // Embedding setting
  $form['swftools_flowplayer3_embedding'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Flowplayer3 embedding'),
  );

  $form['swftools_flowplayer3_embedding']['swftools_flowplayer3_embed'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('swftools_flowplayer3_embed', FALSE),
    '#title' => t('Use FlowPlayer3 embedding'),
    '#description' => t('When checked the default embedding method wil be over-ridden and the FlowPlayer3 embedding script will be used. The script file must be installed and the correct path added in <em>Player and plugin files</em> above.'),
  );
  
  $form['swftools_flowplayer3_embedding']['swftools_flowplayer3_load'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('swftools_flowplayer3_load', TRUE),
    '#title' => t('Load FlowPlayers immediately'),
    '#description' => t('If this option is cleared then the FlowPlayers will not load until the container content is clicked.'),
  );
  
  $form['swftools_flowplayer3_embedding']['swftools_flowplayer3_playlist'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('swftools_flowplayer3_playlist', FALSE),
    '#title' => t('Generate HTML playlists (experimental)'),
    '#description' => t('If checked then a simple HTML list will be output beneath players that have been given a playlist. This feature is experimental and the output is not yet themeable'),
  );
  
  // Add custom form handler to flush cache upon submit
  $form['#submit'][] = 'swftools_admin_settings_submit';
  
  // Return finished form
  return system_settings_form($form);

}


/**
 * Options used to populate the select elements of the form above
 * Collect them here to make them easier to find and adjust!
 */
function _swftools_flowplayer3_options() {
  $options['bool'] = array('true' => 'true', 'false' => 'false');
  $options['scaling'] = array('fit' => 'fit', 'half' => 'half', 'orig' => 'orig', 'scale' => 'scale');
  $options['autoHide'] = array('never' => 'never', 'always' => 'always', 'fullscreen' => 'fullscreen');
  $options['backgroundRepeat'] = array('no-repeat' => 'no-repeat', 'repeat' => 'repeat');

  // Options for radios
  $options['enabled'] = array(
    'true' => t('Enabled'),
    'false' => t('Disabled'),
  );
  $options['accessible'] = array(
    1 => t('Enabled'),
    0 => t('Disabled'),
  );
  $options['visible'] = array(
    1 => t('Visible'),
    0 => t('Hidden'),
  );
  $options['scaling'] = array(
    'fit' => t('Fit - fit to window by preserving the aspect ratio encoded in the file\'s metadata.'),
    'half' => t('Half - half-size (preserves aspect ratio)'),
    'orig' => t('Original - use the dimensions encoded in the file. If it is too big for the available space it is scaled using the \'fit\' option.'),
    'scale' => t('Scale - Scale the video to fill all available space. Ignores the dimensions in the metadata.'),
  );
  $options['linkWindow'] = array(
    '_blank' => t('_blank - a new window.'),
    '_parent' => t('_parent - the parent of the current window.'),
    '_self' => t('_self - the current frame in the current window.'),
    '_top' => t('_top - the top level frame in the current window.'),
  );
  $options['gradient'] = array(
    'none' => t('None'),
    'low' => t('Low'),
    'medium' => t('Medium'),
    'high' => t('High'),
  );
  $options['autoHide'] = array(
    'never' => t('Never - the control bar is always shown.'),
    'always' => t('Always - the control bar will always hide itself when not in use.'),
    'fullscreen' => t('Fullscreen - the control will be only autohide during full screen playback.'),
  );
  return $options;
}


/**
 * Retrieve the color scheme information for FlowPlayer3 styling.
 * 
 * @return
 *   An array of data defining color information and names for each preset style.  
 */
function swftools_flowplayer3_get_info() {

  // Cache $info
  static $info;
  
  // If $info is populated, return it
  if (isset($info)) {
    return $info;
  }
  
  // Gather $info
  $path = drupal_get_path('module', 'swftools_flowplayer3');
  $file = $path . '/swftools_flowplayer3.colorschemes.inc';
  include $file;
  return $info;
}


/**
 * Helper function to retrieve the color palette for a particular style.
 * 
 * @param $default
 *   Optional parameter (default false). If false or omitted returns the
 *   current palette, if true returns the default palette.
 * @return
 *   An array of key/value pairs - the key defines the componenent and the
 *   value defines the color.
 */
function swftools_flowplayer3_get_palette($default = false, $profile = '') {

  // Define palette properties
  $fields = array(
    'backgroundColor',
    'controlbarbackgroundColor',
    'timeColor',
    'durationColor',
    'progressColor',
    'bufferColor',
    'sliderColor',
    'buttonColor',
    'buttonOverColor',
    'volumeSliderColor',
    'timeBgColor',
  );

  // Get the theme information
  $info = swftools_flowplayer3_get_info();

  // Get the keys (strings of colors) from the available schemes
  $keys = array_keys($info['schemes']);
  
  // Exploded the first (default) string in an array
  foreach (explode(',', array_shift($keys)) as $k => $scheme) {
    // Build a palette
    $palette[$fields[$k]] = $scheme;
  }
    
  // If default is required, return it, otherwise load palette variable
  return $default ? $palette : swftools_variable_get('swftools_flowplayer3_palette', $palette, $profile);
}


/**
 * Helper function to produce the color scheme form for the flowplayer
 */
function swftools_flowplayer3_scheme_form(&$form_state, $profile = '') {
  
  // Get path to the flowplayer3 module
  $base = drupal_get_path('module', 'swftools_flowplayer3');

  // Add Farbtastic color picker
  drupal_add_css('misc/farbtastic/farbtastic.css');
  drupal_add_js('misc/farbtastic/farbtastic.js');

  // Add custom CSS/JS
  drupal_add_css($base . '/swftools_flowplayer3.colorpicker.css');
  drupal_add_js($base . '/swftools_flowplayer3.colorpicker.js');
  drupal_add_js(array('color' => array(
    'reference' => swftools_flowplayer3_get_palette(true, $profile)
  )), 'setting');

  // Get info about the current theme color scheme
  $info = swftools_flowplayer3_get_info();
  
  // See if we're using a predefined scheme
  // The variable is empty if using the default, or an array of key/value pairs otherwise
  $current = implode(',', swftools_variable_get('swftools_flowplayer3_palette', array(), $profile));

  // Note: we use the original theme when the default scheme is chosen.
  $current = isset($info['schemes'][$current]) ? $current : ($current == '' ? reset($info['schemes']) : '');

  // Add custom to scheme selector options
  $info['schemes'][''] = t('Custom');
  
  // Add scheme selector to form (the value is a comma separated string of hex colors)
  $form['swftools_flowplayer3_scheme'] = array(
    '#type' => 'select',
    '#title' => t('Color set'),
    '#options' => $info['schemes'],
    '#default_value' => $current,
  );

  // Get current palette as an array
  $palette = swftools_flowplayer3_get_palette(false, $profile);
  
  // Build an array of titles to be used for each palette element
  $names = array(
    'backgroundColor' => array(
      '#title' => t('Background color'),
    ),
    'controlbarbackgroundColor' => array(
      '#title' => t('Control bar background color'),
    ),
    'timeColor' => array(
      '#title' => t('Elapsed time font color'),
    ),
    'durationColor' => array(
      '#title' => t('Total time font color'),
    ),
    'progressColor' => array(
      '#title' => t('Progress bar color'),
    ),
    'bufferColor' => array(
      '#title' => t('Buffer color'),
    ),
    'sliderColor' => array(
      '#title' => t('Slider color'),
    ),
    'buttonColor' => array(
      '#title' => t('Button color'),
    ),
    'buttonOverColor' => array(
      '#title' => t('Button over color'),
    ),
    'volumeSliderColor' => array(
      '#title' => t('Volume slider color'),
    ),
    'timeBgColor' => array(
      '#title' => t('Time background color'),
    ),
  );
  
  // Form elements to be part of a tree
  $form['swftools_flowplayer3_palette']['#tree'] = true;
  
  // Cycle through each palette element
  foreach ($palette as $name => $value) {
    $form['swftools_flowplayer3_palette'][$name] = array(
      '#type' => 'textfield',
      '#title' => $names[$name]['#title'],
      '#default_value' => $value,
      '#size' => 8,
    );
  }

  // Return the form
  return $form;
}


/**
 * Theme the FlowPlayer3 color settings for the admin form.
 */
function theme_swftools_flowplayer3_scheme_form($form, $profile = '') {

  $output = '';

  // Wrapper
  $output .= '<div class="color-form clear-block">';

  // Color schemes
  $output .= drupal_render($form['swftools_flowplayer3_scheme']);

  // Palette
  $output .= '<div id="palette" class="clear-block">';
  foreach (element_children($form['swftools_flowplayer3_palette']) as $name) {
    $output .= drupal_render($form['swftools_flowplayer3_palette'][$name]);
  }
  $output .= '</div>';
  
  // Close wrapper
  $output .= '</div>';

  return $output;
}


function swftools_flowplayer3_profile_form($profile = '') {
  
  // Retrieve combination of default and saved settings
  $saved_settings = _swftools_flowplayer3_settings($profile);
  
  // Retrieve options needed to populate select elements
  $options = _swftools_flowplayer3_options();

  // Initialise array to hold form
  $form = array();
  
  // Add color scheme form
  $form['color'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Color scheme'),
    '#weight' => -1,
    '#attributes' => array('id' => 'swftools_flowplayer3_scheme_form'),
    '#theme' => 'swftools_flowplayer3_scheme_form',
  );
  
  $form['color'] += swftools_flowplayer3_scheme_form($form_state, $profile);
  
  // Initialise tree from this point forward as want to store arrays
  $form['swftools_flowplayer3']['#tree'] = TRUE;
  
  // Clip settings
  $form['swftools_flowplayer3']['clip'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Overall clip properties'),
  );
  
  $form['swftools_flowplayer3']['clip']['autoPlay'] = array(
    '#type' => 'radios',
    '#options' => $options['enabled'],
    '#default_value' => $saved_settings['clip']['autoPlay'],
    '#title' => t('Auto play'),
    '#description' => t('When enabled the player will being playback immediately after it has finished loading.'),
  );
  
  $form['swftools_flowplayer3']['clip']['autoBuffering'] = array(
    '#type' => 'radios',
    '#options' => $options['enabled'],
    '#default_value' => $saved_settings['clip']['autoBuffering'],
    '#title' => t('Auto buffering'),
    '#description' => t('When enabled loading of clip into the player\'s memory will begin as soon as the player is loaded on the page.'),
  );

  $form['swftools_flowplayer3']['clip']['scaling'] = array(
    '#type' => 'radios',
    '#options' => $options['scaling'],
    '#default_value' => $saved_settings['clip']['scaling'],
    '#title' => t('Scaling'),
    '#description' => t('This determines how a video clip should be scaled if it is bigger than the player canvas.'),
  );

  $form['swftools_flowplayer3']['clip']['start'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['clip']['start'],
    '#title' => t('Start'),
    '#description' => t('Specify start point for playback (only works with a streaming server). Streaming support not yet in place for SWF Tools.'),
    '#size' => 8,
  );

  $form['swftools_flowplayer3']['clip']['duration'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['clip']['duration'],
    '#title' => t('Duration'),
    '#description' => t('The time (in seconds) for which a video clip should be played until playback ceases.'),
    '#size' => 8,
  );

  $form['swftools_flowplayer3']['clip']['accelerated'] = array(
    '#type' => 'radios',
    '#options' => $options['enabled'],
    '#default_value' => $saved_settings['clip']['accelerated'],
    '#title' => t('Acceleration'),
    '#description' => t('When enabled browsers using Flash 9 or higher will use hardware-accelerated full screen mode.'),
  );

  $form['swftools_flowplayer3']['clip']['bufferLength'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['clip']['bufferLength'],
    '#title' => t('Buffer length'),
    '#description' => t('The amount of video data (in seconds) which should be loaded into Flowplayer\'s memory in advance of playback commencing. '),
    '#size' => 8,
  );

  $form['swftools_flowplayer3']['clip']['provider'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['clip']['provider'],
    '#title' => t('Provider'),
    '#description' => t('Not sure if this will be supported in this module. Need to investigate.'),
  );

  $form['swftools_flowplayer3']['clip']['fadeInSpeed'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['clip']['fadeInSpeed'],
    '#title' => t('Fade in speed'),
    '#description' => t('Time in milliseconds to fade from zero to full opacity upon commencement of video playback.'),
    '#size' => 8,
  );

  $form['swftools_flowplayer3']['clip']['fadeOutSpeed'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['clip']['fadeOutSpeed'],
    '#title' => t('Fade out speed'),
    '#description' => t('Time in milliseconds to fade from full to zero opacity upon completion of video playback.'),
    '#size' => 8,
  );

  $form['swftools_flowplayer3']['clip']['linkUrl'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['clip']['linkUrl'],
    '#title' => t('Link url'),
    '#description' => t('The URL to direct users to when clicking the video screen.'),
  );

  $form['swftools_flowplayer3']['clip']['linkWindow'] = array(
    '#type' => 'radios',
    '#options' => $options['linkWindow'],
    '#default_value' => $saved_settings['clip']['linkWindow'],
    '#title' => t('Link window'),
    '#description' => t('This determines where the url defined by the linkUrl setting will open.'),
  );

  $form['swftools_flowplayer3']['clip']['live'] = array(
    '#type' => 'radios',
    '#options' => $options['enabled'],
    '#default_value' => $saved_settings['clip']['live'],
    '#title' => t('Live'),
    '#description' => t('RTMP streaming servers support live streaming, which means that it is possible to setup a video camera or other live video source to stream live video data to Flowplayer. If you have an RTMP server which is providing a live video stream, you should set this property to enabled. Streaming support not yet in place for SWF Tools.'),
  );

  $form['swftools_flowplayer3']['clip']['cuePointMultiplier'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['clip']['cuePointMultiplier'],
    '#title' => t('Cue point multiplier'),
    '#description' => t('The times of embedded cuepoints are multiplied by this value before being used. Some encoding tools embed cuepoints in seconds but Flowplayer processes cuepoints in milliseconds. Note that the times are also rounded to the nearest 100 milliseconds. For example, if a file has a cuepoint at 5.535 seconds, the cuepoint is fired at 5500 milliseconds (assuming the default multiplier value of 1000).'),
    '#size' => 8,
  );

  // Control bar settings
  $form['swftools_flowplayer3']['controls'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Controlbar properties'),
  );

  $form['swftools_flowplayer3']['controls']['backgroundGradient'] = array(
    '#type' => 'select',
    '#options' => $options['gradient'],
    '#default_value' => $saved_settings['controls']['backgroundGradient'],
    '#title' => t('Background gradient'),
    '#description' => t('The control bar can be displayed with a fade that runs vertically, or if set to none it will be a flat color.'),
  );
  
  $form['swftools_flowplayer3']['controls']['progressGradient'] = array(
    '#type' => 'select',
    '#options' => $options['gradient'],
    '#default_value' => $saved_settings['controls']['progressGradient'],
    '#title' => t('Progress gradient'),
    '#description' => t('The progress bar can be displayed with a fade that runs vertically, or if set to none it will be a flat color.'),
  );

  $form['swftools_flowplayer3']['controls']['bufferGradient'] = array(
    '#type' => 'select',
    '#options' => $options['gradient'],
    '#default_value' => $saved_settings['controls']['bufferGradient'],
    '#title' => t('Buffer gradient'),
    '#description' => t('The buffer progress can be displayed with a fade that runs vertically, or if set to none it will be a flat color.'),
  );

  $form['swftools_flowplayer3']['controls']['sliderGradient'] = array(
    '#type' => 'select',
    '#options' => $options['gradient'],
    '#default_value' => $saved_settings['controls']['sliderGradient'],
    '#title' => t('Slider gradient'),
    '#description' => t('The slider can be displayed with a fade that runs vertically, or if set to none it will be a flat color.'),
  );

  $form['swftools_flowplayer3']['controls']['volumeSliderGradient'] = array(
    '#type' => 'select',
    '#options' => $options['gradient'],
    '#default_value' => $saved_settings['controls']['volumeSliderGradient'],
    '#title' => t('Volume slider gradient'),
    '#description' => t('The volume bar can be displayed with a fade that runs vertically, or if set to none it will be a flat color.'),
  );
  
  $form['swftools_flowplayer3']['controls']['autoHide'] = array(
    '#type' => 'select',
    '#options' => $options['autoHide'],
    '#default_value' => $saved_settings['controls']['autoHide'],
    '#title' => t('Hide control bar'),
    '#description' => t('Specifies whether the controlbar should be hidden when the user is not actively using the player.'),
  );

  $form['swftools_flowplayer3']['controls']['play'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['controls']['play'],
    '#title' => t('Play button'),
    '#description' => t('When enabled the play button will be shown. When disabled it will be hidden.'),
  );

  $form['swftools_flowplayer3']['controls']['volume'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['controls']['volume'],
    '#title' => t('Volume button'),
    '#description' => t('When enabled the volume button will be shown. When disabled it will be hidden.'),
  );

  $form['swftools_flowplayer3']['controls']['mute'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['controls']['mute'],
    '#title' => t('Mute button'),
    '#description' => t('When enabled the mute button will be shown. When disabled it will be hidden.'),
  );

  $form['swftools_flowplayer3']['controls']['time'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['controls']['time'],
    '#title' => t('Time display'),
    '#description' => t('When enabled the timer will be shown. When disabled it will be hidden.'),
  );

  $form['swftools_flowplayer3']['controls']['stop'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['controls']['stop'],
    '#title' => t('Stop button'),
    '#description' => t('When enabled the stop button will be shown. When disabled it will be hidden.'),
  );

  $form['swftools_flowplayer3']['controls']['playlist'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['controls']['playlist'],
    '#title' => t('Playlist buttons'),
    '#description' => t('When enabled the playlist buttons will be shown. When disabled they will be hidden. These buttons will allow navigation through the playlist entries that have been configured for the player. These buttons are always hidden if there are less than two entries in the playlist.'),
  );

  $form['swftools_flowplayer3']['controls']['fullscreen'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['controls']['fullscreen'],
    '#title' => t('Fullscreen button'),
    '#description' => t('When enabled the full screen button will be shown. When disabled it will be hidden. Note that to enabled full screen playback the flash settings must also be set to allow full screen, otherwise the button will not work.'),
  );

  $form['swftools_flowplayer3']['controls']['scrubber'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['controls']['scrubber'],
    '#title' => t('Scrubber'),
    '#description' => t('The scrubber is the timeline/playhead combination. This specifies whether it should be visible.'),
  );

  $form['swftools_flowplayer3']['controls']['borderRadius'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['controls']['borderRadius'],
    '#title' => t('Border radius'),
    '#description' => t('Specifies the amount of rounding for the control bar. Larger values mean more rounding.'),
    '#size' => 8,
  );

  $form['swftools_flowplayer3']['controls']['scrubberHeightRatio'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['controls']['scrubberHeightRatio'],
    '#title' => t('Scrubber height ratio'),
    '#description' => t('How much the scrubber handle should take of the controlbar total height. A value of 1.0 means that the scrubber handle takes the entire available height in the controlbar plugin.'),
    '#size' => 8,
  );
  
  $form['swftools_flowplayer3']['controls']['scrubberBarHeightRatio'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['controls']['scrubberBarHeightRatio'],
    '#title' => t('Scrubber bar height ratio'),
    '#description' => t('The ratio between the scrubber bar and the scrubber handle. A value of 1.0 means that the scrubber bar\'s height is the same as the handle\'s height.'),
    '#size' => 8,
  );
  
  $form['swftools_flowplayer3']['controls']['volumeSliderHeightRatio'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['controls']['volumeSliderHeightRatio'],
    '#title' => t('Volume slider height ratio'),
    '#description' => t('How much the volume slider handle should take of the controlbar total height.'),
    '#size' => 8,
  );
  
  $form['swftools_flowplayer3']['controls']['volumeBarHeightRatio'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['controls']['volumeBarHeightRatio'],
    '#title' => t('Volume bar height ratio'),
    '#description' => t('The ratio between the volume bar and the voume slider handle. A value of 1.0 means that the bar\'s height is the same as the handle\'s height.'),
    '#size' => 8,
  );
  
  $form['swftools_flowplayer3']['controls']['timeBgHeightRatio'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['controls']['timeBgHeightRatio'],
    '#title' => t('Time background height ratio'),
    '#description' => t('How much the time/duration display should take of the controlbar total height. A value of 1.0 means that it takes the entire available height of the controlbar plugin.'),
    '#size' => 8,
  );
  
  $form['swftools_flowplayer3']['controls']['hideDelay'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['controls']['hideDelay'],
    '#title' => t('Hide delay'),
    '#description' => t('The delay in milliseconds before the controlbar is automatically hidden. The timer starts over again when the user stops moving the mouse or moves the mouse out of the player. Specifying 0 here causes the controlbar to hide immediately.'),
    '#size' => 8,
  );
  
  // Canvas settings
  $form['swftools_flowplayer3']['canvas'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Canvas properties'),
  );
  
  $form['swftools_flowplayer3']['canvas']['height'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['canvas']['height'],
    '#title' => t('Height'),
    '#description' => t('The height of the player in pixels.'),
    '#size' => 8,
  );
  
  $form['swftools_flowplayer3']['canvas']['width'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['canvas']['width'],
    '#title' => t('Width'),
    '#description' => t('The width of the player in pixels.'),
    '#size' => 8,
  );

  $form['swftools_flowplayer3']['canvas']['backgroundImage'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['canvas']['backgroundImage'],
    '#title' => t('Background image'),
    '#description' => t('The absolute or relative path to the image that should be used as the background to this plugin. Supported formats are GIF, JPEG and PNG. The syntax is similar to CSS in that you must enclose your path inside a url() wrapper.'),
    '#size' => 24,
  );

  $form['swftools_flowplayer3']['canvas']['backgroundRepeat'] = array(
    '#type' => 'select',
    '#options' => $options['backgroundRepeat'],
    '#default_value' => $saved_settings['canvas']['backgroundRepeat'],
    '#title' => t('Background repeat'),
    '#description' => t('Default is "repeat", which makes the background image repeat both horizontally and vertically. "no-repeat" displays the background image only once from the top left-hand corner.'),
  );

  $form['swftools_flowplayer3']['canvas']['backgroundGradient'] = array(
    '#type' => 'select',
    '#options' => $options['gradient'],
    '#default_value' => $saved_settings['canvas']['backgroundGradient'],
    '#title' => t('Background gradient'),
    '#description' => t('Gradient setting for the canvas.'),
  );

  $form['swftools_flowplayer3']['canvas']['border'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['canvas']['border'],
    '#title' => t('Border'),
    '#description' => t('Draws a border around a plugin\'s edges. The syntax follows the CSS standard: width style color. For example: "1px solid #cccccc". The only supported style currently is "solid", but the width and colour can be set to any valid value.'),
    '#size' => 24,
  );

  $form['swftools_flowplayer3']['canvas']['borderRadius'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['canvas']['borderRadius'],
    '#title' => t('Border radius'),
    '#description' => t('Specifies the amount of rounding for each corner. Larger values mean more rounding.'),
    '#size' => 8,
  );

  // Play button configuration
  $form['swftools_flowplayer3']['play'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Play button properties'),
  );  

  $form['swftools_flowplayer3']['play']['url'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['play']['url'],
    '#title' => t('Button url'),
    '#description' => t('A relative path to the play button, which can be a JPG, PNG or SWF file. Note that the button can only be changed in the commercial versions of FlowPlayer.'),
    '#size' => 24,
  );

  $form['swftools_flowplayer3']['play']['opacity'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['play']['opacity'],
    '#title' => t('Opacity'),
    '#description' => t('Opacity (0.0-1.0)'),
    '#size' => 5,
  );
  
  $form['swftools_flowplayer3']['play']['fadeSpeed'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['play']['fadeSpeed'],
    '#title' => t('Fade speed'),
    '#description' => t('Time in milliseconds for the play button to fade out when the video starts.'),
    '#size' => 8,
  );
  
  $form['swftools_flowplayer3']['play']['rotateSpeed'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['play']['rotateSpeed'],
    '#title' => t('Rotate speed'),
    '#description' => t('The rotation speed of the buffering animation, in milliseconds.'),
    '#size' => 8,
  );
  
  $form['swftools_flowplayer3']['play']['height'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['play']['height'],
    '#title' => t('Height'),
    '#description' => t('The height of the play button, either in pixels or as a percentage.'),
    '#size' => 8,
  );
  
  $form['swftools_flowplayer3']['play']['width'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['play']['width'],
    '#title' => t('Width'),
    '#description' => t('The width of the play button, either in pixels or as a percentage.'),
    '#size' => 8,
  );

  $form['swftools_flowplayer3']['play']['label'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['play']['label'],
    '#title' => t('Label'),
    '#description' => t('Text to display with the play button.'),
    '#size' => 25,
  );
  
  $form['swftools_flowplayer3']['play']['replayLabel'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['play']['replayLabel'],
    '#title' => t('Replay label'),
    '#description' => t('Text to display with the replay button.'),
    '#size' => 25,
  );
  
  // Logo configuration
  $form['swftools_flowplayer3']['logo'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Logo properties (commercial players only)'),
    '#description' => t('This section is only relevant if you are using a commercial version of FlowPlayer.'),
  );

  $form['swftools_flowplayer3']['logo']['use_logo'] = array(
    '#type' => 'checkbox',
    '#default_value' => $saved_settings['logo']['use_logo'],
    '#title' => t('Use logo settings'),
    '#description' => t('Check this option to pass the logo settings to FlowPlayer.'),
  ); 
  
  $form['swftools_flowplayer3']['logo']['url'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['logo']['url'],
    '#title' => t('URL'),
    '#description' => t('Relative URL of logo image.'),
    '#size' => 100,
  );
  
   $form['swftools_flowplayer3']['logo']['displayTime'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['logo']['displayTime'],
    '#title' => t('Display time'),
    '#description' => t('mSecs to display logo.'),
    '#size' => 5,
  );  

  $form['swftools_flowplayer3']['logo']['fadeSpeed'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['logo']['fadeSpeed'],
    '#title' => t('Fade speed'),
    '#description' => t('Logo fade to opacity 0 speed.'),
    '#size' => 5,
  ); 

  $form['swftools_flowplayer3']['logo']['opacity'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['logo']['opacity'],
    '#title' => t('Opacity'),
    '#description' => t('Opacity (0.0-1.0)'),
    '#size' => 5,
  ); 
  
  $form['swftools_flowplayer3']['logo']['top'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['logo']['top'],
    '#title' => t('Top offset'),
    '#description' => t('Logo position from top.'),
    '#size' => 5,
  ); 
  
  $form['swftools_flowplayer3']['logo']['right'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['logo']['right'],
    '#title' => t('Right offset'),
    '#description' => t('Logo position from right.'),
    '#size' => 5,
  ); 
  
  $form['swftools_flowplayer3']['logo']['width'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['logo']['width'],
    '#title' => t('Width'),
    '#description' => t('Logo width.'),
    '#size' => 5,
  ); 
  
  $form['swftools_flowplayer3']['logo']['height'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['logo']['height'],
    '#title' => t('Height'),
    '#description' => t('Logo height.'),
    '#size' => 5,
  ); 

  $form['swftools_flowplayer3']['logo']['zIndex'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['logo']['zIndex'],
    '#title' => t('Z-order'),
    '#description' => t('Logo z-order - just leave it as is.'),
    '#size' => 5,
  ); 

  $form['swftools_flowplayer3']['logo']['fullscreenOnly'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['logo']['fullscreenOnly'],
    '#title' => t('Fullscreen only'),
    '#description' => t('When set to true the logo is only shown when fullscreen.'),
  );
  
  $form['swftools_flowplayer3']['logo']['linkUrl'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['logo']['linkUrl'],
    '#title' => t('Link URL'),
    '#description' => t('URL to open if the logo is clicked.'),
    '#size' => 100,
  );

  $form['swftools_flowplayer3']['logo']['linkWindow'] = array(
    '#type' => 'select',
    '#options' => $options['linkWindow'],
    '#default_value' => $saved_settings['logo']['linkWindow'],
    '#title' => t('Link window'),
    '#description' => t('Where should the URL open when the logo is clicked.'),
  );
  
  $form['swftools_flowplayer3']['accessibility'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Accessibility'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['swftools_flowplayer3']['accessibility']['accessible'] = array(
    '#type' => 'radios',
    '#options' => $options['accessible'],
    '#default_value' => $saved_settings['accessibility']['accessible'],
    '#title' => t('Accessibility controls'),
    '#description' => t('When enabled accessible links will be put below the player to allow it to be controlled using a keyboard or other input device.'),
  );

  $form['swftools_flowplayer3']['accessibility']['accessible_visible'] = array(
    '#type' => 'radios',
    '#options' => $options['visible'],
    '#default_value' => $saved_settings['accessibility']['accessible_visible'],
    '#title' => t('Control visibility'),
    '#description' => t('Accessible controls can be hidden so they do not appear on the page, but they will still be accessible to devices such as screen readers.'),
  );
  
  // Return finished form
  return $form;

}
