<?php
// $Id$

/**
 * 回调函数
 */ 
function aispeech_oral_test_page(){
	//drupal_add_js('http://sandbox.api.aispeech.com/aispeechapi-js/load_core.js', 'external');
	
	drupal_add_css(drupal_get_path('module', 'aispeech') .'/css.css');
	
	$output = "";

	//$variables = array();
	$word  = aispeech_get_next_word();
	// $word  = aispeech_get_next_word();
	//$output .= theme('aispeech_word_content',$variables;
	$output .= theme('aispeech_word_content',$word);
	drupal_add_js(drupal_get_path('module', 'aispeech') .'/aispeech.js');
	//$word  = $variables['word'];
	//$output .='spell:'. $word->spell;
	//$output .='explaination:'. $word->explaination;
	return $output;
}

/**
 * 回调函数
 */ 
function aispeech_oral_test1_page(){
	$output = "";
	$output .= '<div id="aiPlayer1"><a href="http://www.adobe.com/go/getflashplayer">get flash player</a></div>';
	$output .= "<div>";
	$output .= '<p><input type="button" value="player1Load" id="player1Load" /></p>';
	$output .= '<p><input type="button" value="player1Play" id="player1Play" /></p>';
	$output .= "</div>";
	$output .= '<div id="player1AiDebug">          </div>';
	 drupal_add_js(drupal_get_path('module', 'aispeech') .'/aispeech1.js');
	 drupal_add_css(drupal_get_path('module', 'aispeech') .'/css.css');
	return $output;
}

/**
 * 回调函数
 */ 
function aispeech_oral_test_next(){
  $word =  aispeech_get_next_word();
	if(!empty($_POST['js'])){
	  drupal_json(array(
		    'word' => $word,
		  )
		);
		exit();
	}
	$path = 'oral/test';
	drupal_goto($path);
}
function theme_aispeech_word_content($variables){
  drupal_add_css(drupal_get_path('module', 'aispeech') .'/css.css');
	
	$output .= '<div id="word-wrapper">';
	$output .= '<div id="spell-wrapper">'.$variables['word']->spell.'</div>';
	$output .= '<div id="explaination-wrapper">'.$variables['word']->explaination.'</div>';


	$output .= '</div>';
	$output .= '<div id="aiRecorder-wrapper" ><div id="aiRecorder"> </div></div>';
	$output .= '<div id="aiPlayer1"><a href="http://www.adobe.com/go/getflashplayer">get flash player</a></div>';
	$output .= "<div>";
	$output .= '<div id="readit-wrapper"><input type="button" value="读它" id="readit" /></div>';
	$output .= '<div id="read-after-wrapper"><input type="button" value="跟读" id="followit"/></div>';
	$output .= '<div id="grogress-wrapper">进度条</div>';
	$output .= '<div id="next-word-wrapper"><input type="button" value="下一个" id="next-word" /></div>';
	$output .= '<div id="testing-wrapper"><input type="button" value="测评" id="testit"/></div>'; 
	$output .= "</div>";
	$output .= '<div id="charsContainer" > </div>';
	$output .= '<div id="charsContainer1" > </div>';
	return $output;
}

function aispeech_oral_test_point_add(){
	global $user;
	//测试成功后，加积分的数量，可以在这里调整，默认为1
	$points = 1;
	
	if(!empty($_POST['js']) && !empty($_POST['word'])){
		$word = $_POST['word'];
		$params = array (
			'tid' => 0,
			'uid' => $user->uid,
			'points' => $points,
			'operation' => 'insert',
			'description' => '用户作了单词口语测评，单词：' . $word ,
		);
		$uu = userpoints_userpointsapi($params);
	  drupal_json(array(
		    'uu' => $uu,
		  )
		);
		exit();
	}
	$path = 'oral/test/point/add';
	//drupal_goto($path);
	return $path;
}
function aispeech_oral_test_get_session_key(){
	
	$appKey = "1298426941825";
	$secretkey = "595fd7706b9a96bd892a0c88a2e772b0d0565316";
	$apiHost = "http://sandbox.api.aispeech.com";
	$apiVersion = "v1.0";
	$apiSessionKey = null;

	$url = "$apiHost/api/$apiVersion/auth/getSessionKey/appkey/$appKey/secretkey/$secretkey";

	if (empty ( $appKey ) || empty ( $secretkey ) ) {
		$json = array ("error" => "missing parameters" );
		echo json_encode ( $json );
		die ();
	}



	$validateResultJson = curl_post ( $url );
	$validateResultObj = json_decode ( $validateResultJson );
	//drupal_set_message(print_r($validateResultObj));
	if(!empty($_POST['js'])){
	  $validateResultJson = curl_post ( $url );
	  $validateResultObj = json_decode ( $validateResultJson );
	  drupal_json(array(
		    'result' => $validateResultObj,
				//'result' => array('session_key'=>'123456789'),
		  )
		);
		exit();
	}
	
	$path = 'oral/test/session/key';
	//drupal_goto($path);
	return $path;
}

/**
 * Send a POST requst using cURL
 * @param string $url to request
 * @param array $post values to send
 * @param array $options for cURL
 * @return string
 */
function curl_post($url, array $post = NULL, array $options = array()) {
	$defaults = array (CURLOPT_POST => 1, CURLOPT_HEADER => 0, CURLOPT_URL => $url, CURLOPT_FRESH_CONNECT => 1, CURLOPT_RETURNTRANSFER => 1, CURLOPT_FORBID_REUSE => 1, CURLOPT_TIMEOUT => 4, CURLOPT_POSTFIELDS => http_build_query ( $post ) );
	
	$ch = curl_init ();
	curl_setopt_array ( $ch, ($options + $defaults) );
	if (! $result = curl_exec ( $ch )) {
		trigger_error ( curl_error ( $ch ) );
	}
	curl_close ( $ch );
	return $result;
}
