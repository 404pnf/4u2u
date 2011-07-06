<?php
// $Id: sina_open.pages.inc,v 1.5 2011/02/11 03:52:44 eastcn Exp $

/**
 * 获取授权令牌并在 Drupal 可登录
 */
function sina_open_page_t_login() {
  global $user;
  
  if ($user->uid) {
    if ($tok = sina_open_get_access_token($user->uid)){
      
      if ($result = sina_open_t_set_request('http://api.t.sina.com.cn/account/verify_credentials.json')) {
        if ($result->code == 200) {
          drupal_set_message('授权成功');
          drupal_goto('user/'.$user->uid);
        }
      }
      
    }
  }
  
  if ($_GET['op'] == 'validate') {
    if ($tok = sina_open_t_access_token()) {
      
      _sina_open_t_login($tok);
      
    } else {
      
      drupal_set_message('授权未通过验证', 'error');
      drupal_goto('user/login');
      
    }
    
    exit;
  }
  
  if ($to_url = sina_open_t_login_url()) {
    drupal_goto($to_url);
  } else {
    drupal_set_message('新浪服务器未响应，无法验证', 'error');
    drupal_goto('user/login');
  }
}

/**
 * 让用户登录，若用户不存在，则创建新用户并登录.
 * 若用户已登录，则将新浪微博帐号绑定
 * 必须先获取访问令牌
 * @param (object) $tok
 *  访问令牌
 */
function _sina_open_t_login($tok = NULL) {
  global $user;
  
  $values = array();
  if (isset($tok)) {
    $values['oauth_access_token_key'] = $tok->key;
    $values['oauth_access_token_secret'] = $tok->secret;
    if ($tok->verifier) {
      $values['oauth_verifier'] = $tok->verifier;
    }
  }
  
  if ($result = sina_open_t_set_request('http://api.t.sina.com.cn/account/verify_credentials.json', $values)) {
    if ($result->code == 200) {
      if ($json = json_decode($result->data)) {
        
        $authname = $json->name;
        $sina_uid = $json->id;
        
        $result = db_query("SELECT uid FROM {sina_open_user} WHERE sina_name = '%s'", $authname);
        
        if ($ac = db_fetch_array($result)) {
          $account = user_load($ac);
        }
        
        if (isset($account->uid)) {
          // 该微博帐号已经存在
          if ($user->uid) {
            
            if ($user->uid != $account->uid) {
              drupal_set_message('该帐号已与其它用户绑定', 'error');
              drupal_goto('user/'.$user->uid);
            }
            
          } else {
            user_external_login($account, 'sina_open');
          }
          
          if (isset($tok)) {
            db_query("UPDATE {sina_open_user} SET sina_uid = '%s', token = '%s' WHERE uid = %d",
            $sina_uid, serialize($tok), $account->uid);
          }
          
        } else if ($user->uid > 0) {
          // 绑定到当前用户
          if (db_result(db_query('SELECT uid FROM {sina_open_user} WHERE uid = %d', $user->uid))) {
            drupal_set_message('您已经绑定了一个新浪微博帐号', 'error');
            drupal_goto('user/'.$user->uid);
          } else {
            $account = $user;
            db_query("INSERT INTO {sina_open_user} (uid, sina_uid, sina_name, token, config) VALUES ('%s', '%s', '%s', '%s', '')",
            $user->uid, $sina_uid, $authname, serialize($tok));
            /**
             * drupal 不支持远程图片做为头像
            if (db_affected_rows() && !$user->picture) {
              db_query("UPDATE {users} SET picture = '%s' WHERE uid = %d", $json->profile_image_url, $user->uid);
            }
            */
          }
          
        } else {
          // 新注册一个用户
          
          // 检查用户名是否存在，若存在，则选择一个新的用户名。
          $new_name = $authname;
          $i = 1;
          while ($uid = db_result(db_query("SELECT uid FROM {users} WHERE name = '%s'", $new_name))) {
            $new_name = $authname.'_'.$i;
            ++$i;
          }
          
          $pass = user_password();
          $ac = array(
            'name' => $new_name,
            'mail' => $new_name.'@t.sina.com.cn', // 默认使用新浪微博的域名做为邮件
            'pass' => $pass,
            //'picture' => $json->profile_image_url,
            'status' => variable_get('user_register', 1) == 1,
            'auth_sina_open' => $new_name
          );
          
          if (!$account = user_save('', $ac)) {
            drupal_set_message('无法注册帐号', 'error');
            drupal_goto('user/register');
          }
          
          db_query("INSERT INTO {sina_open_user} (uid, sina_uid, sina_name, token, config) VALUES ('%s', '%s', '%s', '%s', '')",
          $account->uid, $sina_uid, $authname, serialize($tok));
          drupal_set_message('已为你成功创建帐号，随机密码：'.$pass.'，如果你需要从本站直接登录，请记住此密码或'.l('立即修改', 'user/'.$account->uid.'/edit'));
          user_external_login($account);
        }
        
        if (isset($_REQUEST['redirect']) && $_REQUEST['redirect']) {
          drupal_goto($_REQUEST['redirect']);
        } else {
          drupal_goto('user/'.$account->uid.'/sina_open/config');
        }
      }
    }
  }
  
  drupal_set_message('无法登录，请重试', 'error');
  drupal_goto('user/login');
}

