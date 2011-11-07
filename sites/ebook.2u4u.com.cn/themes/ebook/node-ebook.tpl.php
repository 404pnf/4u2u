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
<indexAreaStart><!--  索引内容 开始 --></indexAreaStart>
<?php if (!$page): ?>
<h1 class="title"><?php print $title; ?></h1>
<?php endif; ?>
<?php if ($page): ?>
<div class="node <?php print $classes; ?>" id="node-<?php print $node->nid; ?>">
 <div class="node-inner">

  <div class="content clear">
      <div class="ebook_title_bg"><h1 class="title"><?php print $title; ?></h1></div>
	  <div class="ebook_top clearfix">
	  
  
		<div class="yuedu_permission fleft">
			<?php print ebook_output_buy_button($node); ?>

			<?php 
				$output = '';
				$node_terms=taxonomy_node_get_terms($node , $key = 'tid'); 
				foreach($node_terms as $tid => $tmp_term){
					if($tid==10359) 
						$output .= '<div class="pdfdl"><a href="http://shop.2u4u.com.cn/pdfdl">pdf文件下载</a></div>';
				}
				print $output;
			?>
			
			
		</div>
		<div class="fivestar_votes fright">	
				<?php // print fivestar_widget_form($node); ?>
				<?php print $node->content[fivestar_widget]['#value']; ?>
		</div>
	  </div>

	
    	<script>  
	<?php
	      $image = $node->field_yuedu_cover[0]['filepath'];
	      $output = 'var pic="http://ebook.2u4u.com.cn/'.$image.'";';
	      print $output;
	 ?>
	 
	 </script>
	 	
	<?php $block_sharetosina = module_invoke('block', 'block', 'view', 81); ?>
	<?php print $block_sharetosina['content']; ?>
	 
	
	
	
	<div class="author_tags clearfix">
		<?php if(strlen($node->field_yuedu_author[0]['view'])>2):?>		  
			<div class="field_yuedu_author fleft"> <span class="field_label">作者：</span>
				<span class="field_content"><?php print $node->field_yuedu_author[0]['view'] ?></span>
			</div>
		 <?php endif ?>
		<?php if ($terms): ?>
			<div class="ebook_terms terms terms-inline fright"><span class="field_label">标签：</span>
				<span class="field_content"><?php print $terms; ?></span>
			</div>
		<?php endif; ?>
	</div>
			
	<?php if(strlen($node->field_yuedu_summary[0]['view'])>2):?>		  
		<div class="field_yuedu_summary">
			<span class="field_content"><?php print $node->field_yuedu_summary[0]['view'] ?></span>
		</div>
    <?php endif ?>
		
<?php print ebook_output_mp3($node); ?>
		
		<?php if(strlen($node->field_yuedu_player[0]['view'])>2):?>		  
			<div class="field_yuedu_player"> 
				<a id="yuedu_player" name="yuedu_player"></a><span class="field_content"><?php print $node->field_yuedu_player[0]['view'] ?></span>
			</div>
		<?php endif ?>
     
    </div>


    <indexAreaEnd><!--  索引内容 结束 --></indexAreaEnd>
    <?php if ($links): ?> 
      <div class="links clear"> <?php print $links; ?></div>
    <?php endif; ?>

	
		<?php 

		$output=""; 
		$output2=""; 
		$node_terms=taxonomy_node_get_terms($node , $key = 'tid'); 
		foreach($node_terms as $tid => $tmp_term){
			$output .= $tid.",";
			$output2 .= phptemplate_get_videoterms('termid_by_name','default',$tmp_term->name);
		}
		$output=substr($output,0,strlen($output)-1);
		$output2=substr($output2,0,strlen($output2)-1);
	?>
	<?php 
				$relate_video ='';
				//$relate_ebook ='';
				
				$relate_ebook =views_embed_view('yuedu_taxonomy_term','block_2',$node->nid,$output);
				$relate_video =phptemplate_get_video('media_taxonomy_term','block_3',$output2);
				
				
				if(strlen($relate_video)>146) {
					$relate_video .='<div class="more-link"><a href="http://video.2u4u.com.cn/erelate/'.$output2.'">更多>></a></div>'; 
				}
				else {
					$relate_ebook =views_embed_view('yuedu_taxonomy_term','block_3',$node->nid,$output);
					$relate_ebook = '<div class="ebook_none_mrelate">'.$relate_ebook.'</div>';
				}
			?>
	<div class="relatebox">
		<? print $relate_ebook; ?>
		<div class="video_relate">
			<? print $relate_video; ?>
		</div>
	</div>
	
	
 </div> <!-- /node-inner -->
</div> <!-- /node-->
<?php endif; ?>
