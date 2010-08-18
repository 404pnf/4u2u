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
<div class="node <?php print $classes; ?>" id="node-<?php print $node->nid; ?>">
 <div class="node-inner">

  <div class="content clear">
   <div class="ebook_ad_top clearfix">
		  <div class="ebook_ad_left fleft">
			<div class="ebook_title_bg"><h1 class="title"><?php print $title; ?></h1></div>
				
			<?php 	$flag = flag_get_flag('yuedu_freebie'); if($flag && $flag->is_flagged($node->nid)): ?>
						<div id='points_free'>
							<a href="#yuedu_player">免费阅读</a> 
						</div>
			<?php else: ?>   
				<?php if (!yuedu_check_access($node->nid)): ?>
						<div id='points'><a title="购买本图书" href = "/yuedu/buy/<?=$node->nid?>" class="duihuan"><span class="price"><?php print $node->field_yuedu_pricebypoints[0]['value'];?></span><span class="price_unit">积分</span></a>
						</div>  
						
				<?php endif;?>  
			<?php endif;?>  
			
				<?php 
					if (user_is_anonymous()){
						print t('想阅读更多页面,请').l('登录','user/login');
					} 
				?>
				
				<?php 
					$output = '';
					$node_terms=taxonomy_node_get_terms($node , $key = 'tid'); 
					foreach($node_terms as $tid => $tmp_term){
						if($tid==10359) 
							$output .= '<div class="pdfdl"><a href="http://shop.2u4u.com.cn/pdfdl">pdf文件下载</a></div>';
					}
				?>		 
				<?php print $output?>
					
				<?php if(strlen($node->field_yuedu_author[0]['view'])>2):?>		  
					<div class="field_yuedu_author"> <span class="field_label">作&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;者：</span>
						<span class="field_content"><?php print $node->field_yuedu_author[0]['view'] ?></span>
					</div>
				 <?php endif ?>
				<?php if ($terms): ?>
					<div class="ebook_terms terms terms-inline"><span class="field_label">标&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;签：</span>
						<span class="field_content"><?php print $terms; ?></span>
					</div>
				<?php endif; ?>
			</div>	
			
			<div id="ebook_ad" class="ebook_ad_right fright">
				<?php $block = module_invoke('block', 'block', 'view', 77); ?>	
				<?php print $block['content']; ?>
			</div>	
	</div>
	
		<?php if(strlen($node->field_yuedu_summary[0]['view'])>2):?>		  
			<div class="field_yuedu_summary"> <span class="field_label">内容简介：</span>
				<span class="field_content"><?php print $node->field_yuedu_summary[0]['view'] ?></span>
			</div>
		<?php endif ?>
		<?php if(strlen($node->field_yuedu_player[0]['view'])>2):?>		  
			<div class="field_yuedu_player"> 
				<a id="yuedu_player" name="yuedu_player"></a><span class="field_content"><?php print $node->field_yuedu_player[0]['view'] ?></span>
			</div>
		 <?php endif ?>
      <?php //print $content; ?>
    </div>

    
    <?php if ($links): ?> 
      <div class="links clear"> <?php print $links; ?></div>
    <?php endif; ?>

  </div> <!-- /node-inner -->
</div> <!-- /node-->