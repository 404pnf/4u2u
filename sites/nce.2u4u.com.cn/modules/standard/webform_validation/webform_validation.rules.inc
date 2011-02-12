<?php
// $Id: webform_validation.rules.inc,v 1.1 2009/11/16 16:03:32 xeniox Exp $

/**
 * @file
 * provides API and management functions for the webform validation rules
 */

/**
 * Get a rule entry
 */
function webform_validation_get_rule($ruleid) {
  $result = db_query("SELECT ruleid, rulename, nid, validator, data, error_message FROM {webform_validation_rule} WHERE ruleid = %d", $ruleid);
  if ($rule = db_fetch_array($result)) {
    $rule['components'] = webform_validation_get_rule_components($ruleid, $rule['nid']);
  }
  return $rule;
}

/**
 * Get an array of rules assigned to a webform node
 */
function webform_validation_get_node_rules($nid) {
  $rules = array();
  $result = db_query("SELECT ruleid, rulename, nid, validator, data, error_message FROM {webform_validation_rule} WHERE nid = %d ORDER BY ruleid DESC", $nid);
  while ($rule = db_fetch_array($result)) {
    $rule['components'] = webform_validation_get_rule_components($rule['ruleid'], $rule['nid']);
    $rules[$rule['ruleid']] = $rule;
  }
  return $rules;
}

/**
 * Get an array of components linked to a rule
 */
function webform_validation_get_rule_components($ruleid, $nid) {
  $cids = array();
  $components = array();
  //$result = db_query("SELECT v.cid, c.name FROM {webform_validation_rule_components} v INNER JOIN {webform_component} c ON v.cid = c.cid AND c.nid = %d WHERE v.ruleid = %d", $ruleid);
  $result = db_query("SELECT cid FROM {webform_validation_rule_components} WHERE ruleid = %d", $ruleid);
  while ($row = db_fetch_array($result)) {
    $cids[] = $row['cid'];
  }

  if ($cids) {
    $all_components = webform_validation_get_all_components($nid);
    $all_component_keys = array_keys($all_components);
    foreach ($cids as $cid) {
      if (in_array($cid, $all_component_keys)) {
        $components[$cid] = $all_components[$cid];
      }
    }
  }
  return $components;
}

/**
 * Get info on all components that are available on a webform
 */
function webform_validation_get_all_components($nid) {
  $components = array();
  $result = db_query("SELECT * FROM {webform_component} WHERE nid = %d", $nid);
  while ($row = db_fetch_array($result)) {
    $components[$row['cid']] = $row;
  }
  return $components;
}

/**
 * This helper function takes a list of full component info arrays and returns a basic representation of it for output purposes.
 */
function webform_validation_rule_components_basic($components) {
  $ret = array();
  if ($components) {
    foreach ($components as $cid => $component) {
      $ret[$cid] = $component["name"];
    }
  }
  return $ret;
}

/**
 * Delete a rule and dependencies
 */
function webform_dynamic_delete_rule($ruleid) {
  db_query("DELETE FROM {webform_validation_rule} WHERE ruleid = %d" , $ruleid);
  db_query("DELETE FROM {webform_validation_rule_components} WHERE ruleid = %d", $ruleid);
}