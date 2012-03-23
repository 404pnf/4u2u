<div class="ai_speech">
	<?php
		$block = module_invoke('aispeech', 'block', 'view', 0);
	   print $block['content'];
	?>	
</div>
<div class="google_gg">
	<?php	
		$block_googlead = module_invoke('block', 'block', 'view', 83);
	   print $block_googlead['content'];
	?>
</div>

