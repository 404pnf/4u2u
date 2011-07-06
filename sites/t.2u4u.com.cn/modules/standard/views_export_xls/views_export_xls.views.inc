<?php
// $Id: views_export_xls.views.inc,v 1.1.2.1 2009/11/04 17:22:39 jkarsum Exp $
/**
 * @file
 * Views include file with views hooks.
 */

/**
 * Implementation of hook_views_plugins().
 */
function views_export_xls_views_plugins() {
  $path = drupal_get_path('module', 'views_export_xls');
  return array(
    'style' => array(
      'parent' => array(
        // this isn't really a display but is necessary so the file can
        // be included.
        'no ui' => TRUE,
        'handler' => 'views_plugin_style',
        'parent' => '',
      ),
      'xls' => array(
        'title' => t('XLS Feed'),
        'help' => t('Generates an XLS feed from a view.'),
        'handler' => 'views_export_xls_plugin_style_xls',
        'theme' => 'views_export_xls_view_xls',
        'uses fields' => TRUE,
        'uses row plugin' => FALSE,
        'uses options' => TRUE,
        'type' => 'feed',
      ),
    ),
  );
}

