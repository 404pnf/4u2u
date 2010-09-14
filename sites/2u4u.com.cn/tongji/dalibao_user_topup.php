<?php
require 'connect-shop.php';

$name = urlencode("大礼包兑换用户充值使用的图书统计");
header("Content-type:application/vnd.ms-excel;charset:utf-8"); 
header("Content-Disposition:filename=$name.xls"); 
header("Pragma: no-cache");
header("Expires: 0");
echo "<TABLE height=45 cellSpacing=0 borderColorDark=#ffffff width='100%'  
bgColor=#ffffff borderColorLight=#c0c0c0 border=1><TBODY><tr><td align='center'>图书名</td>
	 <td align='center' >充值次数</td></tr>";

$sql = "SELECT tp.emno,count(tp.emno) num 
FROM 2u4u.`topup` tp 
LEFT JOIN shop.`uc_orders` uo ON tp.uid=uo.uid 
WHERE uo.order_status IN ('payment_received','completed') AND uo.order_total >500 AND uo.order_id>56 AND uo.uid>1 
GROUP BY tp.emno ORDER BY num DESC";
$rs = mysql_query($sql);
while($row = mysql_fetch_object($rs)){
//	$query = "SELECT field_erp_shuming_value FROM ebook.`content_type_erp` WHERE `field_erp_wuliaohao_value` LIKE '$row->emno' ORDER BY vid DESC LIMIT 1 ";
$query = "SELECT `name` FROM `book_info` WHERE `sku`=".$row->emno;	
 $erp = mysql_fetch_object(mysql_query($query));
	if(strlen($erp->name)>2)
	       $title = $erp->name;
	else  
	       $title = $row->emno;	              	

echo "<tr><td align='left'>".$title."</td><td>".$row->num."</td></tr>";

}
echo " </TBODY> </TABLE>"; 
?>
