<?php
// $Id$

//统计回调函数
function tongji_products_downloads_page(){
  
	$output = "";
	$output .="<div id ='tongji-form'>";
	$output .= drupal_get_form('tongji_products_downloads_form');
	$output .="</div>"; 
	
	$output .="<div id ='tongji-list'>";
	$output .= tongji_products_downloads_list();
	$output .="</div>"; 
	
	return  $output;
}
function tongji_products_downloads_list(){
  $tongji_term = $_SESSION['tongji_term'];
	//$tongji_term_array = array();
	$tongji_term_str ="";
	//print_r($tongji_term);
	if(!empty($tongji_term)){
		foreach($tongji_term as $tid){
			$term = taxonomy_get_term($tid);
			$tree = taxonomy_get_tree($term->vid, $tid);
			$tongji_term_array[] = array_merge(array($tid), array_map('_taxonomy_get_tid_from_term', $tree));
			
		}
		//$tongji_term_array = array_merge($tongji_term_array,$tongji_term);
		//$tongji_term_array_keys = array_keys($tongji_term_array);
		$args = call_user_func_array('array_merge', $tongji_term_array);
		//print_r($args);
		$tongji_term_str = implode(",",$args);
	}
	//print_r($tongji_term_str);
	if(isset($_SESSION['tongji_start_date'])){
		$tongji_start_date = $_SESSION['tongji_start_date'];
		$tongji_start_time = strtotime($tongji_start_date['year'].'-'.$tongji_start_date['month'].'-'.$tongji_start_date['day']);
	}else{
		$tongji_start_time = strtotime('2009-01-01');
	}
	if(isset($_SESSION['tongji_end_date'])){
		$tongji_end_date = $_SESSION['tongji_end_date'];
		$tongji_end_time = strtotime($tongji_end_date['year'].'-'.$tongji_end_date['month'].'-'.$tongji_end_date['day']);
	}else{
		$tongji_end_time = time();
	}
	$output = "";
	//$sql = "SELECT uop.title,uop.nid, uop.price, sum(uop.qty) as total_buy, sum(ufu.accessed) as access_times ";
	$sql = "SELECT uop.title, uop.nid, uop.price, sum(uop.qty) as total_buy, sum(uop.qty * uop.price) as total_money ";
	$sql .= "FROM {uc_order_products} uop ";
	$sql .= "LEFT JOIN {node} n ON uop.nid = n.nid ";
	$sql .= "LEFT JOIN {uc_orders} uo ON uo.order_id = uop.order_id ";
	//$sql .= "LEFT JOIN {term_node} tn ON tn.vid = n.vid ";
	
	//$sql .= "LEFT JOIN {uc_product_features} upf ON upf.nid = uop.nid ";
	//$sql .= "LEFT JOIN {uc_file_users} ufu ON ufu.pfid = upf.pfid ";
	$sql .= "WHERE n.nid is not NULL ";
	$sql .= "AND uo.order_status in ('completed','payment_received') ";
	$sql .= "AND (uo.created BETWEEN $tongji_start_time AND $tongji_end_time) ";
	//注意下面的sql语句采用了子语句的形式，它表示当前节点应该属于所给的分类，也就是至少具有一个分类（或者某一个分类的子（孙）分类）
	if(!empty($tongji_term)){
		$sql .= "AND (SELECT COUNT(*) FROM term_node tn
					WHERE tn.vid = n.vid
					AND tid in($tongji_term_str))>0 ";
	}
	
	$sql .= "GROUP BY uop.nid ";
	$sql .= "ORDER BY total_buy DESC";
	$pager_num = 0;
	//$count_sql = "SELECT COUNT(*) FROM (SELECT count(uop.nid) FROM uc_order_products uop  LEFT JOIN node n ON uop.nid = n.nid WHERE n.nid is not NULL GROUP BY uop.nid) as tongjitotal ";
	$count_sql = "SELECT COUNT(*) FROM (".$sql.") as tongjitotal ";
	//$total_result =db_result(db_query($count_sql));
	//$output .= "total_result:".$total_result;
	$result = pager_query($sql, 50, $pager_num, $count_sql);
	//$header = array("产品名称","购买次数","下载次数");
	$header = array("产品名称","总计","购买次数");
	$ta = array('id' => 'tongji-products-downloads-table', 'align' => 'center');
	$trows = array();
	$total_money = 0;
	$paid_num = 0;
	$free_num = 0;
	while($data = db_fetch_object($result)){
		$trows[] = array(
			array('data'=>l($data->title,'node/'.$data->nid),'valign'=>'top'),
			//array('data'=>number_format($data->price,2),'valign'=>'top'),
			array('data'=>$data->total_money,'valign'=>'top'),
			array('data'=>$data->total_buy,'valign'=>'top'),
			//array('data'=>$data->access_times,'valign'=>'top'),
			//array('data'=>l('删除','invite/delete/'.$data->invite_id),'valign'=>'top'),
		);
				
		$total_money += $data->total_money;			
		
		//下载次数		
		if($data->price>0){			
			$paid_num += $data->total_buy;  //收费的下载次数
		}else{
			$free_num += $data->total_buy;	 //免费下载次数		
		}
	}
	$output .="<div id='sum-total'>";
	$output .= "总收入：".$total_money."元"."付费下载：".$paid_num."免费下载：".$free_num; 
	$output .="</div>";
	$output .= theme('table', $header, $trows, $ta);
	$output .= theme('pager', NULL, 50, $pager_num);
 // global $pager_page_array, $pager_total;

  //print_r($pager_total);
	// print_r($pager_page_array);
	 
	return  $output;
}
function tongji_products_downloads_form(){
	/*
	$term_options = array(
		1,
		2,
		3,
	);
	$form['tongji_term'] = array(
		'#title' => t('分类'),
		'#type' =>'select',
		'#default_value' =>isset($_SESSION['tongji_term'])?$_SESSION['tongji_term']:'all',
		'#options' => $term_options,
	);
	*/
	$vid = 27;
	$form['tongji_term'] = taxonomy_form($vid);
	$form['tongji_term']['#default_value'] = $_SESSION['tongji_term'];
	
	$default_tongji_start_date = array();
	if(isset($_SESSION['tongji_start_date'])){
		$default_tongji_start_date = $_SESSION['tongji_start_date'];
	}else{
		$default_tongji_start_date = array(
        'month' => 1,
        'day' => 1,
        'year' => 2009,
    );
	}
	$form['tongji_start_date'] = array(
    '#title' => t('起始日期'),
    '#type' => 'date',
    '#default_value' => $default_tongji_start_date,
	);
	
	$default_tongji_end_date = array();
	if(isset($_SESSION['tongji_end_date'])){
		$default_tongji_end_date = $_SESSION['tongji_end_date'];
	}else{
		$default_tongji_end_date = array(
        'month' => format_date(time(), 'custom', 'n'),
        'day' => format_date(time(), 'custom', 'j'),
        'year' => format_date(time(), 'custom', 'Y'),
    );
	}
	$form['tongji_end_date'] = array(
    '#title' => t('截止日期'),
    '#type' => 'date',
    '#default_value' => $default_tongji_end_date,
	);
	
	$form['submit'] = array(
		'#type' =>'submit',
		'#value' => t('查询'),
	);
	return $form;
}
function tongji_products_downloads_form_submit($form,&$form_state){
	$_SESSION['tongji_term'] = $form_state['values']['tongji_term'];
	$_SESSION['tongji_start_date'] = $form_state['values']['tongji_start_date'];
	$_SESSION['tongji_end_date'] = $form_state['values']['tongji_end_date'];
	//drupal_set_message(print_r($_SESSION['tongji_term']));
}