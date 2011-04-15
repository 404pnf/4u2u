<?php
// $Id: default.config.inc,v 1.2.2.4 2010/05/03 06:01:27 rapsli Exp $

/**
 * @file 
 * We are giving some config options for the default storage engine
 */

/**
 * Callback function default storage engine
 * @return html
 */
function fast_gallery_default_config() {
  return drupal_get_form('fast_gallery_default_config_form');
}

/**
 * Form definition for default storage engine configuration
 * @return array
 */
function fast_gallery_default_config_form() {
  $items = array();
  $items['fg_folder_first'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display folders first'),
    '#default_value' => variable_get('fg_folder_first', FALSE),
    '#description' => t('If checked folders will be displayed first'),
  );
  
  $items['fg_sort_order'] = array(
    '#type' => 'select',
    '#title' => t('Sort by'),
    '#options' => array('filename' => 'name', 'filecreated' => 'filecreation'),
    '#default_value' => variable_get('fg_sort_order', array('filename')),
    '#description' => t('Specify how to order your gallery. If you choose the filecreation
      option, it\'s only going to affect the images and not the folder sorting. '),
  );
  
  $items['fg_sort_direction'] = array(
    '#type' => 'select',
    '#title' => t('Sort by'),
    '#options' => array('asc' => 'ascending', 'desc' => 'descending'),
    '#default_value' => variable_get('fg_sort_direction', array('descending')),
    '#description' => t('Which direction should it be ordered'),
  );
  
  $items['fg_pager_amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Amount of images per page'),
    '#default_value' => variable_get('fg_pager_amount', 20),
    '#description' => t('Specify how many images should be displayed on the page. If there are more than the given images in the gallery, a pager will be displayed.'),
  );
  
  return system_settings_form($items);
}

/**
 * validation function for the settinsg form
 * @param $form
 * @param $form_state
 */
function fast_gallery_default_config_form_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['fg_pager_amount'])) {
    form_error($form['fg_pager_amount'], t('The pager amount needs to be numeric.'));
  }
}