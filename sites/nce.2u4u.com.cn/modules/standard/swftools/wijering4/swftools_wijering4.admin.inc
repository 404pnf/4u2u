<?php
// $Id: swftools_wijering4.admin.inc,v 1.1.2.13 2010/04/12 23:16:22 stuartgreenfield Exp $

function swftools_wijering4_admin_form() {

  // Fetch form definition
  $form = swftools_wijering4_profile_form();
  
  // Add custom form handler to flush cache upon submit
  $form['#submit'][] = 'swftools_admin_settings_submit';
  
  // Return finished form
  return system_settings_form($form);

}


/**
 * Submit handler to filter out form settings that are either empty strings or 'default'
 */

function swftools_wijering4_admin_form_submit($form, &$form_state) {
  
  // Keep only those items that actually have a value
  foreach($form_state['values']['swftools_jwplayer4'] as $key => $settings) {
    if($temp = array_diff($settings, array('', 'default'))) {
      $filtered_settings[$key] = $temp;
    }
  }
  
  // Replace full suite of values with the reduced set we created
  $form_state['values']['swftools_jwplayer4'] = $filtered_settings;
  
}


/**
 * Options used to populate the select elements of the form above
 * Collect them here to make them easier to find and adjust!
 */
function _swftools_wijering4_options() {

  // Define options
  $options['type'] = array('default' => 'default', 'sound' => 'sound', 'image' => 'image', 'video' => 'video', 'youtube' => 'youtube', 'camera' => 'camera', 'http' => 'http', 'rtmp' => 'rtmp', );
  $options['overstretch'] = array('default' => 'default', 'uniform' => 'uniform', 'fill' => 'fill', 'exactfit' => 'exactfit', 'none' => 'none', );
  $options['repeat'] = array('default' => 'default', 'none' => 'none', 'list' => 'list', 'always' => 'always', );
  $options['linktarget'] = array('default' => 'default', '_self' => '_self', '_blank' => '_blank', 'none' => 'none', );
  $options['playlist'] = array('default' => 'default', 'bottom' => 'bottom', 'over' => 'over', 'right' => 'right', 'none' => 'none', );
  $options['controlbar'] = array('default' => 'default', 'bottom' => 'bottom', 'over' => 'over', 'none' => 'none', );
  $options['displayclick'] = array('default' => 'default', 'play' => 'play', 'link' => 'link', 'fullscreen' => 'fullscreen', 'none' => 'none', 'mute' => 'mute', 'next' => 'next', );
  $options['bool'] = array('default' => 'default', 'true' => 'true', 'false' => 'false');
  
  // Return the result
  return $options;

}


/**
 * Autocompleter to suggest possible skin names.
 * 
 * @param $string
 *   The partial name of the skin.
 * @return
 *   A list of possible matches.
 */
function swftools_wijering4_autocomplete_skin($string = '') {
  
  // Only do something if there is a string to be matched
  if ($string) {

    // Scan the mediaplayer4/skins directory for swf files
    $skins = file_scan_directory(SWFTOOLS_LIBRARIES . '/mediaplayer4/skins', '\.swf$');
  
    // Build an array skin names
    $possible_values = array();
    foreach ($skins as $skin) {
      $possible_values[] = $skin->basename;
    }
  
    // Find matches
    $matches = array();  
    foreach ($possible_values as $value) {
      if (preg_match("/$string/i", $value)) {
        $matches[$value] = $value;
      }
    }
    
    print drupal_json($matches);
  } 

}


/**
 * Returns a form definition for use by the profile system.
 *
 * @return
 *   A form definition array
 */
