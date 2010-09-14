<?php
// $Id: nodehierarchy_pathauto.inc,v 1.3.2.1 2008/05/14 22:22:00 ronan Exp $

/**
 * @file
 * pathauto.module v1 integration functions for nodehierarchy.module
 * pathauto v2 uses token for generation makingt his file obsolete
 */


/**
 * Implementation of hook_pathauto_node().
 */
function nodehierarchy_pathauto_node($op, $node = NULL) {
  switch ($op) {
    case 'placeholders':
      $placeholders = array();
      $placeholders[t('[hierarchypath]')] =
        t('The hierarchy path of an item.');
      $placeholders[t('[fullhierarchypath]')] =
        t('The hierarchy path of an item including the title.');
      return $placeholders;
    case 'values':
      $results = nodehierarchy_pathauto_get_placeholders($node);
      return $results;
    default:
      break;
  }
}

/**
 * Generate the hierarchy placeholders.
 *
 * @param $node
 *   The node object generate placeholders for.
 *
 * @return
 *   An array with relevant placeholders.
 */
function nodehierarchy_pathauto_get_placeholders($node) {
  $placeholders = array();
  $placeholders[t('[hierarchypath]')]     = nodehierarchy_pathauto_get_hierarchypath($node->nid);
  $placeholders[t('[fullhierarchypath]')]   = nodehierarchy_pathauto_get_fullhierarchypath($node->nid);
  return $placeholders;
}

function nodehierarchy_pathauto_get_fullhierarchypath($node) {
  $node = node_load($node);
  // return the hierarchy path with the converted title
  return trim(nodehierarchy_pathauto_get_hierarchypath($node->nid) ."/". pathauto_cleanstring($node->title), "/");
}

function nodehierarchy_pathauto_get_hierarchypath($node) {
  if ($node) {
    $node = node_load($node);
    // the hierarchy path is the parent node's full hierarchy path
    if ($node->parent) {
      // if the parent already has an alias (generated or entered) use that
      $parent_path = drupal_get_path_alias("node/$node->parent");
      if ($parent_path != "node/$node->parent") {
        return $parent_path;
      }
      elseif ($node->parent) {
        // recurse
        return nodehierarchy_pathauto_get_fullhierarchypath($node->parent);
      }
    }
  }
  return "";
}