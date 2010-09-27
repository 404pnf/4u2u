<?php
// $Id$

function invite_list_method_page(){
	global $user;
	$output = "";
	drupal_set_title(t('邀请朋友加入'));
	//匿名用户,返回登录提示
	if($user->uid==0){
		$output .= "<div class='invitelist'>";
		$output .= "<p>只有登录用户才能邀请自己的朋友.</p>";
		$output .= l('现在马上登录','user',array('query'=>array('destination'=>invite)));
		$output .= "</div>";
		return $output;
	}
	
	$output .= "<div class='invitelist'>";
	$output .= "<div class='invite-method'>".l('发送邀请链接给朋友','invite/link')."</div>";
	$output .= "<p>使用QQ、MSN、SKYPE等聊天工具发送邀请链接</p>";
	$output .= "</div>";
	
	$output .= "<div class='invitelist'>";
	$output .= "<div class='invite-method'>".l('通过Email邀请','invite/email')."</div>";
	$output .= "<p>向对方的邮箱发送邀请邮件</p>";
	$output .= "</div>";
	/*
	$output .= "<div class='invitelist'>";
	$output .= "<div class='invite-method'>".l('导入邮箱的通讯录至邀请名单','invite/contacts')."</div>";
	$output .= "<p>支持163,gmail,hotmail,QQ等4类免费邮箱</p>";
	$output .= "</div>";
	*/
	return $output;
}

function invite_method_link_page(){
	global $user;
	$output = "";
	if($user->uid==0){
		drupal_set_message(t('只有登录用户才能邀请自己的朋友'));
		drupal_goto('invite');
		//return ;
	}

	$usercode = _invite_get_usercode_by_uid($user->uid);
	$output .= "<div class='imlp-des'>"."复制此邀请链接地址，用QQ、MSN等发送给你的朋友；对方加入后即自动为你添加相应的积分"."</div>";
	$output .= "<span>邀请链接：</span> ".'http://'.$_SERVER['HTTP_HOST'].base_path()."user/register?uid=".$user->uid."&usercode=".$usercode;
	return $output;
}
function _invite_get_usercode_by_uid($uid){
	if($uid <=0){
		return NULL;
	}
	$count_sql = "SELECT COUNT(uid) FROM {usercode} WHERE uid= %d";
	$count = db_result(db_query($sql,$uid));
	if($count == 1){
		$sql = "SELECT ucode FROM {usercode} WHERE uid= %d";
		$usercode = db_result(db_query($sql,$uid));
		return $usercode;
	}
	else{
		$sql = "DELETE FROM {usercode} WHERE uid = %d";
		db_query($sql,$uid);
		//$str = $uid.time();
		//原来使用drupal_get_token函数生成32位邀请码,现在直接使用md5，这样用户的新生成的邀请码就不会变化了。后面加了字符串'2u4u'，作为站点的密钥
		//$usercode = drupal_get_token($uid);
		$usercode = md5($uid.'2u4u');
		$sql = "INSERT INTO {usercode} (uid, ucode) VALUES (%d, '%s')";
		db_query($sql, $uid, $usercode);
		return $usercode;
	}
}

function invite_method_email_page(){
	global $user;
	if($user->uid <= 0){
		drupal_set_message(t('只有登录用户才能邀请自己的朋友'));
		drupal_goto('invite');
		//return ;
	}
	$output = "";
	$output .=drupal_get_form('invite_method_email_form');
	return $output;
}
function invite_method_email_form(){
	$form['emails'] = array(
		'#type' => 'textarea',
		'#title' => t('对方Email'),
		'#description' => t('一次填写多个Email地址请用回车换行分隔'),
	);
	$default_invite_default_email_body = t('默认邀请邮件的正文');
	$form['body'] = array(
		'#type' => 'textarea',
		'#title' => t('邀请留言'),
		'#default_value' => variable_get('invite_default_email_body',$default_invite_default_email_body),
	);
	$form['name'] = array(
		'#type' => 'textfield',
		'#title' => t('你的姓名'),
		
	);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('发送邀请'),
		
	);
	return $form;
}
function invite_method_email_form_validate($form,&$form_state){
	$emails = $form_state['values']['emails'];
	$email_array = explode("\n",$emails);
	foreach($email_array as $key => $email){
		//消除字符串两边的空格
		$email = trim($email);
		$email_array[$key] = $email;
		if(!valid_email_address($email)){
			form_set_error('emails',t('你输入的Email地址不对，该地址为：@email',array('@email' =>$email)));
		}
	}
	//如果没有错误，那么重新为$form_state['values']['emails']赋值
	$form_state['values']['emails'] = $email_array;
	
}
function invite_method_email_form_submit($form,&$form_state){
  global $user;
	$emails = $form_state['values']['emails'];
	$from = variable_get('site_mail', ini_get('sendmail_from'));
	$values = array();
	$values['body'] = $form_state['values']['body'];
	$values['name'] = $form_state['values']['name'];
	
	$usercode = _invite_get_usercode_by_uid($user->uid);
	$invite_link = 'http://'.$_SERVER['HTTP_HOST'].base_path()."user/register?uid=".$user->uid.'&usercode='.$usercode;
	
	$job_queue_exists = module_exists('job_queue');
	
	foreach($emails as $to){	
		$invite_id = _invite_get_inviteid_by_uid_and_email($user->uid, $to, $values);
		$values['invite_link'] =  $invite_link.'_'.$invite_id; 
		if(module_exists('job_queue')){
			job_queue_add('drupal_mail', '发送邀请链接的邮件', array('invite', 'invite_notify', $to, language_default(), $values, $from), '', TRUE);
		}else{
			drupal_mail('invite', 'invite_notify', $to, language_default(), $values, $from);
		}
	}
		
	drupal_set_message(t('您的邀请邮件已发送,对方接受邀请注册后，就会为您添加相应的积分'));
	drupal_goto('invite');
}

