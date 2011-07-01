<?php
// $Id$

/**
 * 我的悠游区块的主题函数
 */
 function theme_my2u4u_my_account_block(){
	$output = "";
	global $user;
	$uid = $user->uid;
	if(arg(0)=='user'&& arg(1)>0){
		$uid = arg(1);
	}
	$name = $user->name;
        db_set_active('discuz');
	$sql = "SELECT uid, username, extcredits2  FROM `uu_members` where username='%s' ";  //%s占位符
	$rs = db_query($sql,$name);
        db_set_active('default');
        while($row = db_fetch_object($rs)){	
	        $dz_money= $row->extcredits2;
        }	
	$output .= '<ul class="my_content">';
		$output .= '<li class="user_points">'.  t('悠游积分：').userpoints_get_current_points($uid). '</li>';
		$output .= '<li class="discuz_money">'.  t('论坛金钱：').$dz_money. '</li>';
		$output .= '<li class="chongzhi">'.  l(t('积分充值'),'user/'.$uid.'/chongzhi') . '</li>';
		$output .= '<li class="buy_points">'.  l(t('积分购买'),'user/'.$uid.'/buyuserpoints'). '</li>';
		$output .= '<li class="discuz_exchange">'.  l(t('积分兑换'),'user/'.$uid.'/discuz'). '</li>';
		$output .= '<li class="mypoints">'.  l(t('积分记录'),'user/'.$uid.'/mypoints'). '</li>';
		$output .= '<li class="user_invites">'.  l(t('邀请积分'),'user/'.$uid.'/invites'). '</li>';
	$output .= '</ul>';
	
	return $output;
}
 
 /*
function theme_my2u4u_my_account_block(){
	$output = "";
	if(arg(0)=='user'&& arg(1)>0){
		$uid = arg(1);
		$output .= '<ul class="my_content">';
		$output .= '<li>'.  t('悠游积分：').userpoints_get_current_points($uid). '</li>';
		$output .= '<li>'.  t('论坛金钱：').$uid. '</li>';
		$output .= '<li>'.  l(t('积分充值'),'user/'.$uid.'/chongzhi') . '</li>';
		$output .= '<li>'.  l(t('积分购买'),'user/'.$uid.'/buyuserpoints'). '</li>';
		$output .= '<li>'.  l(t('积分兑换'),'user/'.$uid.'/discuz'). '</li>';
		$output .= '<li>'.  l(t('积分记录'),'user/'.$uid.'/mypoints'). '</li>';
		$output .= '<li>'.  l(t('邀请积分'),'user/'.$uid.'/invites'). '</li>';
		$output .= '</ul>';
	}
	return $output;
}

*/
/**
 * 我的图书馆区块的主题函数
 */
function theme_my2u4u_my_ebooks_block(){
	$output = "";
	global $user;
	$uid = $user->uid;
	
	if(arg(0)=='user'&& arg(1)>0){
		$uid = arg(1);
	}
	$output .= '<ul class="my_content">';
		$output .= '<li class="boughtbooks">'.l(t('购买的图书'),'user/'.$uid.'/boughtbooks'). '</li>';
		$output .= '<li class="readbooks">'.l(t('看过的图书'),'user/'.$uid.'/readbooks'). '</li>';
		$output .= '<li class="favoritebooks">' .l(t('收藏的图书'),'user/'.$uid.'/favoritebooks'). '</li>';
		$output .= '<li class="recommendbooks">' .l(t('推荐的图书'),'user/'.$uid.'/recommendbooks'). '</li>';
	$output .= '</ul>';
	return $output;
}

/**
 * 我的多媒体课堂区块的主题函数
 */
