<?php


function duhougan_pingfen_views_data()  {


  $data = array();
  $data['duhougan_pingfen']['table']['group']  = t('Du Hougan Ping Fen');

  // We also show up for node revisions.
  $data['duhougan_pingfen']['table']['join'] = array(
    'node' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
  );

  // score
  $data['duhougan_pingfen']['score'] = array(
    'title' => t('Score'),
    'help' => t('The score of Duhougan'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  return $data;
}