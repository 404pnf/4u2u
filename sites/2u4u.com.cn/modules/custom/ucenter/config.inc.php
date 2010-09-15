<?php

//define('UC_CONNECT', 'mysql');				// 连接 UCenter 的方式: mysql/NULL, 默认为空时为 fscoketopen()
// mysql 是直接连接的数据库, 为了效率, 建议采用 mysql



define('UC_CONNECT', 'mysql');
define('UC_DBHOST', 'localhost');
define('UC_DBUSER', 'wzs');
define('UC_DBPW', 'wuzhangshu');
define('UC_DBNAME', 'uchome');
define('UC_DBCHARSET', 'utf8');
define('UC_DBTABLEPRE', '`uchome`.uc_');
define('UC_DBCONNECT', '0');
define('UC_KEY', '9999Nbder3I5rbNeu6u2g1G4Gdj6F6K8Ba30obb1CfZf76yaCcodd2zfRb3196uc');
define('UC_API', 'http://u.2u4u.com.cn/ucenter');
define('UC_CHARSET', 'utf-8');
define('UC_IP', '221.122.115.57');
define('UC_APPID', '3');
define('UC_PPP', '20');






//数据库相关 (mysql 连接时, 并且没有设置 UC_DBLINK 时, 需要配置以下变量)
//define('UC_DBHOST', 'localhost');			// UCenter 数据库主机
//define('UC_DBUSER', 'root');				// UCenter 数据库用户名
//define('UC_DBPW', '');					// UCenter 数据库密码
//define('UC_DBNAME', 'ucenter');				// UCenter 数据库名称
//define('UC_DBCHARS/T', 'utf8');				// UCenter 数据库字符集
//define('UC_DBTABLEPRE', 'ucenter.uc_');			// UCenter 数据库表前缀

//通信相关
//define('UC_KEY', '123456789');				// 与 UCenter 的通信密钥, 要与 UCenter 保持一致
<<<<<<< HEAD
//define('UC_API', 'http://u.2u4u.com.cn/ucenter');	// UCenter 的 URL 地址, 在调用头像时依赖此常量
=======
<<<<<<< HEAD
//define('UC_API', 'http://u.2n4n.com.cn/ucenter');	// UCenter 的 URL 地址, 在调用头像时依赖此常量
=======
//define('UC_API', 'http://u.2u4u.com.cn/ucenter');	// UCenter 的 URL 地址, 在调用头像时依赖此常量
>>>>>>> 38bb059944fd61a7cfe8c157a96ad4d10e7dd137
>>>>>>> 9e2f05ab6c023db767b6cf2c5d5072543ee31dd3
//define('UC_CHARSET', 'utf8');				// UCenter 的字符集
//define('UC_IP', '');					// UCenter 的 IP, 当 UC_CONNECT 为非 mysql 方式时, 并且当前应用服务器解析域名有问题时, 请设置此值
//define('UC_APPID', 1);					// 当前应用的 ID

// 应用程序数据库连接参数
$database = 'mysql';
$dbhost = 'localhost';				// 数据库服务器
$dbuser = 'wzs';		// 数据库用户名
$dbpw = 'wuzhangshu';		// 数据库密码
$dbname = 'uchome';				// 数据库名
$pconnect = 0;						// 数据库持久连接 0=关闭, 1=打开
$tablepre = '';   		// 表名前缀, 同一数据库安装多个论坛请修改此处
$dbcharset = 'utf8';				// MySQL 字符集, 可选 'gbk', 'big5', 'utf8', 'latin1', 留空为按照论坛字符集设定

//同步登录 Cookie 设置
$cookiedomain = '.2u4u.com.cn'; 	// cookie 作用域
$cookiepath = '/';					// cookie 作用路径