function theme_my2u4u_my_videos_block(){
	$output = "";
	global $user;
	$uid = $user->uid;
	
	if(arg(0)=='user'&& arg(1)>0){
		$uid = arg(1);
	}
	$output .= '<ul class="my_content">';
		$output .= '<li class="boughtvideos">'.l(t('购买的视频'),'user/'.$uid.'/boughtvideos'). '</li>';
		$output .= '<li class="readvideos">'.l(t('看过的视频'),'user/'.$uid.'/readvideos'). '</li>';
		$output .= '<li class="favoritevideos">'.l(t('收藏的视频'),'user/'.$uid.'/favoritevideos'). '</li>';
		$output .= '<li class="recommendvideos">'.l(t('推荐的视频'),'user/'.$uid.'/recommendvideos'). '</li>';
	$output .= '</ul>';
	return $output;
}

/**
 * 我的测试中心区块的主题函数
 */
function theme_my2u4u_my_quizs_block(){
	$output = "";
	global $user;
	$uid = $user->uid;
	
	if(arg(0)=='user'&& arg(1)>0){
		$uid = arg(1);
	}
	$output .= '<ul class="my_content">';
		$output .= '<li class="donequizs">'.l(t('做过的测试'),'user/'.$uid.'/donequizs'). '</li>';
		$output .= '<li class="recommendquizs">'.l(t('推荐的测试'),'user/'.$uid.'/recommendquizs'). '</li>';
	$output .= '</ul>';
	return $output;
}

/**
 * 我的问答区块的主题函数
 */
function theme_my2u4u_my_answers_block(){
	$output = "";
	global $user;
	$uid = $user->uid;
	
	if(arg(0)=='user'&& arg(1)>0){
		$uid = arg(1);
	}
	
	$output .= '<ul class="my_content">';
		$output .= '<li class="questions">'.l(t('我的提问'),'user/'.$uid.'/questions'). '</li>';
		$output .= '<li class="answers">'.l(t('我的回答'),'user/'.$uid.'/answers'). '</li>';
	$output .= '</ul>';
	return $output;
}


/**
 * 我的订单区块的主题函数
 */
function theme_my2u4u_my_orders_block(){
	$output = "";
	global $user;
	$uid = $user->uid;
	
	if(arg(0)=='user'&& arg(1)>0){
		$uid = arg(1);
	}
	//$user = user_load($uid);
		$output .= '<ul class="my_content my_account_info">';
		$output .= '<li class="unfinishedorders">'.l(t('未结算订单'),'user/'.$uid.'/unfinishedorders'). '</li>';
		$output .= '<li class="orders">'.l(t('订单记录'),'user/'.$uid.'/orders'). '</li>';
	$output .= '</ul>';
	return $output;
}


/**
 * 我的积分回调函数
 */
function  my2u4u_my_pionts_page($user){
	$output ='<div id = "my_points">';
	$output .= '<div id="my-points-total-points">';
	//$output .= '您的当前总积分：';
	$output .= '您的当前总积分：'.userpoints_get_current_points($user->uid);
	$output.=$GLOBALS['user']->uid;
	$output .= "</div>";
	
$header = array(
    array('data' => t('积分'), 'field' => 'points'),
    array('data' => t('日期'), 'field' => 'time_stamp', 'sort' => 'desc'),
    array('data' => t('操作'), 'field' => 'operation'),
    array('data' => t('描述'), 'field' => 'description'),
  );
  $sql  = "SELECT p.points, p.time_stamp, p.operation, p.description, p.status, p.tid, t.name as cat , p.entity_id, p.entity_type 
           FROM {userpoints_txn} p 
           LEFT JOIN {term_data} t on p.tid = t.tid
           WHERE p.uid = %d";
					 
  $sql .= tablesort_sql($header);
  $pager_limit = variable_get(USERPOINTS_REPORT_LIMIT, 10);
  $result = pager_query($sql, $pager_limit, 0, NULL, $user->uid);
 
  $num_rows = 0;
  while ($row = db_fetch_object($result)) {
    $num_rows++;
    //$status = $stati[$row->status];
    
    if ($row->description) {
      $description = $row->description;
    }
    else {
      $description = t('None');
    }
 
    $rows[] = array(
        array('data' => $row->points, 'align' => 'center'),
        array('data' => format_date($row->time_stamp, 'small'), 'align' => 'center'),
        array('data' => $row->operation),
        array('data' => $description),
    );
  	if ($num_rows <= 0) {
    	$rows[] = array(
          array('data' => t('您还没有挣取任何积分'), 'colspan' => 4, 'align' => 'center')
    			);
  	}
  }
	$output  .= theme('table', $header, $rows);
	$output .= theme('pager', NULL, $pager_limit, 0);
	
	$output .='</div>';
	return $output;
}

