<?php
// $Id: swftools-wijering4-playlist-wrapper.tpl.php,v 1.1.2.2 2010/03/29 22:07:14 stuartgreenfield Exp $

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
?>

<playlist version="1" xmlns="http://xspf.org/ns/0/">
<title><?php print $header['title']; ?></title>
<trackList>

<?php print $xml; ?>
  
</trackList>
</playlist>