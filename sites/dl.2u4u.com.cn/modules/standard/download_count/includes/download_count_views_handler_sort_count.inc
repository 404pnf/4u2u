<?php
// $Id: download_count_views_handler_sort_count.inc,v 1.1.2.1 2010/12/20 18:41:47 worldfallz Exp $

/**
 * @file
 * Download count per file views handler.
 */

/**
 * Download count per file views sort handler.
 */
class download_count_views_handler_sort_count extends views_handler_sort {
  function query() {
    $this->table_alias = $this->ensure_my_table();
    $sql = "SELECT COUNT(dc.fid) FROM {download_count} dc WHERE dc.fid = ". $this->table_alias . ".fid";
    $this->field_alias = $this->query->add_orderby(NULL, "(". $sql .")", $this->options['order'], $this->table_alias .'_'. $this->field);
  }
}
