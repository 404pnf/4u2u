<?php
// $Id: jplayer.views.inc,v 1.1 2010/05/01 04:28:08 quicksketch Exp $

/**
 * @file
 * Views module hooks for the jPlayer module.
 */
 
/**
 * Implementation of hook_views_plugins().
 */
function jplayer_views_plugins() {
  $path = drupal_get_path('module', 'jplayer');

  return array(
    'style' => array(
      'jplayer' => array(
        'title' => t('jPlayer'),
        'help' => t('Display audio files from different nodes as a jPlayer playlist.'),
        'handler' => 'jplayer_style_plugin',
        'path' => "$path/includes",
        'uses row plugin' => TRUE,
        'uses options' => TRUE,
        'uses grouping' => FALSE,
        'type' => 'normal',
      ),
    ),
  );
}
