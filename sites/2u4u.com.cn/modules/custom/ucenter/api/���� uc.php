<?php
define('DRUPAL_ROOT_PATH', 'D:/work/php/drupal');
define('IN_DISCUZ', FALSE);
define('UC_CLIENT_VERSION', '1.5.0');	//note UCenter 版本标识
define('UC_CLIENT_RELEASE', '20081031');
define('API_SYNLOGIN', 1);		//note 同步登录 API 接口开
define('API_SYNLOGOUT', 1);		//note 同步登出 API 接口开
define('API_RETURN_SUCCEED', '1');
define('API_RETURN_FAILED', '-1');
define('API_RETURN_FORBIDDEN', '-2');
//define('API_DELETEUSER', 1);		//note 用户删除 API 接口开
//define('API_RENAMEUSER', 1);		//note 用户改名 API 接口开
//define('API_GETTAG', 1);		//note 获取标签 API 接口开

//define('API_UPDATEPW', 1);		//note 更改用户密码 开关
//define('API_UPDATEBADWORDS', 1);	//note 更新关键字列表 开关
//define('API_UPDATEHOSTS', 1);		//note 更新域名解析缓存 开关
//define('API_UPDATEAPPS', 1);		//note 更新应用列表 开关
//define('API_UPDATECLIENT', 1);		//note 更新客户端缓存 开关
//define('API_UPDATECREDIT', 1);		//note 更新用户积分 开关
//define('API_GETCREDITSETTINGS', 1);	//note 向 UCenter 提供积分设置 开关
//define('API_GETCREDIT', 1);		//note 获取用户的某项积分 开关
//define('API_UPDATECREDITSETTINGS', 1);	//note 更新应用积分设置 开关


chdir(DRUPAL_ROOT_PATH);
require_once './includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
//note 普通的 http 通知方式
Global $user;
echo "当前用户:".$user->name.'/'.$get['time'];
if(!defined('IN_UC')) {

	error_reporting(0);
	set_magic_quotes_runtime(0);

	define('DISCUZ_ROOT', substr(dirname(__FILE__), 0, -3));
	defined('MAGIC_QUOTES_GPC') || define('MAGIC_QUOTES_GPC', get_magic_quotes_gpc());
	//define('UC_CLIENT_ROOT', DISCUZ_ROOT.'./uc_client/');
	require_once DISCUZ_ROOT.'./config.inc.php';
	//print DISCUZ_ROOT.'./config.inc.php';
	$_DCACHE = $get = $post = array();

	$code = @$_GET['code'];
	parse_str(_authcode($code, 'DECODE', UC_KEY), $get);
	if(MAGIC_QUOTES_GPC) {
		$get = _stripslashes($get);
	}

	$timestamp = time();
	if($timestamp - $get['time'] > 3600) {
		exit('Authracation has expiried');
	}
	if(empty($get)) {
		exit('Invalid Request');
	}
	$action = $get['action'];

	require_once DISCUZ_ROOT.'./uc_client/lib/xml.class.php';
	$post = xml_unserialize(file_get_contents('php://input'));

	if(in_array($get['action'], array('test', 'deleteuser', 'renameuser', 'gettag', 'synlogin', 'synlogout', 'updatepw', 'updatebadwords', 'updatehosts', 'updateapps', 'updateclient', 'updatecredit', 'getcreditsettings', 'updatecreditsettings'))) {
		require_once DISCUZ_ROOT.'./include/db_'.$database.'.class.php';
		$GLOBALS['db'] = new dbstuff;
		$GLOBALS['db']->connect($dbhost, $dbuser, $dbpw, $dbname, $pconnect, true, $dbcharset);
		$GLOBALS['tablepre'] = $tablepre;
		unset($dbhost, $dbuser, $dbpw, $dbname, $pconnect);
		$uc_note = new uc_note();
		exit($uc_note->$get['action']($get, $post));
	} else {
		exit(API_RETURN_FAILED);
	}
	//note include 通知方式
} else {

	/*$uc_note = new uc_note('../', '../config.inc.php');
	 $uc_note->deleteuser('3');*/
	define('DISCUZ_ROOT', $app['extra']['apppath']);
	require_once DISCUZ_ROOT.'./config.inc.php';
	require_once DISCUZ_ROOT.'./include/db_'.$database.'.class.php';
	$GLOBALS['db'] = new dbstuff;
	$GLOBALS['db']->connect($dbhost, $dbuser, $dbpw, $dbname, $pconnect, true, $dbcharset);
	$GLOBALS['tablepre'] = $tablepre;
	unset($dbhost, $dbuser, $dbpw, $dbname, $pconnect);
}