/**
 * 积分充值回调函数
 */
function  my2u4u_my_chongzhi_page($user){
	$node = node_load(1); 	
	$output ='<div id = "my_chongzhi">';
	$output .= node_view($node);
	$output .='</div>';
	return $output;
}


/**
 * 积分购买回调函数
 */
function  my2u4u_my_buyuserpoints_page($user){
	$node = node_load(2); 	
	$output ='<div id = "my_buyuserpoints">';
	$output .= node_view($node);
	$output .='</div>';
	return $output;
}


/**
 * 购买的图书回调函数
 */
function  my2u4u_my_boughtbooks_page($user){
	$output ='<div id = "my_boughtbooks">';
	
	$output .= get_views_content('ebook','flag_bookmarks_tab','block_2',$user->uid);

	$output .='</div>';
	return $output;
}
/**
 * 看过的图书回调函数
 */
function  my2u4u_my_readbooks_page($user){
	$output ='<div id = "my_readbooks">';
	
	$output .= get_views_content('ebook','flag_bookmarks_tab','block_3',$user->uid);
	$output .='</div>';
	return $output;
}
/**
 * 收藏的图书回调函数
 */
function  my2u4u_my_favoritebooks_page($user){
	$output ='<div id = "my_favoritebooks">';
	$output .= get_views_content('ebook','flag_bookmarks_tab','block_1',$user->uid);
	$output .='</div>';
	return $output;
}
/**
 * 推荐的图书回调函数
 */
function  my2u4u_my_recommendbooks_page($user){
	$output ='<div id = "my_recommendbooks">';
	$output .= get_views_content('ebook','whx_frontpage','attachment_1');
	$output .='</div>';
	return $output;
}


/**
 * 购买的视频回调函数
 */
function  my2u4u_my_boughtvideos_page($user){
	$output ='<div id = "my_boughtvideos">';
	//$output .= get_views_content('video','flag_bookmarks_tab','block_1',$user->uid);

	$video_content = xmlrpc('http://video.2u4u.com.cn/xmlrpc.php', 'myvideo.get', $user->uid);
	$output.= $video_content;
	$output .='</div>';
	return $output;
}
/**
 * 看过的视频回调函数
 */
function  my2u4u_my_readvideos_page($user){
	$output ='<div id = "my_readvideos">';
	
	$output .= get_views_content('video','flag_bookmarks_tab','block_2',$user->uid);
	$output .='</div>';
	return $output;
}
/**
 * 收藏的视频回调函数
 */
function  my2u4u_my_favoritevideos_page($user){
	$output ='<div id = "my_favoritevideos">';
	
	$output .= get_views_content('video','flag_bookmarks_tab','block_1',$user->uid);
	$output .='</div>';
	return $output;
}
/**
 * 推荐的视频回调函数
 */
function  my2u4u_my_recommendvideos_page($user){
	$output ='<div id = "my_recommendvideos">';
	$output .= get_views_content('video','whx_frontpage','attachment_6');
	$output .='</div>';
	return $output;
}


/**
 * 做过的测试回调函数
 */
function  my2u4u_my_donequizs_page($user){
	$output ='<div id = "my_donequizs">';
	$output .= '<div class = "egs user_result"><img src = "/sites/my.2u4u.com.cn/themes/stable/css/images/redjiantou.gif"/>&nbsp;&nbsp;<a href = "http://test.2u4u.com.cn/html/www/main.html?op=user_result">查看考试测试历史记录</a></div>';
	$quiz_content = xmlrpc('http://quiz.2u4u.com.cn/xmlrpc.php', 'myquiz.get', $user->uid);
	$output.= $quiz_content;
	$output .='</div>';
	return $output;
}
/**
 * 推荐的测试回调函数
 */
