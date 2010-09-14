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

<LINK href="/sites/2u4u.com.cn/themes/2u4u/shipin/shipinqiehuan.css" type="text/css" rel="stylesheet">
<SCRIPT src="/sites/2u4u.com.cn/themes/2u4u/shipin/jquery.tools.min.js"></SCRIPT>

<?php $i=0; ?>
<?php foreach ($fields as $id => $field): ?>
<?php $i++; ?>
<?php if($i<4):?>  
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
  <?php endif; ?>
<?php endforeach; ?>

<?php $i=0; ?>
<UL class=shipin-tabs>
<?php foreach ($fields as $id => $field): ?>
<?php $i++; ?>
<?php if($i>3):?>
  <LI><A href="#">
    <?php if ($field->label): ?>
      <label class="views-label-<?php print $field->class; ?>">
        <?php print $field->label; ?>:
      </label>
    <?php endif; ?>
	</A> 
	</LI>
  <?php endif; ?>
<?php endforeach; ?>
</UL>


<?php $j=0; ?>
<DIV class=shipin-panes>
<?php foreach ($fields as $id => $field): ?>
  <?php if (!empty($field->separator)): ?>
    <?php print $field->separator; ?>
  <?php endif; ?>
<?php $j++; ?>
<?php if($j>3):?>  
      <?php
      // $field->element_type is either SPAN or DIV depending upon whether or not
      // the field is a 'block' element type or 'inline' element type.
      ?>
	<<?php print $field->inline_html;?> class="views-field-<?php print $field->class; ?>">
      <<?php print $field->element_type; ?> class="field-content"><?php print $field->content; ?></<?php print $field->element_type; ?>>
  </<?php print $field->inline_html;?>>
  <?php endif; ?>
<?php endforeach; ?>
</DIV>

<SCRIPT>
// perform JavaScript after the document is scriptable.
$(function() {
	// setup ul.tabs to work as tabs for each div directly under div.panes
	$("ul.shipin-tabs").tabs("div.shipin-panes > div");
});
</SCRIPT>