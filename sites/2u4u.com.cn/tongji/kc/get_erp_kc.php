<?php
   $emno = $_GET['sku'];
   $kc = file_get_contents('http://2u4u.com.cn/erp_kc?sku='.$emno);
   var_dump($kc);
?>