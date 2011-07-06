<?php
// $Id: views_handler_argument_nodehierarchy_ancestor.inc,v 1.1.2.1 2008/09/29 02:19:05 ronan Exp $

/**
 * Argument handler to accept a node type.
 *
 * @ingroup views_argument_handlers
 */
class views_handler_argument_nodehierarchy_ancestor extends views_handler_argument {

  /**
   * Build the query based upon the formula
   */
  function query() {
    $this->ensure_my_table();
    $descendants = _nodehierarchy_views_get_descendant_parents($this->argument);
    $descendant_list = implode(",", $descendants);
    $this->query->add_where(0, "nodehierarchy.parent IN ( $descendant_list )");
  }
}

/**
 * Return the list of descendants of the given node which can also themselves be parents.
 */
function _nodehierarchy_views_get_descendant_parents($nid) {
  static $parent_types = NULL;
  if (!$parent_types) {
    $types = _nodehierarchy_get_parent_types("", TRUE);
    $parent_types = implode(",", $types);
  }

  $out = array($nid);
  $result = db_query("SELECT n.nid FROM {node} n LEFT JOIN {nodehierarchy} h ON h.nid = n.nid WHERE h.parent = %d and n.type IN (". $parent_types .")", $nid);
  while ($child = db_fetch_object($result)) {
    $out = array_merge($out, _nodehierarchy_views_get_descendant_parents($child->nid));
  }

  return $out;
}