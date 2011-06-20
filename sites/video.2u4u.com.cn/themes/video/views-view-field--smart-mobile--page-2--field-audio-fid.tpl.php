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
<!--<pre> <?php print_r($row);?></pre>-->
     <?php 
     	$nid = $row->nid;
     
     
        $file = field_file_load($row->{$field->field_alias});
		$filepath = $file['filepath'];
		//$fileurl = 	file_create_url($filepath);
			
	?>
			
			
<div id="jplayer_<?php print $nid; ?>" class="jp-jplayer"  alt="<?php print $filepath; ?>"></div>

<div class="jp-audio">
	<div class="jp-type-single">
		<div id="jp_interface_<?php print $nid; ?>" class="jp-interface">
			<ul class="jp-controls">
				<li><a href="#" class="jp-play" tabindex="1">play</a></li>
				<li><a href="#" class="jp-pause" tabindex="1">pause</a></li>
				<li><a href="#" class="jp-stop" tabindex="1">stop</a></li>
				<!--
					<li><a href="#" class="jp-mute" tabindex="1">mute</a></li>
					<li><a href="#" class="jp-unmute" tabindex="1">unmute</a></li>
				-->
			</ul>
			<div class="jp-progress">
				<div class="jp-seek-bar">
					<div class="jp-play-bar"></div>
				</div>
			</div>
			<div class="jp-volume-bar">
				<div class="jp-volume-bar-value"></div>
			</div>
			<div class="jp-current-time"></div>
			<div class="jp-duration"></div>
		</div>
	</div>
</div>