class uc_note {

	var $dbconfig = '';
	var $db = '';
	var $tablepre = '';
	var $appdir = '';

	function _serialize($arr, $htmlon = 0) {
		if(!function_exists('xml_serialize')) {
			include_once DISCUZ_ROOT.'./uc_client/lib/xml.class.php';
		}
		return xml_serialize($arr, $htmlon);
	}

	function uc_note() {
		$this->appdir = substr(dirname(__FILE__), 0, -3);
		$this->dbconfig = $this->appdir.'./config.inc.php';
		$this->db = $GLOBALS['db'];
		$this->tablepre = $GLOBALS['tablepre'];
	}

	function test($get, $post) {
		return API_RETURN_SUCCEED;
	}

	function deleteuser($get, $post) {
		$uids = $get['ids'];
		!API_DELETEUSER && exit(API_RETURN_FORBIDDEN);

		//note 用户删除 API 接口
		$threads = array();

		$query = $this->db->query("SELECT f.fid, t.tid FROM ".$this->tablepre."threads t LEFT JOIN ".$this->tablepre."forums f ON t.fid=f.fid WHERE t.authorid IN ($uids) ORDER BY f.fid");
		while($thread = $this->db->fetch_array($query)) {
			$threads[$thread['fid']] .= ($threads[$thread['fid']] ? ',' : '').$thread['tid'];
		}

		if($threads) {
			require_once $this->appdir.'./forumdata/cache/cache_settings.php';
			foreach($threads as $fid => $tids) {
				$query = $this->db->query("SELECT attachment, thumb, remote FROM ".$this->tablepre."attachments WHERE tid IN ($tids)");
				while($attach = $this->db->fetch_array($query)) {
					@unlink($_DCACHE['settings']['attachdir'].'/'.$attach['attachment']);
					$attach['thumb'] && @unlink($_DCACHE['settings']['attachdir'].'/'.$attach['attachment'].'.thumb.jpg');
				}

				foreach(array('threads', 'threadsmod', 'relatedthreads', 'posts', 'polls', 'polloptions', 'trades', 'activities', 'activityapplies', 'debates', 'debateposts', 'attachments', 'favorites', 'mythreads', 'myposts', 'subscriptions', 'typeoptionvars', 'forumrecommend') as $value) {
					$this->db->query("DELETE FROM ".$this->tablepre."$value WHERE tid IN ($tids)", 'UNBUFFERED');
				}

				require_once $this->appdir.'./include/post.func.php';
				updateforumcount($fid);
			}
			if($globalstick && $stickmodify) {
				require_once $this->appdir.'./include/cache.func.php';
				updatecache('globalstick');
			}
		}

		$query = $this->db->query("DELETE FROM ".$this->tablepre."members WHERE uid IN ($uids)");
		$this->db->query("DELETE FROM ".$this->tablepre."access WHERE uid IN ($uids)", 'UNBUFFERED');
		$this->db->query("DELETE FROM ".$this->tablepre."memberfields WHERE uid IN ($uids)", 'UNBUFFERED');
		$this->db->query("DELETE FROM ".$this->tablepre."favorites WHERE uid IN ($uids)", 'UNBUFFERED');
		$this->db->query("DELETE FROM ".$this->tablepre."moderators WHERE uid IN ($uids)", 'UNBUFFERED');
		$this->db->query("DELETE FROM ".$this->tablepre."subscriptions WHERE uid IN ($uids)", 'UNBUFFERED');

		$query = $this->db->query("SELECT uid, attachment, thumb, remote FROM ".$this->tablepre."attachments WHERE uid IN ($uids)");
		while($attach = $this->db->fetch_array($query)) {
			@unlink($_DCACHE['settings']['attachdir'].'/'.$attach['attachment']);
			$attach['thumb'] && @unlink($_DCACHE['settings']['attachdir'].'/'.$attach['attachment'].'.thumb.jpg');
		}
		$this->db->query("DELETE FROM ".$this->tablepre."attachments WHERE uid IN ($uids)");

		$this->db->query("DELETE FROM ".$this->tablepre."posts WHERE authorid IN ($uids)");
		$this->db->query("DELETE FROM ".$this->tablepre."trades WHERE sellerid IN ($uids)");

		return API_RETURN_SUCCEED;
	}

