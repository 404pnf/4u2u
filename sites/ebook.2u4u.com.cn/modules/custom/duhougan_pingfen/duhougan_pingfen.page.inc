<?php

/**
*读后感评分模块管理员设置页面，主要设置谁可以进行评分
*/

function duhougan_pingfen_admin_settings() {
  $form = "";
	
	$all_roles = user_roles();

	foreach($all_roles as $key=>$value){
		$roles_options[$value] = $value;
	}

    $form["who_can_pingfen"] = array(
    '#type' => 'select',
    '#title' => t('请选择哪个角色可以对读后感评分'),
    '#options' => $roles_options,
    '#default_value' => variable_get(who_can_pingfen, "读后感比赛评审教研员"),
  );

  return system_settings_form($form);
}