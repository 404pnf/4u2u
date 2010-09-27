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
	
	$form['jijiangdaoqi'] = array(
		'#type' => 'fieldset',
		'#title' => t('即将到期的提问通知邮件'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
		
	);	
	$form['jijiangdaoqi']['expert_jijiangdaoqi_email_title'] = array(
		'#title' => t('邮件主题'),
		'#type' => 'textfield',
		'#default_value' => variable_get('expert_jijiangdaoqi_email_title', t('您的提问"[question-title]"即将到期')),
		'#description' => t('统一的即将到期提问的邮件通知主题'),
	);
	$form['jijiangdaoqi']['expert_jijiangdaoqi_email_body'] = array(
		'#title' => t('邮件正文'),
		'#type' => 'textarea',
		'#default_value' => variable_get('expert_jijiangdaoqi_email_body', t('您的提问"[question-title]"即将到期，请及时处理。\n [question-link] ')),
		'#description' => t('默认邀请邮件的正文，这里可使用令牌占位符[question-title],[question-link]，用户可以修改'),
	);
	
	$form['huidatiwen'] = array(
		'#type' => 'fieldset',
		'#title' => t('有人回答自己的提问'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
		
	);
	$form['huidatiwen']['expert_huidatiwen_email_title'] = array(
		'#title' => t('邮件主题'),
		'#type' => 'textfield',
		'#default_value' => variable_get('expert_huidatiwen_email_title', t('您的提问"[question-title]"已有人回答')),
		'#description' => t('有人回答自己的提问时所发通知邮件的主题'),
	);
	$form['huidatiwen']['expert_huidatiwen_email_body'] = array(
		'#title' => t('邮件正文'),
		'#type' => 'textarea',
		'#default_value' => variable_get('expert_huidatiwen_email_body', t('您的提问"[question-title]"已有人回答，快去看看吧。\n [question-link] ')),
		'#description' => t('默认邮件的正文，这里可使用令牌占位符[question-title],[question-link]，用户可以修改'),
	);
	
	$form['zuijiadaan'] = array(
		'#type' => 'fieldset',
		'#title' => t('有人接纳自己的回答为最佳答案'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
		
	);
	$form['zuijiadaan']['expert_zuijiadaan_email_title'] = array(
		'#title' => t('邮件主题'),
		'#type' => 'textfield',
		'#default_value' => variable_get('expert_zuijiadaan_email_title', t('您对提问"[question-title]"的回答已被选为最佳答案')),
		'#description' => t('有人接纳自己的回答为最佳答案时,所发邮件通知主题'),
	);
	$form['zuijiadaan']['expert_zuijiadaan_email_body'] = array(
		'#title' => t('邮件正文'),
		'#type' => 'textarea',
		'#default_value' => variable_get('expert_zuijiadaan_email_body', t('您对提问"[question-title]"的回答已被选为最佳答案，快去看看吧。\n [question-link] ')),
		'#description' => t('默认邮件的正文，这里可使用令牌占位符[question-title],[question-link]，用户可以修改'),
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

function expert_run_cron_page(){
	$output ="";
	$output .=drupal_get_form('expert_run_cron_form');
	return $output;
}
function expert_run_cron_form(){
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('运行'),	
	);
	return $form;
}
function expert_run_cron_form_submit(){
	expert_cron();
	drupal_set_message(t('成功100个'));
}