<?php
// $Id: filefield_tracker.admin.inc,v 1.2 2010/06/26 16:44:23 xeniox Exp $

/**
 * @file
 * Renders administrative pages for filefield tracker module
 */

function filefield_tracker_admin_settings() {
  $form = array();
  $defaults = array_keys(node_get_types('names'));

  $form['filefield_tracker_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Trackable content types'),
    '#weight' => 0,
    '#description' => t('Specify which content types should allow download tracking. Defaults to all.'),
    '#options' => node_get_types('names'),
    '#default_value' => variable_get('filefield_tracker_types', $defaults),
  );

  $views = views_get_all_views();
  $filefield_tracker_views = array();
  foreach ($views as $key => $view) {
    if (substr($key, 0, strlen('filefield_tracker_')) == 'filefield_tracker_') {
      $options[$key] = $view->name;
    }
  }
  $form['filefield_tracker_report_view'] = array(
    '#type' => 'select',
    '#title' => t('File download report View'),
    '#description' => t('Select a View to be used for the <a href="!url">File download report</a> admin page. Note that only viewnames starting with "filefield_tracker_" are eligible.', array('!url' => url('admin/reports/filefield_tracker'))),
    '#options' => $options,
    '#default_value' => variable_get('filefield_tracker_report_view', 'filefield_tracker_report'),
  );

  $form['filefield_tracker_node_view'] = array(
    '#type' => 'select',
    '#title' => t('Node tab View'),
    '#description' => t('Select a View to be used for the "File download tracker" tab on nodes. Note that only viewnames starting with "filefield_tracker_" are eligible.'),
    '#options' => $options,
    '#default_value' => variable_get('filefield_tracker_node_view', 'filefield_tracker_node'),
  );

  return system_settings_form($form);
}