function  my2u4u_my_recommendquizs_page($user){

	$output ='<div id = "my_recommendquizs">';
		$title_1978 = "<div class='block_title title'> 主题测试 </div>";
		$title_8587 = "<div class='block_title title'> 考试测试 </div>";
		$title_1977 = "<div class='block_title title'> 趣味测试 </div>";
		
		$content_1978 = get_views_content('quiz','whx_frontpage','block_1',1978);
		//$content_8587 = get_views_content('quiz','whx_frontpage','block_1',8587);
		
		$content_1977 = get_views_content('quiz','whx_frontpage','block_1',1977);
		
		$content_8587 = '';
		$content_8587 .='<div class="floatl">';
		$content_8587 .= '<div class="dxyy_lv4_content"><ul>'.egscontent('paper_list', 1,2).'</ul></div>';	//四级
	   $content_8587 .= '<div class="dxyy_lv4_content"> <ul>'.egscontent('paper_list', 4,2).'</ul></div>';	//六级
	   $content_8587 .='</div><div class="floatl">';
	   
	   $content_8587 .= '<div class="dxyy_lv4_content"> <ul>'.egscontent('paper_list', 21,2).'</ul></div>';	//专六
	   $content_8587 .= '<div class="dxyy_lv4_content"> <ul>'.egscontent('paper_list', 22,2).'</ul></div>';	//专八
	   
	   $content_8587 .='</div><div class="floatl">';
	   $content_8587 .= '<div class="dxyy_lv4_content"> <ul>'.egscontent('paper_list', 25,2).'</ul></div>';	//PRETCO高校英语应用能力
		 $content_8587 .='</div>';
		 
	$output .= "<div class='quiz_content quiz_content_8587'>".$title_8587.$content_8587."</div>";	
	$output .= "<div class='quiz_content quiz_content_1978'>".$title_1978.$content_1978."</div>";
	
	$output .= "<div class='quiz_content quiz_content_1977'>".$title_1977.$content_1977."</div>";
	
	$output .='</div>';
	return $output;
	
	
}


/**
 * 提出的问题回调函数
 */
function  my2u4u_my_questions_page($user){
	$output ='<div id = "my_questions">';
	$output .= get_views_content('answer','my_answer','page_4',$user->uid);
	$output .='</div>';
	return $output;
}
/**
 * 回复的问题回调函数
 */
function  my2u4u_my_answers_page($user){
	$output ='<div id = "my_answers">';
	$output .= get_views_content('answer','my_answer','attachment_1',$user->uid);
	$output .='</div>';
	return $output;
}

/**
 * 未结算的订单回调函数
 */
function  my2u4u_my_unfinishedorders_page($user){
	$output ='<div id = "my_unfinishedorders">';
	$output .= get_views_content('store','service_orders','default',$user->uid);
	$output .='</div>';
	return $output;
}
/**
 * 订单记录回调函数
 */
function  my2u4u_my_orders_page($user){
	$output ='<div id = "my_orders">';
	$output .= get_views_content('store','service_orders','block_1',$user->uid);
	$output .='</div>';
	return $output;
}


function get_views_content($sites,$view_name,$display_id){
	$args=func_get_args(); 
	array_shift($args); //remove $sites
	array_shift($args);	//remove $view_name
	if(count($args)){
		array_shift($args);	//remove $display_id
	}
	$output='';
	$views_content=xmlrpc('http://'.$sites.'.2u4u.com.cn/xmlrpc.php','views.get',$view_name,$display_id,$args,0,0,true);
	$output.=$views_content[0];
	
	return $output;
}



/**
 * 我的UCHOME主题函数
 */
