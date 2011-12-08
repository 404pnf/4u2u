<?php

/**
 * @file
 * Provides some WURFL functionalities as ThemeKey properties.
 *
 * @author Markus Kalkbrenner | Cocomore AG
 *   @see http://drupal.org/user/124705
 */


/**
 * Implements hook_themekey_properties().
 *
 * Provides additional properties for module ThemeKey:
 * - wurfl:is_mobile
 *
 * @return
 *   array of themekey properties and mapping functions
 */
function themekey_wurfl_themekey_properties() {
  // Attributes for properties
  $attributes = array();

  $attributes['wurfl:is_mobile_browser'] = array(
    'description' => t("wurfl: is_mobile_browser - If WURFL module is installed, 'true' if a visitor is using a mobile browser, otherwise 'false'."),
    'validator' => 'themekey_validator_string_boolean',
    'page cache' => THEMEKEY_PAGECACHE_UNSUPPORTED,
  );

  $maps = array();

  $maps[] = array('src'       => 'system:dummy',
                  'dst'       => 'wurfl:is_mobile_browser',
                  'callback'  => 'themekey_wurfl_dummy2is_mobile_browser');

  return array('attributes' => $attributes, 'maps' => $maps);
}


/**
 * ThemeKey mapping function to set a
 * ThemeKey property's value (destination)
 * with the aid of another ThemeKey property (source).
 *
 * src: system:dummy
 * dst: wurfl:is_mobile_browser
 *
 * @param $dummy
 *   just a dummy
 *
 * @return
 *   string 'true' if client is a mobile browser, otherwise 'false',
 *   or NULL if no value could be mapped
 */
function themekey_wurfl_dummy2is_mobile_browser($dummy) {
  $requesting_device = wurfl_get_requestingDevice();

  if (is_object($requesting_device)) {
    return $requesting_device->getCapability('mobile_browser') ? 'true' : 'false';
  }

  return NULL;
}
