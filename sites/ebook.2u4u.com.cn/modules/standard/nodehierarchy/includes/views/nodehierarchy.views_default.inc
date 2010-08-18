<?php
// $Id: nodehierarchy.views_default.inc,v 1.1.2.1 2008/09/29 02:19:05 ronan Exp $

/**
 * Implementation of hook_views_default_views().
 */
function nodehierarchy_views_views_default_views() {
  $view = new view;
  $view->name = 'nodehierarchy_children_teasers';
  $view->description = 'Display a node\'s children as teasers';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = '0';
  $view->api_version = 2;
  $view->disabled = FALSE; // Edit this to TRUE to make a default view disabled initially
  $view->display = array();
    $display = new views_display;
    $display->id = 'default';
    $display->display_title = 'Defaults';
    $display->display_plugin = 'default';
    $display->position = '1';
    $display->display_options = array(
      'style_plugin' => 'default',
      'style_options' => array(),
      'row_plugin' => 'node',
      'row_options' =>
      array(
        'teaser' => 1,
      ),
      'relationships' => array(),
      'fields' => array(),
      'sorts' =>
      array(
        'order_by' =>
        array(
          'id' => 'order_by',
          'table' => 'nodehierarchy',
          'field' => 'order_by',
          'order' => 'ASC',
        ),
      ),
      'arguments' =>
      array(
        'parent' =>
        array(
          'id' => 'parent',
          'table' => 'nodehierarchy',
          'field' => 'parent',
          'default_action' => 'not found',
          'style_plugin' => 'default_summary',
          'style_options' =>
          array(
          ),
          'wildcard' => 'all',
          'wildcard_substitution' => 'All',
          'title' => '',
        ),
      ),
      'filters' =>
      array(
        'status' =>
        array(
          'id' => 'status',
          'table' => 'node',
          'field' => 'status',
          'operator' => '=',
          'value' => 1,
          'group' => 0,
          'exposed' => FALSE,
          'expose' =>
          array(
            'operator' => FALSE,
            'label' => '',
          ),
          'expose_button' =>
          array(
            'button' => 'Expose',
          ),
        ),
      ),
      'items_per_page' => 10,
    );
  $view->display['default'] = $display;
  $views[$view->name] = $view;

    // duplicate the view
  $view = unserialize(serialize($view));
  $view->display['default']->display_options['style_plugin'] = 'list';
  $view->display['default']->display_options['style_options'] = array('type' => 'ul');
  $view->display['default']->display_options['row_plugin'] = 'fields';
  $view->display['default']->display_options['fields'] =
      array(
        'title' =>
        array(
          'id' => 'title',
          'table' => 'node',
          'field' => 'title',
          'label' => 'Title',
          'link_to_node' => 1,
        ),
      );
  $view->name = 'nodehierarchy_children_list';
  $view->description = t('Display a node\'s children as a list');
  $views[$view->name] = $view;


  return $views;
}
