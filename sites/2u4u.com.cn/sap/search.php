<?php

//error_reporting(E_ALL);
//ini_set('display_errors', TRUE);
//ini_set('display_startup_errors', TRUE);

header("Content-type: text/html; charset=utf-8");

include('connect.php');


$order = $_POST['order'];
$sql = "SELECT shop.uc_orders.order_id as uc_id,
               sap.orders.sap as sap_id,
               shop.uc_orders.order_total as uc_total,
               shop.uc_orders.delivery_first_name as uc_name,
               shop.uc_orders.delivery_phone as uc_phone,
               shop.uc_orders.delivery_street1 as uc_street,
               shop.uc_orders.delivery_city as uc_city,
               shop.uc_orders.delivery_postal_code as uc_code,
               shop.uc_orders.created as uc_created
         FROM  shop.uc_orders,sap.orders
         WHERE shop.uc_orders.order_id = sap.orders.order
         AND sap.orders.order
         LIKE '$order'";


if(!empty($order)){
        $query1 = mysql_query($sql);
        while($row=mysql_fetch_array($query1)){
          $query2 = "SELECT nid,title,qty,price FROM `uc_order_products` WHERE order_id=$row[uc_id]";
          $res = mysql_query($query2);
          while($arr = mysql_fetch_array($res)){   //要考虑到一个订单中有多个商品
		        $query3 = "SELECT field_product_neirongtiyao_value as content FROM `content_type_product` WHERE nid=$arr[nid]";
		        $result =  mysql_fetch_array(mysql_query($query3));
		        		
           }
          //用正则去掉所有的换行,否则在js里调用不出来结果.
          $output = preg_replace("/\s/","",$result[content]);
      	  echo "<script>alert('查询结果为：\\n SAP号: ".$row[sap_id].
                                          "\\n 收货人: ".$row[uc_name].
      	                                  "\\n 内容: ".$output.
      	                                  "\\n 运送地址: ".$row[uc_city].$row[uc_street].
      	                                  "\\n 运送电话: ".$row[uc_phone].
      	                                  "\\n 订单时间: ".date("Y-m-d",$row[uc_created]).
      	                                  "');history.back();</script>";
      	
      	
         }
}else{
	      echo "<script>alert(".$order."'查询结果不存在,请检查输入是否正确!');history.back();</script>";
}


?>
