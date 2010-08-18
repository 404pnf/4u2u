<?php
// $Id: node.tpl.php,v 1.4.2.1 2009/05/12 18:41:54 johnalbin Exp $

/**
 * @file node.tpl.php
 *
 * Theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: Node body or teaser depending on $teaser flag.
 * - $picture: The authors picture of the node output from
 *   theme_user_picture().
 * - $date: Formatted creation date (use $created to reformat with
 *   format_date()).
 * - $links: Themed links like "Read more", "Add new comment", etc. output
 *   from theme_links().
 * - $name: Themed username of node author output from theme_user().
 * - $node_url: Direct url of the current node.
 * - $terms: the themed list of taxonomy term links output from theme_links().
 * - $submitted: themed submission information output from
 *   theme_node_submitted().
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $teaser: Flag for the teaser state.
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 */
?>



<script src="/misc/jquery.js" type="text/javascript"></script> 
<?php   if($node->type != 'best_answer'||$teaser):?>
<div class="shipin-terms"><div class="terms_label">分类导航>>  </div><?php print views_embed_view('shipin_terms', $display_id = 'default');?></div>
<div id="node-<?php print $node->nid; ?>" class="<?php  print $classes;  ?>">
<div class="node-inner">
  <?php if ($node->type == 'shipin'): ?>
    <h2 class="title">
      <?php print $title; ?>
    </h2>
  <?php endif; ?>

   <?php if ($unpublished): ?>
    <div class="unpublished"><?php print t('Unpublished'); ?></div>
  <?php endif; ?> 

  <?php if ($submitted || $terms): ?>
    <div class="meta">
      <?php if ($submitted): ?>
        <div class="submitted">
          <?php print $submitted; ?>
        </div>
      <?php endif; ?>


    </div>
  <?php endif; ?>

  <div class="content">
     <div id="shipin-tab_area">
     <div id="shipin_area">
    <div class="field field-type-filefield field-field-shipin-upload">
		   <div class="field-items">
		      <div class="field-item">
		      	<?php if (video_perm_check_access($node->nid)) : ?>
					<?php print $node->field_shipin_upload[0]['view']; ?>
					<?php if ($terms): ?>
						<div class="terms terms-inline"><?php print ('标&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;签：') . $terms; ?></div>
					<?php endif; ?>
					<?php if ($date): ?>
						<div class="date node-shipin-date"><span class="date_label">发布时间：</span><span class="date"><?php print $date; ?></span></div>
					<?php endif; ?>
         	   <?php else : ?>          
					<?php print $node->field_shipin_cover[0]['view']; ?>
					<?php if ($terms): ?>
						<div class="terms terms-inline"><?php print ('标&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;签：') . $terms; ?></div>
					<?php endif; ?>
					<?php if ($date): ?>
						<div class="node-shipin-date"><span class="date_label">发布时间：</span><span class="date"><?php print $date; ?></span></div>
					<?php endif; ?>
						<div id='points'>
							<div class="points_label">视频积分：<?php print $node->field_shipin_points[0]['value'];?></div>
							<div class="points_image">	<a title="购买本视频" href = "/shipin/buy/<?=$node->nid?>"><img src="http://video.2u4u.com.cn/sites/video.2u4u.com.cn/themes/video/css/shipin_images/duihuanshipin.gif"></a></div>
						</div> 
					
				<?php endif;?>
				
				<?php if ($comment): ?>
					<?php if ($logged_in): ?>
						<div class="shipin-comment"><a href="#pinglun">发表评论</a></div>
					<?php else : ?> 
						<div class="shipin-comment">登录后才能发表评论，请您先<a href="http://2u4u.com.cn/user">登录</a>或<a href="http://2u4u.com.cn/user/register">注册</a></div>
					<?php endif; ?> 
				<?php endif; ?> 
					<div class="shipin-shareTo">
						<!-- ShareTo Button START -->
						<a class="shareto_button" href="http://shareto.com.cn/share.html"><img src="http://video.2u4u.com.cn/sites/video.2u4u.com.cn/themes/video/css/shipin_images/shareto.gif" alt="分享道" style="border:0"/></a>
						<script type="text/javascript" src="http://s.shareto.com.cn/js/shareto_button.js"></script>
						<!-- ShareTo Button END -->
					</div>
					<div class="shipin_links"><?php print $links; ?></div>

			</div>
	  </div>
	</div>
<!-- 		<div class="field field-type-text field-field-shipin-neirong">
     <?php if(strlen($node->field_shipin_neirong[0]['view'])>2):?>		  
         <h3 class="field-label">背景介绍</h3>
        <?php endif ?>
                <div class="field-items">
		      <div class="field-item"><?php print $node->field_shipin_neirong[0]['view'] ?></div>
		  </div>
		</div> -->
  </div>


<div id="tab_area">
<ul class="shipin-tabs"> 
<?php $i=0 ;?>
<?php foreach ($node as $id => $field): ?>
<?php if(strpos($id,'field_shipin')!==false):?>
<?php $i++;?>
<?php // print $i."----".$id;?>
<?php endif;?>  
<?php if(($i==1|($i>3&&$i<=6))&&strlen($field[0]['view'])>2):?>
<LI id="tab<?php print $i ?>"><a href="#"><?php print $node->content[$id]['field']['#title'];?></a></LI> 
<?php endif;?>
<?php endforeach; ?>
</UL> 

<!-- tab "panes" --> 
<?php $j=0;?>
<DIV class="shipin-panes"> 
<?php foreach ($node as $id => $field): ?>
<?php if(strpos($id,'field_shipin')!==false):?>
<?php $j++;?>
<?php endif;?>  
<?php if(($j==1|($j>3&&$j<=6))&&strlen($field[0]['view'])>2):?>   
<DIV id="pane<?php print $j ?>"><?php print $field[0]['view'];?></DIV> 
<?php endif;?>    
<?php endforeach; ?>
</DIV>
</div>
<div style="clear:both"></div>
</div>

	<?php 

		$output=""; 
		$output2=""; 
		$node_terms=taxonomy_node_get_terms($node , $key = 'tid'); 
		foreach($node_terms as $tid => $tmp_term){
			$output .= $tid.",";
			$output2 .= phptemplate_get_ebookterms('termid_by_name','default',$tmp_term->name);
		}
		$output=substr($output,0,strlen($output)-1);
		$output2=substr($output2,0,strlen($output2)-1);
	?>
	<div class="relatebox">
		<? print views_embed_view('media_taxonomy_term','block_1',$node->nid,$output);?>
		<div class="ebook_relate">
			<? print phptemplate_get_ebook('yuedu_taxonomy_term','block_1',$output2); ?>
			<? print '<div class="more-link"><a href="http://ebook.2u4u.com.cn/mrelate/'.$output2.'">更多>></a></div>';  ?>
		</div>
	</div>
</div>
</div>
</div> <!-- /node-inner, /node -->
  
<?php endif; ?>  
<script>
// perform JavaScript after the document is scriptable.
$(function() {
	// setup ul.tabs to work as tabs for each div directly under div.panes
	$("div.shipin-panes div").hide();
	$("div.shipin-panes").children().eq(0).show();
	$("ul.shipin-tabs").children().eq(0).addClass("current");
	$("ul.shipin-tabs li").click(function(){
		$("ul.shipin-tabs li").removeClass("current");
		$(this).addClass("current");
		$("div.shipin-panes div").hide();
		$("div.shipin-panes #pane"+this.id.slice(-1)).show();	
		return false;
	});
});
</script>

