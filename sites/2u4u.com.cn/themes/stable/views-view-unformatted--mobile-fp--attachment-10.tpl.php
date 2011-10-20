<?php
// $Id: views-view-unformatted.tpl.php,v 1.6 2008/10/01 20:52:11 merlinofchaos Exp $
/**
 * @file views-view-unformatted.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/mobile/js/jquery.KinSlideshow-1.2.1.min.js"></SCRIPT>
<div id= "KinSlideshow" style="visibility:hidden;">
<?php foreach ($rows as $id => $row): ?>
    <?php print $row; ?>
<?php endforeach; ?>
</div>
<style>
	#KinSlideshow a img{
		display: block;
	}
</style>
<script type="text/javascript">

$(function(){
	$("#KinSlideshow").KinSlideshow({
			moveStyle:"down",
			intervalTime:4,
			mouseEvent:"mouseover",
			titleBar:{
				titleBar_height:50,	titleBar_bgColor:"#08355c",titleBar_alpha:0.5
			},
            titleFont:{
            	TitleFont_size:14,
            	TitleFont_color:"#FFFFFF"
            }, 
            btn:{
            	btn_bgColor:"#000000",
            	//btn_bgHoverColor:"#1072aa",
            	btn_fontColor:"#FFFFFF",
            	//btn_fontHoverColor:"#FFFFFF",
            	btn_borderColor:"#cccccc",
            	//btn_borderHoverColor:"#1188c0",
            	btn_borderWidth:1
           }
	});
});

</script>