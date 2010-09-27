<?php
// $Id$

function recommender_points_setting_form(){
	$form['recommender_points_bili'] = array(
		'#title' => t('积分比例'),
		'#type' => 'textfield',
		'#default_value' => variable_get('recommender_points_bili',0.4),
		'#description' => t('推荐人获得的积分与用户充值积分之间的比例,比例应该是大于0的数字'),
	);
	return system_settings_form($form);
}

function recommender_points_setting_form_validate($form,&$form_state){
	$bili = $form_state['values']['recommender_points_bili'];
	if(!is_numeric($bili) || $bili <= 0){
		form_set_error('recommender_points_bili',t('积分比例应该是大于0的数字'));
	}
}