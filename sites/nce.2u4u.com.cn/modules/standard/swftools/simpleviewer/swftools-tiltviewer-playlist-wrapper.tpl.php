<?php
// $Id: swftools-tiltviewer-playlist-wrapper.tpl.php,v 1.1.2.1 2010/04/14 20:05:27 stuartgreenfield Exp $

/**
 * Prepare xml output for a playlist
 * The markup is placed in a template so that it can be easily over-ridden by the theme system
 * to allow flexibility
 * 
 * This template wraps the xml headers and footers around the xml markup that was produced using
 * the wijering4-playlist-elements template.
 * 
 * Available variables:
 * - $header: An array of data that can be used to inject variables to the markup.
 * - $xml: The markup that describes all the playlist elements.
 * 
 */


// Open xml file
print '<?xml version="1.0" encoding="UTF-8"?>';

$attributes = drupal_attributes($header['xml_vars']);
$attributes = str_replace(array('#', '0x'), '', $attributes);

// Define gallery settings
//print '<tiltviewergallery ' . $attributes . '>';
print '<tiltviewergallery>';
print '<photos>';

// Output image list
print $xml;

// Close gallery
print '</photos>';
print '</tiltviewergallery>';

?>
