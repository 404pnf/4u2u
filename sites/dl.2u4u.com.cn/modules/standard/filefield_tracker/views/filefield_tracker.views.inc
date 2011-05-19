<?php

function filefield_tracker_views_data(){
  $tables['filefield_tracker'] = array(
    'table' => array(
      'group' => t('Filefield Tracker'),
      'base' => array(
        'field' => 'id',
        'title' => t('Filefield Tracker'),
        'help' => t("Filefield download tracker entries."),
      ),
      'join' => array(
        'files' => array(
          'left_field' => 'fid',
          'field' => 'fid',
         ),
        'node' => array(
          'left_field' => 'nid',
          'field' => 'nid',
         ),
        'users' => array(
          'left_field' => 'uid',
          'field' => 'uid',
        ),
      ),
    ),
    'fid' => array(
      'title' => t('Downloaded file'),
      'help' => t('The downloaded file'),
      'relationship' => array(
       'base' => 'files',
       'field' => 'fid',
       'handler' => 'views_handler_relationship',
       'label' => t('Downloaded file'),
     ),
    ),
    'nid' => array(
      'title' => t('Downloaded from node'),
      'help' => t('The node where the file was downloaded from'),
      'relationship' => array(
       'base' => 'node',
       'field' => 'nid',
       'handler' => 'views_handler_relationship',
       'label' => t('Downloaded from node'),
     ),
    ),
    'uid' => array(
      'title' => t('Downloaded by user'),
      'help' => t('The user downloading the file'),
      'relationship' => array(
       'base' => 'users',
       'field' => 'uid',
       'handler' => 'views_handler_relationship',
       'label' => t('Downloaded by user'),
     ),
    ),
    'download_time' => array(
      'field' => array(
        'title' => t('Download time'),
        'help' => t('The file download time'),
        'handler' => 'views_handler_field_date',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'title' => t('Download time'),
        'help' => t('The file download time'),
        'handler' => 'views_handler_sort_date',
      ),
    ),
  );
  return $tables;
}

/*function filefield_tracker_views_handlers(){
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'filefield_tracker') . '/views',
    ),
    'handlers' => array(
    ),
  );
}*/