function theme_my2u4u_my_uchome_block(){
        $discuz_url = "http://u.2u4u.com.cn/"; 
	global $user;
	$uid = $user->uid;	
	if($uid > 0) $name = $user->name;
	db_set_active('uchome');
	$sql = "SELECT uid, credit, experience, viewnum, username  FROM `uchome_space` where username='%s' ";
	$rs = db_query($sql,$name);
        db_set_active('default');
	DEFINE('UC_API',"http://u.2u4u.com.cn/ucenter");
	while($row = db_fetch_object($rs)){
    	  $photo = '';
    	  $photo = ckavatar($row->uid) ? avatar($row->uid, 'big',true) : UC_API.'/images/noavatar_big.gif';
    	  $content .= "<div class='avt'><a href='".$discuz_url."home/space.php?uid=".$row->uid."'  target='_blank'><img src ='".$photo."'></a></div>";
   	  $content .= "<div class='jibenxinxi'><div class='myname'><a href='".$discuz_url."home/space.php?uid=".$row->uid."'  target='_blank'>".$row->username."</a></div>";
	  $content .= "<div class='personal-info'>"."我的经验:".$row->experience ."我的访问次数:".$row->viewnum."</div>";
	  $content .= "<div class='myadress'>我的主页:<a href='".$discuz_url."home/space.php?uid=".$row->uid."'  target='_blank'>".$discuz_url."home/?".$row->uid."</a></div></div>";
       }      
	  return $content;	    
}		    


/*
 * PHP 获取url输出的jSON内容，解决jSON跨域访问问题
 * @author whx 
 *
 */
function getURLjSON($url){
//根据URL获取jSON数据

	$result	= '';
	try{
		$fp=fopen($url,'r');
		stream_get_meta_data($fp);
		while(!feof($fp)){
			$result.=fgets($fp,1024);
		}
		
		fclose($fp);
		$result = json_decode($result);
  	}
  	catch(Exception $e){
  		return 'Message: ' .$e->getMessage();
  	}
	/**/
	
	return $result;
}



/*
 * EGS 试卷或者模板列表
 * @author whx 
 *
 */

function egscontent($type = 'module_list', $id = '',$num = 5) {

//判断获取模板或者试卷列表的URL

	if($type == 'module_list')
		$url = 'http://test.2u4u.com.cn/html/egs/index.php?op=exam_structure_list&type=simple&num='.$num.'&id='.$id;
		//$url = 'http://test.2u4u.com.cn/html/egs/index.php?op=exam_structure_list&type=simple&num=5';
	else if($type == 'paper_list')
		$url = 'http://test.2u4u.com.cn/html/egs/index.php?op=paper_info_by_term_id&type=simple&num='.$num.'&id='.$id;
  	else 
  		$url = 'http://test.2u4u.com.cn/html/egs/index.php?op=exam_structure_list&type=simple&num='.$num.'&id='.$id;
  	
  	$result = getURLjSON($url);
  	
if($result != null && $result != ''){

//处理获取的jSON数据，输出到页面上。输出的链接地址在EGS系统中处理显示结果  	
  	if($type == 'module_list')
  		foreach ( $result as $index => $value ) {
  		
  			$sid = $value -> sid;
  			$name = $value -> title;
			$output .= ' <li><a href="http://test.2u4u.com.cn/html/www/main.html?op=create_paper_by_module&id='.$sid.'" >'.$name. "</a></li>";
			//$output .= ' <li><a href="http://test.2u4u.com.cn/html/www/index.html?op=create_paper_by_module&id='.$sid.'" onclick="egs_paper('.$sid.')" >'.$name. "</a></li>";
		}
	else if($type == 'paper_list')
		foreach ( $result as  $index => $value ) {
  			$sid = $value-> paper_id;
  			$name = $value-> paper_name;
			$output .= ' <li><a href="http://test.2u4u.com.cn/html/www/main.html?op=paper_info&id='.$sid.'" >'.$name. "</a></li>";
		}

	return $output;
}
else
	return null;
/*
return 'abc';*/
}




