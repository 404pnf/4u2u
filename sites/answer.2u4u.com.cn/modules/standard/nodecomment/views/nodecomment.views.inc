<?php
// $Id: nodecomment.views.inc,v 1.1.2.1 2008/09/29 14:00:23 sirkitree Exp $
/**
 * @file
 * Provide views data and handlers for nodecomment.module
 */

/**
 * @defgroup views_nodecomment_module nodecomment.module handlers
 *
 * Includes the tables 'node', 'node_comments' and 'node_comment_statistics'.
 * @{
 */

function nodecomment_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'nodecomment') .'/views',
    ),
    'handlers' => array(
      'views_handler_field_username_comment' => array(
        'parent' => 'views_handler_field',
      ),
      'views_handler_field_comment_depth' => array(
        'parent' => 'views_handler_field'
      ),
      'views_handler_field_username_comment' => array(
        'parent' => 'views_handler_field'
      ),
      'views_handler_field_comment_link' => array(
        'parent' => 'views_handler_field'
      ),
      'views_handler_field_comment_link_reply' => array(
        'parent' => 'views_handler_field_comment_link'
      ),
      'views_handler_sort_comment_thread' => array(
        'parent' => 'views_handler_sort'
      ),
    ),
  );
}

/**
 * Implementation of hook_views_data()
 */
function nodecomment_views_data() {
  // since comments are nodes we keep with the Node group
  $data['node_comments']['table']['group']  = t('Node');
	
	// ----------------------------------------------------------------
  // node table -- basic table information.

	$data['node_comments']['table']['join'] = array(
		// node_comments links to node
		'node' => array(
			'left_field' => 'nid',
			'field' => 'cid',
		),
	);
	
	// ----------------------------------------------------------------
  // node_comments table -- fields
  
  $data['node_comments']['cid'] = array(
    'title' => t('Nid'),
    'help' => t('The node ID of the comment.'),
    'argument' => array(
      'handler' => 'views_handler_argument_node_nid',
      'name field' => 'title', 
      'numeric' => TRUE,
      'validate type' => 'nid',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  $data['node_comments']['nid'] = array(
    'title' => t('Original Parent Nid'),
    'help' => t('The original node the comment is a reply to.'),
    'relationship' => array(
      'base' => 'node',
      'field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Node'),
    ),
  );
  
  $data['node_comments']['pid'] = array(
    'title' => t('Parent Nid'),
    'help' => t('The node of the parent comment. Could be another comment.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'relationship' => array(
      'title' => t('Parent comment'),
      'help' => t('The parent comment.'),
      'base' => 'comments',
      'field' => 'cid',
      'handler' => 'views_handler_relationship',
      'label' => t('Parent comment'),
    ),
  );
  
  $data['node_comments']['name'] = array(
    'title' => t('Author'),
    'help' => t('The name of the poster.'),
    'field' => array(
      'handler' => 'views_handler_field_username_comment',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['node_comments']['homepage'] = array(
    'title' => t("Author's website"),
    'help' => t("The website address of the comment's author. Can be a link. The homepage can also be linked with the Name field. Will be empty if posted by a registered user."),
    'field' => array(
      'handler' => 'views_handler_field_url',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['node_comments']['thread'] = array(
    'field' => array(
      'title' => t('Depth'),
      'help' => t('Display the depth of the comment if it is threaded.'),
      'handler' => 'views_handler_field_comment_depth',
    ),
    'sort' => array(
      'title' => t('Thread'),
      'help' => t('Sort by the threaded order. This will keep child comments together with their parents.'),
      'handler' => 'views_handler_sort_comment_thread',
    ),
  );
  
  // link to reply to comment
  $data['node_comments']['replyto_comment'] = array(
    'field' => array(
      'title' => t('Reply-to link'),
      'help' => t('Provide a simple link to reply to the comment.'),
      'handler' => 'views_handler_field_comment_link_reply',
    ),
  );
	
  return $data;
}


/**
 * Implementation of hook_views_plugins
 */
function nodecomment_views_plugins() {
  return array(
    'style' => array(
      'nodecomment_threaded' => array(
  		  'path' => drupal_get_path('module', 'nodecomment') .'/views',
        'theme path' => drupal_get_path('module', 'nodecomment') .'/views',
        'title' => t('Comments threaded'),
        'help' => t('Display the comment with a threaded comment view.'),
        'handler' => 'nodecomment_plugin_style_threaded',
        'theme' => 'nodecomment_threaded',
        'uses row plugin' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}

?>