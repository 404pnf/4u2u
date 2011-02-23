<?php
// $Id: swftools-flowplayer3-playlist-element.tpl.php,v 1.1.2.5 2010/04/03 00:56:24 stuartgreenfield Exp $

/**
 * Prepare a flowplayer3 configuration string for a playlist
 * The config is placed in a template so that it can be easily over-ridden by the theme system
 * to allow flexibility
 * 
 * This template formats single elements for the JSON playlist configuration. This template should
 * return its data already formatted to JSON as it is producing strings, not an array, and so the
 * Drupal JSON function will not be able to format it automatically.
 * 
 * By way of example this implementation of the template will include data from the ID3 tags
 * to pass the length of the clip and the artist, if available.
 * 
 * Available variables:
 * - $element: An array of available playlist data for this element.
 * 
 * As a minimum the $element array can be expected to contain the following keys:
 * - fileurl
 *   The resolved url to the file
 * - filepath
 *   The filepath of the file (which will be different to the url if on the local file system)
 * - filename
 *   The filename of the file, obtained from the url
 * - title
 *   The title of the file, e.g. user supplied, assigned by ID3, or may be the filename
 *   
 * Other keys may be available, depending on which additional modules have been enabled. 
 * 
 */
?>
<?php

  // See if playtime is available from id3
  $duration = isset($element['getid3']['playtime_string']) ? $element['getid3']['playtime_string'] : '';

  // Suppress notice errors if author is not defined
  $element += array(
    'author' => '',
  );
  
  // Ampersands and quotes in the playlist break FlowPlayer3 (see flowplayer.org/forum/8/16714 and flowplayer.org/forum/3/20389)
  $author = str_replace('&', 'and', $element['author']);
  $author = str_replace("'", "", $author);
  
  // Prepare output array
  $output = array();
  
  // Add elements that should be included for each playlist element
  $output[] = '"url": "' . check_url($element['fileurl']) . '"';
  $output[] = '"title": "' . check_plain($element['title']) . '"';
  $output[] = '"duration": "' . check_plain($duration) . '"';
  $output[] = '"artist": "' . check_plain($author) . '"';
  
  // Output the result
  print '{ ' . implode(', ', $output) . ' }';
  
?>