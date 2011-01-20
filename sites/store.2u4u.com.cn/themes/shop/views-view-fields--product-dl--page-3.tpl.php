<?php
// $Id: views-view-fields.tpl.php,v 1.6 2008/09/24 22:48:21 merlinofchaos Exp $
/**
 * @file views-view-fields.tpl.php
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->separator: an optional separator that may appear before a field.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>
<?php foreach ($fields as $id => $field): ?>
  <?php if (!empty($field->separator)): ?>
    <?php print $field->separator; ?>
  <?php endif; ?>

  <<?php print $field->inline_html;?> class="views-field-<?php print $field->class; ?>">
    <?php if ($field->label): ?>
      <label class="views-label-<?php print $field->class; ?>">
        <?php print $field->label; ?>:
      </label>
    <?php endif; ?>
      <?php
      // $field->element_type is either SPAN or DIV depending upon whether or not
      // the field is a 'block' element type or 'inline' element type.
      ?>
      <<?php print $field->element_type; ?> class="field-content"><?php print $field->content; ?></<?php print $field->element_type; ?>>
  </<?php print $field->inline_html;?>>
<?php endforeach; ?>

<?php 
/* $str = $fields['sell_price']->handler->original_value;
$str = preg_match('/\d+/',$str,$matches); */
//$price_num = shop_dl_sellprice($fields);
$price_num = shop_dl_sellprice($fields['sell_price']->handler);
if($price_num==2)
{
	 print ' 
	 <div id="mobile1_gundong" class="gundong">
		<span class="title"> <a href="/dlprice/2" target="_blank">其他2元产品 </a></span>
									<a id="next1" ></a><!--向后滚动的按钮 因为float是right，所以next与prev调换位置-->
									<div class="navi"></div><!-- navigator 确定每个页面的圆圈-->
									<a id="prev1"></a><!--向前滚动的按钮-->';
	print views_embed_view('product_dl', $display_id = 'attachment_5');
	print '</div>';
}
else if($price_num==10)
{
	 print '
	 <div id="mobile1_gundong" class="gundong"><span class="title"> <a href="/dlprice/3" target="_blank">其他10元产品 </a></span>
									<a id="next2" ></a><!--向后滚动的按钮 因为float是right，所以next与prev调换位置-->
									<div class="navi"></div><!-- navigator 确定每个页面的圆圈-->
									<a id="prev2"></a><!--向前滚动的按钮-->';
	print views_embed_view('product_dl', $display_id = 'attachment_6');
	print '</div>';
}
else if($price_num==0)
{
	 print '
	 <div id="mobile1_gundong" class="gundong"><span class="title"> <a href="/dlprice/0" target="_blank">其他免费资源 </a></span>
									<a id="next3" ></a><!--向后滚动的按钮 因为float是right，所以next与prev调换位置-->
									<div class="navi"></div><!-- navigator 确定每个页面的圆圈-->
									<a id="prev3"></a><!--向前滚动的按钮-->';
	print views_embed_view('product_dl', $display_id = 'attachment_7');
	print '</div>';
}
else
	return; 
?>



