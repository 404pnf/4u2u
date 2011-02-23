<?php
// $Id: swftools.genericplayers.inc,v 1.1.2.2 2010/04/14 23:29:54 stuartgreenfield Exp $

/**
 * Support for generic Flash player for SWF Tools
 */

/**
 * Implementation of hook_swftools_methods().
 */
function swftools_genericplayers_swftools_methods() {

  $mp3_player = array (
    'module'      => 'swftools',
    'title'       => t('Generic MP3 player'),
    'height'      => 31,
    'width'       => 30,
    'library'     => drupal_get_path('module', 'swftools') . '/swf/generic_mp3.swf',
  );
  
  $methods['audio']['generic_mp3'] = $mp3_player;

  $flv_player = array (
    'module'      => 'swftools',
    'title'       => t('Generic FLV player'),
    'height'      => 275,
    'width'       => 320,
    'library'     => drupal_get_path('module', 'swftools') . '/swf/generic_flv.swf',
  );
  
  $methods['video']['generic_flv'] = $flv_player;

  return $methods;
}


/**
 * Implementation of hook_menu(). Items such as access control is set by swftools automatically
 * This is not a "true" hook, but the contents returned by this function are merged with
 * swftools_menu to provide the complete menu structure for SWF Tools
 */
function swftools_genericplayers_menu() {

  $items = array();

  $items['admin/settings/swftools/generic'] = array(
    'title' => 'Generic players',
    'description' => 'Basic Flash players that ship with SWF Tools',
    'access arguments' => array('administer flash'),
    'weight' => -1,
    'page callback' => 'drupal_get_form',
    'page arguments' => array('swftools_admin_generic_form'),
  );
  return $items;
}


/**
 * Returns the generic player administration form.
 */
function swftools_admin_generic_form() {

  $form = array();

  $methods = swftools_get_methods('swftools_embed_method');

  $form['generic_mp3_autostart'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('generic_mp3_autostart', FALSE),
    '#title' => t('Autostart MP3 files'),
    '#description' => t('Automatically start playing MP3 files.'),
  );

  $form['generic_flv_autostart'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('generic_flv_autostart', TRUE),
    '#title' => t('Autostart FLV files'),
    '#disabled' => TRUE, // Generic player always autoplays
    '#description' => t('Automatically start playing FLV files.<br />
                         This option cannot be changed as the generic player
                         always automatically starts playing FLV files.
                        '),
  );

  return system_settings_form($form);
}


/**
 * Implementation of hook_swftools_preprocess_[player]().
 */
function swftools_swftools_preprocess_generic_mp3(&$data) {

  // Attach file url of the content to display to flashvars
  $data['flashvars']['file_url'] = $data['othervars']['file_url'];

  $data['flashvars']['autostart'] = (isset($data['flashvars']['autostart'])) ? ($data['flashvars']['autostart']) : variable_get('generic_mp3_autostart', FALSE) ? 'true' : 'false';
  
}

/**
 * Implementation of hook_swftools_preprocess_[player]().
 */
function swftools_swftools_preprocess_generic_flv(&$data) {

  // Attach file url of the content to display to flashvars
  $data['flashvars']['file_url'] = $data['othervars']['file_url'];

  $data['flashvars']['autostart'] = (isset($data['flashvars']['autostart'])) ? ($data['flashvars']['autostart']) : variable_get('generic_flv_autostart', FALSE) ? 'true' : 'false';
  
}
