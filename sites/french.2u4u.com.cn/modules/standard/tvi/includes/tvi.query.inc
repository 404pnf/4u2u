<?php

/**
 * @file
 * TVI Database Interface
 */

/**
 * Returns a default setting object.
 */
function tvi_default_settings($type = TVI_TYPE_TERM, $xid = 0) {
  $schema = drupal_get_schema('tvi_settings');
  $settings = array_map(create_function('$field', 'return array_key_exists("default", $field) ? $field["default"] : NULL;'), $schema['fields']);
  
	// Override some values
  $settings['type'] = $type;
  $settings['xid']  = $xid;
  
  // Add some extra properties
  $settings['view_id'] = 0;
  $settings['is_default'] = TRUE;
		
  return (object) $settings;	
}

/**
 * Loads a setting from the database or return a default, if the $return_default
 * flag is set.
 */
function tvi_load_settings($xid, $type = TVI_TYPE_TERM, $return_default = TRUE) {
	$settings = db_fetch_object(db_query("SELECT * FROM {tvi_settings} ts WHERE ts.type = '%s' AND ts.xid = %d", $type, $xid));
  
  if (!is_object($settings)) {
  	return ($return_default ? tvi_default_settings($type, $xid) : NULL);
  }
  
  $settings->is_default = FALSE;
  return $settings;
}

/**
 * Saves settings information for a taxonomy vocabulary or term to the database.
 */
function tvi_update_settings($settings) {
  // Do not use db_affected_rows(), which may fail with old versions
  // of MySQL, returning 0 when data are unchanged.
  $update = array();
  if (db_result(db_query("SELECT COUNT(*) FROM {tvi_settings} WHERE type = '%s' AND xid = %d", $settings->type, $settings->xid))) {
    $update = array('type', 'xid');
  }
  
  return drupal_write_record('tvi_settings', $settings, $update);
}

/**
 * Removes a specific settings entry from the database.
 * 
 * @param $xid The object ID
 * @param $type The object type (TVI_TYPE_TERM or TVI_TYPE_VOCAB)
 * @return The database query resource
 */
function tvi_remove_settings($xid, $type = TVI_TYPE_TERM) {
  return db_query("DELETE FROM {tvi_settings} WHERE type = '%s' AND xid = %d", $type, $xid);	
}
