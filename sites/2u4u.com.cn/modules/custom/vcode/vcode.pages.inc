<?php
// $Id: uc_alipay.pages.inc,v 1.1 2009/01/05 23:27:34 yangyicn Exp $


function vcode_generate_page() {
	$output = "";
	$output .= drupal_get_form('vcode_generate_form');
	return $output;
}

function vcode_generate_form(){
  $total_options =array(
	  '' => '请选择记录数',
	  100 => 100,
		200 => 200,
		300 => 300,
		400 => 400,
		500 => 500,
		600 => 600,
		700 => 700,
		800 => 800,
		900 => 900,
		1000 => 1000,
	);
  $form['total'] = array(
	  '#type' =>'select',
		'#title' => t('记录数'),
		'#description' =>t('一次生成的验证码记录数。'),
		//'#default_value' => 500,
		'#options' => $total_options,
	);
	$point_options = array(
	  '' => '请选择积分额度',
	  10 => 10,
		20 => 20,
		30 => 30,
		40 => 40,
		50 => 50,
		60 => 60,
		70 => 70,
		80 => 80,
		90 => 90,
		100 => 100,
	);
	$form['point'] = array(
		'#title' => t('积分'),
		'#type' =>'select',
		'#description' =>t('验证码的积分。'),
		//'#default_value' => 50,
		'#options' => $point_options,
	);
	$form['submit'] = array(
		'#type' =>'submit',
		'#value' => t('提交'),
	);
	return $form;
}
function vcode_generate_form_validate($form,&$form_state){

  $total = $form_state['values']['total'];
	if(!preg_match("/^[0-9]*[1-9][0-9]*$/",$total)){
	  form_set_error('total',t('必须是整数').preg_match("^[0-9]*[1-9][0-9]*$",$total));
	}
	
	$point = $form_state['values']['point'];
	if(!preg_match("/^[0-9]*[1-9][0-9]*$/",$point)){
	  form_set_error('point',t('必须是整数').$point);
	}
	
}

function vcode_generate_form_submit($form,&$form_state){
  $total = $form_state['values']['total'];
	$point = $form_state['values']['point'];
	
	$i=0; 
	while($i<$total){
	  $vcode = '2u4u'.vcode_generate_vcode(8);
		$sql = "SELECT COUNT(id) FROM {vcode} WHERE code = '%s' ";
		$count = db_result(db_query($sql,$vcode));
		if($count <=0){
		  $sql = "INSERT INTO {vcode} (code, point, status, uid, created, updated) VALUES('%s', %d, %d, %d, %d, %d)";
			$current_time = time();
			//status的值可以为0,1,2；0表示刚刚创建的；1表示已经发送给用户的；2表示用户已经重值过了。
			$status = 0; 
			$uid = 0;
			db_query($sql, $vcode, $point, $status, $uid, $current_time, $current_time);
		  $i++;
		}
	  
	
	}
	drupal_set_message(t('已生成').$total.t('个').$point.t('积分的验证码'));
	
}

function vcode_generate_vcode( $length = 8 ) {
  // 密码字符集，可任意添加你需要的字符
  $chars = 'abcdefghijkmnopqrstuvwxyz0123456789';

  $vcode = '';
  for ( $i = 0; $i < $length; $i++ ) {
    // 这里提供两种字符获取方式
    // 第一种是使用 substr 截取$chars中的任意一位字符；
    // 第二种是取字符数组 $chars 的任意元素
    // $password .= substr($chars, mt_rand(0, strlen($chars) - 1), 1);
    $vcode .= $chars[ mt_rand(0, strlen($chars) - 1) ];
  }
  return $vcode;
}

/********************新建验证码列表页面的代码 **************************************************************************/

function vcode_admin_page(){
	$output = "";
  $output = "";
	$output .="<div id ='filter-form'>";
	$output .= drupal_get_form('vcode_filter_form');
	$output .="</div>"; 
	$output .= drupal_get_form("vcode_admin_form");
	//$output .="123456";
	return $output;
}

