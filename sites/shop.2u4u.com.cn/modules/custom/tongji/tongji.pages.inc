<?php
// $Id$

//统计回调函数
function tongji_products_downloads(){
	$output = "";
	$sql = "SELECT uop.title,uop.nid,sum(uop.qty) as total_buy, sum(ufu.accessed) as access_times ";
	$sql .= "FROM {uc_order_products} uop ";
	$sql .= "LEFT JOIN {node} n ON uop.nid = n.nid ";
	$sql .= "LEFT JOIN {uc_product_features} upf ON upf.nid = uop.nid ";
	$sql .= "LEFT JOIN {uc_file_users} ufu ON ufu.pfid = upf.pfid ";
	$sql .= "WHERE n.nid is not NULL ";
	$sql .= "GROUP BY uop.nid ";
	$sql .= "ORDER BY total_buy DESC";
	$pager_num = 0;
	$count_sql = "SELECT COUNT(*) FROM (SELECT count(uop.nid) FROM uc_order_products uop  LEFT JOIN node n ON uop.nid = n.nid WHERE n.nid is not NULL GROUP BY uop.nid) as tongjitotal ";
	//$total_result =db_result(db_query($count_sql));
	//$output .= "total_result:".$total_result;
	$result = pager_query($sql, 50, $pager_num, $count_sql);
	$header = array("产品名称","购买次数","下载次数");
	//$header = array("用户","邀请人数");
	$ta = array('id' => 'tongji-products-downloads-table', 'align' => 'center');
	$trows = array();
	while($data = db_fetch_object($result)){
		$trows[] = array(
			array('data'=>l($data->title,'node/'.$data->nid),'valign'=>'top'),
			array('data'=>$data->total_buy,'valign'=>'top'),
			array('data'=>$data->access_times,'valign'=>'top'),
			//array('data'=>l('删除','invite/delete/'.$data->invite_id),'valign'=>'top'),
		);
	}

	$output .= theme('table', $header, $trows, $ta);
	$output .= theme('pager', NULL, 50, $pager_num);
 // global $pager_page_array, $pager_total;

  //print_r($pager_total);
	// print_r($pager_page_array);
	 
	return  $output;
}