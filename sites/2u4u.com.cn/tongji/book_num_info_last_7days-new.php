<?php
require 'connect.php';


header("Content-type:application/vnd.ms-excel;charset:utf-8"); 
header("Content-Disposition:filename=book_num_info_last_7days.xls"); 
header("Pragma: no-cache");
header("Expires: 0");


$sql = "SELECT tp.emno,count(tp.emno) as num ,bi.`name`,bi.`price` 
        FROM `topup` tp
        LEFT JOIN `book_info` bi ON bi.sku=tp.emno
        WHERE tp.time>unix_timestamp(now())-86400*7 GROUP BY tp.emno ORDER BY num desc ";


$result = @mysql_query($sql);




$table = '<TABLE height=45 cellSpacing=0 borderColorDark=#ffffff width="100%"  
bgColor=#ffffff borderColorLight=#c0c0c0 border=1> 
   <tbody>     
	 <td align="center" >书名</td>
	 	 <td align="center" >价格</td>
	 <td align="center" >物料号</td>	
	 <td align="center" >次数</td>	
</tr>'; 

while($row = mysql_fetch_array($result))
{ 

   $table .= '<tr><td align="center" >'.$row['name'].'</td>
	          <td align="center" >'.$row['price'].'</td>
	          <td align="center" >'.$row[emno].'</td>	
	          <td align="center" >'.$row[num].'</td>';
	$table .= '</tr>'; 
} 
$table .=" </TBODY> </TABLE>"; 
echo $table;

?>