function vcode_admin_form(){

  $options = array(
	  '1' => '改为已发放',
	//	'2' => '改为已使用',
	);

  $form['options']['operation'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => '1',
  );
  $form['options']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#submit' => array('vcode_admin_code_submit'),
  );

  $languages = language_list();
  $destination = drupal_get_destination();
  $codes = array();
	$result = pager_query(db_rewrite_sql('SELECT * FROM {vcode} WHERE status = 0'), 50, 0, NULL);
  $status_array = array(
	  0 => t('新建的'),
		1 => t('已公开'),
		2 => t('已使用'),
	);
  while ($code = db_fetch_object($result)) {
    $codes[$code->id] = '';
    $options = empty($code->language) ? array() : array('language' => $languages[$node->language]);
    $form['id'][$code->id] = array('#value' => $code->id);
    $form['code'][$code->id] =  array('#value' => $code->code);
    $form['point'][$code->id] = array('#value' => $code->point);
    $form['status'][$code->id] =  array('#value' => $status_array[$code->status]);
		$username = "";
		if($code->uid <=0){
		  // $temp_user = user_load($code->uid);
		  //$username = $temp_user->name;
			//$username = "123456";
			//$username = l($username,'user/'.$code->uid);
		}else{
		  $temp_user = user_load($code->uid);
		  $username = $temp_user->name;
			$username = l($username,'user/'.$code->uid);
		}
		$form['uid'][$code->id] =  array('#value' => $username);
		

    //$form['operations'][$code->id] = array('#value' => l(t('公开'), 'vcode/open/'. $code->id , array('query' => $destination)));
  }
  $form['codes'] = array('#type' => 'checkboxes', '#options' => $codes);
  $form['pager'] = array('#value' => theme('pager', NULL, 50, 0));
  $form['#theme'] = 'vcode_admin_codes';
  return $form;
}


/**
 * Theme node administration overview.
 *
 * @ingroup themeable
 */
 
function theme_vcode_admin_codes($form) {
  // If there are rows in this form, then $form['title'] contains a list of
  // the title form elements.
  $has_posts = isset($form['code']) && is_array($form['code']);
  $select_header = $has_posts ? theme('table_select_header_cell') : '';
  $header = array($select_header, t('ID'), t('验证码'), t('积分'), t('状态'), t('用户'));

  //$header[] = t('Operations');
  $output = '';

  $output .= drupal_render($form['options']);
  if ($has_posts) {
    foreach (element_children($form['code']) as $key) {
      $row = array();
      $row[] = drupal_render($form['codes'][$key]);
      $row[] = drupal_render($form['id'][$key]);
      $row[] = drupal_render($form['code'][$key]);
      $row[] = drupal_render($form['point'][$key]);
      $row[] = drupal_render($form['status'][$key]);
			$row[] = drupal_render($form['uid'][$key]);

      //$row[] = drupal_render($form['operations'][$key]);
      $rows[] = $row;
    }

  }
  else {
    $rows[] = array(array('data' => t('No posts available.'), 'colspan' => '7'));
  }

  $output .= theme('table', $header, $rows);
  if ($form['pager']['#value']) {
    $output .= drupal_render($form['pager']);
  }

  $output .= drupal_render($form);

  return $output;
}
function vcode_admin_code_submit($form, &$form_state){
	$operation = $form_state['values']['operation'];
  // Filter out unchecked nodes
  $codes = array_filter($form_state['values']['codes']);
	$codes_filter = '('. implode(', ', $codes) .')';
	$sql = "UPDATE {vcode} SET status = %d WHERE id IN ".$codes_filter;
	db_query($sql, $operation);
}
/*
function vcode_filter_form(){
  $point_options = array(
	  '' => '请选择积分额度',
	  10 => 10,
		20 => 20,
		30 => 30,
		40 => 40,
		50 => 50,
		60 => 60,
		70 => 70,
		80 => 80,
		90 => 90,
		100 => 100,
	);
	$form['point'] = array(
		'#title' => t('积分'),
		'#type' =>'select',
		'#description' =>t('验证码的积分。'),
		//'#default_value' => 50,
		'#options' => $point_options,
	);
	$form['submit'] = array(
		'#type' =>'submit',
		'#value' => t('提交'),
	);
  $form['submit'] = array(
		'#type' =>'submit',
		'#value' => t('过滤'),
	);
	return $form;
}
*/

/********************已公开验证码的代码 **************************************************************************/

function vcode_admin_open_page(){
	$output = "";

	$output .= drupal_get_form("vcode_admin_open_form");
	//$output .="123456";
	return $output;
}

function vcode_admin_open_form(){

  $codes = array();
	$result = pager_query(db_rewrite_sql('SELECT * FROM {vcode} WHERE status = 1'), 50, 0, NULL);
  $status_array = array(
	  0 => t('新建的'),
		1 => t('已公开'),
		2 => t('已使用'),
	);
  while ($code = db_fetch_object($result)) {
    //$codes[$code->id] = '';
    $options = empty($code->language) ? array() : array('language' => $languages[$node->language]);
    $form['id'][$code->id] = array('#value' => $code->id);
    $form['code'][$code->id] =  array('#value' => $code->code);
    $form['point'][$code->id] = array('#value' => $code->point);
    $form['status'][$code->id] =  array('#value' => $status_array[$code->status]);
		$username = "";
		if($code->uid <=0){
		  // $temp_user = user_load($code->uid);
		  //$username = $temp_user->name;
			//$username = "123456";
			//$username = l($username,'user/'.$code->uid);
		}else{
		  $temp_user = user_load($code->uid);
		  $username = $temp_user->name;
			$username = l($username,'user/'.$code->uid);
		}
		$form['uid'][$code->id] =  array('#value' => $username);
		

    //$form['operations'][$code->id] = array('#value' => l(t('公开'), 'vcode/open/'. $code->id , array('query' => $destination)));
  }
 // $form['codes'] = array('#type' => 'checkboxes', '#options' => $codes);
  $form['pager'] = array('#value' => theme('pager', NULL, 50, 0));
  $form['#theme'] = 'vcode_admin_codes';
  return $form;
}


