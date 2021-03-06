<?php
// $Id: rewrite.inc,v 1.1.2.6 2011/02/01 02:33:13 twistor Exp $

$plugin = array(
  'form'     => 'feeds_tamper_rewrite_form',
  'callback' => 'feeds_tamper_rewrite_callback',
  'name'     => 'Rewrite',
  'multi'    => 'skip',
  'category' => 'Other',
);

function feeds_tamper_rewrite_form($importer, $element_key, $settings) {
  $form = array();
  $mappings = $importer->processor->config['mappings'];
  $replace = array();
  $options = array();

  foreach ($mappings as $mapping) {
    $replace[] = '[' . $mapping['source'] . ']';
  }
  $form['title']['#markup'] = t('The availiable replacement patterns are:');
  $form['help']['#markup'] = theme('item_list', array('items' => $replace));

  $form['text'] = array(
    '#type' => 'textarea',
    '#title' => t('Replacement pattern'),
    '#default_value' => isset($settings['text']) ? $settings['text'] : '',
  );
  return $form;
}

function feeds_tamper_rewrite_callback($source, $item_key, $element_key, &$field, $settings) {
  $trans = array();
  $item = $source->batch->items[$item_key];
  foreach ($item as $key => $value) {
    $trans['[' . $key . ']'] = $value;
  }
  $field = strtr($settings['text'], $trans);
}
