<?php
// $Id: node.config.inc,v 1.1.2.2 2010/03/15 18:38:08 rapsli Exp $

/**
 * @file
 * This is a dummy file for the node storage containing the config stuff
 * 
 */

function fast_gallery_node_config() {
  return drupal_get_form('fast_gallery_default_config_form');
}

function fast_gallery_default_config_form() {
  $types = node_type_get_types();
  $names = node_type_get_names();
  
  $form = array();
  
  $options = array();
  foreach ($types as $type) {
    $options[$type->type] = $type->type;
  }
  
  $form['fast_gallery_node_type']  = array(
    '#title' => 'node type for saving',
    '#type' => 'select',
    '#options' => $options,
  );
  
  return $form;
}