<?php
header("Content-type: text/html; charset=utf-8");
require 'connect.php';
$name = "大礼包兑换用户充值使用的图书统计";
//$name = urlencode("大礼包兑换用户充值使用的图书统计");
header("Content-type:application/vnd.ms-excel;charset:utf-8"); 
header("Content-Disposition:filename=$name.xls"); 
header("Pragma: no-cache");
header("Expires: 0");

$table =  "<TABLE height=45 cellSpacing=0 borderColorDark=#ffffff width='100%'  
bgColor=#ffffff borderColorLight=#c0c0c0 border=1><TBODY><tr><td align='center'>图书名</td>
	 <td align='center' >充值次数</td></tr>";

$sql = "SELECT uo.uid 
		FROM shop.`uc_orders` uo
		WHERE uo.order_status='completed'
		AND uo.order_total >500
		AND uo.order_id >56
		AND uo.uid >1
		GROUP BY uo.uid";

$rs = mysql_query($sql);

while($row = mysql_fetch_object($rs)){
	$uid_str .=$row->uid."," ;	
}
$uid_condition = substr($uid_str,0,-1);

$query = "SELECT tp.emno, name,count( tp.emno ) num
		FROM 2u4u.`topup` tp
		LEFT JOIN 2u4u.`book_info` bi 
		ON bi.sku=tp.emno
		WHERE tp.uid in (".$uid_condition.")
		GROUP BY tp.emno
		ORDER BY num DESC";
$result = mysql_query($query);

while($arr = mysql_fetch_object($result)){
	

	if(strlen($arr->name)>2)
	       $title = $arr->name;
	else  
	       $title = $arr->emno;	              	

$table .= "<tr><td>".$title."</td><td>".$arr->num."</td></tr>";

}
$table .= " </TBODY> </TABLE>"; 
echo $table;
?>
