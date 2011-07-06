<?php
// $Id: nodehierarchy_workflow_ng.inc,v 1.2.2.1 2008/05/14 22:22:00 ronan Exp $

/**
 * @file
 * Some workflow-ng conditions/actions
 */

/**
 * Implementation of hook_condition_info()
 */
function nodehierarchy_condition_info() {
  return array(
    'nodehierarchy_has_parent' => array(
      '#label' => t('Content has parent'),
      '#arguments' => array(
        'node' => array('#entity' => 'node', '#label' => t('Content')),
      ),
      '#module' => t('Node Hierarchy'),
    ),
  );
}

function nodehierarchy_has_parent($node, $settings) {
  return (bool)$node->parent;
}


/**
 * Implementation of hook_action_info()
 */
function nodehierarchy_action_info() {
  return array(
    'nodehierarchy_action_load' => array(
      '#label' => t('Load a content\'s parent content'),
      '#arguments' => array(
        'node' => array('#entity' => 'node', '#label' => t('Child content')),
      ),
      '#new arguments' => array(
        'node_parent' => array('#entity' => 'node', '#label' => t('Parent content')),
      ),
      '#module' => t('Node Hierarchy'),
    ),
  );
}

/**
 * Loads the node's parent.
 */
function nodehierarchy_action_load($node, $settings) {
  if ($parent = node_load($node->parent)) {
    return array('#new arguments' => array('node_parent' => $parent));
  }
}
