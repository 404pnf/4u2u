<?php
// $Id: box.tpl.php,v 1.3 2007/12/16 21:01:45 goba Exp $

/**
 * @file box.tpl.php
 *
 * Theme implementation to display a box.
 *
 * Available variables:
 * - $title: Box title.
 * - $content: Box content.
 *
 * @see template_preprocess()
 */
?>
<div class="box">
<!--<?php if ($title): ?>
  <h2><?php print $title ?></h2>
<?php endif; ?>-->
	<a id="pinglun" name="pinglun"></a>
  <div class="content">
  	<?php print $content ?>

  	<div calss="wordleft-tip">还可以输入 <span class="charsLeft">140</span> 字</div>
  </div>
</div>
<SCRIPT type="text/javascript" src="/misc/jquery.js"></SCRIPT>

<script>
$(function () {
	var max=$(".charsLeft").text();
	
	$('textarea#edit-comment').keyup(function() {
		var text=$(this).val();
		var counter=text.length;
		$(".charsLeft").text(max-counter);
	}); 
	
});

</script>
