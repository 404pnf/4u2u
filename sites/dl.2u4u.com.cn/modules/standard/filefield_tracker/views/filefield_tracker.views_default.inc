<?php

/**
 * Implementation of hook_views_default_views().
 */
function filefield_tracker_views_default_views() {
  /*
   * View 'filefield_tracker_node'
   */
  $view = new view;
  $view->name = 'filefield_tracker_node';
  $view->description = 'Show a report of all tracked file downloads for a specific node';
  $view->tag = 'filefield_tracker';
  $view->view_php = '';
  $view->base_table = 'filefield_tracker';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'uid' => array(
      'label' => 'Downloaded by user',
      'required' => 1,
      'id' => 'uid',
      'table' => 'filefield_tracker',
      'field' => 'uid',
      'relationship' => 'none',
    ),
    'fid' => array(
      'label' => 'Downloaded file',
      'required' => 1,
      'id' => 'fid',
      'table' => 'filefield_tracker',
      'field' => 'fid',
      'relationship' => 'none',
    ),
    'nid' => array(
      'label' => 'Downloaded from node',
      'required' => 1,
      'id' => 'nid',
      'table' => 'filefield_tracker',
      'field' => 'nid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'filename' => array(
      'label' => 'Name',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_file' => 0,
      'exclude' => 0,
      'id' => 'filename',
      'table' => 'files',
      'field' => 'filename',
      'relationship' => 'fid',
    ),
    'name' => array(
      'label' => 'Downloaded by',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'uid',
    ),
    'download_time' => array(
      'label' => 'Download time',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'date_format' => 'medium',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'download_time',
      'table' => 'filefield_tracker',
      'field' => 'download_time',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'download_time' => array(
      'order' => 'DESC',
      'granularity' => 'second',
      'id' => 'download_time',
      'table' => 'filefield_tracker',
      'field' => 'download_time',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'nid' => array(
      'default_action' => 'not found',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'node',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'relationship' => 'nid',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '3' => 0,
      ),
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'file' => 0,
        'page' => 0,
        'story' => 0,
        'upload' => 0,
      ),
      'validate_argument_node_access' => 1,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'view filefield_tracker reports',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'desc',
    'columns' => array(
      'filename' => 'filename',
      'name' => 'name',
      'download_time' => 'download_time',
    ),
    'info' => array(
      'filename' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'download_time' => array(
        'sortable' => 1,
        'separator' => '',
      ),
    ),
    'default' => 'download_time',
  ));
  $views[$view->name] = $view;

  /*
   * View 'filefield_tracker_report'
   */
  $view = new view;
  $view->name = 'filefield_tracker_report';
  $view->description = 'Show a report of all tracked file downloads on the site';
  $view->tag = 'filefield_tracker';
  $view->view_php = '';
  $view->base_table = 'filefield_tracker';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'nid' => array(
      'label' => 'Downloaded from node',
      'required' => 1,
      'id' => 'nid',
      'table' => 'filefield_tracker',
      'field' => 'nid',
      'relationship' => 'none',
    ),
    'fid' => array(
      'label' => 'Downloaded file',
      'required' => 1,
      'id' => 'fid',
      'table' => 'filefield_tracker',
      'field' => 'fid',
      'relationship' => 'none',
    ),
    'uid' => array(
      'label' => 'Downloaded by user',
      'required' => 1,
      'id' => 'uid',
      'table' => 'filefield_tracker',
      'field' => 'uid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'filename' => array(
      'label' => 'Filename',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_file' => 0,
      'exclude' => 0,
      'id' => 'filename',
      'table' => 'files',
      'field' => 'filename',
      'relationship' => 'fid',
    ),
    'title' => array(
      'label' => 'Downloaded from',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'nid',
    ),
    'name' => array(
      'label' => 'Downloaded by',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => 'Anonymous',
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'uid',
    ),
    'download_time' => array(
      'label' => 'Download time',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'date_format' => 'medium',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'download_time',
      'table' => 'filefield_tracker',
      'field' => 'download_time',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'view filefield_tracker reports',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'File download report');
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'desc',
    'columns' => array(
      'filename' => 'filename',
      'title' => 'title',
      'name' => 'name',
      'download_time' => 'download_time',
    ),
    'info' => array(
      'filename' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'download_time' => array(
        'sortable' => 1,
        'separator' => '',
      ),
    ),
    'default' => 'download_time',
  ));
  $views[$view->name] = $view;

  return $views;
}