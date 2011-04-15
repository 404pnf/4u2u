<?php
// $Id:

/**
 * Implementation of hook_features_export_options().
 */
function fast_gallery_features_export_options() {
  $options = array();
  $options['fast_gallery_default_settings'] = 'Fast Gallery Default Settings';
  return $options;
}

/**
 * Implementation of hook_features_export().
 */
function fast_gallery_features_export($data, &$export) {
  $pipe = array();
  // Default hooks are provided by the feature module so we need to add
  // it as a dependency.
  $export['dependencies']['features'] = 'features';
  $export['dependencies']['fast_gallery'] = 'fast_gallery';

  foreach ($data as $options) {
    $export['features']['fast_gallery'][$options] = $options;
  }
  return $pipe;
}

/**
 * Implementation of hook_features_export_render()
 */
function fast_gallery_features_export_render($module = 'foo', $data) {
  $code = array();
  $code[] = '  $items = array();';
  $code[] = '';

  $code[] = "  \$items[fg_folder_cache] = " . features_var_export(variable_get('fg_folder_cache', 1)) . ";";
  $code[] = "  \$items[fg_folder_first] = " . features_var_export(variable_get('fg_folder_first', 1)) . ";";
  $code[] = "  \$items[fg_galleries] = " . features_var_export(variable_get('fg_galleries', array())) . ";";
  $code[] = "  \$items[fg_iptc_settings] = " . features_var_export(variable_get('fg_iptc_settings', '<none>')) . ";";
  $code[] = "  \$items[fg_pager_amount] = " . features_var_export(variable_get('fg_pager_amount', 20)) . ";";
  $code[] = "  \$items[fg_sort_direction] = " . features_var_export(variable_get('fg_sort_direction', NULL)) . ";";
  $code[] = "  \$items[fg_sort_order] = " . features_var_export(variable_get('fg_sort_order', 'filename')) . ";";
  $code[] = "  \$items[fg_storage_engine] = " . features_var_export(variable_get('fg_storage_engine', array())) . ";";
  $code[] = "  \$items[fast_gallery_cron] = " . features_var_export(variable_get('fast_gallery_cron', 1)) . ";";
  $code[] = "  \$items[fast_gallery_ic_full] = " . features_var_export(variable_get('fast_gallery_ic_full', '')) . ";";
  $code[] = "  \$items[fast_gallery_ic_thumb] = " . features_var_export(variable_get('fast_gallery_ic_thumb', '')) . ";";
  $code[] = "  \$items[fast_gallery_js_framework] = " . features_var_export(variable_get('fast_gallery_js_framework', '')) . ";";
  $code[] = "  \$items[fg_iptc_settings_title] = " . features_var_export(variable_get('fg_iptc_settings_title', '<none>')) . ";";
  
  $code[] = '';
  $code[] = '  return $items;';
  $code = implode("\n", $code);
  return array('features_default_fast_gallery' => $code);
}

/**
 * Implementation of hook_features_revert().
 */
function fast_gallery_features_revert($module) {
  fast_gallery_features_rebuild($module);
}

/**
 * Implementation of hook_features_rebuild().
 */
function fast_gallery_features_rebuild($module) {
  $defaults = module_invoke($module, 'features_default_fast_gallery');
  $menus = array();
  
  if (!empty($defaults)) {
    foreach ($defaults as $key => $item) {
      variable_set($key, $item);
    }
  }
  $fg = fast_gallery_get_FastGallery();
  $fg->rescanGallery();
}