<?php

/**
*读后感评分模块管理员设置页面，主要设置谁可以进行评分
*/
/*
function duhougan_pingfen_admin_settings() {
  
	$duhougan_pingfen_selectable_roles = user_roles(TRUE);
  // remove authenticated user
  unset($duhougan_pingfen_selectable_roles[DRUPAL_AUTHENTICATED_RID]);
	ksort($duhougan_pingfen_selectable_roles);
	$default_electable_roles =array(
	
	);
	$default_electable_roles =variable_get('duhougan_pingfen_selectable_roles', array());
	
	$form['duhougan_pingfen_selectable_roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('选择积分相关角色'), 
    //'#default_value' => variable_get('up_roles_selectable_roles', array()),
		'#default_value' => $default_electable_roles,
    '#options' => $duhougan_pingfen_selectable_roles,
    '#description' => t('请选择哪个角色可以对读后感评分'),
  );

  return system_settings_form($form);
}
function up_roles_select_form_validate($form, &$form_state){
	$form_state['values']['duhougan_pingfen_selectable_roles'] = array_filter($form_state['values']['duhougan_pingfen_selectable_roles']);
}
*/