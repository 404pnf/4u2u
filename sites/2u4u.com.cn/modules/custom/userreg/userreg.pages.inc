<?php
// $Id$
/**
 * 菜单回调函数.
 */
function userreg_callback_page() {
  //获取传递过来的值
	$name = $_REQUEST['name'];
	$pass = $_REQUEST['pass'];
	//$pass2 = $_REQUEST['pass2'];
	$mail = $_REQUEST['mail'];
	$source = isset($_REQUEST['source'])?$_REQUEST['source']:'';
	$errors = array();
	/*
	//密码是否一致验证
	if($pass != $pass2){
		$errors[] = t('确认密码必须和输入密码保持一致');
	}
	// 用户名验证:
	$error = user_validate_name($name);
	if ($error) {
		$errors[] = $error;
	}
	else if (db_result(db_query("SELECT COUNT(*) FROM {users} WHERE LOWER(name) = LOWER('%s')",  $name)) > 0) {
		$errors[] =  t('The name %name is already taken.', array('%name' => $name));
	}
	else if (drupal_is_denied('user', $form_state['values']['name'])) {
		$errors[] =  t('The name %name has been denied access.', array('%name' => $name));
	}

	// email地址验证:
	
	$ret = user_validate_mail($mail);
	if ($ret) {
		$errors[] = $ret;
	}
	else if (db_result(db_query("SELECT COUNT(*) FROM {users} WHERE LOWER(mail) = LOWER('%s')",  $mail)) > 0) {
		$errors[] =  t('The e-mail address %email is already registered.', array('%email' =>  $mail));
	}
	else if (drupal_is_denied('mail',  $form_state['values']['mail'])) {
		$errors[] = t('The e-mail address %email has been denied access.', array('%email' =>  $mail));
	}
	//添加ucenter的验证
  if(module_exist('ucenter')){
		$name_result = uc_user_checkname($name);
		if ($name_result == -1) {
			$errors[] = t('用户名不合法');
		}
		else if ($name_result == -2) {
			$errors[] = t('包含要允许注册的词语');
		}
		else if ($name_result == -3) {
			$errors[] = t('用户名已经存在');
		}
		// check the email with ucenter's function
		$email_result = uc_user_checkemail($mail);
		if ($email_result == -4) {
			$errors[] = t('Email 格式有误');
		}
		else if ($email_result == -5) {
			$errors[] = t('Email 不允许注册');
		}
		else if ($email_result == -6) {
			$errors[] = t('该 Email 已经被注册');
		}
	}
	*/
	$form_state = array();
	$form_state['values']['name'] = $name; 
	$form_state['values']['mail'] = $mail; 
	$form_state['values']['pass'] = array(
		'pass1' => $pass,
		'pass2' => $pass,
	);
	$form_state['values']['op'] = t('Create new account');
	global $user;
  $user = user_load(array('uid' => 1));

	$ret = drupal_execute('user_register', $form_state);
	$errors = form_get_errors();
	
	if(!empty($errors)){
		$reurn_result = array(
			'status' => FALSE,
			'errors' => implode("\n", $errors),
		);
		//print drupal_to_js($output);
		drupal_json($reurn_result);
		//drupal_set_message('123123');
		//unset($_SESSION['messages']['error']);
		exit();
	}else{
		//module_load_include('inc', 'user', 'user.pages');
		//return $form_state['user']->uid;
		$reurn_result = array(
			'status' => TRUE,
			'errors' => '',
		);
		$sql = "INSERT INTO {userreg} (uid, source, created) VALUES(%d, '%s', %d)";
		db_query($sql,$form_state['user']->uid,$source,time());
		//print drupal_to_js($output);
		drupal_json($reurn_result);
		exit();
	}
	
}

function userreg_test_page(){
	$output ="";
	drupal_add_js(drupal_get_path('module','userreg').'/userreg.js');
	$output .=  t('测试用户注册特别通道的页面');
	$output .= "<div>在下面的输入框中输入测试链接数据</div>";
	$output .='<div><input id="test-userreg-page-input" type="text" name="userreg-input" size="60" /></div>';
	$output .= '<div><a href="#" id="test-userreg-page-link" >提交测试</a></div>';
	return $output;
}