<div id="aispeech-top">
	<img src="<?php print base_path().drupal_get_path('module', 'aispeech') ?>/images/test1.jpg" width="332" height="49" />
</div>
<div id="aispeech-center">
	<div id="aispeech-word"><?php print $word->spell; ?></div>
	<div id="aispeech-explain"><?php print $word->explaination ?></div>
</div>

<div id="aispeech-result">
	<div id="aispeech-result-A" style="display:none"><img src="<?php print base_path().drupal_get_path('module', 'aispeech') ?>/images/testA.jpg" width="87" height="127" /></div>
	
	<div id="aispeech-result-B" style="display:none"><img src="<?php print base_path().drupal_get_path('module', 'aispeech') ?>/images/testB.jpg" width="87" height="127" /> </div>
	
	<div id="aispeech-result-C" style="display:none"><img src="<?php print base_path().drupal_get_path('module', 'aispeech') ?>/images/testC.jpg" width="87" height="127" /> </div>
	
	<div id="aispeech-result-D" style="display:none"><img src="<?php print base_path().drupal_get_path('module', 'aispeech') ?>/images/testD.jpg" width="87" height="127" /> </div>
</div>

<div id="aispeech-result2" style="display:none">
	<table width="140" border="0" align="center" cellpadding="0" cellspacing="0">
	  <tr>
		<td width="19%"><img src="<?php print base_path().drupal_get_path('module', 'aispeech') ?>/images/test4.jpg" width="25" height="24" /></td>
		<td width="79%">您获得1个悠游积分</td>
	  </tr>
	</table>
</div>

<div id="aiRecorder-wrapper"><div id="aiRecorder"> </div></div>
<div id="aiPlayer1-wrapper"><div id="aiPlayer1" ><a href="http://www.adobe.com/go/getflashplayer"></a></div></div>

<div id="charsContainer" style="display:none"> </div>
<div id="aispeech-user-login" style="display:none"><?php global $user; print $user->uid ?></div>

<div id="aispeech-button">
	<table border="0" cellspacing="0" cellpadding="0" id="aispeech-table-step-1" >
	  <tr>
		<td width="40">&nbsp;</td>
		<td class="aispeech-tdbutton">
			<table border="0" cellspacing="0" cellpadding="0">
				<tr>
				  <td align="center"><img src="<?php print base_path().drupal_get_path('module', 'aispeech') ?>/images/laba.gif" /></td>
				  <td ><div id="readit-wrapper"><a href="#" id="readit">听&nbsp;&nbsp;&nbsp;&nbsp;读</a></div></td>
				</tr>
			  </table>
		  </td>
		<td>&nbsp;</td>
		<td class="aispeech-tdbutton"><div id="next-word-wrapper"><a href="#" id="next-word">下一个 </a></div></td>
		<td>&nbsp;</td>
	  </tr>
	</table>	
	<table border="0" cellspacing="0" cellpadding="0" id="aispeech-table-step-2" style="display:none">
	  <tr>
		<td  width="70">&nbsp;</td>
		<td class="aispeech-tdbutton2">
			<table border="0" cellspacing="0" cellpadding="0">
				<tr>
				  <td align="center"><img src="<?php print base_path().drupal_get_path('module', 'aispeech') ?>/images/renlian.gif" width="16" height="12" /></td>
				  <td ><div id="read-after-wrapper"><a href="#" id="followit">跟&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;读</a></div></td>
				</tr>
			  </table>
		</td>
		<td>&nbsp;</td>
	   </tr>
	</table>
	
	<!--<table width="282" border="0" cellspacing="0" cellpadding="0" id="aispeech-table-step-3" style="display:none">-->
	<table border="0" cellspacing="0" cellpadding="0" id="aispeech-table-step-3" style="display:none">
	  <tr>
		<td width="146">
			<table border="0" cellspacing="0" cellpadding="0">
			  <tr>
				<td align="center"><span id="defaultCountdown"></span></td>
			  </tr>
			  <tr>
				<td align="center" class="td02">正在录音</td>
			  </tr>
			</table>
		 </td>
		 <td width="25">&nbsp;</td>
		 <td width="120" class="aispeech-tdbutton2">
			 <table border="0" cellspacing="0" cellpadding="0" width="120"> 
				<tr>
				  <td width="30" align="center"><img src="<?php print base_path().drupal_get_path('module', 'aispeech') ?>/images/duigou.gif" width="15" height="15"  /></td>
				  <td width="96"><div id="testing-wrapper">正在录音</div></td>
				</tr>
			  </table>
		  </td>
		</tr>
	</table>
	<table width="120" border="0" align="center" cellpadding="0" cellspacing="0"  id="aispeech-table-step-4" style="display:none">

      <tr>
      	<td  width="90">&nbsp;</td>
		<td width="129" class="aispeech-tdbutton2"><div id="next-word-wrapper1"><a href="#" id="next-word1">下一个单词</a></div></td>
        	<td>&nbsp;</td>
	   </tr>
	</table>
</div>

<div id="aispeech-footer" align="center"><a href="http://www.askform.cn/3381-43724.aspx" target="_blank"><img src="<?php print base_path().drupal_get_path('module', 'aispeech') ?>/images/test6.jpg" width="208" height="42" /></a>
</div>
<div id="aispeech-foot"></div>
