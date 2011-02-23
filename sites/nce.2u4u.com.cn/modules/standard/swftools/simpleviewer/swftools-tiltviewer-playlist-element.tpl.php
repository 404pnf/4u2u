<?php
// $Id: swftools-tiltviewer-playlist-element.tpl.php,v 1.1.2.1 2010/04/14 20:05:27 stuartgreenfield Exp $

/**
 * Prepare xml output for a playlist
 * The markup is placed in a template so that it can be easily over-ridden by the theme system
 * to allow flexibility
 * 
 * This template formats single elements for the xml playlist. By modifying the content here
 * the xml can be modified directly to provide customised xml handling for different players.
 * 
 * By way of example this implementation of the template will include data from the ID3 tags
 * to pass the length of the clip, plus album and year data, if available.
 * 
 * Available variables:
 * - $element: An array of available playlist data for this element.
 * 
 * As a minimum the $element array can be expected to contain the following keys:
 * - fileurl
 *   The resolved url to the file
 * - filepath
 *   The filepath of the file (which will be different to the url if on the local file system)
 * - title
 *   The title of the file, e.g. user supplied, assigned by ID3, or may be the filename
 *   
 * Other keys may be available, depending on which additional modules have been enabled. 
 * 
 */
?>

<?php

  // Output xml markup
  print '<photo imageurl="' . check_plain($element['fileurl']) . '" >'; 
  print '<title>' . check_plain($element['title']) . '</title>';
  print '<description>' . check_plain($element['description']) . '</description>';
  print '</photo>';
    
?>
