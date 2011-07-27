<?php
// $Id: sina_open.admin.inc,v 1.3 2010/09/16 08:40:43 eastcn Exp $

/**
 * 管理设置
 */
function sina_open_admin_settings(){
  $form['sina_open_is_login'] = array(
    '#type' => 'radios',
    '#title' => '允许使用微博帐号登录',
    '#default_value' => variable_get('sina_open_is_login', 1),
    '#options' => array('不允许', '允许'),
    '#description' => '将自动创建一个新用户'
  );
  $form['sina_open_oauth_consumer_key'] = array(
    '#type' => 'textfield',
    '#title' => '新浪微博 API',
    '#default_value' => variable_get('sina_open_oauth_consumer_key', NULL),
    '#description' => '你可以到 http://open.t.sina.com.cn/wiki/index.php 申请，若没有，请留空。'
  );
  $form['sina_open_oauth_consumer_secret'] = array(
    '#type' => 'textfield',
    '#title' => 'API 密钥',
    '#default_value' => variable_get('sina_open_oauth_consumer_secret', NULL),
    '#description' => '除非你自行设置了 API，否则请留空'
  );
  $form['sina_open_comment'] = array(
    '#type' => 'radios',
    '#title' => '在评论中启用',
    '#default_value' => variable_get('sina_open_comment', 1),
    '#options' => array('否', '是')
  );
  
  $types = node_get_types();
  
  foreach ($types as $type){
    $form['sina_open_node_'.$type->type] = array(
      '#title' => '在 '.$type->name.' 中启用',
      '#type' => 'checkbox',
      '#default_value' => variable_get('sina_open_node_'.$type->type, 1),
    );
  }
  
  return system_settings_form($form);
}

/**
 * 绑定了新浪微博帐号或通过新浪微博帐号注册的用户
 */
function sina_open_admin_users() {
  $result = pager_query('SELECT u.uid, u.name FROM {sina_open_user} s INNER JOIN {users} u ON s.uid = u.uid ORDER BY u.uid DESC', 50);
  $table = NULL;
  while ($o = db_fetch_object($result)) {
    $destination = array('query' => drupal_get_destination());
    $table[] = array(
      theme('username', $o),
      l('解除绑定', 'user/'.$o->uid.'/sina_open/remove', $destination),
      l('删除用户', 'user/'.$o->uid.'/delete', $destination)
    );
  }
  
  if ($table) {
    $output =  theme('table', array(), $table);
    $output .= theme('pager');
  } else {
    $output = '没有数据';
  }
  
  return $output;
}