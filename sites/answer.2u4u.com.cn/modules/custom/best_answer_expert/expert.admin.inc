<?php 

function expert_config_page(){
	$output ="";
	$output .=drupal_get_form('expert_admin_config_form');
	return $output;
}

function expert_admin_config_form(){
	$form['expert_minimum_points'] = array(
		'#title' => t('专家提问所需最小积分数'),
		'#type' => 'textfield',
		'#default_value' => variable_get('expert_minimum_points',10),
		'#description' => t('专家提问所需最小积分数应该是大于0的整数'),
	);
	$form['expert_minimum_days'] = array(
		'#title' => t('用户提问有效天数'),
		'#type' => 'textfield',
		'#default_value' => variable_get('expert_minimum_days',30),
		'#description' => t('用户提问的有效天数，过了这个有效天数，问题会自动关闭'),
	);
	return system_settings_form($form);
}

function expert_admin_config_form_validate($form,&$form_state){
	$expert_minimum_points = $form_state['values']['expert_minimum_points'];
	if(!is_numeric($expert_minimum_points) || $expert_minimum_points <= 0){
		form_set_error('expert_minimum_points',t('专家提问所需最小积分数应该是大于0的整数'));
	}
	
	$expert_minimum_days = $form_state['values']['expert_minimum_days'];
	if(!is_numeric($expert_minimum_days) || $expert_minimum_days <= 0){
		form_set_error('expert_minimum_days',t('用户提问的有效天数应该是大于0的整数'));
	}
}