<?php

/*
**  打印出最近一段时间的网站订单。 by wzs 090913
**  时间格式有两种：一是到本周一网站所有的订单（已排除前期的订单）；另一种是上一周的网站订单（周一至周日）
*/

header("Content-type: text/html; charset=utf-8");
require 'connect.php';

if(date('w')==5){
   $start = strtotime("this friday-1 week");
   $end = strtotime("this friday"); 
}else{
   $start = strtotime("last friday-1 week");
   $end = strtotime("last friday"); 
} 

 if($_GET['op']=="latest"){
 	$time = " uo.order_id>118 AND uo.created<$end ";
 	$filename = date("Ymd",$end).urlencode("订单");
 }else{
 	$time =" uo.created>=$start AND uo.created<$end ";
 	$filename = date("Ymd",$start)."-".date("Ymd",$end).urlencode("订单");
 }

	//echo date("Y-m-d",$end); 
	$sql = "SELECT uo.order_id,uo.delivery_first_name,uo.delivery_company,uo.delivery_phone,
	uo.delivery_street1,uo.delivery_city,uo.delivery_postal_code,created,up.nid,up.title,up.qty,up.price 
	FROM `uc_orders` uo  LEFT JOIN `uc_order_products` up ON up.order_id = uo.order_id
	WHERE $time AND uo.order_status='payment_received' AND uo.order_total>500";
	//echo $sql;
	$re = mysql_query($sql);
	$num = mysql_num_rows($re);
	if($num>0){
		

	header("Content-type:application/vnd.ms-excel;charset:utf-8"); 
	header("Content-Disposition:filename=$filename.xls"); 
	header("Pragma: no-cache");
	header("Expires: 0");
	
	echo ' <TABLE height=60 cellSpacing=0 borderColorDark=#ffffff width="100%"  
	bgColor=#ffffff borderColorLight=#c0c0c0 border=1> 
	   <tbody>
	      <strong>2u4u网站用户订单（'.date("Ymd",$start).'-'.date("Ymd",$end).'）</strong>	
		<tr>
		 <td align="center" >订单号</td>
		 <td align="center" >姓名</td>
		 <td align="center" >订单时间</td>	
		 <td align="center" >名称</td>	
		 <td align="center" >数量</td>	
		 <td align="center" >码洋</td>	
		 <td align="center" >兑换积分</td>	
		 <td align="center" >内容</td>
		 <td align="center" >邮寄地址</td>
		 <td align="center" >邮编</td>	
		 <td align="center" >联系电话</td>
	</tr>'; 
	
	while($row=mysql_fetch_array($re)){
		$content_new = '';
	  if($_GET['info']=='update'){  
	   	$sql2 = "UPDATE `uc_orders` SET order_status='completed' WHERE order_id='$row[order_id]' LIMIT 1";
	   	mysql_query($sql2);
	 }
		
	   	$query = "SELECT field_product_neirongtiyao_value as content,field_product_mayang_value as mayang FROM `content_type_product` WHERE nid=$row[nid] ORDER BY vid DESC LIMIT 1"; 
	   	$result =  mysql_fetch_array(mysql_query($query));
	   	if($result[mayang]>0){
	   		$content = strip_tags($result[content]);
	   		if(strpos($content,"+")!==false){
	   		   $content = substr($content,1);
               $content =preg_replace("/：.*?\+/s",";",$content); 
	   		} 
	        if(strpos($content,"1.")!==false)
                $content =substr(str_replace("1.","; ",$content),1);	

                  
       if(strpos($content,";")){
        	$book_list = explode(";",$content);
        	foreach($book_list as $value){
        			$new_value = '';
        		if(strlen($value)>2){
        		
	        		$value = trim($value);
	//        		if(strpos($value,"*)"))	
	  //      		      $value = str_replace("(*)","",$value);

	        
	        	// $new_value =preg_replace("/\(.*\)\[^\(^\)\]*$/","",$value);  	       
	        		       
	        		$new_query = "SELECT price FROM `book_info` 
	        		                    WHERE name LIKE	'".$value."%' 
	        		                    AND `sku` 
	        		                    IN (SELECT `sku` FROM `book_kc`)";
	        		
		            $new_rs = mysql_fetch_object(mysql_query($new_query));
		            if($new_rs->price>0)
	        	    $content_new .=$new_rs->price>0?$value."-".$new_rs->price.";":$value.";";
                    else{	        	
                   		if(strpos($value,"("))	
	        		       $new_value =preg_replace("/\(.*\)/","",$value);   
	        		    else        
                           $new_value = $value;
                     $new_sql = "SELECT price FROM `book_info` 
	        		                    WHERE name LIKE	'".$new_value."%' 
	        		                    AND `sku` 
	        		                    IN (SELECT `sku` FROM `book_kc`)";
	        		
		             $new_res = mysql_fetch_object(mysql_query($new_sql)); 
	        	     $content_new .=$new_res->price>0?$value."-".$new_res->price.";":$value.";";
		                                       
                    }
               }
        	} 
        	
        }
	 
       
     
       if(strpos($row[delivery_street1],$row[delivery_city]))
           $address = $row[delivery_street1].$row[delivery_company];
        else 
           $address = $row[delivery_city].$row[delivery_street1].$row[delivery_company];
       
        
	   	echo "<tr><td align='center'>".$row[order_id]."</td>";
	    echo "<td align='center'>".$row[delivery_first_name]."</td>";
	    echo "<td align='center'>".date("Ymd",$row[created])."</td>";
	    echo "<td align='center'>".$row[title]."</td>";
	    echo "<td align='center'>".intval($row[qty])."</td>";              //要考虑到订单中的商品数量
	    echo "<td align='center'>".$result[mayang]."</td>"; 	   
	    echo "<td align='center'>".intval($row[price])*intval($row[qty])."</td>";
	  	echo "<td align='center'>".$content_new."</td>";
	    echo "<td align='center'>".$address."</td>";
	   	echo "<td align='center'>".$row[delivery_postal_code]."</td>";
	   	echo "<td align='center'>".$row[delivery_phone]."</td>";
	   	echo "</tr>";
	   }	
	 }
	
}else 
    echo "上周没有订单或订单已经发出!";
    