/**
 * 微博相关设置
 * @param (object) $ac
 */
function sina_open_page_config($ac) {
  $output = '';

  $data = db_fetch_object(db_query('SELECT uid, token, sina_name FROM {sina_open_user} WHERE uid = %d', $ac->uid));
  
  if ($data->uid) {
    $items[] = '您绑定的帐号：'. $data->sina_name
    . l('解除绑定', 'user/'.$ac->uid.'/sina_open/remove', array('attributes' => array('class' => 'sina_open_user_remove')));
    
    if ($GLOBALS['user']->uid == $ac->uid) {
      $items[] = drupal_get_form('sina_open_set_tweet_form', $ac->uid);
    }
  } else {
    $items[] = '您还没有绑定帐号，' . l('立即绑定', 'sina_open/t_login');
  }
  
  $output = theme('item_list', $items, '新浪微博', 'ul', array('id' => 'sina_open_page_config'));
  
  return $output;
  
  if ($data = sina_open_t_get_info($ac)) {
    
    if ($data->screen_name) {
      $items[] = '您绑定的帐号：'. $data->screen_name;
      $output = theme('item_list', $items);
    }
    
  } else {
    
  }
  
  return $output;
}

/**
 * 解除新浪微博帐号绑定
 * @param (array) $form_state
 * @param (object) $ac
 */
function sina_open_remove_confirm($form_state, $ac) {
  if ($data = db_fetch_object(db_query('SELECT uid, token, sina_name FROM {sina_open_user} WHERE uid = %d', $ac->uid))) {
    $form = array();
    $form['uid'] = array('#type' => 'hidden', '#value' => $ac->uid);
    $output = confirm_form($form,
                    '解除微博帐号绑定',
                    'user/'.$ac->uid.'/sina_open/config',
                    '当前绑定的帐号为：'.$data->sina_name . '，确定要解除绑定吗？此操作不可恢复，但不会影响已经发布到微博的数据。',
                    '解除绑定',
                    '取消');
    return $output;
  } else {
    drupal_access_denied();
    exit;
  }
}

function sina_open_remove_confirm_submit($form, &$form_state) {
  db_query('DELETE FROM {sina_open_user} WHERE uid = %d', $form_state['values']['uid']);
  db_query("DELETE FROM {authmap} WHERE uid = %d AND module = '%s'", $form_state['values']['uid'], 'sina_open');
  drupal_set_message('成功解除绑定');
  $form_state['redirect'] = 'user/'.$form_state['values']['uid'].'/sina_open/config';
  return;
}