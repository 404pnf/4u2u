<?php
// $Id: views_slideshow.theme.inc,v 1.1.2.2.2.2 2009/09/18 22:15:49 redndahead Exp $

/**
 *  This displays the main element, where the current slide is shown.
 */
function theme_views_slideshow_main_section($id, $hidden_elements, $plugin) {
  $output = "\n\n" . '<div id="views_slideshow_' . $plugin . '_main_' . $id . '" class="views_slideshow_' . $plugin . '_main">' . "\n  ";
  $output .= $hidden_elements;
  $output .= '</div><!--close views_slideshow_' . $plugin . '_main_' . $id . "-->\n\n";
  return $output;
}
