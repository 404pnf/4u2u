<?php
// $Id$

/**
 * Discuz金钱转Drupal积分菜单回调函数 
 */
function dz2drupalpoints_callback_page(){
	global $user;
	
	//从discuz中查询当前用户可以交易转换的金钱，这里假定金钱（extcredits2）是可以转换的
	$discuz_sql = "SELECT extcredits2 FROM uu_members WHERE username = '%s'";
	$discuz_sql_exist = "SELECT count(*) FROM uu_members WHERE username = '%s'";
	
	//切换到discuz数据库
	db_set_active('discuz');
	//判断当前用户在discuz系统中是否存在
	$discuz_total_records = db_result(db_query($discuz_sql_exist, $user->name));
	//如果当前用户存在于discuz系统中，那么读取该用户的可用的金钱数
	if($discuz_total_records>0){
		$discuz_total_points = db_result(db_query($discuz_sql, $user->name));
	}
	//切换到default数据库
	db_set_active('default');
	
	$output ="";
	
	//drupal_set_title('外语圈金钱换悠游积分');
	
	//当前用户在discuz中存在
	if($discuz_total_records>0){
	/*
		$output .="<div style='text-align:center;'><p>";
		$output .=t("当前Discuz可用金钱：").$discuz_total_points;
		$output .="</p><p>";
		$output .=t("当前用户积分："). userpoints_get_current_points();
		$output .="</p><p>";
		$output .=t("当前换算比率（Discuz金钱/用户积分）："). variable_get('dz2drupalpoints_bilv', '10');
		$output .="</p>";
		$output .=drupal_get_form('dz2drupalpoints_callback_form');
		$output .="</div>";
		*/
		$variables =array();
		$variables['discuz_points'] = $discuz_total_points;
		$variables['current_points'] = userpoints_get_current_points();
		$variables['bilv'] = variable_get('dz2drupalpoints_bilv', '10');
		$variables['form_content'] = drupal_get_form('dz2drupalpoints_callback_form');
		
		$output = theme('dz2drupalpoints_page_content', $variables);
	}else{
	//当前用户在discuz中不存在
	/*
		$output .="<div style='text-align:center;'><p>";
		$output .=t("当前用户帐号还没有同步到Discuz系统中去。");
		$output .="</p><p>";
		$output .=t("请首先将2u4u主站的帐号同步到Discuz论坛子站上。");
		$output .="</p>";
		$output .="</div>";
		*/
		$output = theme('dz2drupalpoints_page_empty',array());
	}
	
	return $output;
}

function theme_dz2drupalpoints_page_content($variables){
	$output ="";
	$output .="<div style='text-align:center;'><p>";
	$output .=t("您当前的外语圈金钱：").$variables['discuz_points'];
	$output .="</p><p>";
	$output .=t("您当前的悠游积分："). $variables['current_points'];
	$output .="</p><p>";
	$output .=t("换算比率："). $variables['bilv'].'/1(外语圈金钱/悠游积分)';
	$output .="</p>";
	$output .= $variables['form_content'];
	$output .="</div>";
	return $output;
}

function theme_dz2drupalpoints_page_empty($variables){
	$output ="";
	$output .="<div style='text-align:center;'><p>";
	$output .=t("当前悠游用户帐号还没有同步到外语圈系统中去。");
	$output .="</p><p>";
	$output .=t("请首先将悠游主站的帐号同步到外语圈论坛上。");
	$output .="</p>";
	$output .="</div>";
	return $output;
}

/**
 * Discuz金钱转Drupal积分表单 
 */
function dz2drupalpoints_callback_form(){
	$form['dzpoints'] = array(
		'#type'          => 'textfield',
		'#title'         => t("请输入要转换的外语圈论坛金钱数"),
		'#description'   => t("金钱数量应该是比率的整数倍，如果不是系统则按照最接近的整数倍处理"),
		'#size'          => 5,
  );
	//这个是占位符字段，在表单验证中用来存储用户的实际Discuz金钱数
	$form['exist_points'] = array(
		'#type'          => 'value',
		'#value'          => 0,
  );
	$form['submit'] = array(
		'#type'          => 'submit',	
		'#value' => t('转换'),
	
  );
	return $form;
}

/**
 * 表单验证理函数 
 */
function dz2drupalpoints_callback_form_validate($form, &$form_state){
	//Discuz金钱数 正整数验证规则
	if(is_numeric($form_state['values']['dzpoints']) && strpos($form_state['values']['dzpoints'],".") == false && $form_state['values']['dzpoints'] >0){	
	}else{
		form_set_error('dzpoints',t('输入的外语圈论坛金钱数必须是大于0的整数'));
	}
	
	global $user;
	//从discuz中查询当前用户可以交易转换的金钱，
	$discuz_sql = "SELECT extcredits2 FROM uu_members WHERE username = '%s'";
	//切换到discuz数据库
	db_set_active('discuz');
	$discuz_total_points = db_result(db_query($discuz_sql, $user->name));
	// 切换到default数据库.
	db_set_active('default');
	
	//为占位符字段赋值，这样在表单的提交处理函数中就不需要重新读取该数值
	form_set_value($form['exist_points'],$discuz_total_points,$form_state);
	
	//Discuz金钱数 不能超过实际金钱数验证规则
	if($form_state['values']['dzpoints'] > $discuz_total_points){
		form_set_error('dzpoints',t('输入的外语圈论坛金钱数不能超过用户拥有的金钱总数'));
	}
}

/**
 * 表单提交处理函数，用于从discuz中扣除金钱数，为用户添加积分 
 */
function dz2drupalpoints_callback_form_submit($form, &$form_state){
	global $user;
	
	//从表单中获取要转换的DISCUZ金钱数
	$dzpoints = $form_state['values']['dzpoints'];
	//读取预先设置的转换比率
	$bilv = variable_get('dz2drupalpoints_bilv',10);
	//可以转换多少个积分
	$userpoints = floor($dzpoints/$bilv);
	//实际用去的DISCUZ金钱数
	$real_dzpoints = $userpoints * $bilv;
	
	//当没有转换任何积分或者转换的积分为负，直接返回
	if($userpoints<=0){
		drupal_set_message('要转换的外语圈论坛金钱数不足');
		return;
	}
	
	//扣除后的Discuz金钱数
	$new_dzpoints = $form_state['values']['exist_points'] - $real_dzpoints;
	//用户更新的SQL语句
	$discuz_sql = "UPDATE uu_members SET extcredits2 = %d WHERE username = '%s'";
	//切换到discuz数据库
	db_set_active('discuz');
	//在discuz系统中，更新金钱数，以减去要转换的金钱
	$success = db_query($discuz_sql,$new_dzpoints, $user->name);
	// 切换到default数据库
	db_set_active('default');
	
	//Discuz更新成功，此时为用户添加相应的积分
	if($success){	
		$params = array (
			'uid' => arg(1),
			'points' => $userpoints,
			'description' => t('通过转换外语圈论坛金钱获取的积分'),
		);
		userpoints_userpointsapi($params);
		drupal_set_message(t('转换成功:扣除外语圈论坛金钱%real_dzpoints ;添加悠游积分%userpoints',array('%real_dzpoints'=>$real_dzpoints,'%userpoints'=>$userpoints)));	
	}
	//Discuz更新未成功，此时为用户返回相应的错误提示。
	else{
		drupal_set_message('由于未知原因，转换未成功，请重试');
		return;
	}
	
}