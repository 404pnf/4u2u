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

function invite_admin_list_page(){
	$output ="";
	//$output .=t("邀请记录汇总排名");
	
	$sql = "SELECT uid, count(invitee) as subtotal FROM {invite} WHERE invitee > 0 GROUP BY uid ORDER BY subtotal DESC";
	$pager_num = 0;
	$result = pager_query($sql, 50, $pager_num, NULL);
	//$header = array("Email地址","邀请时间","再次邀请","删除");
	$header = array("用户","邀请人数");
	$ta = array('id' => 'invite-sum-table', 'align' => 'center');
	$trows = array();
	while($data = db_fetch_object($result)){
		$current_user = user_load($data->uid);
		$trows[] = array(
			array('data'=>l($current_user->name,'user/'.$current_user->uid),'valign'=>'top'),
			array('data'=>$data->subtotal,'valign'=>'top'),
			
			//array('data'=>l('删除','invite/delete/'.$data->invite_id),'valign'=>'top'),
		);
	}
	$output .= theme('table', $header, $trows, $ta);
  $output .= theme('pager', NULL, 50, $pager_num);
	
	return $output;
}