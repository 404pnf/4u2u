<link href='table.css' rel='stylesheet' type='text/css' >
<form action='' method='post'>
请选择时间段:
<select name='time'>
<option value='week' <?php if($_POST['time']=='week'|$_POST['time']=='') echo "selected"; ?>>本周</option>
<option value='last_week' <?php if($_POST['time']=='last_week') echo "selected"; ?>>上周</option>
<option value='month' <?php if($_POST['time']=='month') echo "selected"; ?>>本月</option>
<option value='last_month' <?php if($_POST['time']=='last_month') echo "selected"; ?>>上个月</option>
<option value='two_month' <?php if($_POST['time']=='two_month') echo "selected"; ?>>上上个月</option>
<option value='year' <?php if($_POST['time']=='year') echo "selected"; ?>><?php echo date("Y");?>财年</option>
<option value='all' <?php if($_POST['time']=='all') echo "selected"; ?>>所有</option>
</select>
<input type='submit' name='btn' value='提交'>
</form>
<?php
function time_limit($time_field){
$end = strtotime("today");
if(isset($_POST['btn'])){
      $time = $_POST['time'];

      if($time=='week'){    //本周
      	    $time_limit = " $time_field>$end-86400*7 AND $time_field<$end AND "; 
            $string = "从".date("Y-m-d",$end-86400*7)." 至 ".date("Y-m-d",$end);     
      }
      if($time=='last_week'){    //上周
          $time_limit = "$time_field>$end-86400*14 AND $time_field<$end-86400*7 AND "; 
          $string = "从".date("Y-m-d",$end-86400*14)." 至 ".date("Y-m-d",$end-86400*7);         
      }    
      if($time=='month'){       //本月
      	  $start = mktime(0, 0 , 0,date("m"),1,date("Y"));
          $time_limit = "$time_field>$start AND $time_field<$end AND ";   
          $string = "从".date("Y-m-d",$start)." 至 ".date("Y-m-d",$end);      
      }
      if($time=='last_month'){  //上月
      	  $start = mktime(0, 0 , 0,date("m")-1,1,date("Y"));
      	  $this_month = mktime(0, 0 , 0,date("m"),1,date("Y"));
          $time_limit = "$time_field>$start AND $time_field<$this_month AND ";  
          $string = "从".date("Y-m-d",$start)." 至 ".date("Y-m-d",$this_month);        
      }
      if($time=='two_month'){  //上月
          $start = mktime(0, 0 , 0,date("m")-2,1,date("Y"));
          $this_month = mktime(0, 0 , 0,date("m")-1,1,date("Y"));
          $time_limit = "$time_field>$start AND $time_field<$this_month AND ";
          $string = "从".date("Y-m-d",$start)." 至 ".date("Y-m-d",$this_month);
      }


      if($time=='year'){  //上月
      	  $start = mktime(0, 0 , 0,11,1,date("Y")-1);
      	  $this_month = mktime(0, 0 , 0,11,1,date("Y"));
          $time_limit = "$time_field>$start AND $time_field<$this_month AND ";  
          $string = "从".date("Y-m-d",$start)." 至 ".date("Y-m-d",$this_month);        
      }
      

      if($time=='all'){  //所有
          $time_limit = "$time_field<$end AND ";     
          $string .="截至".date("Y-m-d",$end);  
      }
 }else{
 	     $time_limit = "$time_field>$end-86400*7 AND $time_field<$end AND "; 
         $string = "从".date("Y-m-d",$end-86400*7)." 至 ".date("Y-m-d",$end);   
 }
//echo $time_limit;
$array['time'] = $time_limit;
$array['string'] = $string;
return $array;
}
?>
