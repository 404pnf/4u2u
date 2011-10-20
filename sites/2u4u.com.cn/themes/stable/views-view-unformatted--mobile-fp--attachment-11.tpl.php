<?php
// $Id: views-view-unformatted.tpl.php,v 1.6 2008/10/01 20:52:11 merlinofchaos Exp $
/**
 * @file views-view-unformatted.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>

<marquee direction="left" scrollamount="1"  scrollDelay="4" >
<?php foreach ($rows as $id => $row): ?>
    <img src="http://2u4u.com.cn/sites/2u4u.com.cn/themes/stable/mobile/css/images/fangkuang.gif"/>
    
    <?php print $row; ?>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    
<?php endforeach; ?>
</marquee> 
