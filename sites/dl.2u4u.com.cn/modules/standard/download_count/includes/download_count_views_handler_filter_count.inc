<?php
// $Id: download_count_views_handler_filter_count.inc,v 1.1.2.1 2010/12/20 18:41:47 worldfallz Exp $

/**
 * @file
 * Download count per file views handler.
 */

/**
 * Download count per file views field handler.
 */
class download_count_views_handler_filter_count extends views_handler_filter_numeric {
  function query() {
    $this->table_alias = $this->ensure_my_table();
    if (empty($this->relationship)) {
      $sql = "SELECT COUNT(dc.fid) FROM {download_count} dc WHERE dc.fid = ". $this->table_alias . ".fid";
    }
    else {
      $sql = "SELECT COUNT(dc.fid) FROM {download_count} dc WHERE dc.fid = ". $this->relationship . ".fid";
    }
    $this->query->add_where($this->options['group'], "(". $sql .") " . $this->operator . " '%d'", $this->value['value']);
  }
}
