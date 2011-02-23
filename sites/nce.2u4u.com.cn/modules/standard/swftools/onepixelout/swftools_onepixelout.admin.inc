<?php
// $Id: swftools_onepixelout.admin.inc,v 1.1.2.6 2010/03/29 22:07:14 stuartgreenfield Exp $

function swftools_onepixelout_admin_form() {

  // Get saved settings
  $saved = _swftools_onepixelout_settings();

  // See if colorpicker 2 is loaded
  $can_pick = function_exists('colorpicker_2_or_later');
  
  // Initialise array
  $form = array();

  $form['swftools_onepixelout']['height'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['height'],
    '#title' => t('Height'),
    '#description' => t('The height of the player in pixels.'),
    '#size' => 8,
  );
  
  $form['swftools_onepixelout']['width'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['width'],
    '#title' => t('Width'),
    '#description' => t('The width of the player in pixels.'),
    '#size' => 8,
  );
  
  $form['swftools_onepixelout']['autostart'] = array(
    '#type' => 'select',
    '#options' => array('yes' => 'yes', 'no' => 'no'),
    '#default_value' => $saved['autostart'],
    '#title' => t('Autostart'),
    '#description' => t('Automatically start playing the MP3. (<em>autostart</em>)'),
  );

  $form['swftools_onepixelout']['loop'] = array(
    '#type' => 'select',
    '#options' => array('yes' => 'yes', 'no' => 'no'),
    '#default_value' => $saved['loop'],
    '#title' => t('Loop'),
    '#description' => t('Loop the sound file back to the beginning when done. (<em>loop</em>)'),
  );
  
  $form['swftools_onepixelout']['map'] = array(
    '#value' => '<img src="http://www.1pixelout.net/wp-content/plugins/audio-player/map.gif" alt="Player Map" />',
  );

  // Unset the parameters that aren't used to populate colours
  unset($saved['height']);
  unset($saved['width']);
  unset($saved['loop']);
  unset($saved['autostart']);

  // Iterate over remaining parameters, which are now all color settings
  foreach ($saved AS $key => $color) {
    $form['swftools_onepixelout'][$key] = array(
      '#type' => ($can_pick ? 'colorpicker_' : '') .'textfield',
      '#default_value' => $can_pick ? preg_replace('/0x/', '#', $color) : $color,
      '#size' => 8,
      '#maxlength' => 8,
      '#title' => t($key .' color'),
      '#description' => t('Hexadecimal color of the format !prefixRRGGBB', array('!prefix' => $can_pick ? '#' : '0x')),
    );
  }

  // Initialise tree as we want to store arrays
  $form['swftools_onepixelout']['#tree'] = TRUE;

  // Add custom form handler to ensure colors are coded properly
  $form['#submit'][] = 'swftools_onepixelout_admin_submit';
  
  // Add custom form handler to flush cache upon submit
  $form['#submit'][] = 'swftools_admin_settings_submit';
  
  // Return finished form
  return system_settings_form($form);

}


/**
 * Custom form handler to encode colors properly when using color picker module.
 */
function swftools_onepixelout_admin_submit($form, &$form_state) {
  
  // Make sure colors are coded properly
  if (function_exists('colorpicker_2_or_later')) {
    foreach (array_keys($form_state['values']) AS $key) {
      $form_state['values'][$key] = preg_replace(array('/^#\s*$/', '/^#/'), array('', '0x'), $form_state['values'][$key]);
    }
  }

}
