<?php
$app_dir="/games";

$admin_id="administrator";
$admin_password="changeit";//����Ա���룬��ס����ʽ������ʱ��һ��Ҫ�޸�
/*
score �ǳ��еĻ��ֵȼ�
rate�ǳ��еĸ���
max�Ǹõȼ���෢�Ŷ��ٸ���
*/
$awards_levels=array(0=>array('score'=>100,'rate'=>5,'max'=>2),1=>array('score'=>50,'rate'=>10,'max'=>5),2=>array('score'=>10,'rate'=>45,'max'=>10));
$awards_min_score=300;//��������߷ִﵽ���ٷ���ʱ���ܳ齱
$award_open=TRUE;//��ʾ�Ƿ���Կ��ų����˽�

include 'conn.php';

?>