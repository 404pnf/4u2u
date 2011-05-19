<?php
// $Id: filefield_tracker.pages.inc,v 1.2 2010/06/26 16:44:23 xeniox Exp $

/**
 * Page callback to show global filefield download tracker overview table
 */
function filefield_tracker_report_page() {
  if (module_exists('views')) {
    $reportview = variable_get('filefield_tracker_report_view', 'filefield_tracker_report');
    return views_embed_view($reportview, 'default', $node->nid);
  }
  else {
    $entries = filefield_tracker_get_logs();
    $header[] = array('data' => t('Filename'));
    $header[] = array('data' => t('Node'));
    $header[] = array('data' => t('Downloaded by'));
    $header[] = array('data' => t('Download time'));

    if ($entries) {
      foreach ($entries as $entry) {
        $file = field_file_load($entry->fid);
        $node = node_load(array('nid' => $entry->nid));
        $account = user_load($entry->uid);
        $rows[] = array(
          $file['filename'],
          l($node->title, 'node/' . $node->nid),
          theme('username', $account),
          format_date($entry->download_time)
        );
      }
    }
    else {
        $rows[][] = array(
          'data' => t('No files have been downloaded.'),
          'colspan' => 4,
        );
    }
    return theme('table', $header, $rows);
  }

}

/**
 * Page callback to show filefield download tracker node overview table
 */
function filefield_tracker_tab_page($node) {
  if (module_exists('views')) {
    $nodeview = variable_get('filefield_tracker_node_view', 'filefield_tracker_node');
    return views_embed_view($nodeview, 'default', $node->nid);
  }
  else {
    $entries = filefield_tracker_get_logs($node->nid);
    $header[] = array('data' => t('Filename'));
    $header[] = array('data' => t('Downloaded by'));
    $header[] = array('data' => t('Download time'));

    if ($entries) {
      foreach ($entries as $entry) {
        $file = field_file_load($entry->fid);
        $account = user_load($entry->uid);
        $rows[] = array(
          $file['filename'],
          theme('username', $account),
          format_date($entry->download_time)
        );
      }
    }
    else {
        $rows[][] = array(
          'data' => t('No files have been downloaded.'),
          'colspan' => 4,
        );
    }

    return theme('table', $header, $rows);
  }
}