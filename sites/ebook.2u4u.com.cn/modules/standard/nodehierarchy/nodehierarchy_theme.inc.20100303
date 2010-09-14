<?php
// $Id: nodehierarchy_theme.inc,v 1.4.2.4 2009/11/03 15:57:05 ronan Exp $

function nodehierarchy_theme() {
  return array(
    'nodehierarchy_node_list' => array(
      'arguments' => array('nodes' => NULL, 'expandable' => FALSE),
    ),
    'nodehierarchy_new_child_links' => array(
      'arguments' => array('node' => NULL),
    ),
    'nodehierarchy_actions' => array(
      'arguments' => array('node' => NULL),
    ),
    'nodehierarchy_action' => array(
      'arguments' => array('url' => '', 'name' => '', 'active' => TRUE),
    ),
    'node_hierarchy_item_list' => array(
      'arguments' => array('items' => array(), 'attributes' => NULL),
    ),
    'nodehierarchy_children_list' => array(
      'arguments' => array('node' => NULL, 'children' => array(), 'show_create_links' => TRUE),
    ),
    'nodehierarchy_children_list_more_link' => array(
      'arguments' => array('node' => NULL, 'num_displayed' => 20, 'total' => 0),
    ),
  );
}

/**
 * @file
 * Nodehierarchy theming functions
 */

/**
 * Display a list of nodes with nodehierarchy actions
 */
function theme_nodehierarchy_node_list($nodes, $expandable = FALSE) {
  $out = "";

  $rows = array();
  foreach ($nodes as $node) {
    if (node_access('view', $node)) {
      $row = array(
        "class"   =>  "nodehierarchy_child",
        "id"      =>  'nh-'. $node->nid,
        'data'    =>  theme("nodehierarchy_actions", $node)
      );

      if ($expandable) {
        $row['data'] .= _nodehierarchy_toggle_expand_link($node->title, $node->nid);
      }
      else {
        $row['data'] .= l($node->title, "node/". $node->nid);
      }

      if ($expandable && _nodehierarhcy_is_expanded($node->nid)) {
        $row['data']  .= _nodehierarchy_display_children_list($node, TRUE);
        $row['class'] .= " expanded";
      }
      elseif ($expandable && variable_get('nh_parent_'. $node->type, FALSE)) {
        $row['class'] .= " collapsed";
      }
      $rows[] = $row;
    }
  }

  if ($rows) {
    $out .= theme("node_hierarchy_item_list", $rows, array("class" => "nodehierarchy_outline menu"));
  }
  return $out;
}

/**
 * Display links to create new children nodes of the given node
 */
function theme_nodehierarchy_new_child_links($node) {
  $out = "";
  $create_links = array();

  if (user_access('create child nodes') && node_access('update', $node)) {
    foreach (node_get_types() as $key => $type) {
      if (node_access('create', $key) && variable_get('nh_child_'. $key, FALSE)) {
        $destination = drupal_get_destination() ."&edit[parent]=$node->nid";
        $key = str_replace('_', '-', $key);
        $title = t('Add a new %s.', array('%s' => $type->name));
        $create_links[] = l($type->name, "node/add/$key", array('query' => $destination, 'attributes' => array('title' => $title)));
      }
    }
    if ($create_links) {
      $out = '<div class="newchild">'. t("create new child !s", array('!s' => implode(" | ", $create_links))) .'</div>';
    }
  }
  return $out;
}

/**
 * Display node hierarchy action links (view, edit, move up, move down, etc.)
 */
function theme_nodehierarchy_actions($node) {
  global $user;
  drupal_add_css(drupal_get_path('module', 'nodehierarchy') .'/nodehierarchy.css');

  $destination = drupal_get_destination();
  $actions = array();
  $actions[] = theme('nodehierarchy_action', url("node/$node->nid"), 'view', node_access('view', $node));
  $actions[] = theme('nodehierarchy_action', url("node/$node->nid/edit", array('query' => $destination)), 'edit', node_access('update', $node));
  $actions[] = theme('nodehierarchy_action', url("node/$node->nid/delete", array('query' => $destination)), 'delete', node_access('delete', $node));
  if (user_access('reorder children')) {
    $actions[] = theme('nodehierarchy_action', url("hierarchy/$node->nid/up", array('query' => $destination)), 'up');
    $actions[] = theme('nodehierarchy_action', url("hierarchy/$node->nid/down", array('query' => $destination)), 'down');
  }

  return "<div class='nodehierarchy_actions'>". implode("", $actions) .'</div>';
}