function _invite_get_inviteid_by_uid_and_email($uid, $email, $data = array()){
	if($uid <= 0){
		return '';
	}
	$count_sql = "SELECT COUNT(uid) FROM {invite} WHERE uid= %d AND email= '%s'";
	$count = db_result(db_query($count_sql, $uid, $email));
	if($count == 1){
		$sql = "SELECT invite_id FROM {invite} WHERE uid= %d AND email= '%s'";
		$invite_id = db_result(db_query($sql, $uid, $email));
		db_query("UPDATE {invite} SET changed = %d, data ='%s' WHERE invite_id = %d", time(), serialize($data), $invite_id);
		return $invite_id;
	}
	else{
		$sql = "DELETE FROM {invite} WHERE uid = %d AND email= '%s'";
		db_query($sql, $uid, $email);
		//$str = $uid.time();
		$sql = "INSERT INTO {invite} (email, uid, created, changed, data) VALUES ('%s', %d, %d, %d, '%s')";
		$current_time = time();
		db_query($sql, trim($email), $uid, $current_time, $current_time, serialize($data));
		$invite_id = db_last_insert_id('invite','invite_id');
		return $invite_id;
	}
}

function invite_method_contacts_page(){
	$output ="";
	$output .=t("正在建设中，请稍候");
	return $output;
}

function invite_user_pending_page($account){
	$output ="";
	$output .=t("你发出的以下邀请，对方并没有来注册 (这里的历史邀请数据不包括成功的邀请)");
	
	$sql = "SELECT * FROM {invite} WHERE uid= %d AND joined = 0 ORDER BY changed DESC";
	$pager_num = 0;
	$result = pager_query($sql, 50, $pager_num, NULL, $account->uid);
	$count = db_result(db_query("SELECT COUNT(*) FROM {invite} WHERE uid= %d AND joined = 0", $account->uid));
	//$header = array("Email地址","邀请时间","再次邀请","删除");
	$header = array("Email地址","邀请时间","再次邀请");
	$ta = array('id' => 'invite-table', 'align' => 'center');
	$trows = array();
	while($data = db_fetch_object($result)){
		$trows[] = array(
			array('data'=>$data->email,'valign'=>'top'),
			array('data'=>format_date($data->changed,'custom','Y-m-d - H:i'),'valign'=>'top'),
			array('data'=>l('再次邀请','invite/resend/'.$data->invite_id),'valign'=>'top'),
			//array('data'=>l('删除','invite/delete/'.$data->invite_id),'valign'=>'top'),
		);
	}
	$output .= theme('table', $header, $trows, $ta);
  $output .= theme('pager', NULL, 50, $pager_num);
	
	return $output;
}

function invite_user_accepted_page($account){
	$output ="";
	$output .=t("下面是通过你的邀请，成功注册的用户列表");
	
	$sql = "SELECT * FROM {invite} WHERE uid= %d AND joined > 0 ORDER BY joined DESC";
	$pager_num = 0;
	$result = pager_query($sql, 50, $pager_num, NULL, $account->uid);
	$count = db_result(db_query("SELECT COUNT(*) FROM {invite} WHERE uid= %d AND joined > 0", $account->uid));
	//$header = array("用户","注册时间");
	$header = array("用户","注册时间","Email","Referrer");
	$ta = array('id' => 'invite-table', 'align' => 'center');
	$trows = array();
	while($data = db_fetch_object($result)){
		$invitee = user_load($data->invitee);
		$trows[] = array(
			array('data'=>l($invitee->name,'user/'.$invitee->uid),'valign'=>'top'),
			array('data'=>format_date($data->joined,'custom','Y-m-d - H:i'),'valign'=>'top'),
			array('data'=>$invitee->mail,'valign'=>'top'),
			//array('data'=>l('删除','invite/delete/'.$data->invite_id),'valign'=>'top'),
			array('data'=>$data->referrer,'valign'=>'top'),
			//array('data'=>l('删除','invite/delete/'.$data->invite_id),'valign'=>'top'),
		);
	}
	$output .= theme('table', $header, $trows, $ta);
  $output .= theme('pager', NULL, 50, $pager_num);
	
	return $output;
}

