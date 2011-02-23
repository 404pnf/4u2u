<?php
// $Id: swftools_wpaudio.admin.inc,v 1.1.2.8 2010/04/14 22:13:39 stuartgreenfield Exp $

function swftools_wpaudio_admin_form() {

  // Fetch the form by using the profile definition
  $form = swftools_wpaudio_profile_form();
  
  // Add custom form handler to flush cache upon submit
  $form['#submit'][] = 'swftools_admin_settings_submit';
  
  // Return finished form
  return system_settings_form($form);

}


/**
 * Custom form handler to encode checkboxes to yes/no responses and process color settings.
 */
function swftools_wpaudio_admin_form_submit($form, &$form_state) {
  
  // Convert 1/0 to yes/no
  swftools_wpaudio_admin_boolean_settings($form_state['values']['swftools_wpaudio']['player'], SWFTOOLS_ADMIN_STORE);

  // Strip leading # from color settings
  swftools_wpaudio_admin_colors_submit($form_state['values']['swftools_wpaudio']['colors'], SWFTOOLS_ADMIN_STORE);
  
}


/**
 * Convert 1/0 to yes/no, or vice versa.
 * 
 * The settings form stores 1/0 for checkboxes, but WordPress audio
 * player uses yes/no in its configuration string. This function will
 * convert the appropriate options in the settings between the two.
 * 
 * @param $settings
 *   An array of WordPress audio player configuration parameters.
 * @param $mode
 *   SWFTOOLS_ADMIN_STORE: convert 1/0 to yes/no
 *   SWFTOOLS_ADMIN_RETRIEVE: convert yes/no to 1/0
 * @return
 *   Nothing - the array is passed by reference.
 */
function swftools_wpaudio_admin_boolean_settings(&$settings, $mode) {

  // Encode the following parameters to yes/no
  $encode = array(
    'autostart',
    'loop',
    'animation',
    'remaining',
    'noinfo',
    'encode',
    'checkpolicy',
    'rtl',
    'transparentpagebg'
  );
  
  // Build the map to either encode or decode
  $map = array(
    SWFTOOLS_ADMIN_RETRIEVE => array(
      'yes' => 1,
      'no' => 0,
    ),
    SWFTOOLS_ADMIN_STORE => array(
      0 => 'no',
      1 => 'yes',
    ),
  );

  // Iterate over these settings encoding them, skipping settings that are not present
  foreach ($encode as $parameter) {
    if (isset($settings[$parameter])) {
      $settings[$parameter] = $map[$mode][$settings[$parameter]];
    }
  }

}


/**
 * Adds, or removes, the leading # from a color setting.
 * 
 * The colorpicker modules like to prepend the color with a #, but
 * WordPress audio wants to receive colors without any leading character.
 * This function will add, or remove, the # from an array of color
 * settings.
 * 
 * @param $settings
 *   An array of color settings.
 * @param $mode
 *   SWFTOOLS_ADMIN_STORE: strip leading #
 *   SWFTOOLS_ADMIN_RETRIEVE: restore leading #
 * @return
 *   Nothing - the array is passed by reference.
 */
function swftools_wpaudio_admin_colors_submit(&$settings, $mode) {
  
  foreach ($settings as $key => $value) {
    if ($value != '') {
      if ($mode == SWFTOOLS_ADMIN_STORE) {
        $settings[$key] = str_replace('#', '', $value);
      }
      else {
        $settings[$key] = '#' . $value;
      }
    }
  }
  
}


/**
 * Returns a form definition for use by the profile system.
 */
