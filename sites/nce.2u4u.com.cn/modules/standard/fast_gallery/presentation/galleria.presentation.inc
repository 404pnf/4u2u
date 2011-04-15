<?php 
// $Id: galleria.presentation.inc,v 1.1.2.3 2010/08/28 09:29:56 rapsli Exp $

/**
 * @file
 */

/**
 * implementation of hook_fast_gallery_presentation
 */
function fast_gallery_fast_gallery_presentation($images, $ar_bc) {
  global $base_url; 
  $current_path_alias = check_plain($_GET['q']);

  foreach ($images as $image) {
    if (!$image->isDir()) {
      $thumb = theme('imagecache', variable_get('fast_gallery_ic_thumb', ''), $image->getPath());
      $image = l($thumb, imagecache_create_url(variable_get('fast_gallery_ic_full', ''), $image->getPath()), array('html' => TRUE, 'attributes' => array('title' => '')));
      $image_list[] = array(
        'data' => $image,
        'class' => ($i == 0) ? 'active' : '',
      );
    }
  }
  
  $attribs = array(
    'class' => 'gallery clear-block',
  );
  $thumbnails = theme('item_list', $image_list, NULL, 'ul', $attribs);
  $image_count = count($images);
  $prev = t('previous');
  $next = t('next');
  
  $html .= '<div id="galleria-content">';
  $html .= '<div id="main-image"></div>';
  $html .= $thumbnails;
  $html .= '<script type="text/javascript">
      <!--//--><![CDATA[//><!--
      //Hide images while Galleria is loading
      $("ul.gallery img").css("display", "none");
      //--><!]]>
    </script>';
  $html .= '<div class="galleria-nav">
        <a onclick="$.galleria.prev(); return false;" href="#">&laquo; <?php print $prev; ?></a> |
        <a onclick="$.galleria.next(); return false;" href="#"><?php print $next; ?> &raquo;</a>
      </div>';
  $html .= '</div>';

  return $html;
}

/**
 * implementation of hook_fast_gallery_load_requirements()
 */
function fast_gallery_fast_gallery_load_requirements() {
  $module_path = drupal_get_path('module', 'fast_gallery');
  drupal_add_css($module_path . '/presentation/galleria/galleria.css');
  drupal_add_js($module_path . '/presentation/galleria/galleria.js');
  drupal_add_js($module_path . '/presentation/galleria/jquery.galleria.js');
  
}