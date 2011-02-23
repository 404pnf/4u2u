<?php
// $Id: node_limitnumber.inc,v 1.3.2.1 2009/09/22 17:17:34 jdwfly Exp $

/**
 * @file
 * Helper functions for node_limitnumber.module
 */


/**
  * Admin form for new rules
  */

function node_limitnumber_admin_modify_form() {
  // Get list of node types and roles, and actual rules
  $roles = user_roles(TRUE);
  $pubtypes = node_get_types('names');
  $rules = node_limitnumber_get_all();
  // Build the form
  
  $form['add'] = array(
    '#id' => 'node_limitnumber_admin_add_form',
    '#redirect' => 'admin/settings/node_limitnumber',
	'#type' => 'fieldset',
  );
  $form['add']['title'] = array(
    '#value' => '<h2>'. t('Add limit') .'</h2>',
  );
  $form['add']['role'] = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#title' => t('Role'),
    '#options' => $roles,
  );
  $form['add']['pubtype'] = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#title' => t('Publication type'),
    '#options' => $pubtypes,
  );
  $form['add']['limit'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
	'#default_value' => '1',
    '#title' => t('Limit'),
    '#description' => t('Number of nodes of selected type the user is allowed to send. A limit of zero is not allowed, you\'d better use !access_control for that.', array( '!access_control' => l(t('Access control'), 'admin/user/permissions'))),
    '#maxlength' => 4,
    '#size' => 4,
  );
  $form['add']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#submit' => array('node_limitnumber_admin_add_form_submit'),
    '#validate' => array('node_limitnumber_admin_add_form_validate'),
  );
  $form['modify'] = array(
    '#id' => 'node_limitnumber_admin_modify_form_submit',
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );
  $form['modify']['title'] = array(
    '#value' => '<h2>'. t('Stored limits') .'</h2>',
  );
  // Loop for every stored rule
  $i = 0;
  foreach ($rules as $rule) {
    $form['modify'][$i]['role'] = array(
      '#type' => 'select',
      '#required' => TRUE,
      '#options' => $roles,
      '#default_value' => $rule['item'],
    );
    $form['modify'][$i]['pubtype'] = array(
      '#type' => 'select',
      '#required' => TRUE,
      '#options' => $pubtypes,
      '#default_value' => $rule['pubtype'],
    );
    $form['modify'][$i]['limit'] = array(
      '#type' => 'textfield',
      '#required' => TRUE,
      '#maxlength' => 4,
      '#size' => 4,
      '#default_value' => $rule['max'],
    );
    $form['modify'][$i]['id'] = array(
      '#type' => 'hidden',
      '#value' => $rule['id'],
    );
    $i++;  
  }
  $form['modify']['modify'] = array(
    '#type' => 'submit',
    '#value' => t('Modify'),
    '#weight' => 99,
    '#tree' => FALSE,
    '#submit' => array('node_limitnumber_admin_modify_form_submit'),
  );
  return $form;
}
/**
  * Theme function to render modify rules form in admin side
  */
function theme_node_limitnumber_admin_modify_form($form) {
  $header = array(t('Role'), t('Publication type'), t('Limit'), '');
  $i = 0;
  while ($form['modify'][$i]) {
    $row = array(
      drupal_render($form['modify'][$i]['role']),
      drupal_render($form['modify'][$i]['pubtype']),
      drupal_render($form['modify'][$i]['limit']),
      drupal_render($form['modify'][$i]['id']) . l(t('delete'), 'admin/settings/node_limitnumber/delete/'. $form['modify'][$i]['id']['#value']),
    );
    unset($form['modify'][$i]);
    $rows[] = $row;
    $i++;
  }
  $table = theme('table', $header, $rows);
  $form['modify']['table'] = array(
    '#value' => $table,
    '#weight' => 90,
  );
  $output = drupal_render_form($form['#id'], $form);
  return $output;
}
/**
  * Get all rules and return as multidimensional array.
  */
function node_limitnumber_get_all() {
  $result = db_query("SELECT * FROM {node_limitnumber_rules} WHERE class = 'role'");
  $rules = array();
  while ($rules[] = db_fetch_array($result)) {
  }
  array_pop($rules);
  return $rules;
}
/**
  * GHelper function: get all limits for a user and a publication type
  */
function _get_limits_for_user($user, $nodetype) {
  $i = count($user->roles);
  foreach ($user->roles as $key => $role) {
    $ax .= 'item = '. $key;
    $i--;
    if ($i > 0) $ax .= ' OR ';
  }
  $q = "SELECT max FROM {node_limitnumber_rules} WHERE class = 'role'";
  $q .= " AND pubtype = '". $nodetype ."'";
  $q .= " AND (". $ax .") ORDER BY max DESC LIMIT 1";
  $result = db_query($q);
  $max = db_result($result);
  return $max;
}