function invite_resend_invite_callback(){
	global $user;
	if($user->uid <= 0){
		drupal_set_message(t('只有登录用户才能邀请自己的朋友'));
		drupal_goto('invite');
		//return ;
	}
	$output ="";
	$invite_id = arg(2);
	if(empty($invite_id)){
		drupal_set_message(t('无效的邀请ID'));
		drupal_goto('invite');
	}
	//$output .=t("正在建设中，请稍候");
	//drupal_set_message(t("正在建设中，请稍候"));
	$sql =  "SELECT * FROM {invite} WHERE invite_id= %d";
	$result = db_query($sql,$invite_id);
	$invite = db_fetch_object($result);
	//$limit = time() -24*60*60;
	if($invite && $user->uid == $invite->uid ){
		$limit = time() -24*60*60;
		if($invite->changed < $limit){
			return drupal_get_form('invite_resend_invite_form',$invite);
			//return drupal_get_form('invite_resend_invite_form');
		}
		else{
			drupal_set_message(t('今天你已向@email发送过邀请，同一天内请勿重新发送。',array('@email'=>$invite->email)));
			drupal_goto('user/'.$user->uid.'/invites');
		}
	}else{
		drupal_set_message(t('只有登录用户才能邀请自己的朋友'));
		drupal_goto('user/'.$user->uid.'/invites');
	}
	
	//return $output;
}
function invite_resend_invite_form(&$form_state,$invite){
	drupal_set_message(t('SUCCESS'));
//	$invite = 
	$form['email'] = array(
		'#type' => 'textfield',
		'#title' => t('对方Email'),
		'#value' => $invite->email,
		'#attributes' => array('disabled'=>TRUE),
	);
	$namebody = unserialize($invite->data);
	$form['body'] = array(
		'#type' => 'textarea',
		'#title' => t('邀请留言'),
		'#default_value' => $namebody['body'],
	);
	$form['name'] = array(
		'#type' => 'hidden',
		'#value' => $namebody['name'],
	);
	$form['invite'] = array(
		'#type' => 'hidden',
		'#value' => $invite,
	);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('发送邀请'),
		
	);
	return $form;
}
function invite_resend_invite_form_submit($form,&$form_state){
	global $user;
	$email = trim($form_state['values']['email']);
	$from = variable_get('site_mail', ini_get('sendmail_from'));
	$values = array();
	$values['body'] = $form_state['values']['body'];
	$values['name'] = $form_state['values']['name'];
	
	$usercode = _invite_get_usercode_by_uid($user->uid);
	$invite_link = 'http://'.$_SERVER['HTTP_HOST'].base_path()."user/register?uid=".$user->uid.'&usercode='.$usercode;
	
	$job_queue_exists = module_exists('job_queue');
	
	$invite_id = _invite_get_inviteid_by_uid_and_email($user->uid, $email, $values);
	$values['invite_link'] =  $invite_link.'_'.$invite_id; 
	if(module_exists('job_queue')){
		job_queue_add('drupal_mail', '发送邀请链接的邮件', array('invite', 'invite_notify', $email, language_default(), $values, $from), '', TRUE);
	}else{
		drupal_mail('invite', 'invite_notify', $email, language_default(), $values, $from);
	}

		
	drupal_set_message(t('您的再次邀请已发送,对方接受邀请注册后，就会为您添加相应的积分'));
	drupal_goto('user/'.$user->uid.'/invites');
}

function invite_award_inviter_callback(){
  //邀请人
	$inviter = arg(2);
	//被邀请人
	$invitee = arg(3);
	//奖励码
	$awardcode = arg(4);
	//被邀请人对象
	$invitee_user = user_load($invitee); 
	$sql = "SELECT * FROM {invite} WHERE uid= %d AND invitee= %d ";
	//邀请记录对象
	$invite = db_fetch_object(db_query($sql, $inviter, $invitee));
	//邀请记录不存在
	if(empty($invite) || !isset($invite->invite_id)){
		drupal_set_message(t('积分奖励码无效，无法为邀请人添加积分'));
		drupal_goto('invite');
	}
	//邀请记录中email不为空，此时表示已经为用户奖励了积分
	//drupal_set_message($invite->email."123123".$invitee);
	if(!empty($invite->email)){
		drupal_set_message(t('已经为邀请人奖励了相应积分，本链接有效性只有一次，请勿重复点击'));
		drupal_goto('invite');
	}
	$md5_value = md5($invitee_user->mail.$invite->invite_id);
	//奖励码无效
	if($awardcode != $md5_value){
		drupal_set_message(t('积分奖励码无效，无法为邀请人添加积分'));
		drupal_goto('invite');
	}else{
		$sql = "UPDATE {invite} SET email = '%s' WHERE invite_id= %d";
		db_query($sql, $invitee_user->mail, $invite->invite_id);
		
		//为邀请人添加分数
		$params = array (
			'uid' => $inviter,
			'points' => variable_get('invite_award_points_per_user',30),
			'description' => t('通过邀请用户获取的积分.邀请了用户:@username(ID: @uid)',array('@username'=>$invitee_user->name,'@uid'=>$invitee_user->uid)),
		);
		userpoints_userpointsapi($params);
		drupal_set_message(t('成功的为邀请人奖励了相应积分，现在您也可以通过邀请朋友挣取积分了'));
		drupal_goto('invite');
	}
	
}
