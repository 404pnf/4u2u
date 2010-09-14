<?php
require 'connect.php';


header("Content-type:application/vnd.ms-excel;charset:utf-8"); 
header("Content-Disposition:filename=book_num_info_last_7days.xls"); 
header("Pragma: no-cache");
header("Expires: 0");


$sql = "SELECT emno,count(emno) as num FROM `topup` WHERE time>unix_timestamp(now())-86400*7 GROUP BY emno ORDER BY num desc ";


$result = @mysql_query($sql,$Connect) or die(mysql_error());




echo ' <TABLE height=45 cellSpacing=0 borderColorDark=#ffffff width="100%"  
bgColor=#ffffff borderColorLight=#c0c0c0 border=1> 
   <tbody>     
	 <td align="center" >书名</td>
	 	 <td align="center" >价格</td>
	 <td align="center" >物料号</td>	
	 <td align="center" >次数</td>	
</tr>'; 

while($row = mysql_fetch_array($result))
{ 

	$query = "SELECT field_erp_shuming_value as name ,field_erp_dingjia_value as price FROM `content_type_erp` WHERE field_erp_wuliaohao_value=".$row[emno];
		
	$res = @mysql_query($query) or die(mysql_error());
    $count = mysql_num_rows($res);
	if($count>0){	
      $arr = mysql_fetch_array($res);
	  $name = $arr['name'];
	  $price = $arr['price'];
    }else{
	  $name = '';
      $price = '';
    }
	 echo '<tr><td align="center" >'.$name.'</td>
	      <td align="center" >'.$price.'</td>
	 <td align="center" >'.$row[emno].'</td>	
	 <td align="center" >'.$row[num].'</td>';
	echo '</tr>'; 
} 
echo " </TBODY> </TABLE>"; 

?>
