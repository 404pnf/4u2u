<?php
// $Id$

/**
 * 大学英语四级区块的主题函数
 */
function theme_egscontent_CET4_block(){
	$output = '  	<div class="dxyy_lv4_title"></div>
<div class="dxyy_lv4_content">
   <ul>';
	
	//egscontent(模板or试卷,分类id,个数)
	$moduleresult = egscontent('module_list',19,1);
	$paperresult = egscontent('paper_list', 1,4);
	$output .= $moduleresult;
	$output .= $paperresult;
	
	if($moduleresult == null && $paperresult == null)
		$output .='</ul></div>';		
	else
		$output .='</ul>
			<div class="dxyy_lv4_more"><a href="http://test.2u4u.com.cn/html/www/main.html?op=paper_list&stid=19&tid=1">>>更多</a></div>
		</div>';

	
	return $output;
}


/**
 * 大学英语六级区块的主题函数
 */
function theme_egscontent_CET6_block(){
	$output = '<div class="dxyy_lv6_title"></div>
					<div class="dxyy_lv6_content">
  	 					<ul>';

	//egscontent(模板or试卷,分类id,个数)
	$moduleresult = egscontent('module_list',20,1);
	$paperresult = egscontent('paper_list', 4,4);
	$output .= $moduleresult;
	$output .= $paperresult;
	
	if($moduleresult == null && $paperresult == null)
		$output .='</ul></div>';		
	else
		$output .='</ul>
			 <div class="dxyy_lv6_more"><a href="http://test.2u4u.com.cn/html/www/main.html?op=paper_list&stid=20&tid=4">>>更多</a></div>
			</div>';
	
	return $output;
}


/**
 * 英语专业四级区块的主题函数
 */
function theme_egscontent_TEM4_block(){
	$output = '<div class="zy_pf4_title"></div>
		<div class="zy_pf4_content">
		 <ul>';
	
	//egscontent(模板or试卷,分类id,个数)
	$moduleresult = egscontent('module_list',18,1);
	$paperresult = egscontent('paper_list', 21,4);
	
	$output .= $moduleresult;
	$output .= $paperresult;
	
	
	if($moduleresult == null && $paperresult == null)
		$output .='</ul></div>';		
	else
		$output .='</ul>
			<div class="dxyy_lv4_more"><a href="http://test.2u4u.com.cn/html/www/main.html?op=paper_list&stid=18&tid=21">>>更多</a></div>
		</div>';
	return $output;
}


/**
 * 英语专业八级区块的主题函数
 */
function theme_egscontent_TEM8_block(){
	$output = '<div class="zy_pf8_title"></div>
		<div class="zy_pf8_content">
		 <ul>';

	//egscontent(模板or试卷,分类id,个数)
	$moduleresult = egscontent('module_list',23,1);
	$paperresult = egscontent('paper_list', 22,4);
	
	$output .= $moduleresult;
	$output .= $paperresult;
	
	if($moduleresult == null && $paperresult == null)
		$output .='</ul></div>';		
	else
		$output .='</ul>
			 <div class="zy_pf8_more"><a href="http://test.2u4u.com.cn/html/www/main.html?op=paper_list&stid=23&tid=22">>>更多</a></div>
			</div>';
		
	return $output;
}


/**
 * 高校英语应用能力考试主题函数
 */
function theme_egscontent_PRETCO_block(){
	$output = '<div class="yingyong_title"></div>
<div class="yingyong_content">
 <ul>';
	
	//egscontent(模板or试卷,分类id,个数)
	$moduleresult = egscontent('module_list',26,2);
	$paperresult = egscontent('paper_list', 25,3);
	$output .= $moduleresult;
	$output .= $paperresult;
	
	if($moduleresult == null && $paperresult == null)
		$output .='</ul></div>';		
	else
		$output .='</ul>
			<div class="yingyong_more"><a href="http://test.2u4u.com.cn/html/www/main.html?op=paper_list&stid=26&tid=25">>>更多</a></div>
		</div>';
	
	
	return $output;
}


/**
 * 全国英语等级考试主题函数
 */
