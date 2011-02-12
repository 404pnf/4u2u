<?php
// $Id: webform_validation.admin.inc,v 1.7 2010/09/11 11:44:33 xeniox Exp $

/**
 * @file
 * Manages validation rules administration UI
 */

/**
 * Menu callback function to show an overview of the existing validation rules, and the option to add a rule
 */
function webform_validation_manage($node) {
  $rules = webform_validation_get_webform_rules($node);
  $output .= theme('webform_validation_manage_overview', $rules, $node);
  $output .= theme('webform_validation_manage_add_rule', $node->nid);
  return $output;
}

/**
 * Get the list of rules associated with the webform
 */
function webform_validation_get_webform_rules($node) {
  $vars = webform_validation_get_vars();
  if (in_array($node->type, $vars['webform_contenttypes'])) {
    $webform_nid = $node->nid;
    $rules = webform_validation_get_node_rules($node->nid);
  }
  return $rules;
}

/**
 * Themable function to list the rules assigned to a webform
 */
function theme_webform_validation_manage_overview($rules = array(), $node = NULL) {
  $vars = webform_validation_get_vars();
  $suffix = $vars['path_suffix'];

  $header = array(t('Rule name'), t('Validator'), t('Components'), array('data' => t('Operations'), 'colspan' => 2));
  $validators = webform_validation_get_validators_selection();
  if (!empty($rules)) {
    foreach ($rules as $rule) {
      $component_info = webform_validation_rule_components_basic($rule['components']);
      $row = array();
      $row[] = array(
        'data' => $rule['rulename'],
      );
      $row[] = array(
        'data' => $validators[$rule['validator']],
      );
      $row[] = array(
        'data' => theme('item_list', $component_info),
      );
      $row[] = array(
        'data' => l(t('Edit'), 'node/'. $node->nid .'/' . $suffix . '/validation/edit/'. $rule['validator'] .'/'. $rule['ruleid'], array("query" => drupal_get_destination())),
      );
      $row[] = array(
        'data' => l(t('Delete'), 'node/'. $node->nid .'/' . $suffix . '/validation/delete/'. $rule['ruleid'], array("query" => drupal_get_destination())),
      );
      $rows[] = $row;
    }
  }
  else {
      $rows[][] = array(
        'data' => t('No validation rules available.'),
        'colspan' => 5,
      );
  }

  return theme('table', $header, $rows);
}

function webform_validation_manage_rule($form_state, $node, $action = 'add', $validator, $rule = NULL) {
  $form = array();
  $rule_validator = webform_validation_get_validator_info($validator);

  $form['rule'] = array(
    '#type' => 'fieldset',
    '#title' => ($action == 'edit') ? t('Edit rule') : t('Add rule'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['rule']['validator'] = array(
    '#type' => 'hidden',
    '#value' => $validator,
  );

  $form['rule']['action'] = array(
    '#type' => 'hidden',
    '#value' => $action,
  );

  if ($action == 'edit' && $rule) {
    $form['rule']['ruleid'] = array(
      '#type' => 'hidden',
      '#value' => $rule['ruleid'],
    );

    $form['rule']['nid'] = array(
      '#type' => 'hidden',
      '#value' => $rule['nid'],
    );
  }
  else {
    $form['rule']['nid'] = array(
      '#type' => 'hidden',
      '#value' => $node->nid,
    );
  }

  $form['rule']['rulename'] = array(
    '#type' => 'textfield',
    '#title' => t('Rule name'),
    '#default_value' => (isset($rule['rulename'])) ? $rule['rulename'] : '',
    '#required' => TRUE,
    '#size' => 60,
    '#maxlength' => 255,
    '#weight' => 1,
  );

  $form['rule']['rule_components'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Components'),
    '#weight' => 3,
    '#description' => t('Select the components to be validated by this validation rule'),
    '#options' => webform_validation_get_webform_components($node, $validator),
    '#default_value' => (isset($rule['components'])) ? array_keys($rule['components']) : array(),
  );

  if (is_array($rule_validator['custom_data'])) {
    $form['rule']['data'] = array(
      '#type' => 'textfield',
      '#title' => $rule_validator['custom_data']['label'],
      '#description' => $rule_validator['custom_data']['description'],
      '#required' => TRUE,
      '#size' => 60,
      '#maxlength' => 255,
      '#default_value' => $rule['data'],
      '#weight' => 4,
    );
  }

  if ($rule_validator['custom_error']) {
    $form['rule']['error_message'] = array(
      '#type' => 'textfield',
      '#title' => t('Custom error message'),
      '#description' => t("Specify an error message that should be displayed when user input doesn't pass validation"),
      '#required' => TRUE,
      '#size' => 60,
      '#maxlength' => 255,
      '#default_value' => $rule['error_message'],
      '#weight' => 5,
    );
  }

  $form['rule']['submit'] = array(
    '#type' => 'submit',
    '#value' => (isset($rule['ruleid'])) ? t('Edit rule') : t('Add rule'),
    '#weight' => 25,
  );

  return $form;
}

/**
 * Validation handler to add / edit a rule
 */
function webform_validation_manage_rule_validate($form, &$form_state) {
  $values = $form_state['values'];
  if ($values['action'] == 'edit') {
    if (!is_numeric($values['ruleid']) || $values['ruleid'] == 0) {
      form_set_error(NULL, t('A problem occurred while editing this rule. Please try again.'));
    }
  }

  $rule_validator = webform_validation_get_validator_info($values['validator']);
  $selected_components = count(array_filter($values['rule_components']));
  // check validator min_components property
  if (isset($rule_validator['min_components']) && $rule_validator['min_components'] > 0) {
    if ($rule_validator['min_components'] > $selected_components) {
      form_set_error('rule_components', format_plural($rule_validator['min_components'], 'You need to select at least @count component', 'You need to select at least @count components'));
    }
  }
  // check validator max_components property
  if (isset($rule_validator['max_components']) && $rule_validator['max_components'] > 0) {
    if ($rule_validator['max_components'] < $selected_components) {
      form_set_error('rule_components', format_plural($rule_validator['max_components'], 'You can select @count component at most', 'You can select @count components at most'));
    }
  }
}


/**
 * Submit handler to add / edit a rule
 */
function webform_validation_manage_rule_submit($form, &$form_state) {
  $values = $form_state['values'];
  webform_validation_rule_save($values);
}

/**
 * Get a list of components for a specific webform, filtered by the validator settings
 */
function webform_validation_get_webform_components($node, $validator) {
  $ret = array();
  $components = $node->webform['components'];
  $valid_components = webform_validation_valid_component_types($validator);
  if ($components) {
    foreach ($components as $cid => $component) {
      if (in_array($component['type'], $valid_components)) {
        $ret[$cid] = $component['name'];
      }
    }
  }
  return $ret;
}

/**
 * Confirmation form to delete a rule
 */
function webform_validation_delete_rule(&$form_state, $rule) {
  $form['ruleid'] = array(
    '#type' => 'value',
    '#value' => $rule['ruleid'],
  );

  return confirm_form($form,
    t('Are you sure you want to delete the rule %name?', array('%name' => $rule['rulename'])),
    isset($_GET['destination']) ? $_GET['destination'] : $_GET['q'],
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Submit handler to delete a rule
 */
function webform_validation_delete_rule_submit($form, &$form_state) {
  $ruleid = $form_state['values']['ruleid'];
  webform_dynamic_delete_rule($ruleid);
  module_invoke_all('webform_validation', 'rule', 'delete', $ruleid);
}
