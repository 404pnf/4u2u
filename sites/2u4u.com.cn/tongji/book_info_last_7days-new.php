<?php 
/*
 * get user info for the celebrate
 */

require 'connect.php';
if($_GET['t']=='week'|empty($_GET['t'])){
     $filename = "book_info_last_7days";
     $time_limit =" where tp.time>".time()."-86400*7 ";
}
if($_GET['t']=='all'){
	 $filename = "book_info_all";
	 $time_limit = '';
}
if($_GET['info']=='new'){
	 $time_limit = '';
	 $limit = "LIMIT 300";
}

if($_GET['info']!='new'){
	header("Content-type:application/vnd.ms-excel;charset:utf-8"); 
	header("Content-Disposition:filename=$filename.xls"); 
	header("Pragma: no-cache");
	header("Expires: 0");
}

//$sql = "SELECT uid,gcode, emno, from_unixtime(time) as time FROM `topup` WHERE time>unix_timestamp(now())-86400*7 ORDER BY time desc ";

$sql = "SELECT tp.`emno`,tp.`uid`,tp.`gcode`,tp.`time`,bi.`name`,bi.`price`   
        FROM `topup` tp LEFT JOIN `book_info` bi ON bi.sku = tp.emno $time_limit ORDER BY tp.time desc $limit";

$result = @mysql_query($sql);




$table .=' <TABLE height=45 cellSpacing=0 borderColorDark=#ffffff width="100%"  
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

	if(strlen($row['name'])>2){	
	  $name = $row['name'];
	  $price = $row['price'];
    }else{
	  $name = '';
      $price = '';
    }
	$table .= '<tr><td align="center" >'.$name.'</td>
	      <td align="center" >'.$price.'</td>
	 <td align="center" >'.$row[gcode].'</td>
	 <td align="center" >'.$row[emno].'</td>	
	 <td align="center" >'.date("Y-m-d H:i:s",$row[time]).'</td>
	 <td align="center" >'.$row[uid].'</td></tr>'; 
} 
$table .= " </TBODY> </TABLE>"; 
echo $table;
?>