	function renameuser($get, $post) {
		$uid = $get['uid'];
		$usernameold = $get['oldusername'];
		$usernamenew = $get['newusername'];
		if(!API_RENAMEUSER) {
			return API_RETURN_FORBIDDEN;
		}

		//note 获取标签 API 接口
		require $this->dbconfig;
		require_once $this->appdir.'./include/db_'.$database.'.class.php';

		$db = new dbstuff;
		$this->db->connect($dbhost, $dbuser, $dbpw, $dbname, $pconnect, true, $dbcharset ? $dbcharset : $charset);
		unset($dbhost, $dbuser, $dbpw, $dbname, $pconnect);

		$this->db->query("UPDATE ".$this->tablepre."announcements SET author='$usernamenew' WHERE author='$usernameold'");
		$this->db->query("UPDATE ".$this->tablepre."banned SET admin='$usernamenew' WHERE admin='$usernameold'");
		$this->db->query("UPDATE ".$this->tablepre."forums SET lastpost=REPLACE(lastpost, '\t$usernameold', '\t$usernamenew')");
		$this->db->query("UPDATE ".$this->tablepre."members SET username='$usernamenew' WHERE uid='$uid'");
		$this->db->query("UPDATE ".$this->tablepre."pms SET msgfrom='$usernamenew' WHERE msgfromid='$uid'");
		$this->db->query("UPDATE ".$this->tablepre."posts SET author='$usernamenew' WHERE authorid='$uid'");
		$this->db->query("UPDATE ".$this->tablepre."threads SET author='$usernamenew' WHERE authorid='$uid'");
		$this->db->query("UPDATE ".$this->tablepre."threads SET lastposter='$usernamenew' WHERE lastposter='$usernameold'");
		$this->db->query("UPDATE ".$this->tablepre."threadsmod SET username='$usernamenew' WHERE uid='$uid'");
		return API_RETURN_SUCCEED;
	}

	function gettag($get, $post) {
		$name = $get['id'];
		if(!API_GETTAG) {
			return API_RETURN_FORBIDDEN;
		}

		//note 获取标签 API 接口
		require $this->dbconfig;
		require_once $this->appdir.'./include/db_'.$database.'.class.php';

		$db = new dbstuff;
		$this->db->connect($dbhost, $dbuser, $dbpw, $dbname, $pconnect, true, $dbcharset ? $dbcharset : $charset);
		unset($dbhost, $dbuser, $dbpw, $dbname, $pconnect);

		$name = trim($name);
		if(empty($name) || !preg_match('/^([\x7f-\xff_-]|\w|\s)+$/', $name) || strlen($name) > 20) {
			return API_RETURN_FAILED;
		}

		require_once $this->appdir.'./include/misc.func.php';

		$tag = $this->db->fetch_first("SELECT * FROM ".$this->tablepre."tags WHERE tagname='$name'");
		if($tag['closed']) {
			return API_RETURN_FAILED;
		}

		$tpp = 10;
		$PHP_SELF = $_SERVER['PHP_SELF'] ? $_SERVER['PHP_SELF'] : $_SERVER['SCRIPT_NAME'];
		$boardurl = 'http://'.$_SERVER['HTTP_HOST'].preg_replace("/\/+(api)?\/*$/i", '', substr($PHP_SELF, 0, strrpos($PHP_SELF, '/'))).'/';
		$query = $this->db->query("SELECT t.* FROM ".$this->tablepre."threadtags tt LEFT JOIN ".$this->tablepre."threads t ON t.tid=tt.tid AND t.displayorder>='0' WHERE tt.tagname='$name' ORDER BY tt.tid DESC LIMIT $tpp");
		$threadlist = array();
		while($tagthread = $this->db->fetch_array($query)) {
			if($tagthread['tid']) {
				$threadlist[] = array(
					'subject' => $tagthread['subject'],
					'uid' => $tagthread['authorid'],
					'username' => $tagthread['author'],
					'dateline' => $tagthread['dateline'],
					'url' => $boardurl.'viewthread.php?tid='.$tagthread['tid'],
				);
			}
		}
		echo $boardurl;
		$return = array($name, $threadlist);
		return $this->_serialize($return, 1);
	}

