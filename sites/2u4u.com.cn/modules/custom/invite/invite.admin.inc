<?php
// $Id$

function invite_admin_config_page(){
	$output ="";
	$output .=drupal_get_form('invite_admin_config_form');
	return $output;
}

function invite_admin_config_form(){
	$form['invite_award_points_per_user'] = array(
		'#title' => t('奖励积分数'),
		'#type' => 'textfield',
		'#default_value' => variable_get('invite_award_points_per_user',30),
		'#description' => t('邀请人每邀请一个用户,所获得的积分奖励'),
	);
	$form['email'] = array(
		'#type' => 'fieldset',
		'#title' => t('默认邀请邮件'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
		
	);
	$default_invite_default_email_title = t('默认邀请邮件的主题');
	$form['email']['invite_default_email_title'] = array(
		'#title' => t('主题'),
		'#type' => 'textfield',
		'#default_value' => variable_get('invite_default_email_title', $default_invite_default_email_title),
		'#description' => t('默认邀请邮件的主题，这里可以使用令牌占位符[inviter]，用户不可以修改'),
	);
	$default_invite_default_email_body = t('默认邀请邮件的正文');
	$form['email']['invite_default_email_body'] = array(
		'#title' => t('正文'),
		'#type' => 'textarea',
		'#default_value' => variable_get('invite_default_email_body', $default_invite_default_email_body),
		'#description' => t('默认邀请邮件的正文，这里不使用令牌占位符，用户可以修改'),
	);
	$default_invite_default_email_link = t('默认邀请邮件的正文下面的邀请链接');
	$form['email']['invite_default_email_link'] = array(
		'#title' => t('邀请链接'),
		'#type' => 'textarea',
		'#default_value' => variable_get('invite_default_email_link', $default_invite_default_email_link),
		'#description' => t('默认邀请邮件正文下面的邀请链接，这里使用令牌占位符[join-link]，用户不可以修改'),
	);
	return system_settings_form($form);
}

function invite_admin_config_form_validate($form,&$form_state){
	$bili = $form_state['values']['invite_award_points_per_user'];
	if(!is_numeric($bili) || $bili <= 0){
		form_set_error('invite_award_points_per_user',t('积分比例应该是大于0的数字'));
	}
}