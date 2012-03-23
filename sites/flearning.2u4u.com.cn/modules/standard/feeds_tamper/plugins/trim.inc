<?php
// $Id: trim.inc,v 1.1.2.7 2011/02/01 02:33:13 twistor Exp $

$plugin = array(
  'form' => 'feeds_tamper_trim_form',
  'callback' => 'feeds_tamper_trim_callback',
  'description' => 'feeds_tamper_trim_description',
  'name' => 'Trim',
  'multi' => 'loop',
  'category' => 'Text',
);

function feeds_tamper_trim_form($importer, $element_key, $settings) {
  $form = array();
  $form['mask'] = array(
    '#type' => 'textfield',
    '#title' => t('Characters to trim'),
    '#default_value' => isset($settings['mask']) ? $settings['mask'] : '',
    '#description' => t('The characters to remove from the string. If blank, then whitespace will be removed.'),
  );
  $form['side'] = array(
    '#type' => 'radios',
    '#title' => t('Side'),
    '#default_value' => isset($settings['side']) ? $settings['side'] : 'trim',
    '#options' => array('trim' => t('Both'), 'ltrim' => t('Left'), 'rtrim' => t('Right')),
  );
  return $form;
}

function feeds_tamper_trim_description($settings) {
  if ($settings['side'] == 'ltrim') {
    $side = ' from the left side';
  }
  else if ($settings['side'] == 'rtrim') {
    $side = ' from the right side';
  }
  else {
    $side = ' from both sides';
  }
  if (empty($settings['mask'])) {
    $mask = 'white space';
  }
  else {
    $mask = $settings['mask'];
  }
  return 'Remove "' . $mask . '"' . $side . '.';
}

function feeds_tamper_trim_callback($source, $item_key, $element_key, &$field, $settings) {
  $field = $settings['side']($field, $settings['mask']);
}