function theme_egscontent_PETS_block(){
	$output = '<div class="quanguo_title"></div>
<div class="quanguo_content">
 <ul>';

	//egscontent(模板or试卷,分类id,个数)
	$moduleresult = egscontent('module_list',24,5);
	//$paperresult = egscontent('paper_list', 4,4);
	$output .= $moduleresult;
	//$output .= $paperresult;
	
	if($moduleresult == null && $paperresult == null)
		$output .='</ul></div>';		
	else
		$output .='</ul>
			 <div class="quanguo_more"><a href="http://test.2u4u.com.cn/html/www/main.html?op=paper_list&stid=24">>>更多</a></div>
			</div>';
	
		
	return $output;
}



 
/**
 * 四级得分排行 区块的主题函数
 */
function theme_egscontent_userscore_CET4_block(){
	$output = '';
	//egsUserScore_byTid(分类id,个数)
	$output .= egsUserScore_byTid(19);
	
	return $output;
}


/**
 * 六级得分排行 区块的主题函数
 */
function theme_egscontent_userscore_CET6_block(){
	$output = '';
	//egsUserScore_byTid(分类id,个数)
	$output .= egsUserScore_byTid(20);
	
	return $output;
}

/**
 * 专四得分排行 区块的主题函数
 */
function theme_egscontent_userscore_TEM4_block(){
	$output = '';
	//egsUserScore_byTid(分类id,个数)
	$output .= egsUserScore_byTid(21);
	
	return $output;
}


/**
 * 专八得分排行 区块的主题函数
 */
function theme_egscontent_userscore_TEM8_block(){
	$output = '';
	//egsUserScore_byTid(分类id,个数)
	$output .= egsUserScore_byTid(22);
	
	return $output;
}

/**
 * 高校英语应用能力考试得分排行 区块的主题函数
 */
function theme_egscontent_userscore_PRETCO_block(){
	$output = '';
	//egsUserScore_byTid(分类id,个数)
	$output .= egsUserScore_byTid(25);
	
	return $output;
}


/**
 * 全国英语等级考试得分排行 区块的主题函数
 */
function theme_egscontent_userscore_PETS_block(){
	$output = '';
	//egsUserScore_byTid(分类id,个数)
	$output .= egsUserScore_byTid(24);
	
	return $output;
	//return null;
}


/**
 * 专项训练得分排行 区块的主题函数
 */
function theme_egscontent_userscore_zhuanxiang_block(){
	$output = '';
	//egsUserScore_byTid(分类id,个数)
	$output .= egsUserScore_byTid(14);
	
	return $output;
}


/**
 * 英语水平定位测试得分排行 区块的主题函数
 */
function theme_egscontent_userscore_shuipin_block(){
	$output = '';
	//egsUserScore_byTid(分类id,个数)
	$output .= egsUserScore_byTid(10);
	
	return $output;
	//return null;
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



/*
 * EGS 用户得分排行榜
 * @author whx 
 *
 */
	/*
		# 1: "四级真题"
		# 4: "六级真题"
		# 5: "GMAT考试"
	*/
	
	
function egsUserScore_byTid($tid = 1,$num = 7){
	
	//$url = 'http://test.2u4u.com.cn/html/egs/index.php?type=simple&op=exam';
	
	
	$content = '<div class="user_score_content"><table ><tr><th class="user_name">用户</th><th class="user_score">分数</th> <th class="user_rate">正确率</th></tr>';
	
	$url = 'http://test.2u4u.com.cn/html/egs/index.php?op=user_rate_rank&id='.$tid.'&num='.$num;
	$result = getURLjSON($url);
	
	if($result != null && $result != ''){
		$status = $result -> status;
		//$list = $result->list;
		$list = isset($result->listcontent) ? $result->listcontent : array(); 
		 
		if($status == 1){
			foreach ( $list as $index => $item ) {
				$rate = 0;
				//, $name = '', $id = 0, $score = 0, $time = '';
				$rate = number_format($item -> rate * 100,2).'%';
				$score = number_format($item -> score);
				$time = $item -> time_end;
				$info = $item -> info;
				foreach ( $info as $info_id => $info_name ) {
					$id = $info_id;
					$name = $info_name;
					if(strlen($info_name)>12)
						$name = substr($info_name,0,9).'⋯';
					
				}
				$content .='<tr ><td class="user_name">'.$name.'</td><td class="user_score">'.$score.'</td><td class="user_rate">'.$rate.'</td></tr>';
			}
		}
		else if($status == 0){
			$content .='<tr><td class="noresult" colspan = 3>还没有成绩</td></tr>';
		}
	}
	else
		$content .='';
	
	
	$content .='</table></div>';
	
	return $content;
}