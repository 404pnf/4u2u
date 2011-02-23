<?php

/**
 * EGS系统购买积分
 *
 * @param unknown_type $app_key
 * @param unknown_type $session_id
 * @param unknown_type $points
 */
function egs_buy($app_key,$session_id,$points){
	
if($points>0){
	if(check_appkey($app_key)){  //验证key值		
		   global $user;
		   if($user->uid>0){
			   $is_sess = check_session($session_id,$user->uid);
			   if($is_sess){
			   	   //session验证成功，扣除积分
			   	    $totalPoints = userpoints_get_current_points();
			       if($points>$totalPoints){
				        //用户积分不够					
			        }else{			
			        	        	
			           $params = array (
					      'uid' => $user->uid,
					      'points' => -$points,
						  'description' => 'EGS系统用户购买收费试卷',
                        );
				        userpoints_userpointsapi($params);	
			        }
			   	
			   	 
			   }else{
		   	
			       //session验证未成功
			   }		  
		   }else{
		   	   //用户未登录
		   	
		   	   
		   }

		
	}else{
		//appkey值验证未通过
		
		
	}	
}else{
	//要扣除的积分值无效
	
}
}

function query_user_info($app_key,$session_id,$uid){
	
	$is_app = check_appkey($app_key);	
	if($is_app){	
	    $is_sess = check_session($session_id,$uid);		
	    if($is_sess){	    			
		     $sql = "SELECT `name`,`mail` FROM {users} WHERE `uid` =%d ";
		     $row = db_fetch_object(db_query($sql,$uid));			     	    	
	    	 $query = "SELECT ur.`rid`,r.`name` FROM {users_roles} ur LEFT JOIN {role} r ON ur.`rid`=r.`rid` WHERE ur.`uid` =%d";
	    	 $rs = db_query($query,$uid);
	    	 while($arr = db_fetch_object($rs)){    	 	
	    	 	$role[$arr->rid] = $arr->name;    	 	
		 }	    
	    	 $points = 0;
	    	 $points = userpoints_get_current_points($uid);	
	    	 $array = array("status" => "Success",
	    	                "sessid" => $session_id,
	    	                "userid" => $uid,
	    	                "username" => $row->name,
				"email" => $row->mail,  
                                "userpoints" => $points,
	    	                "roles" => $role   
	    	 );    	    	 	
		
	    }else{
			 $array = array("status" => "false");
		}
	    
	}else{
		 $array = array("status" => "false");
	}
	
	 drupal_json($array);   
}

/**
 * 验证密钥
 *
 * @param unknown_type $key
 * @return unknown
 */
function check_appkey($key){
	
	if($key!=''){
		return true;
	}else{
		return false;			
	}		
}

/**
 * 验证session
 *
 * @param unknown_type $sess_id
 * @param unknown_type $uid
 * @return unknown
 */


function check_session($sess_id,$uid){
	
 if($sess_id!=''&&$uid>0){
	$sql = "SELECT uid FROM {sessions} where sid ='%s'";
	$sid = db_result(db_query($sql,$sess_id));
	if($uid==$sid){
		return true;		
	}else{
		return false;
	}
  }else{
    	return false;
  }
}