/**
 * Display a single node hierarchy action link
 */
function theme_nodehierarchy_action($url, $name, $active = TRUE) {
  $img_path = base_path() . drupal_get_path('module', 'nodehierarchy') ."/images/$name.gif";

  if ($active) {
    return '<a href="'. $url .'" class="nodehierarchy_action nodehierarchy_action_'. $name .'" title="'. t($name) .'"><span class="nodehierarchy_icon"><img src="'. $img_path .'" height="16" width="16" /></span><span class="label">'. t($name) .'</span></a>';
  }
  else {
    return '<span class="nodehierarchy_action"><span class="nodehierarchy_icon disabled"><img src="'. $img_path .'" height="16" width="16" /></span><span class="label">'. t($name) .'</span></span>';
  }
}

/**
 * Return a themed list of items.
 */
function theme_node_hierarchy_item_list($items = array(), $attributes = NULL) {
  if (!empty($items)) {
    $output .= "<ul". drupal_attributes($attributes) .'>';
    foreach ($items as $item) {
      $attributes = array();
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }
      $output .= '<li'. drupal_attributes($attributes) .'>'. $data .'</li>';
    }
    $output .= "</ul>";
  }
  return $output;
}

/**
 * Return a themed list of items.
 */
function theme_nodehierarchy_children_list($node, $children, $show_create_links = TRUE) {
  $output = "";
  if (!empty($children)) {
    $output .= '<ul class="nodehierarchy_outline menu">';
    $i = 1;
    foreach ($children as $nid => $item) {
      $children_list = "";
      $attributs = array();

      $title = check_plain($item['node']->title);
      if ($item['url']) {
        $title = '<a href="'. $item['url'] .'" class="'.
                    ($item['expandable'] ? "expand_widget" : "non_expandable") .
                    ($item['expanded'] ? " expanded" : " collapsed") .'" title="'. $item['tooltip'] .'">'. $title .'</a>';
      }

      $attributes['id'] = "nodehierarchy_child-". $item['node']->nid;
      $attributes['class'] = "nodehierarchy_child";
      if ($item['expandable']) {
        $attributes['class'] .= " expandable";
        $attributes['class'] .= $item['expanded'] ? " expanded" : " collapsed";
      }
      if (!nodehierarchy_previous_sibling_nid($item['node'])) {
        $attributes['class'] .= " first";
      }
      if (!nodehierarchy_next_sibling_nid($item['node'])) {
        $attributes['class'] .= " last";
      }
      $actions = theme("nodehierarchy_actions", $item['node']);
      $grandchildren = "";
      if ($item['expanded']) {
        $grandchildren = theme("nodehierarchy_children_list", $item['node'], $item['children']);
      }
      $output .= '<li'. drupal_attributes($attributes) .'><div class="item">'. $actions . $title .'</div><div class="children">'. $grandchildren .'</div></li>';
      $i++;
    }
    $output .= "</ul>";
  }
  else {
    $output .= t("This node has no children");
  }
  if ($show_create_links) {
    $output .= theme("nodehierarchy_new_child_links", $node);
  }
  return $output;
}

/**
 * Return a themed list of items.
 */
function theme_nodehierarchy_children_list_more_link($node, $num_displayed, $total) {
  $output = "";
  if ($num_displayed < $total) {
    $output .= '<div class="nodehierarchy_children_more_link">';
    $output .= t("%num out of %total displayed. ", array("%num" => $num_displayed, "%total" => $total));
    $output .= l(t("See more..."),  "node/". $node->nid ."/children", array(), 'page=1');
    $output .= '</div>';
  }
  return $output;
}