	function synlogin($get, $post) {
		$uid = $get['uid'];
		$username = $get['username'];
		//echo $uid.'/'.$username;
		if(!API_SYNLOGIN) {
			return API_RETURN_FORBIDDEN;
		}
		// drupal user login
		chdir(DRUPAL_ROOT_PATH);
		require_once './includes/bootstrap.inc';
		drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
		drupal_load('module', 'user');
		watchdog(t('user'), t('synlogin:start username:@username uid:@uid',array('@username' => $GLOBALS['user']->name,'@uid' => $GLOBALS['user']->uid )));
		$user = user_load(array('name' => $username));
		//user_external_login_register($username, 'ucenter');
		//sess_regenerate();
		//$state ['values'] = array('name'=>$username);
		//user_authenticate_finalize($state ['values']);
		//echo $username.'/ucenter';
		watchdog(t('user'), t('synlogin:end username:@username uid:@uid',array('@username' => $GLOBALS['user']->name,'@uid' => $GLOBALS['user']->uid )));
		return API_RETURN_SUCCEED;
	}

	function synlogout($get, $post) {
		if(!API_SYNLOGOUT) {
			return API_RETURN_FORBIDDEN;
		}

		// drupal user logout
		chdir(DRUPAL_ROOT_PATH);

		require_once './includes/bootstrap.inc';
		drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

		$path = drupal_get_path('module', 'user');
		include_once $path.'/user.pages.inc';
		watchdog(t('user'), t('synlogout:@username /'.$GLOBALS['user']->name.'/'.$GLOBALS['user']->uid, array('@username' => 'SYN-star' )));
		user_logout();
		watchdog(t('user'), t('synlogout:@username /'.$GLOBALS['user']->name.'/'.$GLOBALS['user']->uid, array('@username' => 'SYN-end' )));
		return API_RETURN_SUCCEED;
	}

	function updatepw($get, $post) {
		if(!API_UPDATEPW) {
			return API_RETURN_FORBIDDEN;
		}
		$username = $get['username'];
		$password = $get['password'];
		require $this->dbconfig;
		require_once $this->appdir.'./include/db_'.$database.'.class.php';
		$db = new dbstuff;
		$this->db->connect($dbhost, $dbuser, $dbpw, $dbname, $pconnect, true, $dbcharset ? $dbcharset : $charset);
		unset($dbhost, $dbuser, $dbpw, $dbname, $pconnect);

		$newpw = md5(time().rand(100000, 999999));
		$this->db->query("UPDATE ".$this->tablepre."members SET password='$newpw' WHERE username='$username'");
		return API_RETURN_SUCCEED;
	}

	function updatebadwords($get, $post) {
		if(!API_UPDATEBADWORDS) {
			return API_RETURN_FORBIDDEN;
		}
		$cachefile = $this->appdir.'./uc_client/data/cache/badwords.php';
		$fp = fopen($cachefile, 'w');
		$data = array();
		if(is_array($post)) {
			foreach($post as $k => $v) {
				$data['findpattern'][$k] = $v['findpattern'];
				$data['replace'][$k] = $v['replacement'];
			}
		}
		$s = "<?php\r\n";
		$s .= '$_CACHE[\'badwords\'] = '.var_export($data, TRUE).";\r\n";
		fwrite($fp, $s);
		fclose($fp);
		return API_RETURN_SUCCEED;
	}

	function updatehosts($get, $post) {
		if(!API_UPDATEHOSTS) {
			return API_RETURN_FORBIDDEN;
		}
		$cachefile = $this->appdir.'./uc_client/data/cache/hosts.php';
		$fp = fopen($cachefile, 'w');
		$s = "<?php\r\n";
		$s .= '$_CACHE[\'hosts\'] = '.var_export($post, TRUE).";\r\n";
		fwrite($fp, $s);
		fclose($fp);
		return API_RETURN_SUCCEED;
	}

	function updateapps($get, $post) {
		if(!API_UPDATEAPPS) {
			return API_RETURN_FORBIDDEN;
		}
		$UC_API = $post['UC_API'];

		//note 写 app 缓存文件
		$cachefile = $this->appdir.'./uc_client/data/cache/apps.php';
		$fp = fopen($cachefile, 'w');
		$s = "<?php\r\n";
		$s .= '$_CACHE[\'apps\'] = '.var_export($post, TRUE).";\r\n";
		fwrite($fp, $s);
		fclose($fp);

		//note 写配置文件
		if(is_writeable($this->appdir.'./config.inc.php')) {
			$configfile = trim(file_get_contents($this->appdir.'./config.inc.php'));
			$configfile = substr($configfile, -2) == '?>' ? substr($configfile, 0, -2) : $configfile;
			$configfile = preg_replace("/define\('UC_API',\s*'.*?'\);/i", "define('UC_API', '$UC_API');", $configfile);
			if($fp = @fopen($this->appdir.'./config.inc.php', 'w')) {
				@fwrite($fp, trim($configfile));
				@fclose($fp);
			}
		}

		global $_DCACHE;
		require_once $this->appdir.'./forumdata/cache/cache_settings.php';
		require_once $this->appdir.'./include/cache.func.php';
		foreach($post as $appid => $app) {
			$_DCACHE['settings']['ucapp'][$appid]['viewprourl'] = $app['url'].$app['viewprourl'];
		}
		updatesettings();

		return API_RETURN_SUCCEED;
	}

