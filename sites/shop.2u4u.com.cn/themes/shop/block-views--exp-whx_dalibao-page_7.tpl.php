<div id="block-<?php print $block->module .'-'. $block->delta ?>" class="<?php print $block_classes . ' ' . $block_zebra; ?>">
  <div class="block-inner">

    <?php if (!empty($block->subject)): ?>
      <h3 class="title block-title"><?php print $block->subject; ?></h3>
    <?php endif; ?>

    <div class="content">
      
	  <form id="views-exposed-form-whx-dalibao-page-7" method="get" accept-charset="UTF-8" action="/shoptest">
		<div class="views-exposed-widget">
			  <?php $searchkeys = $_GET['searchkeys']; ?>
			<input type="text" class="form-text" title="请输入您想搜索的关键词。" value="<?php print $searchkeys; ?>" size="15" id="edit-searchkeys" name="searchkeys" maxlength="128">
			<input type="submit" class="form-submit" value="搜索" id="edit-submit-whx-dalibao">
		</div>
	</form>
	
	  <?php
		$contentterm = $_GET['contentterm'];
		$userpointterm = $_GET['userpointterm'];
		
		if($contentterm == null) $contentterm = "All";
		if($userpointterm == null) $userpointterm = "All";
		
		print '按内容分类：';
			if($contentterm == 'All')		
				print '<span class="active" style="color:red;">'.所有.'&nbsp;&nbsp;</span>';
			else
				print '<a class="term-name" href="?contentterm=All&userpointterm='.$userpointterm.'&searchkeys='.$searchkeys.'">'.所有.'&nbsp;&nbsp;</a>';
			$terms = taxonomy_get_tree(10,9267);
			foreach($terms as $tid=>$term ){
				if($term->tid == $contentterm) 
					print '<span class="active" style="color:red;">'.$term->name.'&nbsp;&nbsp;</span>';
				else
					print '<a class="term-name" href="?contentterm='.$term->tid.'&userpointterm='.$userpointterm.'&searchkeys='.$searchkeys.'">'.$term->name.'&nbsp;&nbsp;</a>';
			}
			
		print '<br>按积分分类：';
			if($userpointterm == 'All')		
				print '<span class="active" style="color:red;">'.所有.'&nbsp;&nbsp;</span>';
			else
				print '<a class="term-name" href="?contentterm='.$contentterm.'&userpointterm=All&searchkeys='.$searchkeys.'">'.所有.'&nbsp;&nbsp;</a>';
			$terms = taxonomy_get_tree(10,9268);
			foreach($terms as $tid=>$term ){
				if($term->tid == $userpointterm) 
					print '<span class="active" style="color:red;">'.$term->name.'&nbsp;&nbsp;</span>';
				else	
					print '<a class="term-name" href="?contentterm='.$contentterm.'&userpointterm='.$term->tid.'&searchkeys='.$searchkeys.'">'.$term->name.'&nbsp;&nbsp;</a>';
			}
	  ?>
    </div>

    <?php print $edit_links; ?>

  </div> <!-- /block-inner -->
</div> <!-- /block -->