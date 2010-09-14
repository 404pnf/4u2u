<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>悠游|用户订单打印</title>
</head>
<style type="text/css"> 
/* CSS Document */ 

body { 
font: normal 11px auto "Trebuchet MS", Verdana, Arial, Helvetica, sans-serif; 
color: #4f6b72; 
background: #E6EAE9; 

} 

a { 
color: #c75f3e; 
} 

#mytable { 
width: 98%; 
padding: 0; 
margin: 0;
margin-top:8%; 
} 

caption { 
padding: 0 0 5px 0; 
width: 98%; 
text-align: center; 
} 

th { 
font: bold 11px "Trebuchet MS", Verdana, Arial, Helvetica, sans-serif; 
color: #4f6b72; 
border-right: 1px solid #C1DAD7; 
border-bottom: 1px solid #C1DAD7; 
border-top: 1px solid #C1DAD7; 
letter-spacing: 2px; 
text-transform: uppercase; 
text-align: left; 
padding: 6px 6px 6px 12px; 
background: #CAE8EA  no-repeat; 
} 
/*power by www.winshell.cn*/ 
th.nobg { 
border-top: 0; 
border-left: 0; 
border-right: 1px solid #C1DAD7; 
background: none; 
} 

td { 
border-right: 1px solid #C1DAD7; 
border-bottom: 1px solid #C1DAD7; 
background: #fff; 
font-size:11px; 
padding: 6px 6px 6px 12px; 
color: #4f6b72; 
} 
/*power by www.winshell.cn*/ 

td.alt { 
background: #F5FAFA; 
color: #797268; 
} 

th.spec { 
border-left: 1px solid #C1DAD7; 
border-top: 0; 
background: #fff no-repeat; 
font: bold 10px "Trebuchet MS", Verdana, Arial, Helvetica, sans-serif; 
} 

th.specalt { 
border-left: 1px solid #C1DAD7; 
border-top: 0; 
background: #f5fafa no-repeat; 
font: bold 10px "Trebuchet MS", Verdana, Arial, Helvetica, sans-serif; 
color: #797268; 
} 
/*---------for IE 5.x bug*/ 
html>body td{ font-size:11px;} 
body,td,th { 
font-family: 宋体, Arial; 
font-size: 14px; 
} 
</style> 


<?php

if(date('w')==5){
   $start = strtotime("this fridayy-1 week");
   $end = strtotime("this friday");
   $time = date("ymd",strtotime("this friday")); 
}else{
   $start = strtotime("last friday-1 week");
   $end = strtotime("last friday"); 
   $time = date("ymd",strtotime("last friday")); 
} 

?>


<table id="mytable" cellspacing="0" align='center' > 

<caption><h2>打印用户订单（EXCEL表）</h2></caption> 
<tr> 
<th scope="col">操作</th><th scope="col">操作说明</th></tr>
<th scope="col"><a href='get_orders_list_new.php'>打印上周订单(<?php echo date("ymd",$start)."-".date("ymd",$end)?>)</a></th><th scope="col">只打印上一周的订单，不改变用户的状态，可重复打印</th></tr>
<th scope="col"><a href='get_orders_list_new.php?op=latest'>打印截至本周五的所有订单(<?php echo $time ?>)</a></th><th scope="col">打印截至本周五的所有订单，不改变用户的状态，可重复打印</th></tr>
<th scope="col"><a href='get_orders_list_new.php?info=update'>打印上周订单(<?php echo date("ymd",$start)."-".date("ymd",$end)?>)并更新用户订单状态</a></th><th scope="col">改变用户的状态，只能打印一次</th></tr>
<th scope="col"><a href='get_orders_list_new.php?op=latest&info=update'>打印截至本周五的所有订单(<?php echo $time ?>)并更新用户订单状态</a></th><th scope="col">改变用户的状态，只能打印一次</th></tr>
</table>
<br>
<a href="http://2u4u.com.cn/admin/store/orders">查看2u4u网站所有订单</a>
