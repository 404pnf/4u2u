<?
include 'IXR_Library.inc.php';
function dump($vars, $label = '', $return = false){
    if (ini_get('html_errors')) {
        $content = "<pre>\n";
        if ($label != '') {
            $content .= "<strong>{$label} :</strong>\n";
        }
        $content .= htmlspecialchars(print_r($vars, true));
        $content .= "\n</pre>\n";
    } else {
        $content = $label . " :\n" . print_r($vars, true);
    }
    if ($return) { return $content; }
    echo $content;
    return null;
}

$client = new IXR_Client('http://gps.2u4u.com.cn/xmlrpc.php');

if(!$client->query('askUserChartInfo', '30', 'SUPER小学生单词王(各关都有奖测试)')){
    die('An error occurred
-'.$client->getErrorCode().":".$client->getErrorMessage());
}
dump($client->getResponse());


if(!$client->query('askUserChartInfo', '30', 'SUPER初中单词王')){
    die('An error occurred
-'.$client->getErrorCode().":".$client->getErrorMessage());
}
dump($client->getResponse());

if(!$client->query('askUserChartInfo', '30', 'SUPER高中单词王')){
    die('An error occurred
-'.$client->getErrorCode().":".$client->getErrorMessage());
}
dump($client->getResponse());

if(!$client->query('askUserChartInfo', '30', 'SUPER大学单词王')){
    die('An error occurred
-'.$client->getErrorCode().":".$client->getErrorMessage());
}
dump($client->getResponse());


if(!$client->query('askUserChartInfo', '30', 'SUPER成人单词王')){
    die('An error occurred
-'.$client->getErrorCode().":".$client->getErrorMessage());
}
dump($client->getResponse());

?>
