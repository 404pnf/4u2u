<?php 
// $Id: default.presentation.inc,v 1.1.2.1 2010/07/29 19:42:36 rapsli Exp $

/**
 * @file
 */

/**
 * implementation of hook_fast_gallery_presentation
 */
function fast_gallery_fast_gallery_presentation($images, $ar_bc) {
    global $base_url; 
    $current_path_alias = check_plain($_GET['q']);
    $html = '';
    $html .='<style type="text/css">.jeip-mouseover { background-color: #ffff99; }</style>';

    $n = 0;
    $script = '';
    
    // Buildung the breadcrumbs that are independant of the site
    $last_element = array_pop($ar_bc);
    $last_element = (count($ar_bc) < 1)?strip_tags($last_element): ' > ' . strip_tags($last_element);
    $html .= '<div id="fg_breadcrumb">' . implode(' > ', $ar_bc) . $last_element . '</div>';
    $html .= '<div id="fg_gallery" class="clear-block">';    
    foreach ($images as $image) {
      if ($image->isDir()) {//incase of a subfolder -> make a different link
        $image_html = l($image->renderHtml(), $current_path_alias .'/'. $image->getName(), array('html' => TRUE));
      }
      else {
        $image_html = '<a href="' . $base_url . '/' . $image->getPath() . '">' . $image->renderHtml() . '</a>';
        $script .= "eip($n, '{$image->getPath()}')\n";
      }

      //use .tpl file to output an image
      $html .= theme('fast_gallery_image_wrapper', $image_html, "<span id=\"fg_imagename-$n\">{$image->getIptc(variable_get('fg_iptc_settings', '<none>'))}</span>");
      $n++;
    }
    $html .= theme('pager');
    if ($html == '') {
      $html .= t('There are no images in this folder. Please make sure that your gallery is !config.', array('!config' => l(t('set up correctly'), 'admin/settings/fast_gallery/general')));
    }
    $html .='</div>';
    if (user_access('administer fast gallery')) {
      $html .= "<script type=\"text/javascript\">\n";
      $html .= "function eip(id, data) { $('#fg_imagename-' + id).eip('$base_url/fast_gallery/ajax/edit-imagename', { select_text: true, form_buttons: '', after_save: false, data: data }) }\n";
      $html .= $script;
      $html .= "</script>\n";
    }
  return $html;
}

/**
 * implementation of hook_fast_gallery_load_requirements()
 */
function fast_gallery_fast_gallery_load_requirements() {
  /* add jeip jquery plugin from joseph scott
   * -> http://josephscott.org/code/javascript/jquery-edit-in-place/
   */
  drupal_add_js(drupal_get_path('module', 'fast_gallery') . '/jeip.js', 'module', 'header');
}