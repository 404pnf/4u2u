<?php
 /**
  * This template is used to print a single field in a view. It is not
  * actually used in default Views, as this is registered as a theme
  * function which has better performance. For single overrides, the
  * template is perfectly okay.
  *
  * Variables available:
  * - $view: The view object
  * - $field: The field handler object that can process the input
  * - $row: The raw SQL result that can be used
  * - $output: The processed output that will normally be used.
  *
  * When fetching output from the $row, copy and paste the following snippet:
  * $data = $row->{$field->field_alias}
  *
  * The above will guarantee that you'll always get the correct data,
  * regardless of any changes in the aliasing that might happen if
  * the view is modified.
  */
?>
<?php if($output):?>
<a href="#" gotoURL="txbookurl:##<?php print $row->nid; ?>##http://2u4u.com.cn/xieq/<?php print $row->node_data_field_ebook_link_field_ebook_link_value; ?>"  nid="<?php print $row->nid; ?>"><?php print $output; ?></a>
<?php endif;?>