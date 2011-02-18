<?php
// $Id$

/**
 * @file
 * 集成首信易的支付服务.
 * zhupou.cn为外研社2u4u.com.cn制作，
 */

/**
 * 从首信易到商户的异步通知接口实现，这里实现了首信易支付（v4.3）接口说明文档中的
 * 第三部分：“首信易支付订单支付结果后台返回接口（首信易支付＝＝>>商户）”
 * 注意：这种方式接收程序的地址需要由商户来确定，在商户号开通时所填写的初始单中，
 * 填写在“订单支付确认返回地址”一栏，并由首信易支付平台管理员按照初始单内容进行开通。
 * 开通后如有修改，需要事先通知管理员确认修改。
 */
function uc_payease_notify() {
	
	 //订单个数
	 $v_count = $_POST["v_count"];
	 
	 //定单编号组
	$v_oid = $_POST["v_oid"];
	
	//支付方式组
	$v_pmode = $_POST["v_pmode"];
	
	//支付状态组 0－待处理，1－支付完成，3－支付失败
	$v_pstatus = $_POST["v_pstatus"];
	
	//支付结果说明： 成功时（v_pstatus=1）为“支付成功”，支付被拒绝时（v_pstatus=3）为失败原因
	$v_pstring = $_POST["v_pstring"];
	
	//订单实际支付金额
	$v_amount = $_POST["v_amount"];
	
	//订单实际支付币种
	$v_moneytype = $_POST["v_moneytype"];

	//MD5校验信息
	$v_mac = $_POST["v_mac"];
	
	
	//MD5校验信息
	$v_md5money = $_POST["v_md5money"]; 
	//商城数据签名
	$v_sign = $_POST["v_sign"];
	
	//MD5私钥
	$md5key = variable_get('uc_payease_md5key', 'test');  // MD5私钥
	
	$currentpath= dirname(__FILE__);
	
	//我们在下面采用v_sign的RSA验证，所以这段代码注释掉了
	
  if(eregi('WIN',PHP_OS)){
  	$default_md5program = str_replace("\\","\\\\",$currentpath)."\\\\MD5Win32";
  }else{
  	$default_md5program = $currentpath.'/MD5Linux';
  }
	$uc_payease_md5program =variable_get('uc_payease_md5program', $default_md5program);
	
	//校验源字符串，v_md5money效验
	
	$md5src1 = $v_oid  .$v_pmode . $v_pstatus . $v_pstring . $v_count;
	//MD5检验结果，v_md5money效验
	// $md5sign1 = strtoupper(md5($md5src1));
	//exec($uc_payease_md5program." $md5src1 $md5key",$md5sign1,$res1);
	exec("$uc_payease_md5program \"$md5src1\" $md5key",$md5sign1,$res1);

	//校验源字符串，v_md5money效验
	$md5src2 = $v_amount . $v_moneytype;
	//MD5检验结果，v_md5money效验
	// $md5sign2 = strtoupper(md5($md5src2));

	//exec($uc_payease_md5program." $md5src2 $md5key",$md5sign2,$res2);
	exec("$uc_payease_md5program \"$md5src2\" $md5key",$md5sign2,$res2);
	/*
	$rsa_source=$v_oid . $v_pstatus . $v_amount . $v_moneytype . $v_count;
	$rsa_source_length = strlen($rsa_source);
	$default_capinfoRSA = $currentpath.'/capinfoRSA';
	$default_capinfoRSA_key = $currentpath.'/Public_mykey1.key';
	//不知道为什么,这个不起作用.
	//exec("$default_capinfoRSA PublicSignString $default_capinfoRSA_key $rsa_source $rsa_source_length", $rsa_res, $rc);
	//不知道为什么,这个好像起作用.
	exec("$default_capinfoRSA PublicVerifyMD5 $default_capinfoRSA_key $v_sign '".$rsa_source."' $rsa_source_length", $ress, $rcs);
	*/
	$msg = 'v_count:'.$v_count. ';v_oid' . $v_oid . ';v_pmode' . $v_pmode . ';v_pstatus' . $v_pstatus . ';v_pstring' . $v_pstring . ';v_amount' . $v_amount . ';v_moneytype' . $v_moneytype;
  watchdog('uc_payease',$msg);
	watchdog('uc_payease','v_md5money:'.$v_md5money.';md5sign2[0]:'.$md5sign2[0]);
	//if ($v_mac==$md5sign1 && $v_md5money==$md5sign2) {
	//这里面我担心中文验证有问题,所以仅使用了md5money进行验证，下面的代码从理论上和上面是一致的，也就是等效的。	
	//当有特殊字符时,会加密失败,此时$v_md5money为空,所以检查是否为空,以防止潜在的安全漏洞
	if ( $v_md5money==$md5sign2[0] && !empty($v_md5money)) {
	//if ( $v_sign==$rsa_res[0]) {
	//if ($ress[0] === '0') {
		//如果只返回了一个订单
		if($v_count ==1){
			// 商户编号
			$v_mid = variable_get('uc_payease_seller', '888'); 
			//获取Drupal系统内部的订单ID   
			$startno = 8+strlen($v_mid)+2;
			$order_id = substr($v_oid,$startno); 
			//根据订单ID加载订单对象
			$order = uc_order_load($order_id);
			if($v_pstatus ==1){
				if($order->order_status=='payment_received'||$order->order_status=='completed'){
					//订单已经完成,此时不做操作
					watchdog('uc_payease','订单已经完成,此时不做操作');
				}else{
						//内部完成付款
					$comment = t('异步通知--首信易交易ID: @v_oid', array('@v_oid' => $v_oid));
		    	uc_payment_enter($order_id, 'payease', $order->order_total, $order->uid, NULL, $comment);
		    	//完成销售
		    	//uc_cart_complete_sale($order);
					//注意,由于这里是异步通知,我不能直接使用uc_cart_complete_sale
					uc_order_update_status($order->order_id, uc_order_state_default('post_checkout'));
					uc_cart_empty($order->uid);
					$account = user_load($order->uid);
					module_invoke_all('uc_checkout_complete', $order, $account);
					ca_pull_trigger('uc_checkout_complete', $order, $account);
					
		    	//添加相应的订单评论
					uc_order_comment_save($order->order_id, 0, t('异步通知--买家通过首信易完成付款，付款方式：@v_pmode',array('@v_pmode' => $v_pmode)), 'order', 'payment_received');
					uc_order_comment_save($order->order_id, 0, t('异步通知--买家通过首信易完成付款，付款方式：@v_pmode',array('@v_pmode' => $v_pmode)));
				}
			}else{
				//添加相应的订单评论，付款失败
				uc_order_comment_save($order->order_id, 0, t('异步通知--买家通过首信易付款失败,原因:@reason .',array('@reason' => $v_pstring)));
			}
		}
		//如果只返回了一个订单
		else{
			//对于批量订单的发送，以v_oid字段为例，v_oid1表示本次发送的第一笔订单，v_oid2表示本次发送的第二笔订单，
			//依此类推，组成v_oid字段，中间以“|_|”组合分割，举例如下：v_oid=v_oid1|_|v_oid2|_|v_oid3|_|v_oid4|_|…………。
			//所以我们需要将返回的字符串转换为数组的形式
			//定单编号组，
			$v_oid = explode("|_|",$v_oid);
	
			//支付方式组
			$v_pmode = explode("|_|",$v_pmode);
			
			//支付状态组 1－已提交，2－支付成功，3－支付失败
			$v_pstatus = explode("|_|",$v_pstatus);
			
			//支付结果说明： 成功时（v_pstatus=1）为“支付成功”，支付被拒绝时（v_pstatus=3）为失败原因
			$v_pstring = explode("|_|",$v_pstring);
			
			watchdog('uc_payease','进入批量发送的订单,订单个数:'.$v_count);
			for ($i=0; $i<$v_count; $i++) {
				//分别处理每个订单
				_uc_payease_process_order($v_oid[$i],$v_pmode[$i],$v_pstatus[$i],$v_pstring[$i]);
			}
		}	
		//返回消息，“sent”表示成功收到支付结果信息。
		echo "sent";
	}else{
		//返回消息，“error”表示接收消息发生错误，如md5校验错。
		echo "error";
	}
	
	
}
/**
 * 从首信易到商户的即时返回接口实现，这里实现了首信易支付（v4.3）接口说明文档中的
 * 第二部分：“首信易支付订单支付结果页面返回接口（首信易支付＝＝>>商户）”
 */
