<?php 
// $Id: smoothgallery.presentation.inc,v 1.1.2.1 2010/08/28 09:29:56 rapsli Exp $

/**
 * @file
 */

/**
 * implementation of hook_fast_gallery_presentation
 */
function fast_gallery_fast_gallery_presentation($images, $ar_bc) {
  /*global $base_url; 
  $current_path_alias = check_plain($_GET['q']);

  $html .= '<div id="galleria">';
  
  $folders = array();
  foreach ($images as $image) {
    if (!$image->isDir()) {
      if (module_exists('imagecache')) {
        $html .= theme('imagecache', variable_get('fast_gallery_ic_full', ''), $image->getPath());
      }
      else {
        $html .= theme('image', $image->getPath());
      }
    }
    else {
      $folders[] = $image;
    }
  }
  $html .= '</div>';
*/
  /*
  foreach ($folders as $folder) {
    $html .= l($folder->getName(), $current_path_alias . '/' . $folder->getName());
  }
  */
  $html = '<div id="smoothgallery">';
  foreach ($images as $image) {
    if (!$image->isDir()) {
      $html .= '<div class="imageElement">';
      $html .= '<h3>Titel</h3>';
      $html .= '<p>Die Beschreibung</p>';
      if (module_exists('imagecache')) {
        $html .= theme('imagecache', variable_get('fast_gallery_ic_full', ''), $image->getPath(), '', '', array('class' => 'full'));
        $html .= theme('imagecache', variable_get('fast_gallery_ic_thumb', ''), $image->getPath(), '', '', array('class' => 'thumbnail'));
      }
      else {
        $html .= theme('image', $image->getPath());
      }
      $html .= '</div>';
    }
    else {
      $folders[] = $image;
    }
  }
  $html .= '</div>';
  /*<div id="myGallery">
<div class="imageElement">
<h3>Item 1 Title</h3>
<p>Item 1 Description</p>
<a href="mypage1.html" title="open image" class="open"></a>
<img src="images/brugges2006/1.jpg" class="full" />
<img src="images/brugges2006/1-mini.jpg" class="thumbnail" />
</div>
<div class="imageElement">
<h3>Item 2 Title</h3>
<p>Item 2 Description</p>
<a href="mypage2.html" title="open image" class="open"></a>
<img src="images/brugges2006/2.jpg" class="full" />
<img src="images/brugges2006/2-mini.jpg" class="thumbnail" />
</div>
</div>*/
  
  $html .= "<script type=\"text/javascript\">
function startGallery() {
var myGallery = new gallery($('smoothgallery'), {
timed: false
});
}
window.addEvent('domready', startGallery);
</script>";
  
  return $html;
}

/**
 * implementation of hook_fast_gallery_load_requirements()
 */
function fast_gallery_fast_gallery_load_requirements() {
  drupal_add_js(drupal_get_path('module', 'fast_gallery') . '/presentation/smoothgallery/mootools.v1.11.js');
  drupal_add_js(drupal_get_path('module', 'fast_gallery') . '/presentation/smoothgallery/jd.gallery.js');
  drupal_add_css(drupal_get_path('module', 'fast_gallery') . '/presentation/smoothgallery/jd.gallery.css');
  
}