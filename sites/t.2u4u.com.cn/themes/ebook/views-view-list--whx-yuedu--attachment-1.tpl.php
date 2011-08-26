<?php
// $Id: views-view-list.tpl.php,v 1.3 2008/09/30 19:47:11 merlinofchaos Exp $
/**
 * @file views-view-list.tpl.php
 * Default simple view template to display a list of rows.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 */
?>
<?php   

	global $row_num;  
	
	$addClass = '';
	if( $row_num%14 ==0 ){
		$addClass = 'clearr';
	}
	if( $row_num%15 ==0 ){
		$addClass = 'clearl';
		print '<span class="clearfix"></span>';
	}
	
	$row_num++;
?>
<div class="item-list item-list-<?php print $row_num.' '.$addClass;?>">
  <?php if (!empty($title)) : ?>
    <h3><?php print $title; ?></h3>
  <?php endif; ?>
  <<?php print $options['type']; ?>>
    <?php foreach ($rows as $id => $row): ?>
      <li class="<?php print $classes[$id]; ?>"><?php print $row; ?></li>
    <?php endforeach; ?>
  </<?php print $options['type']; ?>>
</div>