	function updateclient($get, $post) {
		if(!API_UPDATECLIENT) {
			return API_RETURN_FORBIDDEN;
		}
		$cachefile = $this->appdir.'./uc_client/data/cache/settings.php';
		$fp = fopen($cachefile, 'w');
		$s = "<?php\r\n";
		$s .= '$_CACHE[\'settings\'] = '.var_export($post, TRUE).";\r\n";
		fwrite($fp, $s);
		fclose($fp);
		return API_RETURN_SUCCEED;
	}

	function updatecredit($get, $post) {
		if(!API_UPDATECREDIT) {
			return API_RETURN_FORBIDDEN;
		}
		$credit = $get['credit'];
		$amount = $get['amount'];
		$uid = $get['uid'];
		require $this->dbconfig;
		require_once $this->appdir.'./include/db_'.$database.'.class.php';
		require_once $this->appdir.'./forumdata/cache/cache_settings.php';

		$db = new dbstuff;
		$this->db->connect($dbhost, $dbuser, $dbpw, $dbname, $pconnect, true, $dbcharset ? $dbcharset : $charset);
		unset($dbhost, $dbuser, $dbpw, $dbname, $pconnect);

		$this->db->query("UPDATE ".$this->tablepre."members SET extcredits$credit=extcredits$credit+'$amount' WHERE uid='$uid'");

		$discuz_user = $this->db->result_first("SELECT username FROM ".$this->tablepre."members WHERE uid='$uid'");

		$this->db->query("INSERT INTO ".$this->tablepre."creditslog (uid, fromto, sendcredits, receivecredits, send, receive, dateline, operation)
				VALUES ('$uid', '$discuz_user', '0', '$credit', '0', '$amount', '$timestamp', 'EXC')");
		return API_RETURN_SUCCEED;
	}

	function getcredit($get, $post) {
		if(!API_GETCREDIT) {
			return API_RETURN_FORBIDDEN;
		}
		require $this->dbconfig;
		require_once $this->appdir.'./include/db_'.$database.'.class.php';

		$db = new dbstuff;
		$this->db->connect($dbhost, $dbuser, $dbpw, $dbname, $pconnect, true, $dbcharset ? $dbcharset : $charset);
		unset($dbhost, $dbuser, $dbpw, $dbname, $pconnect);

		$uid = intval($get['uid']);
		$credit = intval($get['credit']);
		echo $credit >= 1 && $credit <= 8 ? $this->db->result_first("SELECT extcredits$credit FROM ".$this->tablepre."members WHERE uid='$uid'") : 0;
	}

	function getcreditsettings($get, $post) {
		if(!API_GETCREDITSETTINGS) {
			return API_RETURN_FORBIDDEN;
		}
		require_once $this->appdir.'./forumdata/cache/cache_settings.php';
		$credits = array();
		foreach($_DCACHE['settings']['extcredits'] as $id => $extcredits) {
			$credits[$id] = array(strip_tags($extcredits['title']), $extcredits['unit']);
		}
		return $this->_serialize($credits);
	}

	function updatecreditsettings($get, $post) {
		if(!API_UPDATECREDITSETTINGS) {
			return API_RETURN_FORBIDDEN;
		}
		$credit = $get['credit'];
		require $this->dbconfig;
		$outextcredits = array();
		if($credit) {
			foreach($credit as $appid => $credititems) {
				if($appid == UC_APPID) {
					foreach($credititems as $value) {
						$outextcredits[] = array(
							'appiddesc' => $value['appiddesc'],
							'creditdesc' => $value['creditdesc'],
							'creditsrc' => $value['creditsrc'],
							'title' => $value['title'],
							'unit' => $value['unit'],
							'ratiosrc' => $value['ratiosrc'],
							'ratiodesc' => $value['ratiodesc'],
							'ratio' => $value['ratio']
						);
					}
				}
			}
		}

		global $_DCACHE;
		require_once $this->appdir.'./include/db_'.$database.'.class.php';
		require_once $this->appdir.'./forumdata/cache/cache_settings.php';
		require_once $this->appdir.'./include/cache.func.php';

		$db = new dbstuff;
		$this->db->connect($dbhost, $dbuser, $dbpw, $dbname, $pconnect, true, $dbcharset ? $dbcharset : $charset);
		unset($dbhost, $dbuser, $dbpw, $dbname, $pconnect);

		$this->db->query("REPLACE INTO ".$this->tablepre."settings (variable, value) VALUES ('outextcredits', '".addslashes(serialize($outextcredits))."');", 'UNBUFFERED');

		$tmp = array();
		foreach($outextcredits as $value) {
			$key = $value['appiddesc'].'|'.$value['creditdesc'];
			if(!isset($tmp[$key])) {
				$tmp[$key] = array('title' => $value['title'], 'unit' => $value['unit']);
			}
			$tmp[$key]['ratiosrc'][$value['creditsrc']] = $value['ratiosrc'];
			$tmp[$key]['ratiodesc'][$value['creditsrc']] = $value['ratiodesc'];
			$tmp[$key]['creditsrc'][$value['creditsrc']] = $value['ratio'];
		}
		$_DCACHE['settings']['outextcredits'] = $tmp;

		updatesettings();

		return API_RETURN_SUCCEED;

	}
}

//note 使用该函数前需要 require_once $this->appdir.'./config.inc.php';
function _setcookie($var, $value, $life = 0, $prefix = 1) {
	global $cookiepre, $cookiedomain, $cookiepath, $timestamp, $_SERVER;
	setcookie(($prefix ? $cookiepre : '').$var, $value,
	$life ? $timestamp + $life : 0, $cookiepath,
	$cookiedomain, $_SERVER['SERVER_PORT'] == 443 ? 1 : 0);
	echo ($prefix ? $cookiepre : '').$var.'/'.$value.'/'.$timestamp.$life.'/'.$cookiedomain.'/';
}

function _authcode($string, $operation = 'DECODE', $key = '', $expiry = 0) {
	$ckey_length = 4;

	$key = md5($key ? $key : UC_KEY);
	$keya = md5(substr($key, 0, 16));
	$keyb = md5(substr($key, 16, 16));
	$keyc = $ckey_length ? ($operation == 'DECODE' ? substr($string, 0, $ckey_length): substr(md5(microtime()), -$ckey_length)) : '';

	$cryptkey = $keya.md5($keya.$keyc);
	$key_length = strlen($cryptkey);

	$string = $operation == 'DECODE' ? base64_decode(substr($string, $ckey_length)) : sprintf('%010d', $expiry ? $expiry + time() : 0).substr(md5($string.$keyb), 0, 16).$string;
	$string_length = strlen($string);

	$result = '';
	$box = range(0, 255);

	$rndkey = array();
	for($i = 0; $i <= 255; $i++) {
		$rndkey[$i] = ord($cryptkey[$i % $key_length]);
	}

	for($j = $i = 0; $i < 256; $i++) {
		$j = ($j + $box[$i] + $rndkey[$i]) % 256;
		$tmp = $box[$i];
		$box[$i] = $box[$j];
		$box[$j] = $tmp;
	}

	for($a = $j = $i = 0; $i < $string_length; $i++) {
		$a = ($a + 1) % 256;
		$j = ($j + $box[$a]) % 256;
		$tmp = $box[$a];
		$box[$a] = $box[$j];
		$box[$j] = $tmp;
		$result .= chr(ord($string[$i]) ^ ($box[($box[$a] + $box[$j]) % 256]));
	}

	if($operation == 'DECODE') {
		if((substr($result, 0, 10) == 0 || substr($result, 0, 10) - time() > 0) && substr($result, 10, 16) == substr(md5(substr($result, 26).$keyb), 0, 16)) {
			return substr($result, 26);
		} else {
			return '';
		}
	} else {
		return $keyc.str_replace('=', '', base64_encode($result));
	}

}

function _stripslashes($string) {
	if(is_array($string)) {
		foreach($string as $key => $val) {
			$string[$key] = _stripslashes($val);
		}
	} else {
		$string = stripslashes($string);
	}
	return $string;
}