function swftools_wpaudio_profile_form($profile = '') {

  // Get saved settings
  $saved_settings = _swftools_wpaudio_settings($profile);
  
  // Convert yes/no back to 1/0
  swftools_wpaudio_admin_boolean_settings($saved_settings['player'], SWFTOOLS_ADMIN_RETRIEVE);
  
  // Put the # back in front of colors
  swftools_wpaudio_admin_colors_submit($saved_settings['colors'], SWFTOOLS_ADMIN_RETRIEVE);
  
  // See if colorpicker 2 is loaded
  $can_pick = function_exists('colorpicker_2_or_later');

  $form['swftools_wpaudio']['player'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Player'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['swftools_wpaudio']['player']['height'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['player']['height'],
    '#title' => t('Height'),
    '#description' => t('The height of the player in pixels.'),
    '#size' => 8,
  );
  
  $form['swftools_wpaudio']['player']['width'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['player']['width'],
    '#title' => t('Width'),
    '#description' => t('The width of the player in pixels.'),
    '#size' => 8,
  );
  
  $form['swftools_wpaudio']['player']['autostart'] = array(
    '#type' => 'checkbox',
    '#default_value' => $saved_settings['player']['autostart'],
    '#title' => t('Autostart'),
    '#description' => t('Automatically start playing the MP3. (<em>autostart</em>)'),
  );

  $form['swftools_wpaudio']['player']['loop'] = array(
    '#type' => 'checkbox',
    '#default_value' => $saved_settings['player']['loop'],
    '#title' => t('Loop'),
    '#description' => t('Loop the sound file back to the beginning when done. (<em>loop</em>)'),
  );
  
  $form['swftools_wpaudio']['player']['animation'] = array(
    '#type' => 'checkbox',
    '#default_value' => $saved_settings['player']['animation'],
    '#title' => t('Animated player'),
    '#description' => t('Start with the player closed and animate it when it opens. (<em>animation</em>)'),
  );
  
  $form['swftools_wpaudio']['player']['remaining'] = array(
    '#type' => 'checkbox',
    '#default_value' => $saved_settings['player']['remaining'],
    '#title' => t('Time remaining'),
    '#description' => t('Display time remaining in player window. (<em>remaining</em>)'),
  );
  
  $form['swftools_wpaudio']['player']['noinfo'] = array(
    '#type' => 'checkbox',
    '#default_value' => $saved_settings['player']['noinfo'],
    '#title' => t('Hide info'),
    '#description' => t('Don\'t show track information in the player. (<em>noinfo</em>)'),
  );
  
  $form['swftools_wpaudio']['player']['initialvolume'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['player']['initialvolume'],
    '#title' => t('Initial volume'),
    '#description' => t('The initial volume of the player. (<em>initialvolume</em>)'),
    '#size' => 8,
  );

  $form['swftools_wpaudio']['player']['buffer'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['player']['buffer'],
    '#title' => t('Buffer'),
    '#description' => t('The size of the player buffer, in seconds. (<em>buffer</em>)'),
    '#size' => 8,
  );
  
  $form['swftools_wpaudio']['player']['encode'] = array(
    '#type' => 'checkbox',
    '#default_value' => $saved_settings['player']['encode'],
    '#title' => t('Encoded filenames'),
    '#description' => t('When checked indicates that filenames are encoded. (<em>encoded</em>)'),
  );
  
  $form['swftools_wpaudio']['player']['checkpolicy'] = array(
    '#type' => 'checkbox',
    '#default_value' => $saved_settings['player']['checkpolicy'],
    '#title' => t('Use policy file'),
    '#description' => t('When checked allows Flash to use a policy file to access remote ID3 tags. (<em>checkpolicy</em>)'),
  );
  
  $form['swftools_wpaudio']['player']['rtl'] = array(
    '#type' => 'checkbox',
    '#default_value' => $saved_settings['player']['rtl'],
    '#title' => t('Use RTL layout'),
    '#description' => t('When checked indicates that right-to-left layout should be used. (<em>rtl</em>)'),
  );
  
  $form['swftools_wpaudio']['player']['transparentpagebg'] = array(
    '#type' => 'checkbox',
    '#default_value' => $saved_settings['player']['transparentpagebg'],
    '#title' => t('Transparent player'),
    '#description' => t('When checked the player has a transparent background. (<em>transparentpagebg</em>)'),
  );
  
//  $form['swftools_wpaudio']['map'] = array(
//    '#value' => '<img src="http://www.1pixelout.net/wp-content/plugins/audio-player/map.gif" alt="Player Map" />',
//  );

  $form['swftools_wpaudio']['colors'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Colors'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  // Iterate over color settings
  foreach ($saved_settings['colors'] AS $key => $color) {
    $form['swftools_wpaudio']['colors'][$key] = array(
      '#type' => ($can_pick ? 'colorpicker_' : '') . 'textfield',
      '#default_value' => $color,
      '#size' => 8,
      '#maxlength' => 8,
      '#title' => t($key . ' color'),
      '#description' => t('Hexadecimal color of the format #RRGGBB'),
    );
  }
  
  $form['swftools_wpaudio']['accessibility'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Accessibility'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['swftools_wpaudio']['accessibility']['accessible'] = array(
    '#type' => 'checkbox',
    '#default_value' => $saved_settings['accessibility']['accessible'],
    '#title' => t('Make the player accessible'),
    '#description' => t('If this option is enabled then accessible links will be put below the player to allow it to be controlled using a keyboard or other input device.'),
  );
  
  $form['swftools_wpaudio']['accessibility']['accessible_visible'] = array(
    '#type' => 'checkbox',
    '#default_value' => $saved_settings['accessibility']['accessible_visible'],
    '#title' => t('Make the accessible controls visible'),
    '#description' => t('If this option is enabled then accessible links will be visible on the page. If this option is cleared then the links will be hidden, but still accessible to devices such as screen readers.'),
  );

  // Initialise tree as we want to store arrays
  $form['swftools_wpaudio']['#tree'] = TRUE;

  // Add custom form handler to convert 1/0 to yes/no, and to store colors without leading #
  $form['#submit'][] = 'swftools_wpaudio_admin_form_submit';
  
  // Return finished form
  return $form;

}
