<?php

/*
**  打印出所有在网站订购过大礼包用户的信息
**  
*/

header("Content-type: text/html; charset=utf-8");
require 'connect.php';


$sql = "SELECT uid,count( uid ) AS num,delivery_first_name,delivery_company,delivery_phone,delivery_street1,delivery_city,delivery_postal_code,created FROM `uc_orders` WHERE
  order_status 	IN ('payment_received','completed') AND order_total>500 AND order_id>56 AND uid>1 GROUP BY uid ORDER BY delivery_city";

$filename = urlencode("订购大礼包用户信息");
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
	      <strong>订购大礼包用户信息</strong>	
		<tr>
	     <td align="center" >姓名</td>
		 <td align="center" >订单次数</td>	
		 <td align="center" >邮寄地址</td>
		 <td align="center" >邮编</td>	
		 <td align="center" >联系电话</td>
	</tr>'; 
	
	while($row=mysql_fetch_array($re)){

	    echo "<td align='center'>".$row[delivery_first_name]."</td>";
	  	echo "<td align='center'>".$row[num]."</td>";
	    echo "<td align='center'>".$row[delivery_city].$row[delivery_street1].$row[delivery_company]."</td>";
	   	echo "<td align='center'>".$row[delivery_postal_code]."</td>";
	   	echo "<td align='center'>".$row[delivery_phone]."</td>";
	   	echo "</tr>";
	   }	
	
}else 
    echo "没有用户信息!";
    
