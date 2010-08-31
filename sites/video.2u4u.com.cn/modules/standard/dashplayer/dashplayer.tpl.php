<object id="<?php print $id; ?>" classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" width="<?php print $width; ?>" height="<?php print $height; ?>" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab">
   <param name="movie" value="<?php print $player; ?>" />
   <param name="FlashVars" value="<?php print $flashvars; ?>" />
   <param name="quality" value="high" />
   <param name="wmode" value="transparent" />
   <param name="allowfullscreen" value="true" />
   <param name="allowScriptAccess" value="always" />
   <embed name="<?php print $id; ?>" swliveconnect="true" allowScriptAccess="always" src="<?php print $player; ?>" 
      width="<?php print $width; ?>" 
      height="<?php print $height; ?>" 
      border="0" 
      type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer"
      wmode="transparent" allowfullscreen="true" quality="high" flashvars="<?php print $flashvars; ?>" />
</object>