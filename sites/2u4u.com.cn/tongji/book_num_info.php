<?php
require 'connect.php';

 
//header("Content-type:application/vnd.ms-excel;charset:utf-8"); 
//header("Content-Disposition:filename=book_num_info.xls"); 
//header("Pragma: no-cache");
//header("Expires: 0");

$sql = "SELECT emno,count(emno) as num FROM `topup` GROUP BY emno ORDER BY num desc ";


$result = @mysql_query($sql,$Connect) or die(mysql_error());

header("Content-type:application/vnd.ms-excel;charset:utf-8"); 
header("Content-Disposition:filename=book_num_info.xls"); 
header("Pragma: no-cache");
header("Expires: 0");


echo ' <TABLE height=45 cellSpacing=0 borderColorDark=#ffffff width="100%"  
bgColor=#ffffff borderColorLight=#c0c0c0 border=1> 
   <tbody>
         <td align="center" >分类</td>
          <td align="center" >书名</td>
	 <td align="center" >价格</td>
	 <td align="center" >物料号</td>	
	 <td align="center" >次数</td>	
</tr>'; 

while($row = mysql_fetch_array($result))
{ 

	$query = "SELECT nid,field_erp_shuming_value as name ,field_erp_dingjia_value as price FROM `content_type_erp` WHERE field_erp_wuliaohao_value=".$row[emno];
		
	$res = @mysql_query($query) or die(mysql_error());
    $count = mysql_num_rows($res);
	if($count>0){	
      $arr = mysql_fetch_array($res);

      $sqlx = "SELECT td.name FROM `term_data` td LEFT JOIN `term_node` tn ON td.tid= tn.tid WHERE tn.nid=".$arr['nid'];
//echo $sqlx;  
//exit;  
  $term_name = mysql_fetch_array(mysql_query($sqlx));
      $fenlei = $term_name['name'];
	  $name = $arr['name'];
	  $price = $arr['price'];
    }else{
          $fenlei = '';
	  $name = '';
          $price = '';
    }
 echo '<tr>
<td align="center" >'.$fenlei.'</td>
<td align="center" >'.$name.'</td>
	      <td align="center" >'.$price.'</td>
	 <td align="center" >'.$row[emno].'</td>	
	 <td align="center" >'.$row[num].'</td>';
	echo '</tr>'; 
} 
echo " </TBODY> </TABLE>"; 

?>
