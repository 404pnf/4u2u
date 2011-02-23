<?php
// $Id: swftools_flowplayer.admin.inc,v 1.1.2.4 2010/04/04 23:36:21 stuartgreenfield Exp $

function swftools_flowplayer_admin_form() {

  // Retrieve defaults, or saved settings
  $saved_settings = _swftools_flowplayer_settings();
  
  // Retrieve options for drop down lists
  $options = _swftools_flowplayer_options();

  // Initialise form
  $form = array();

  $form['swftools_flowplayer']['player'] = array(
    '#type' => 'select',
    '#default_value' => $saved_settings['player'],
    '#title' => t('FlowPlayer to use'),
    '#options' => $options['player'],
    '#description' => t('Defines which FlowPlayer to use.'),
  );
  
  $form['swftools_flowplayer']['usePlayOverlay'] = array(
    '#type' => 'select',
    '#default_value' => $saved_settings['usePlayOverlay'],
    '#title' => t('Overlay play control'),
    '#options' => $options['bool'],
    '#description' => t('Show a play button at the start of the playlist. (<em>usePlayOverlay</em>)'),
  );
  
  $form['swftools_flowplayer']['hideControls'] = array(
    '#type' => 'select',
    '#default_value' => $saved_settings['hideControls'],
    '#title' => t('Hide controls'),
    '#options' => $options['bool'],
    '#description' => t('Hide the player controls and progress bar. (<em>hideControls</em>)'),
  );
  
  $form['swftools_flowplayer']['controlBarGloss'] = array(
    '#type' => 'select',
    '#default_value' => $saved_settings['controlBarGloss'],
    '#title' => t('Control bar gloss'),
    '#options' => $options['controlBarGloss'],
    '#description' => t('Choose the level of \'gloss\' to apply to the control bar. (<em>controlBarGloss</em>)'),
  );
  
  $form['swftools_flowplayer']['showFullScreenButton'] = array(
    '#type' => 'select',
    '#default_value' => $saved_settings['showFullScreenButton'],
    '#title' => t('Show full screen button'),
    '#options' => $options['bool'],
    '#description' => t('Show a button on the player to allow full screen mode. (<em>showFullScreenButton</em>)'),
  );
  
  $form['swftools_flowplayer']['showPlayListButtons'] = array(
    '#type' => 'select',
    '#default_value' => $saved_settings['showPlayListButtons'],
    '#title' => t('Show playlist buttons'),
    '#options' => $options['bool'],
    '#description' => t('Show previous/next buttons when playing a playlist. (<em>showPlayListButtons</em>)'),
  );
  
  $form['swftools_flowplayer']['autoPlay'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['autoPlay'],
    '#title' => t('Autoplay'),
    '#description' => t('Automatically start playing the media. (<em>autoPlay</em>)'),
  );
  
  $form['swftools_flowplayer']['loop'] = array(
    '#type' => 'select',
    '#default_value' => $saved_settings['loop'],
    '#title' => t('Loop'),
    '#options' => $options['bool'],
    '#description' => t('Set whether the media repeats after completion. (<em>loop</em>)'),
  );
  
  $form['swftools_flowplayer']['initialVolumePercentage'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['initialVolumePercentage'],
    '#size' => 8,
    '#maxlength' => 3,
    '#title' => t('Volume'),
    '#description' => t('Starting volume of the player. (<em>initialVolumePercentage</em>)'),
  );

  // Initialise tree from this point forward as want to store arrays  
  $form['swftools_flowplayer']['#tree'] = TRUE;

  // Add custom form handler to flush cache upon submit
  $form['#submit'][] = 'swftools_admin_settings_submit';
  
  // Return finished form
  return system_settings_form($form);

}


/**
 * flashvar and param option arrays. These are used for options settings in the
 * configuration screen.
 *
 */
function _swftools_flowplayer_options() {
  $options['type'] = array('default' => 'default', 'sound' => 'sound', 'image' => 'image', 'video' => 'video', 'youtube' => 'youtube', 'camera' => 'camera', 'http' => 'http', 'rtmp' => 'rtmp', );
  $options['overstretch'] = array('default' => 'default', 'uniform' => 'uniform', 'fill' => 'fill', 'exactfit' => 'exactfit', 'none' => 'none', );
  $options['repeat'] = array('default' => 'default', 'none' => 'none', 'list' => 'list', 'always' => 'always', );
  $options['linktarget'] = array('default' => 'default', '_self' => '_self', '_blank' => '_blank', 'none' => 'none', );
  $options['playlist'] = array('default' => 'default', 'bottom' => 'bottom', 'over' => 'over', 'right' => 'right', 'none' => 'none', );
  $options['controlbar'] = array('default' => 'default', 'bottom' => 'bottom', 'over' => 'over', 'none' => 'none', );
  $options['displayclick'] = array('default' => 'default', 'play' => 'play', 'link' => 'link', 'fullscreen' => 'fullscreen', 'none' => 'none', 'mute' => 'mute', 'next' => 'next', );

  $options['player'] = array('flowplayer/FlowPlayerClassic.swf' => 'Classic', 'flowplayer/FlowPlayerDark.swf' => 'Dark', 'flowplayer/FlowPlayerLight.swf' => 'Light', 'flowplayer/FlowPlayerLP.swf' => 'LP', );
  $options['controlBarGloss'] = array('default' => 'default', 'high' => 'high', 'low' => 'low', 'none' => 'none', );
  $options['bool'] = array('default' => 'default', 'true' => 'true', 'false' => 'false');
  return $options;
}