function uc_payease_return() {
  $output="";
  
	//定单编号
	$v_oid = $_GET["v_oid"];
	
	//支付方式
	$v_pmode = $_GET["v_pmode"];
	
	//支付结果：1－已提交，20－支付成功，30－支付失败
	$v_pstatus = $_GET["v_pstatus"];
	
	//支付结果信息
	$v_pstring = $_GET["v_pstring"];
	
	
	
	//MD5校验信息
	$v_md5info = $_GET["v_md5info"];
	
	//订单实际支付金额
	$v_amount = $_GET["v_amount"];
	
	//订单实际支付币种
	$v_moneytype = $_GET["v_moneytype"];
	
	//MD5校验信息
	$v_md5money = $_GET["v_md5money"]; 
	
	//商城数据签名
	$v_sign = $_GET["v_sign"];
	
	//MD5私钥
	$md5key = variable_get('uc_payease_md5key', 'test');  // MD5私钥
	
	$currentpath= dirname(__FILE__);
  if(eregi('WIN',PHP_OS)){
  	$default_md5program = str_replace("\\","\\\\",$currentpath)."\\\\MD5Win32";
  }else{
  	$default_md5program = $currentpath.'/MD5Linux';
  }
  //MD5执行程序
	$uc_payease_md5program =variable_get('uc_payease_md5program', $default_md5program);
	
	//校验源字符串，v_md5money效验
	$md5src1 = $v_oid . $v_pstatus . $v_pstring . $v_pmode;
	//MD5检验结果，v_md5money效验
	// $md5sign1 = strtoupper(md5($md5src1));
	//exec($uc_payease_md5program." $md5src1 $md5key",$md5sign1,$res1);
	//exec("$uc_payease_md5program '".$md5src1."' $md5key",$md5sign1,$res1);
	exec("$uc_payease_md5program \"$md5src1\" $md5key",$md5sign1,$res1);

	//校验源字符串，v_md5money效验
	$md5src2 = $v_amount . $v_moneytype;
	//MD5检验结果，v_md5money效验
	// $md5sign2 = strtoupper(md5($md5src2));

	//exec($uc_payease_md5program." $md5src2 $md5key",$md5sign2,$res2);
	//exec("$uc_payease_md5program '".$md5src2."' $md5key",$md5sign2,$res2);
	exec("$uc_payease_md5program \"$md5src2\" $md5key",$md5sign2,$res2);
	
	//if ($v_md5info==$md5sign1[0] && $v_md5money==$md5sign2[0]) {
	//这里面我担心中文验证有问题,所以仅使用了md5money进行验证，下面的代码从理论上和上面是一致的，也就是等效的。
	//当有特殊字符时,会加密失败,此时$v_md5money为空,所以检查是否为空,以防止潜在的安全漏洞	
	if ( $v_md5money==$md5sign2[0] && !empty($v_md5money)) {
		// 商户编号
		$v_mid = variable_get('uc_payease_seller', '888');  
		
		//获取Drupal系统内部的订单ID  
		$startno = 8+strlen($v_mid)+2;
		$order_id = substr($v_oid,$startno); 
		
		//根据订单ID加载订单对象
		$order = uc_order_load($order_id);
		if($order->order_status=='payment_received'||$order->order_status=='completed'){
				//订单已经完成,此时不做操作
				$output = t('该订单已完成付款,您可以查看订单或者继续浏览其他页面');
		}else{
			//内部完成付款
			$comment = t('首信易交易ID: @v_oid', array('@v_oid' => $v_oid));
    	uc_payment_enter($order_id, 'payease', $v_amount, $order->uid, NULL, $comment);
    	//完成销售
    	//uc_cart_complete_sale($order);
    	//添加相应的订单评论
			uc_order_comment_save($order->order_id, 0, t('买家通过首信易付款@amount元.',array('@amount' => $v_amount)), 'order', 'payment_received');
			uc_order_comment_save($order->order_id, 0, t('买家通过首信易付款@amount元.',array('@amount' => $v_amount)));
			$output = uc_cart_complete_sale($order, variable_get('uc_new_customer_login', FALSE));
			
			 global $user;
			$url = 'user/'.$user->uid.'/purchased-files';
			$file_link = l("文件下载",$url);
			$output .= '<br> 如果您购买的产品包含下载资源，那么您可以在'.$file_link.'页面点击下载';
			//订单完成后要跳转到的页面
			$page = variable_get('uc_cart_checkout_complete_page', '');
		}	
		//重定向到订单完成页面
		if (!empty($page)) {
		  drupal_goto($page);
		}	
	}else{
		//出现错误的情况，为用户提供友好的提示说明
		$output = t('您的交易信息是无效的，如果你使用的是已有的返回信息的话，那么交易已经成立，你可以查看订单历史。如果因为其它原因，导致交易的失败，请检查操作，并及时联系网站管理员');
	}
	return $output;
}
/**
 * 辅助函数，用于订单的完成处理
 */
