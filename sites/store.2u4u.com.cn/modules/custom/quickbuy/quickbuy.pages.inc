<?php
// $Id$

/**
 * @file
 * 菜单回调函数.
 */

function quickbuy_checkout(){
	global $user;

  $items = uc_cart_get_contents();
  if (count($items) == 0 || !variable_get('uc_checkout_enabled', TRUE)) {
    drupal_goto('cart');
  }

  $context = array(
    'revision' => 'altered',
    'location' => 'minimum-subtotal',
  );
  
	 
  if (($min = uc_price(variable_get('uc_minimum_subtotal', 0), $context)) > 0) {
    $subtotal = 0;
    if (is_array($items) && count($items) > 0) {
      foreach ($items as $item) {
        $data = module_invoke($item->module, 'cart_display', $item);
        if (!empty($data)) {
          $subtotal += $data['#total'];
        }
      }
    }
    if ($subtotal < $min) {
      $context = array(
        'revision' => 'formatted-original',
        'location' => 'minimum-subtotal-message',
      );
      drupal_set_message(variable_get('uc_minimum_subtotal_text', t('The minimum order subtotal for checkout is !min.', array('!min' => uc_price($min, $context)))), 'error');
      drupal_goto('cart');
    }
  }

  // Send anonymous users to login page when anonymous checkout is disabled.
  if (!$user->uid && !variable_get('uc_checkout_anonymous', TRUE)) {
    drupal_set_message(t('You must login before you can proceed to checkout.'));
    drupal_set_message(t('If you do not have an account, you can <a href="!url">click here</a> to create one.', array('!url' => url('user/register', array('absolute' =>  TRUE)))));
    $_SESSION['checkout-redirect'] = TRUE;
    drupal_goto('user');
  }
  else {
    unset($_SESSION['checkout-redirect']);
  }
  
  /**以下内容为我添加的，用来快速的完成结算*******************************************************/
  
  //$first_node =  node_load($items[0]->nid);
  //注意在系统中,moneyable为0的商品，是积分商品，moneyable为1的商品为现金商品，积分商品和现金商品不能同时添加到购物车
  //积分商品,使用积分支付
  //if($first_node->moneyable != 1){
		$subtotal = 0;
	  if (is_array($items) && count($items) > 0) {
      foreach ($items as $item) {
        $data = module_invoke($item->module, 'cart_display', $item);
        if (!empty($data)) {
          $subtotal += $data['#total'];
        }
      }
	   }
	  //获取用户当前积分
	  //$user_points = userpoints_get_current_points($user->uid);
	  /*
	  //用户当前积分不足
	  if( $user_points <  $subtotal){
	  	drupal_set_message(t('您的积分不足,请及时充值'));
	  	drupal_goto('cart');
	  }
	   */
	  $shippable = uc_cart_is_shippable();
	 
	  //产品都为电子图书
		if(!$shippable &&  $subtotal == 0){
			// 生成订单
			 if (empty($_SESSION['cart_order'])) {
			   $order = uc_order_new($user->uid);
			   $_SESSION['cart_order'] = $order->order_id;
			 }
			  else {
			   $order = new stdClass();
			    $order->uid = $user->uid;
			    $order->order_id = $_SESSION['cart_order'];
			    $order->order_status = uc_order_state_default('in_checkout');
			 }
			 $order->products = $items;
			 $order->order_total = $subtotal;
			 uc_order_save($order);
			 
			// 扣除积分
			/*
			$pointExch	= intval(variable_get(USERPOINTS_UC_PAYMENT, 1));
			$points		= intval(((round($subtotal) * $pointExch) * (-1)));
			$description	= 'User made a purchase and paid with points (Ubercart Order ' . $order->order_id . ')'; 
		  $params = array (
				'tid' => variable_get(USERPOINTS_PAY_CATEGORY, NULL),
				'uid' => $user->uid,
				'points' => $points,
				'operation' => 'delete',
				'description' => $description,
				'entity_id' => $order->order_id,
				'entity_type' => 'Ubercart Payment',
				'moderate' => variable_get(USERPOINTS_PAY_MODERATE, 0),
			);
			userpoints_userpointsapi($params);
			*/
			//完成订单
			uc_payment_enter($order->order_id, 'quickbuy', 0, $user->uid, NULL,  t('使用快速购买0元支付完成结算.'));
			//db_query("insert into {uc_up_payment_log} (uid, oid, points) values(%d, %d, %d)",$user->uid, $order->order_id, $points);
			uc_order_update_status($order->order_id, 'payment_received');
			uc_order_update_status($order->order_id, 'completed');
			
			uc_cart_empty(uc_cart_get_id());
			$_SESSION['do_complete'] = TRUE;
			drupal_goto('quickbuy/checkout/complete');
		}
  //}
	/*
  //现金商品,使用payease系统支付
  else{
  	$shippable = uc_cart_is_shippable();
	  //产品都为电子图书
		if(!$shippable){
			$subtotal = 0;
		  if (is_array($items) && count($items) > 0) {
	      foreach ($items as $item) {
	        $data = module_invoke($item->module, 'cart_display', $item);
	        if (!empty($data)) {
	          $subtotal += $data['#total'];
	        }
	      }
		   }
			// 生成订单
			 if (empty($_SESSION['cart_order'])) {
			   $order = uc_order_new($user->uid);
			   $_SESSION['cart_order'] = $order->order_id;
			 }
			  else {
			   $order = new stdClass();
			    $order->uid = $user->uid;
			    $order->order_id = $_SESSION['cart_order'];
			    $order->order_status = uc_order_state_default('in_checkout');
			 }
			 $order->products = $items;
			 $order->order_total = $subtotal;
			 uc_order_save($order);
		  
			drupal_goto('payease/quickbuy');
		  //$order_id = intval($_SESSION['cart_order']);
		  //$_SESSION['cart_order'] = $order->order_id;
		  //$order = uc_order_load($order->order_id);
		}
  }
  */
  
	  /**以上内容为我添加的，用来快速的完成结算*******************************************************/
 
  $list = _line_item_list();
  foreach ($list as $line_item) {
    if (function_exists($line_item['callback'])) {
      $line_item['callback']('cart-preview', $items);
    }
  }
 	module_load_include('inc', 'uc_cart', 'uc_cart.pages');
  drupal_add_js(drupal_get_path('module', 'uc_cart') .'/uc_cart.js');
  $output = drupal_get_form('uc_cart_checkout_form');

  return $output;
}

function quickbuy_checkout_complete(){
	
	if (!$_SESSION['do_complete']) {
    drupal_goto('cart');
  }
   unset($_SESSION['cart_order'], $_SESSION['do_complete']);

  global $user;
  $url = 'user/'.$user->uid.'/purchased-files';
  $file_link = l("文件下载",$url);
  $output .= '使用快速购买结算成功.您可以在'.$file_link.'页面点击下载';
	//$output .= t('SUCess');
  return $output;
	
}


