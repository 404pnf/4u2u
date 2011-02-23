<?php
// $Id: swftools-flowplayer3-playlist.tpl.php,v 1.1.2.3 2010/03/29 22:07:14 stuartgreenfield Exp $

/**
 * Prepare themeable output for a playlist
 * The markup is placed in a template so that it can be easily over-ridden by the theme system
 * to allow flexibility
 * 
 * This template is quite complex as it must produce the container for the player, the playlist
 * container that will be duplicated, and the JavaScript code. The template has to produce the
 * JavaScript too as the calling module has no way of knowing how the playlist is going to be
 * built, so it cannot produce the required script itself.
 * 
 * Available variables:
 * - $player_id: The CSS id of the player.
 * - $parameters: The parameters to generate a player as part of the $f() call.
 * - $config: The configuration string for the player.
 * - $height: The player height.
 * - $width: The player width.
 * - $html_alt: The alternate content in the event the player doesn't load
 * 
 */
?>



<?php 
/**
 * This markup defines a playlist container - it will be repeated with each playlist element
 */
?>

<div class="<?php print $player_id; ?> clips petrol" style="float:left">
     
    <!-- single playlist entry as an "template" --> 
    <a href="${url}"> 
        ${title} <!-- <span>${subTitle}</span> --><span>${artist}</span>
        <em>${duration}</em>
    </a>

</div>



<?php 
/**
 * This markup defines a container for the player to be placed in
 */
?>

<div id="<?php print $player_id; ?>" class="swftools-flowplayer3-container" style="float:left">
<?php print $html_alt; ?>
</div>



<?php 
/**
 * This markup defines the script to activate the player and populate the playlist
 * Note that we also set the container height and width in here!
 */
?>
    
<script type="text/javascript">
<!--//--><![CDATA[//><!--
  $(function() {
    flowplayer("<?php print $player_id; ?>", <?php print $parameters; ?>, <?php print $config; ?>);
    flowplayer("<?php print $player_id; ?>").playlist("div.<?php print $player_id; ?>.clips:first", {loop:true});
  });
  $("<?php print $player_id; ?>").height(<?php print $height; ?>).width(<?php print $width; ?>);
//--><!]]>
</script>