/**
 * Theme node administration overview.
 *
 * @ingroup themeable
 */
 
function theme_vcode_admin_open_codes($form) {
  // If there are rows in this form, then $form['title'] contains a list of
  // the title form elements.
  //$has_posts = isset($form['code']) && is_array($form['code']);
  //$select_header = $has_posts ? theme('table_select_header_cell') : '';
  $header = array(t('ID'), t('验证码'), t('积分'), t('状态'), t('用户'));

  //$header[] = t('Operations');
  $output = '';

  $output .= drupal_render($form['options']);
  if ($has_posts) {
    foreach (element_children($form['code']) as $key) {
      $row = array();
      //$row[] = drupal_render($form['codes'][$key]);
      $row[] = drupal_render($form['id'][$key]);
      $row[] = drupal_render($form['code'][$key]);
      $row[] = drupal_render($form['point'][$key]);
      $row[] = drupal_render($form['status'][$key]);
			$row[] = drupal_render($form['uid'][$key]);

      //$row[] = drupal_render($form['operations'][$key]);
      $rows[] = $row;
    }

  }
  else {
    $rows[] = array(array('data' => t('No posts available.'), 'colspan' => '7'));
  }

  $output .= theme('table', $header, $rows);
  if ($form['pager']['#value']) {
    $output .= drupal_render($form['pager']);
  }

  $output .= drupal_render($form);

  return $output;
}


/********************已使用验证码的代码 **************************************************************************/
function vcode_admin_used_page(){
	$output = "";

	$output .= drupal_get_form("vcode_admin_used_form");
	//$output .="123456";
	return $output;
}

function vcode_admin_used_form(){

  $codes = array();
	$result = pager_query(db_rewrite_sql('SELECT * FROM {vcode} WHERE status = 2 ORDER BY id DESC'), 50, 0, NULL);
  $status_array = array(
	  0 => t('新建的'),
		1 => t('已公开'),
		2 => t('已使用'),
	);
  while ($code = db_fetch_object($result)) {
    //$codes[$code->id] = '';
    $options = empty($code->language) ? array() : array('language' => $languages[$node->language]);
    $form['id'][$code->id] = array('#value' => $code->id);
    $form['code'][$code->id] =  array('#value' => $code->code);
    $form['point'][$code->id] = array('#value' => $code->point);
    $form['status'][$code->id] =  array('#value' => $status_array[$code->status]);
		$username = "";
		if($code->uid <=0){
		  // $temp_user = user_load($code->uid);
		  //$username = $temp_user->name;
			//$username = "123456";
			//$username = l($username,'user/'.$code->uid);
		}else{
		  $temp_user = user_load($code->uid);
		  $username = $temp_user->name;
			$username = l($username,'user/'.$code->uid);
		}
		$form['uid'][$code->id] =  array('#value' => $username);
		

    //$form['operations'][$code->id] = array('#value' => l(t('公开'), 'vcode/open/'. $code->id , array('query' => $destination)));
  }
 // $form['codes'] = array('#type' => 'checkboxes', '#options' => $codes);
  $form['pager'] = array('#value' => theme('pager', NULL, 50, 0));
  $form['#theme'] = 'vcode_admin_codes';
  return $form;
}


/**
 * Theme node administration overview.
 *
 * @ingroup themeable
 */
 
function theme_vcode_admin_used_codes($form) {
  // If there are rows in this form, then $form['title'] contains a list of
  // the title form elements.
  //$has_posts = isset($form['code']) && is_array($form['code']);
  //$select_header = $has_posts ? theme('table_select_header_cell') : '';
  $header = array(t('ID'), t('验证码'), t('积分'), t('状态'), t('用户'));

  //$header[] = t('Operations');
  $output = '';

  $output .= drupal_render($form['options']);
  if ($has_posts) {
    foreach (element_children($form['code']) as $key) {
      $row = array();
      //$row[] = drupal_render($form['codes'][$key]);
      $row[] = drupal_render($form['id'][$key]);
      $row[] = drupal_render($form['code'][$key]);
      $row[] = drupal_render($form['point'][$key]);
      $row[] = drupal_render($form['status'][$key]);
			$row[] = drupal_render($form['uid'][$key]);

      //$row[] = drupal_render($form['operations'][$key]);
      $rows[] = $row;
    }

  }
  else {
    $rows[] = array(array('data' => t('No posts available.'), 'colspan' => '7'));
  }

  $output .= theme('table', $header, $rows);
  if ($form['pager']['#value']) {
    $output .= drupal_render($form['pager']);
  }

  $output .= drupal_render($form);

  return $output;
}

