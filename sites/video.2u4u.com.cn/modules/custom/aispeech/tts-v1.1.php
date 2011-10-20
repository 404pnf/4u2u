<?php
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
?>
<?php

/**
 * tts.php getSessionKey
 * POST http://sandbox.api.aispeech.com/api/v1.1/auth/getSessionKey
 * applicationId：应用程序标识
 * timestamp：客户端系统时间
 * sig：(applicationId + timestamp + 用户申请applicationId时获取的密钥)经过SHA-1加密后的字符串
 * 
 * 验证成功，服务器返回json格式字符串
 * {
 *    "timestamp": 1300328247960,
 *    "session": "12953375095491300328247639391720efc00de450c56bbd7954171bc9af1b8ccf",
 *    "applicationId": "1295337509549"
 * }
 *
 * 验证失败，服务器返回json中包含error属性
 * {
 *    "timestamp": 1300328247960,
 *    "error": "auth.faield",
 *    "applicationId": "1295337509549"
 * }
 * 
 */
ini_set ('arg_separator.output', '&');
error_reporting ( E_ALL ^ E_NOTICE ^ E_WARNING );

$applicationId = "1300675449010";
$secretKey = "50b87599fcc2bd7bd27cb2799759eba59c56aaf8";
$timestamp = round(microtime(true)*1000);
$sig = sha1("$applicationId$timestamp$secretKey");

$apiHost = "http://sandbox.api.aispeech.com";
$apiVersion = "v1.1";
$session = null;

$url = "$apiHost/api/$apiVersion/auth/getSessionKey";

$validateResultJson = curl_post ( $url , array(
	"applicationId"=>"$applicationId",
	"sig"=>"$sig",
	"timestamp"=>"$timestamp",
) );

$validateResultObj = json_decode ( $validateResultJson );
 
echo $validateResultJson;

?>
