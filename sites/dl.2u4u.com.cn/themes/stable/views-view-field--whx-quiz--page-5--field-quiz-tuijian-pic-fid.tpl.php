<?php
// $Id: views-view-field.tpl.php,v 1.1 2008/05/16 22:22:32 merlinofchaos Exp $
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
  * When fetching output from the $row, this construct should be used:
  * $data = $row->{$field->field_alias}
  *
  * The above will guarantee that you'll always get the correct data,
  * regardless of any changes in the aliasing that might happen if
  * the view is modified.
  */
?>

<?php print $output; ?>

<div class="home-shareto">
                                     <!-- ShareTo Button START -->
    <a class="shareto_button" href="http://shareto.com.cn/share.html"><img src="http://video.2u4u.com.cn/sites/video.2u4u.com.cn/themes/video/css/shipin_images/shareto.gif" width="85" alt="分享道" style="border:0"/></a> <script type="text/javascript" src="http://s.shareto.com.cn/js/shareto_button.js"></script>
                                     <!-- ShareTo Button END -->
</div> 