function _uc_payease_process_order($v_oid,$v_pmode,$v_pstatus,$v_pstring){
	// 商户编号
	$v_mid = variable_get('uc_payease_seller', '888');  
	//系统内部的订单ID
	$startno = 8+strlen($v_mid)+2;
	$order_id = substr($v_oid,$startno); 
	//根据订单ID加载订单对象
	$order = uc_order_load($order_id);
	if($v_pstatus ==1){
		if($order->order_status=='payment_received'||$order->order_status=='completed'){
				//订单已经完成,此时不做操作
		}else{
			//内部完成付款
			$comment = t('首信易交易ID: @v_oid', array('@v_oid' => $v_oid));
	  	uc_payment_enter($order_id, 'payease', $order->order_total, $order->uid, NULL, $comment);
	  	//完成销售
	  	//uc_cart_complete_sale($order);
			//注意,由于这里是异步通知,我不能直接使用uc_cart_complete_sale
			uc_order_update_status($order->order_id, uc_order_state_default('post_checkout'));
			uc_cart_empty($order->uid);
			$account = user_load($order->uid);
			module_invoke_all('uc_checkout_complete', $order, $account);
			ca_pull_trigger('uc_checkout_complete', $order, $account);
			
	  	//添加相应的订单评论
			uc_order_comment_save($order->order_id, 0, t('异步通知--买家通过首信易完成付款，付款方式：@v_pmode',array('@v_pmode' => $v_pmode)), 'order', 'payment_received');
			uc_order_comment_save($order->order_id, 0, t('异步通知--买家通过首信易完成付款，付款方式：@v_pmode',array('@v_pmode' => $v_pmode)));
		}
	}else{
		//添加相应的订单评论，付款失败
		uc_order_comment_save($order->order_id, 0, t('异步通知--买家通过首信易付款失败,原因:@reason .',array('@reason' => $v_pstring)));
	}
}

/**
 * Payease 的快速购买回调函数
 */
function payease_quickbuy(){
	$output ="";
	if(empty($_SESSION['cart_order'])){
		 drupal_goto('cart');
	}else{
		drupal_add_js(drupal_get_path('module', 'uc_payease') .'/uc_payease.js');
		$output .=t('订单已经生成，订单ID为@order_id,您需要使用首信易(Payease)付款后，订单才能完成，您需要点击下面的提交订单按钮，从而转到首信易的支付页面。',array('@order_id'=>$_SESSION['cart_order']));
		$order = uc_order_load($_SESSION['cart_order']);
		$output .= drupal_get_form('uc_payease_form',$order);
	}

	return $output;
}