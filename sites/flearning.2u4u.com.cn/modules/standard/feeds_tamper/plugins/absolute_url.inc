<?php
// $Id: absolute_url.inc,v 1.2.2.5 2011/02/01 02:33:13 twistor Exp $

$plugin = array(
  'form' => 'feeds_tamper_absolute_url_form',
  'callback' => 'feeds_tamper_absolute_url_callback',
  'name' => 'Make URLs absolute',
  'category' => 'HTML',
  'description' => 'feeds_tamper_absolute_url_description',
  'machine_name' => 'feeds_tamper_absolute_url_machine_name',
);

function feeds_tamper_absolute_url_form($importer, $element_key, $settings) {
  $form = array();
  $links = htmlentities('<a href="/stuff/things"> to <a href="http://example.com/stuff/things">');
  $form['info'] = array(
    '#markup' => t('Make URLs in markup absolute. (i.e. ' . $links . ').'),
  );
  return $form;
}

function feeds_tamper_absolute_url_description($settings) {
  return 'Make URLs absolute.';
}

function feeds_tamper_absolute_url_machine_name($settings) {
  return 'make_urls_absolute';
}

/**
 * @todo
 *   Make this not suck.
 */
function feeds_tamper_absolute_url_callback($source, $item_key, $element_key, &$field, $settings) {
  static $base_url = NULL;

  if (!$base_url) {
    $base_url = rtrim($source->batch->link, '/') . '/';
  }

  preg_match_all('/<.*(href|src)(\s*=\s*)(\'|")(.*)("|\').*>/', $field, $matches, PREG_SET_ORDER);
  foreach ($matches as $match) {
    if (!stripos($match[4], 'http://') === 0 && !stripos($match[4], 'https://') === 0) {
      $find_text = implode('', $match);
      $match[4] = $base_url . ltrim($match[4], '/');
      $replace_text = implode('', $match);
      $field = str_replace($find_text, $replace_text, $field);
    }
  }
}
