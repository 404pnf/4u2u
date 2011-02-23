<?php
// $Id: swftools_soundmanager2.admin.inc,v 1.1.2.3 2010/04/11 22:29:41 stuartgreenfield Exp $

function swftools_soundmanager2_admin_form() {

  // Fetch the form by using the profile definition
  $form = swftools_soundmanager2_profile_form();
  
  // Start a fieldset to hold the global settings
  $form['swftools_soundmanager2'] += array(
    '#type'  => 'fieldset',
    '#title' => t('Player type'),
    '#description' => t('SoundManager 2 offers various player formats and the default can be set below.'),
    '#tree' => TRUE,
  );
  
  // Retrieve global settings
  $saved_settings = _swftools_soundmanager2_global_settings();
  
  // Start a fieldset to hold the global settings
  $form['swftools_soundmanager2_globals'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Global settings'),
    '#description' => t('These settings are applied to all SoundManager 2 objects when they are embedded and control the overall performance of the player. Debugging can also be enabled to help troubleshoot the player if it is not performing correctly.'),
    '#tree' => TRUE,
  );
  
  $form['swftools_soundmanager2_globals']['addScripts'] = array(
    '#type' => 'checkboxes',
    '#options' => array(
      'ui360' => t('UI360 - small'),
      'ui360_visualization' => t('UI360 - with visualization'),
      'mp3_links' => t('Playable mp3 links'),
      'mp3_button' => t('Small button player'),
    ),
    '#default_value' => $saved_settings['addScripts'],
    '#title' => t('Scripts to add to every page'),
    '#description' => t('SoundManager 2 relies on JavaScript to render its players. If content is being created through the input filter then the relevant script will need to be added to every page in order to ensure that the player will be shown. To avoid loading the page with every SoundManger 2 script you can select which ones will always be added here. Make sure that \'Add JavaScript to all pages\' is also enabled in the <a href="@embedding">embedding settings</a> when using the input filter.', array('@embedding' => url('admin/swftools/embedding'))),
  );
  
  $form['swftools_soundmanager2_globals']['debugMode'] = array(
    '#type' => 'radios',
    '#options' => array(
      0 => 'Disabled',
      1 => 'Enabled',
    ),
    '#default_value' => $saved_settings['debugMode'],
    '#title' => t('Debug'),
    '#description' => t('When enabled, SoundManager 2 will write console-like output to console.log() style JavaScript interfaces, and an HTML element which will be created at runtime.'),  
  );
  
  $form['swftools_soundmanager2_globals']['useFlashBlock'] = array(
    '#type' => 'radios',
    '#options' => array(
      0 => t('Disabled'),
      1 => t('Enabled'),
    ),
    '#default_value' => $saved_settings['useFlashBlock'],
    '#title' => t('Flash block'),
    '#description' => t('SM2 historically has kept the flash movie off-screen and out of view, and thus the user could not click on and unblock it. Now with flash block enabled the movie positioning can be handled by CSS. The initial state is still off-screen by default, but will change to be in view when a blocking (time-out) situation is encountered.'),
  );
  
  $form['swftools_soundmanager2_globals']['flashVersion'] = array(
    '#type' => 'radios',
    '#options' => array(
      8 => t('Version 8'),
      9 => t('Version 9'),
    ),
    '#default_value' => $saved_settings['flashVersion'],
    '#title' => t('Flash version'),
    '#description' => t('SM2 historically has kept the flash movie off-screen and out of view, and thus the user could not click on and unblock it. Now with useFlashBlock = true, the movie positioning can be handled by CSS. The initial state is still off-screen by default, but will change to be in view when a blocking (time-out) situation may be encountered.'),
  );
  
  $form['swftools_soundmanager2_globals']['useFastPolling'] = array(
    '#type' => 'radios',
    '#options' => array(
      0 => t('Disabled'),
      1 => t('Enabled'),
    ),
    '#default_value' => $saved_settings['useFastPolling'],
    '#title' => t('Fast polling'),
    '#description' => t('By default fast polling is disabled and SoundManager uses a 20 milisecond timer inside Flash when polling for updated sound properties, data and event callbacks. When enabled a 1 msec timer is used and callback frequency may noticeably increase. For optimal results also enable the high performance setting.'),
  );
  
  $form['swftools_soundmanager2_globals']['useHighPerformance'] = array(
    '#type' => 'radios',
    '#options' => array(
      0 => t('Disabled'),
      1 => t('Enabled'),
    ),
    '#default_value' => $saved_settings['useHighPerformance'],
    '#title' => t('High performance'),
    '#description' => t('Flash is given higher priority when positioned within the viewable area of the browser, at least 6 px in height, fully-opaque, visible and displayed on the screen. By default, high performance is enabled and should noticeably reduce JavaScript/Flash lag.'),
  );
  
  // Add custom form handler to flush cache upon submit
  $form['#submit'][] = 'swftools_admin_settings_submit';
  
  // Return finished form
  return system_settings_form($form);

}


/**
 * Returns a form definition for use by the profile system.
 */
function swftools_soundmanager2_profile_form($profile = '') {

  $saved_settings = _swftools_soundmanager2_settings($profile);
  
  $form['swftools_soundmanager2']['player'] = array(
    '#type' => 'radios',
    '#options' => array(
      'ui360' => t('UI360 - small'),
      'ui360_visualization' => t('UI360 - with visualization'),
      'mp3_links' => t('Playable mp3 links'),
      'mp3_button' => t('Small button player'),
    ),
    '#default_value' => $saved_settings['player'],
    '#title' => t('Player'),
    '#description' => t('The type of SoundManager2 player to use.'),
  );
  
  $form['swftools_soundmanager2']['#tree'] = TRUE;
  
  // Return finished form
  return $form;

}
