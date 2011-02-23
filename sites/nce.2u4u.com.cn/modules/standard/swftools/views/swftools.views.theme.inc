<?php
// $Id: swftools.views.theme.inc,v 1.1.2.3 2010/04/14 20:05:27 stuartgreenfield Exp $

/**
 * Template preprocessor for views-view-views-rss-fields.tpl.php.
 */
function template_preprocess_views_view_swftools(&$vars) {
  
  // Initialise swftools options array
  $vars['swftools']['options'] = array(
    'othervars' => array(),
    'flashvars' => array(),
    'methods' => array(),
    'params' => array(),
  );

  // Assign the relevant profile
  if ($vars['options']['profile'] != SWFTOOLS_UNDEFINED) {
    $vars['swftools']['options']['othervars']['profile'] = $vars['options']['profile'];
  }
  
}

/**
 * Adds a single element to the playlist.
 * 
 * This function is designed to be called by templates and it will take care of
 * adding the fileurl, image and title to the playlist. These are the only
 * defaults that SWF Tools takes care of by itself. For more advanced playlists
 * it is required to create a customised views-view-swftools.tpl.php
 * 
 * @param unknown_type $files
 *   The playlist array (passed by reference).
 * @param $key
 *   The key in the array for this playlist element.
 * @param $options
 *   The options variable for the view.
 * @param $work
 *   The results of rendering this row, keyed on field id
 */
function swftools_views_add_playlist_element(&$files, $key, $options, $work) {
  
    // Always attach the filepath
    $files[$key]['filepath'] = $work[$options['filepath']];
    
    // Attach other keys, using empty string if they are undefined
    $elements = array(
      'title',
      'image',
      'description',
      'author',
      'date',
      'link',
      'duration',
    );

    // Attach the image if it is defined
    foreach ($elements as $element) {
      $files[$key][$element] = ($options[$element] != SWFTOOLS_UNDEFINED) && $work[$options[$element]] ? $work[$options[$element]] : '';
    }
    
//    // Attach the image if it is defined
//    if (($options['image'] != SWFTOOLS_UNDEFINED) && $work[$options['image']]) {
//      $files[$key]['image'] = $work[$options['image']];
//    }
//    
//    // Attach the title if it is defined
//    if (($options['title'] != SWFTOOLS_UNDEFINED) && $work[$options['title']]) {
//      $files[$key]['title'] = $work[$options['title']];
//    }
    
}
