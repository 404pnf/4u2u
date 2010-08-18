<?php
// $Id: nodehierarchy.views.inc,v 1.1.2.1 2008/09/29 02:19:05 ronan Exp $

// Implementations of Views 2 Hooks

/**
 * Implementation of hook_views_handlers()
 */
function nodehierarchy_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'nodehierarchy') .'/includes/views',
    ),
    'handlers' => array(
      'views_handler_field_nodehierarchy_actions' => array(
        'parent' => 'views_handler_field',
      ),
      'views_handler_field_nodehierarchy_parent' => array(
        'parent' => 'views_handler_field',
      ),
      'views_handler_argument_nodehierarchy_ancestor' => array(
        'parent' => 'views_handler_argument',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_data()
 */
function nodehierarchy_views_views_data() {
  // Basic table information.

  // Define the base group of this table. Fields that don't
  // have a group defined will go into this field by default.
  $data['nodehierarchy']['table']['group']  = t('Node Hierarchy');

  // Joins
  $data['nodehierarchy']['table']['join'] = array(
    //...to the node table
    'node' => array(
      'handler' => 'views_join',
      'arguments' => array('nodehierarchy', 'node', 'nid', 'nid'),
    ),
  );

  // ----------------------------------------------------------------
  // Fields.

  // Parent.
  $data['nodehierarchy']['parent'] = array(
    'title' => t('Parent Node'),
    'help' => t('The parent id of the node.'),
    // Information for displaying the parent.
    'field' => array(
      'handler' => 'views_handler_field_nodehierarchy_parent',
      'click sortable' => TRUE,
    ),
    // Information for accepting a parent as an argument.
    'argument' => array(
      'handler' => 'views_handler_argument_node_nid',
      'click sortable' => TRUE,
    ),
    // Information for accepting a parent as a filter.
    'filter' => array(
      'handler' => 'views_handler_filter_equality',
    ),

  );

  // Sort order.
  $data['nodehierarchy']['order_by'] = array(
    'title' => t('Child Sort Order'),
    'help' => t('The assigned order of the node relative to it\'s siblings.'),
    // Information for sorting on a order_by.
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Bogus fields for aliasing purposes.
  $data['nodehierarchy']['antecedent'] = array(
    'title' => t('Ancestor Node ID'),
    'help' => t('Use this if you want to display any descendant of the given node'),
    'argument' => array(
      'handler' => 'views_handler_argument_nodehierarchy_ancestor',
    ),
  );

  $data['nodehierarchy']['actions'] = array(
    'title' => t('Actions'),
    'help' => t('Edit, view and reorder actions'),
    'field' => array(
      'field' => 'nid', // the real field
      'group' => t('Node Hierarchy'), // The group it appears in on the UI,
      'handler' => 'views_handler_field_nodehierarchy_actions',
      'click sortable' => FALSE,
    ),
  );

  return $data;
}

