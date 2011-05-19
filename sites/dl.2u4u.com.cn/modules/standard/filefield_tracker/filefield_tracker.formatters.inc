<?php
// $Id: filefield_tracker.formatters.inc,v 1.3 2010/06/26 09:36:14 xeniox Exp $

/**
 * @file
 * Provides the CCK field formatters
 */

/**
 * Implements hook_field_formatter_info().
 */
function filefield_tracker_field_formatter_info() {
  return array(
    'filefield_tracker' => array(
      'label' => 'Filefield download tracking link',
      'description' => t('Output a URL that allows for filefield download tracking'),
      'field types' => array('filefield'),
      'multiple values' => CONTENT_HANDLE_CORE,
    ),


  );
}

/**
 * Theme the filefield_tracker field formatter
 */
function theme_filefield_tracker_formatter_filefield_tracker($element) {
  module_load_include('inc', 'filefield', 'filefield_formatter');
  $downloadpath = filefield_tracker_create_url($element['#item']['fid'], $element['#item']['nid'], $element['#item']['filename']);
  $file = $element['#item'];
  $field = content_fields($element['#field_name']);
  if (filefield_view_access($field['field_name'], node_load($file['nid'])) && filefield_file_listed($file, $field)) {
    $output = theme('filefield_tracker_item', $file, $field, $downloadpath);
  }
  return $output;
}

/**
 * Theme the filefield download link
 */
function theme_filefield_tracker_item($file, $field, $downloadpath) {
  /* Mostly copied from theme_filefield_file, except for $url variable code */
  // Views may call this function with a NULL value, return an empty string.
  if (empty($file['fid'])) {
    return '';
  }

  $icon = theme('filefield_icon', $file);

  // Set options as per anchor format described at
  // http://microformats.org/wiki/file-format-examples
  // TODO: Possibly move to until I move to the more complex format described
  // at http://darrelopry.com/story/microformats-and-media-rfc-if-you-js-or-css
  $options = array(
    'attributes' => array(
      'type' => $file['filemime'] . '; length=' . $file['filesize'],
    ),
  );

  // Use the description as the link text if available.
  if (empty($file['data']['description'])) {
    $link_text = $file['filename'];
  }
  else {
    $link_text = $file['data']['description'];
    $options['attributes']['title'] = $file['filename'];
  }

  return '<div class="filefield-file clear-block">'. $icon . l($link_text, $downloadpath, $options) .'</div>';
}