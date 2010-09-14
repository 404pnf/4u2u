<?php
/*
 * get user info for the celebrate
 */

require 'connect.php';

header("Content-type:application/vnd.ms-excel;charset:utf-8"); 
header("Content-Disposition:filename=book_info.xls"); 
header("Pragma: no-cache");
header("Expires: 0");


$sql = "SELECT tp.`uid`,tp.`gcode`,tp.`emno`,tp.`time`,bi.`name`,bi.`price` 
        FROM `topup` tp
        LEFT JOIN `book_info` bi ON bi.sku=tp.emno
        ORDER BY tp.`time` DESC ";
//echo $sql;

$result = @mysql_query($sql) ;

$table = ' <TABLE height=45 cellSpacing=0 borderColorDark=#ffffff width="100%"  
bgColor=#ffffff borderColorLight=#c0c0c0 border=1> 
   <tbody>     
	 <td align="center" >书名</td>
	 <td align="center" >价格</td>
	 <td align="center" >验证码</td>
	 <td align="center" >物料号</td>	
	 <td align="center" >时间</td>	
	 <td align="center" >用户id</td>
</tr>'; 

while($row = mysql_fetch_array($result))
{ 

	$table .= '<tr><td align="center" >'.$row['name'].'</td>
	           <td align="center" >'.$row['price'].'</td>
	           <td align="center" >'.$row[gcode].'</td>
	           <td align="center" >'.$row[emno].'</td>	
	           <td align="center" >'.$row[time].'</td>
	           <td align="center" >'.$row[uid].'</td>';
	$table .= '</tr>'; 
} 
	$table .=" </TBODY> </TABLE>"; 
	echo $table;

?>
