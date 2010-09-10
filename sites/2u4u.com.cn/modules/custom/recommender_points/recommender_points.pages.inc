<?php
// $Id$

function recommender_points_topup_page(){
	global $user;
	$output = "";
	if($user->uid >0){
		//只有登录用户，才可以参加积分充值推荐活动
		$output .= drupal_get_form('recommender_points_topup_form');
	}
	else {
		//对于匿名用户，为其返回相应的提示，提示登录
		$output .= t('您好，只有<a href="http://2u4u.com.cn/user?destination=chongzhi">登录</a>后，才能把积分充入您的账号。');
		$output .= t('如果您还没有账号，<a href="http://2u4u.com.cn/user/register">注册</a>只需半分钟。');
	}
	return $output;
}

function recommender_points_topup_form(&$form_state = NULL){
	//多步表单步骤的指示器
	$step = isset($form_state['values']) ? (int)$form_state['storage']['step'] : 0;
 
  // Store next step.
  $form_state['storage']['step'] = $step + 1;
	$form = array();
	//当用户第一次访问这个页面时
	if($step<1){
		$form ['tips'] = array(
			'#value' => t('<ol>
			                <li>外研社09年以后出版的大部分图书，封底有一张蓝色刮刮贴，刮开即可得到悠游网在线充值的验证码。</li>
                                        <li>在下方输入框内输入获得的验证码即可进行在线充值。</li>
                                        <li>9月6日到10月20日期间，悠游网举办“通寻令-悠游开学大行动”，在积分充值的同时，为您的好友增加奖励积分。在您充值成功后，就会进入到推荐人页面，输入好友的悠游网ID，您的好友即可获得您充值积分额度的50%作为奖励积分。</li>
					<li>奖励积分与悠游网积分同样使用，并作为“通寻令-悠游开学大行动”主题活动的排名依据，冲击APPLE笔记本、精美上网本和PSP游戏机等诱人大奖！详情访问活动专题：<a href="http://2u4u.com.cn/zhuanti/20100908_tiyan/">http://2u4u.com.cn/zhuanti/20100908_tiyan/</a></li>
				       </ol> '),
			'#type' => 'item',
		); 
		$form['gcode'] = array(
			'#title' => t('输入图书验证码'),
			'#type' => 'textfield',
		 );
		$form['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Submit'),
		);

		//占位给css用
		$form ['tips-tishi'] = array(
			'#value' => '<div id=tishi_title_img> </div>',
			'#type' => 'item',
		);
		//占位结束 

		$path=drupal_get_path('module', 'gift_points');
		$path=$path.'/caution.txt';
		
		$fh = fopen($path, "rb");
		$data = fread($fh, filesize($path));
		fclose($fh);
		 $form['caution']=array(
		'#title'=>'提示',
			'#type'=>'textarea',
			'#disabled'=>true,
			'#rows' => 11,
			'#value'=> $data,   
		 );
	}
	//当用户完成充值后，返回一个表单，提示其输入推荐人的名字，从而为推荐人加分
	else{
		//总共只有两步,超过2的时候重置为2
		if($form_state['storage']['step']>2){
			$form_state['storage']['step'] =2;
		}
		//drupal_set_message('step:'.$form_state['storage']['step']);
		//$form_state['storage']['award'] = $form_state['storage']['award'];
		//drupal_set_title('为推荐人加积分');
		$form['tips_recommender'] = array(
			'#prefix' => '<div class="tips-recommender">',
			'#value' => t('为推荐人加积分'),
			'#suffix' => '</div>',
		);
		$form['recommender'] = array(
			'#title' => t('推荐人'),
			'#type' => 'textfield',
			'#autocomplete_path' => 'user/autocomplete',
		);
		$form['submit1'] = array(
			'#type' => 'submit',
			'#value' => t('提交'),
			//'#weight' => 10,
		);
		$form['skip'] = array(
			'#type' => 'submit',
			'#value' => t('放弃'),
			//'#weight' => 10,
		);
	 }
   return $form;
}
function recommender_points_topup_form_validate($form,&$form_state = NULL){
	//第一步表单提交后的验证逻辑
	if($form_state['storage']['step'] == 1 ){
	
		//
		$values = $form_state['values'];
		$emno = gift_points_get_emno($values['gcode']);
		
		if(!$emno[0]){
			form_set_error('gcode', t("您输入的验证码不对。请再试一次。"));
		}elseif($emno[2]){
				form_set_error('gcode', t("您输入的验证码已经被使用过。"));
		}else{
			//我们将在验证中取得值保存起来，这样在提交函数中可以使用。
			$form_state['storage']['emno'] = $emno;
		}	
		
	}
	//第二步表单提交后的验证逻辑
	elseif($form_state['storage']['step'] == 2 && $form_state['values']['op']== $form_state['values']['submit1']){
		//这里验证用户名的有效性，这里使用drupal自带的user_validate_name做简单的验证
		$error = user_validate_name($form_state['values']['recommender']);
		if ($error) {
			//$form_state['storage']['step'] = $form_state['storage']['step'] - 1;
			//drupal_set_message('step:'.$form_state['storage']['step']);
			form_set_error('recommender', $error);
			return;
		}
		global $user;
		if($user->name == $form_state['values']['recommender']){
			form_set_error('recommender', t('推荐人不能是自己'));
		}
	}
}
function recommender_points_topup_form_submit($form,&$form_state = NULL){
  if($form_state['storage']['step'] == 1 ){
	
		/******************************下面的这段代码复制自gift_points模块*********************************************/	
		
		global $user;
		$values = $form_state['values'];
		//将原来放在submit里面的验证代码放到了validate函数中了，validate中所作的操作保存到了$form_state['storage']['emno']
		$emno = $form_state['storage']['emno'];
		$em = gift_points_get_em(gift_points_full_emno($emno[0]));
		$emfield = variable_get('gpoints_award','').'_value';
		
		//  获取奖励的积分，优先取本地数组，本地没有则用erp返回值，都没有则加10分
		
		$local_points = (int)$em->$emfield;    //本地数据库中查到的积分

		if($local_points>0){
			$local_price = $em->field_erp_dingjia_value;
			$points = $local_points;
			$price = $local_price;
			$is_add = 1;   	
		}else{
			 $erp_info = gift_points_erp_info($emno[0]);  //erp接口返回值   1->价格 4->产品组 6->是否有返回值（1/0）
			 if($erp_info[6]){        
				$price = $erp_info[1];
				$points = (int)$erp_info[1];
				$is_add = 3;   	//加的是社内erp积分
			 }
		}
		
		if($points<=0){
			$points = 10;
			$price = 0;
			$is_add = 2;   	//积分不全	
		}
		
		
		$params = array (
			'uid' => $user->uid,
			'points' => $points,
			// 'tid' => variable_get('gpoints_tid',''),
			'description' => t('积分充值.图书验证码'),
		 );
		
		//$points = $points*2;
		// 继续实行双倍积分。当erp返回充值成功但本数据库中还没有该物料号对应积分的时候
		//给用户20个积分。
		//$points=$points>0?$points:10; 
		//print_r($em->field_award_value);

		$add_status = userpoints_userpointsapi($params);  
		
		gift_points_set_emno($values['gcode']);   //申明验证码失效
		 
		if($add_status['status']==FALSE|$points<=0){  
			$is_add = 0;
		}
		db_query("INSERT INTO {topup} (uid, gcode, emno, time,status,points,price) VALUES (%d, '%s','%s',%d,%d,%d,%f)",$user->uid, $values['gcode'],gift_points_full_emno($emno[0]),time(),$is_add,$points,$price);
		// drupal_set_message(t('充值成功。 增加了 '.$points.' 个积分。'));
		
		/******************************这段代码复制自gift_points模块*********************************************/
		
		$form_state['storage']['award'] = $points;
		//$form_state['storage']['award'] = 100;
		drupal_set_message(t('充值成功。 增加了 '.$form_state['storage']['award'].' 个积分。'));
		
  }
	if($form_state['storage']['step'] == 2 ){
		if($form_state['values']['op']== $form_state['values']['submit1']){
			$recommender =  $form_state['values']['recommender'];
			$recommender_user = user_load(array('name'=>$recommender,));
			if(!$recommender_user){
				drupal_set_message (t("您输入的用户名不对。请再试一次。"),'error');
				return;
			}
			$points = floor($form_state['storage']['award'] * variable_get('recommender_points_bili',0.4));
			if($points >0){
				$params = array (
					'uid' => $recommender_user->uid,
					'points' => $points,
					// 'tid' => variable_get('gpoints_tid',''),
					'description' => t('图书验证码积分充值.奖励推荐'),
				);
				
				$add_status = userpoints_userpointsapi($params); 
				drupal_set_message(t('奖励推荐人@recommender积分@recommender_points',array('@recommender'=>$recommender,'@recommender_points'=>$points,)));
				//drupal_goto('userpoints/gift/promote/'.$form_state['storage']['award']);
				$form_state['redirect'] = 'userpoints/gift/promote/'.$form_state['storage']['award'];
				unset($form_state['storage']);
				
			}else{
				drupal_set_message(t('奖励推荐人的积分小于等于0，已经取消了奖励'));
				//drupal_goto('userpoints/gift/promote/'.$form_state['storage']['award']);
				$form_state['redirect'] = 'userpoints/gift/promote/'.$form_state['storage']['award'];
				unset($form_state['storage']);
			}
		}
		if($form_state['values']['op']== $form_state['values']['skip']){
			//drupal_goto('userpoints/gift/promote/'.$form_state['storage']['award']);
			$form_state['redirect'] = 'userpoints/gift/promote/'.$form_state['storage']['award'];
			unset($form_state['storage']);
		}
	}
 
}