function swftools_wijering4_profile_form($profile = '') {
  
  /**
   * Retrieve profile settings, if they have been created.
   * If there is no profile then the global defaults will be used, which might be
   * those from the module defaults, or those from the primary settings page.
   * This seems like a logical behavior to have!
   */
  $saved_settings = _swftools_wijering4_settings($profile, SWFTOOLS_FULL_SETTINGS);
  
  // Retrieve options needed to populate select elements
  $options = _swftools_wijering4_options();
  
  // See if colorpicker 2 is loaded
  $colorfield = function_exists('colorpicker_2_or_later') ? 'colorpicker_textfield' : 'textfield';

  // Initialise tree from this point forward as want to store arrays
  $form['swftools_jwplayer4']['#tree'] = TRUE;
  
  $form['swftools_jwplayer4']['basic'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Basic'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['swftools_jwplayer4']['basic']['playlistsize'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['basic']['playlistsize'],
    '#size' => 8,
    '#maxlength' => 5,
    '#title' => t('Playlist size'),
    '#description' => t('Leave blank for default. (<em>playlistsize</em>)'),
  );
  
  $form['swftools_jwplayer4']['basic']['height'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['basic']['height'],
    '#size' => 8,
    '#maxlength' => 5,
    '#title' => t('Height'),
    '#description' => t('Leave blank for default. (<em>height</em>)'),
  );
  
  $form['swftools_jwplayer4']['basic']['width'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['basic']['width'],
    '#size' => 8,
    '#maxlength' => 5,
    '#title' => t('Width'),
    '#description' => t('Leave blank for default. (<em>width</em>)'),
  );
  
  $form['swftools_jwplayer4']['color'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Color'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['swftools_jwplayer4']['color']['backcolor'] = array(
    '#type' => $colorfield,
    '#default_value' => $saved_settings['color']['backcolor'],
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Background color'),
    '#description' => t('Enter a hex value eg. for white enter <b>#FFFFFF</b>. (<em>backcolor</em>)'),
  );
  
  $form['swftools_jwplayer4']['color']['frontcolor'] = array(
    '#type' => $colorfield,
    '#default_value' => $saved_settings['color']['frontcolor'],
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Text color'),
    '#description' => t('Enter a hex value eg. for white enter <b>#FFFFFF</b>. (<em>frontcolor</em>)'),
  );
  
  $form['swftools_jwplayer4']['color']['lightcolor'] = array(
    '#type' => $colorfield,
    '#default_value' => $saved_settings['color']['lightcolor'],
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Rollover color'),
    '#description' => t('Enter a hex value eg. for white enter <b>#FFFFFF</b>. (<em>lightcolor</em>)'),
  );
  
  $form['swftools_jwplayer4']['color']['screencolor'] = array(
    '#type' => $colorfield,
    '#default_value' => $saved_settings['color']['screencolor'],
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Screen color'),
    '#description' => t('Enter a hex value eg. for white enter <b>#FFFFFF</b>. (<em>screencolor</em>)'),
  );
  
  $form['swftools_jwplayer4']['appearance'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Appearance'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['swftools_jwplayer4']['appearance']['skin'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['appearance']['skin'],
    '#title' => t('Skin URL'),
    '#description' => t('The name of a player skin in the local library (including the extension), or a full url to a skin. (<em>skin</em>)'),
    '#autocomplete_path' => 'admin/settings/swftools/wijering4/autocomplete',
  );
  
  $form['swftools_jwplayer4']['appearance']['logo'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['appearance']['logo'],
    '#title' => t('Logo URL'),
    '#description' => t('Full url to logo for a watermark, use PNG files for best results. (<em>logo</em>)'),
  );
  
  $form['swftools_jwplayer4']['appearance']['overstretch'] = array(
    '#type' => 'select',
    '#default_value' => $saved_settings['appearance']['overstretch'],
    '#title' => t('Overstretch'),
    '#options' => $options['overstretch'],
    '#description' => t('Defines how to stretch images to fit the display. (<em>overstretch</em>)'),
  );
  
  $form['swftools_jwplayer4']['appearance']['controlbar'] = array(
    '#type' => 'select',
    '#default_value' => $saved_settings['appearance']['controlbar'],
    '#title' => t('Control bar position'),
    '#options' => $options['controlbar'],
    '#description' => t('Defines where to position the control bar. (<em>controlbar</em>)'),
  );
  
  $form['swftools_jwplayer4']['appearance']['playlist'] = array(
    '#type' => 'select',
    '#default_value' => $saved_settings['appearance']['playlist'],
    '#title' => t('Playlist position'),
    '#options' => $options['playlist'],
    '#description' => t('Defines where to position the playlist. (<em>playlist</em>)'),
  );

  $form['swftools_jwplayer4']['appearance']['plugins'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['appearance']['plugins'],
    '#title' => t('Plug ins'),
    '#description' => t('A comma separated list of plugins to use with the player. (<em>plugins</em>)'),
  );
  
  $form['swftools_jwplayer4']['playback'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Playback'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['swftools_jwplayer4']['playback']['autostart'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['playback']['autostart'],
    '#title' => t('Autostart'),
    '#description' => t('Automatically start playing the media. (<em>autostart</em>)'),
  );
  
  $form['swftools_jwplayer4']['playback']['bufferlength'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['playback']['bufferlength'],
    '#size' => 5,
    '#maxlength' => 2,
    '#title' => t('Buffer length'),
    '#description' => t('Number of seconds of buffering before playing file. (<em>bufferlength</em>)'),
  );
  
  $form['swftools_jwplayer4']['playback']['displayclick'] = array(
    '#type' => 'select',
    '#default_value' => $saved_settings['playback']['displayclick'],
    '#title' => t('Display click'),
    '#options' => $options['displayclick'],
    '#description' => t('Action to take when the player is clicked. (<em>displayclick</em>)'),
  );
  
  $form['swftools_jwplayer4']['playback']['repeat'] = array(
    '#type' => 'select',
    '#default_value' => $saved_settings['playback']['repeat'],
    '#title' => t('Repeat'),
    '#options' => $options['repeat'],
    '#description' => t('Set whether the media repeats after completion. (<em>repeat</em>)'),
  );
  
  $form['swftools_jwplayer4']['playback']['shuffle'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['playback']['shuffle'],
    '#title' => t('Shuffle'),
    '#description' => t('Shuffle media randomly. (<em>shuffle</em>)'),
  );
  
  $form['swftools_jwplayer4']['playback']['volume'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['playback']['volume'],
    '#size' => 8,
    '#maxlength' => 3,
    '#title' => t('Volume'),
    '#description' => t('Starting volume of the player. (<em>volume</em>)'),
  );
  
  $form['swftools_jwplayer4']['interaction'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Interaction'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['swftools_jwplayer4']['interaction']['captions'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['interaction']['captions'],
    '#title' => t('Captions URL'),
    '#description' => t('Full url used to an external textfile with captions. (<em>captions</em>)'),
  );
  
  $form['swftools_jwplayer4']['interaction']['link'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['interaction']['link'],
    '#title' => t('Link URL'),
    '#description' => t('Web address linked to logo watermark. (<em>link</em>)'),
  );
  
  $form['swftools_jwplayer4']['interaction']['linktarget'] = array(
    '#type' => 'select',
    '#default_value' => $saved_settings['interaction']['linktarget'],
    '#options' => $options['linktarget'],
    '#title' => t('Link target'),
    '#description' => t('Target of "Link URL". (<em>linktarget</em>)'),
  );
  
  $form['swftools_jwplayer4']['interaction']['streamscript'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['interaction']['streamscript'],
    '#title' => t('Streaming script URL'),
    '#description' => t('Full url to \'fake\' streaming script. (<em>streamscript</em>)'),
  );
  
  $form['swftools_jwplayer4']['interaction']['type'] = array(
    '#type' => 'select',
    '#options' => $options['type'],
    '#default_value' => $saved_settings['interaction']['type'],
    '#title' => t('File type'),
    '#description' => t('Specify a default filetype, the default setting will auto-detect. (<em>type</em>)'),
  );
  
  $form['swftools_jwplayer4']['interaction']['fullscreen'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['interaction']['fullscreen'],
    '#title' => t('Allow use of fullscreen'),
    '#description' => t('Determine whether to allow fullscreen functionality. (<em>usefullscreen</em>).<br /><em>Allow full screen mode</em> must also be enabled on the SWF Tools embedding settings page.'),
  );

  $form['swftools_jwplayer4']['accessibility'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Accessibility'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['swftools_jwplayer4']['accessibility']['accessible'] = array(
    '#type' => 'checkbox',
    '#default_value' => $saved_settings['accessibility']['accessible'],
    '#title' => t('Make the player accessible'),
    '#description' => t('If this option is enabled then accessible links will be put below the player to allow it to be controlled using a keyboard or other input device.'),
  );

  $form['swftools_jwplayer4']['accessibility']['accessible_visible'] = array(
    '#type' => 'checkbox',
    '#default_value' => $saved_settings['accessibility']['accessible_visible'],
    '#title' => t('Make the accessible controls visible'),
    '#description' => t('If this option is enabled then accessible links will be visible on the page. If this option is cleared then the links will be hidden, but still accessible to devices such as screen readers.'),
  );
  
  // Add custom form handler to strip out blank and default settings
  $form['#submit'][] = 'swftools_wijering4_admin_form_submit';
  
  // Return the form
  return $form;

}
