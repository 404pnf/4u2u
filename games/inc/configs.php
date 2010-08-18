<?php
$app_dir="/games";

$admin_id="administrator";
$admin_password="changeit";//管理员密码，记住在正式发布的时候一定要修改
/*
score 是抽中的积分等级
rate是抽中的概率
max是该等级最多发放多少个奖
*/
$awards_levels=array(0=>array('score'=>100,'rate'=>5,'max'=>2),1=>array('score'=>50,'rate'=>10,'max'=>5),2=>array('score'=>10,'rate'=>45,'max'=>10));
$awards_min_score=300;//当单关最高分达到多少分数时才能抽奖
$award_open=TRUE;//表示是否可以开放抽幸运奖

include 'conn.php';

?>