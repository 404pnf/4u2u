<?php

/**
 * Implementation of hook_views_style_plugins().
 */
function swftools_views_plugins() {
  return array(
    'style' => array(
      'swftools' => array(
        'title' => t('SWF Tools'),
        'help' => t('Render fields in to SWF Tools.'),
        'handler' => 'views_plugin_style_swftools',
        'theme' => 'views_view_swftools',
        'theme file' => 'swftools.views.theme.inc',
        'path' => drupal_get_path('module', 'swftools') . '/views',
        'theme path' => drupal_get_path('module', 'swftools') .'/views',
        'uses fields' => TRUE,
        'uses row plugin' => FALSE,
        'uses options' => TRUE,
        'uses grouping' => FALSE,
        'type' => 'normal',
      ),
    ),
  );
}
