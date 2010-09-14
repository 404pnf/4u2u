<?php

function disney_list_page($series_id=0)
 {	
   global $user;
   if($user->uid>0){
	    drupal_add_js(drupal_get_path('module','disney').'/submit.js');
	    drupal_add_css(drupal_get_path('module','disney') .'/disney.css');

 	 $name_array = array ("迪士尼双语小影院","米奇妙妙屋智慧双语故事","小熊维尼温馨双语故事","迪士尼完美公主双语故事集","小熊维尼启智科普故事集","小熊维尼左脑游戏总动员&米奇右脑游戏总动员");
 
 	 $series_id = $series_id<count($name_array)?$series_id:0; 	 
 	 $name = $name_array[$series_id];

	 $sql = "SELECT * FROM {disney_book} WHERE `series_name`='%s' ORDER BY book_id";
	 $res = db_query($sql,$name);
	//echo $sql.$name;    
	//	var_dump($res);     	
	    $j = 0;
	    $series =array();
	    $origin = $series ; 
	    while($row = db_fetch_object($res)){
	    
	    if($row->name_en!=''&&$row->series_name!=''){
	            	if($j%2==0)
	            	   $class = "disney-row-odd";
	            	else 
	            	   $class = "disney-row-even";
	            	   
	          
		       if(!in_array($row->series_name,$series)){	       	
		       		$series[] = $row->series_name;
		     		
		      	if(count($series)>count($origin)){ 
		      
		     	     $content .="</div>";
		             $origin = $series;    
		         }
		       		
		       		
		       	    $content .="<div class='disney-series'>";
		            $content .= "<div class='disney-series-name'>".$row->series_name."</div>";
	
		       }      
		     
		            $content .="<div class='disney-book-content ".$class."'>";
		   	        $content .= "<div class='disney-image'><img src=\"http://cdn1.2u4u.com.cn/disney/img/s/".$row->image.".jpg\"></div>";
		            $content .= "<div class='disney-book-name-ch'>".$row->name_ch."</div>";            
		            $content .= "<div class='disney-book-name-en'>".$row->name_en."</div>";
		            $content .="<div class='disney-auido'><a href=javascript:submit('$row->level','".addslashes($row->image)."','".addslashes($row->audio)."')>在线试听</a></div>";
	                $content .="</div>";
	              
	  
	      }
	
	      $j++;
	    }
	  
	   
    }else{
       drupal_set_message (t("请先登录"));
   	   $url = "http://2u4u.com.cn/user?destination=disney";
	   drupal_goto($url);
   	
    }
     return $content;
  } 

 function disney_series($series_id){ 	
 	$series_id = intval($series_id); 	
    $content = disney_list_page($series_id);
    return $content;
 } 
  