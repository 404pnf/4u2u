<?php
// $Id: swftools-imagerotator-playlist-element.tpl.php,v 1.1.2.3 2010/04/07 21:33:36 stuartgreenfield Exp $

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
 * - url
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

<track>
<?php

  // If title is empty the player shows 'undefined' if other elements have titles! So we will assign '-' for now
  // TODO: What if NO images have a title - if nothing has a title the player correctly shows a blank

  print "<title>" . check_plain($element['title']) . "</title>";
  
  print "<location>" . check_url($element['fileurl']) . "</location>";
    
?>

</track>
