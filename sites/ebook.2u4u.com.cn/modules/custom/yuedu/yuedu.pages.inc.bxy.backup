<?php

/*
 * Validate access permission before transfering the file
 */
function yuedu_transfer_page($nid, $page) {
	global $user;
	//匿名用户能够看到的内容页码的限制
	$anonymous_limit = 15;
  $node = node_load($nid);
  $preview_page = $node->field_yuedu_preview[0]['value'];
	
  $limit_flag = flag_get_flag('limit_read_percentage');
	$flag = flag_get_flag('yuedu_freebie');
	
	if ($limit_flag && $limit_flag->is_flagged($node->nid)) {
		//如果节点标记为了限制级,那么超过页码限制,就显示内容拒绝页面
		if($page > $preview_page){
			 file_transfer(file_directory_path() . '/access.ds', array ());
		}
		//对于限制级图书,如果用户不登录,对于超过匿名用户内容页码限制的页面,也显示内容拒绝页面
		elseif($user->uid ==0 && $page > $anonymous_limit){
			file_transfer(file_directory_path() . '/access.ds', array ());
		}
		//显示允许的页面
		else{
			file_transfer(file_directory_path() . '/pdf/swf/' . $nid . '/' . $page . ".ds", array ());
		}
  }
	elseif ($flag && $flag->is_flagged($node->nid)) {
		//如果是匿名用户,并且页码超过了匿名用户页码限制,那么显示内容拒绝页面
		if($user->uid ==0 && $page > $anonymous_limit){
			 file_transfer(file_directory_path() . '/access.ds', array ());
		}else{
			file_transfer(file_directory_path() . '/pdf/swf/' . $nid . '/' . $page . ".ds", array ());
		}
  }
	else{
	  if(yuedu_check_access($nid)){
	  	if (node_access('view', $node)) 
	  	{
	  		file_transfer(file_directory_path() . '/pdf/swf/' . $nid . '/' . $page . ".ds", array ());
	  	}
	  }
	  else
	  {
	  	if($page > $preview_page){
	    file_transfer(file_directory_path() . '/access.ds', array ());
	  	}
			//如果是匿名用户,并且页码超过了匿名用户页码限制,那么显示内容拒绝页面
			//通常匿名用户页码限制小于$preview_page
			elseif($user->uid == 0 && $page > $anonymous_limit){
			 file_transfer(file_directory_path() . '/access.ds', array ());
			}
	  	else{
	  		file_transfer(file_directory_path() . '/pdf/swf/' . $nid . '/' . $page . ".ds", array ());
	  	}
	  }
  }
}

/*
 * Fullscreen view
 */
function yuedu_fullscreen($nid) {
  drupal_add_css('fullscreen.css');
  $node = node_load($nid);
  $output = "<style type='text/css'>* {padding: 0;margin: 0;}</style>";
  $file = $node->field_yuedu_pdf [0];
  $path_parts = pathinfo($file ['filepath']);
  $domain = $_SERVER ['SERVER_NAME'];
  $swfUrl = "http://$domain/sites/$domain/files/Yuedu.swf";
  $swfDir = file_directory_path() . '/pdf/swf/' . $node->nid;
  $number = count(scandir($swfDir)) - 2;
  $contentUrl = "http://$domain/yuedu/doc/" . $node->nid . '/';
  foreach ($node->field_yuedu_mp3 as $audio) {
    $audio_html .= "<a href=/" . $audio ['filepath'] . '>' . $audio ['filename'] . '</a> ';
  }
  $output .= $audio_html;
  $output .= '<script type="text/javascript" src="http://mediaplayer.yahoo.com/js"></script>';
  $output .= swf($swfUrl, array (
    'params' => array (
    'height' => '100%', 'width' => '100%', 'wmode' => 'window', 'allowscriptaccess' => 'samedomain', 'wmode' => 'window' 
  ), 'flashvars' => array (
    'num' => $number - 1, 'url' => $contentUrl, 'name' => $path_parts ['filename'], 'nid' => $node->nid 
  ) 
  ));
  
  print $output;
}

function yuedu_buy_access($nid){
	global $user;
	$node = node_load($nid);
	if($node->type =='ebook'){
		$sku = $node->field_yuedu_sku[0]['value'];
		$price = $node->field_yuedu_pricebypoints[0]['value'];
		if($user->uid <= 0)
		{
			drupal_set_message('请先登录');
		}
		$hasAccess = yuedu_check_access($nid);
		if($hasAccess)
		{
			drupal_set_message('您已拥有访问权限，无需重复购买');
		}else
		{
			$totalPoints = userpoints_get_current_points();
			if($price>$totalPoints){
				drupal_set_message('您的积分不足');
			}else{
				userpoints_userpointsapi(-$price);
				if($price>0){
                                  $sql = "insert into {yuedu_transaction} (nid, uid, sku, time,points) values(%d,%d,%d,%d,%d)";
			          db_query($sql,$nid,$user->uid,$sku,time(),$price);
				  drupal_set_message("成功购买，扣除积分 $price");
                               }
				$flag = flag_get_flag('yuedu_buy_this_book') or die('no "bookmarks" flag defined');
				$flag->flag('flag', $nid); 
			}
		}
	}
	return drupal_goto("node/$nid");
}

