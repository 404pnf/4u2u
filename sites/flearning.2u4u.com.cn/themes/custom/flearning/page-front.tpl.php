<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

  <head>
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>

	<meta name="viewport" content="width=device-width;"/>

	<link href="<?php print $base_path.$directory?>/css/common.css" media="all" rel="stylesheet" type="text/css">
	<link href="<?php print $base_path.$directory?>/css/mobile.css" media="all" rel="stylesheet" type="text/css">
	<link href="<?php print $base_path.$directory?>/css/mfront.css" media="all" rel="stylesheet" type="text/css">

	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery.js"></SCRIPT>
	<script language="javascript" type="text/javascript" src="<?php print $base_path.$directory?>/js/txgenerictools.js" ></script>
	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery.flearning.common.js"></SCRIPT>
		
  </head>

  <body class="<?php print $body_classes; ?>">

    <div id="main">
    <!--
	  	<div class="toolbar">
			<span  id="paihang" class="button common_btn over_button">排行</span>
			
			<span id="shoucang" class="button common_btn over_button">收藏</span> 
			
			<span class="button title_btn"> <a href="/"><img src="<?php print $base_path.$directory?>/css/images/fltrp.png" /> 精华版</a></span>
			
			<span id="info" class="button common_btn info_btn over_button"> <img src="<?php print $base_path.$directory?>/css/images/info.png" /> </span> 
			
			<span id="lishi" class="button common_btn over_button">历史</span>
			
			<span id="yanzheng" class="button common_btn over_button">验证</span>
			
		  </div>
	
	-->
	
      <div id="page">
        <div id="page-inner" class="inner column center">
		
		
			<!--内容-->
			<div id= "page_content" >
			
				
				<? print views_embed_view('mobile', $display_id = 'tuijian');?>	
				
				<div class="fenglei">
					<table>
						<tr>
							<td>
								<div class="term_image">
									<a href="search/term?tid=四六级"><img src="<?php print $base_path.$directory?>/css/images/siji.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=四六级">四六级</a>
								</div>
								<div class="term_description">
									大学英语四六级考试
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=考试"><img src="<?php print $base_path.$directory?>/css/images/liuji.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=考试">其他考试</a>
								</div>
								<div class="term_description">
									其他考试资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=留学"><img src="<?php print $base_path.$directory?>/css/images/kaoshi.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=留学">留学</a>
								</div>
								<div class="term_description">
									留学攻略全知道
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="http://test.2u4u.com.cn/flearningegs/www/mobile_index.html"><img src="<?php print $base_path.$directory?>/css/images/egs.png" /></a>
								</div>
								<div class="term_name">
									<a href="http://test.2u4u.com.cn/flearningegs/www/mobile_index.html">EGS 测试</a>
								</div>
								<div class="term_description">
									诊断性测试及专项练习
								</div>
								
							</td>
						</tr>
						
						<tr>
							<td>
								<div class="term_image">
									<a href="search/term?tid=小语种"><img src="<?php print $base_path.$directory?>/css/images/xiaoyuzhong.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=小语种">小语种</a>
								</div>
								<div class="term_description">
									各个小语种资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=文学"><img src="<?php print $base_path.$directory?>/css/images/wenxue.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=文学">文学</a>
								</div>
								<div class="term_description">
									各国文学资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=演讲"><img src="<?php print $base_path.$directory?>/css/images/yanjiang.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=演讲">演讲</a>
								</div>
								<div class="term_description">
									CCTV杯演讲比赛
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=辩论"><img src="<?php print $base_path.$directory?>/css/images/bianlun.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=辩论">辩论</a>
								</div>
								<div class="term_description">
									外研社杯英语辩论赛
								</div>
								
							</td>
						</tr>
						
						<tr>
							<td>
								<div class="term_image">
									<a href="search/term?tid=双语"><img src="<?php print $base_path.$directory?>/css/images/shuangyu.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=双语">双语</a>
								</div>
								<div class="term_description">
									双语读物
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=翻译"><img src="<?php print $base_path.$directory?>/css/images/fanyi.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=翻译">翻译</a>
								</div>
								<div class="term_description">
									翻译相关资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=珠宝"><img src="<?php print $base_path.$directory?>/css/images/zhubao.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=珠宝">珠宝</a>
								</div>
								<div class="term_description">
									珠宝系列资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=服饰"><img src="<?php print $base_path.$directory?>/css/images/fushi.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=服饰">服饰</a>
								</div>
								<div class="term_description">
									各类服饰英语
								</div>
								
							</td>
						</tr>
						
						<tr>
							<td>
								<div class="term_image">
									<a href="search/term?tid=名人"><img src="<?php print $base_path.$directory?>/css/images/mingshi.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=名人">名人</a>
								</div>
								<div class="term_description">
									名人传记
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=旅游"><img src="<?php print $base_path.$directory?>/css/images/lvyou.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=旅游">旅游</a>
								</div>
								<div class="term_description">
									旅游类资源
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=结婚"><img src="<?php print $base_path.$directory?>/css/images/jiehun.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=结婚">结婚</a>
								</div>
								<div class="term_description">
									我们结婚吧
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=动物"><img src="<?php print $base_path.$directory?>/css/images/dongwu.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=动物">动物</a>
								</div>
								<div class="term_description">
									动物世界
								</div>
								
							</td>
						</tr>
						
						<tr>
							<td>
								<div class="term_image">
									<a href="search/term?tid=汽车"><img src="<?php print $base_path.$directory?>/css/images/qiche.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=汽车">汽车</a>
								</div>
								<div class="term_description">
									汽车故事
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=电影"><img src="<?php print $base_path.$directory?>/css/images/dianying.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=电影">电影</a>
								</div>
								<div class="term_description">
									看电影学英语
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=美食"><img src="<?php print $base_path.$directory?>/css/images/meishi.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=美食">美食</a>
								</div>
								<div class="term_description">
									各类美食英语
								</div>
								
							</td>
							<td>
								<div class="term_image">
									<a href="search/term?tid=城市"><img src="<?php print $base_path.$directory?>/css/images/chengshi.png" /></a>
								</div>
								<div class="term_name">
									<a href="search/term?tid=城市">城市</a>
								</div>
								<div class="term_description">
									各国城市故事
								</div>
								
							</td>
						</tr>
						
					
					
					</table>
					

				</div>
				
				
				
				
				
			</div>		
		 </div> <!-- /page-inner -->
	  </div> <!-- /page -->
	  
	  
	  <!--
	  
	  <div class="footbar">
		<?php //print $footer_block; ?>
		<div id="advanced_search"><a class="button common_btn" href="/advanced/search">高级检索</a></div>
        
	  </div>
	 -->
	 
<!-- toolbar 中显示与隐藏的内容 -->
<div id="over_content" >

	<div id="over_paihang" class="overlayer">
		<div class="arrow">
			
		</div>
		
		<div class="content">
			<div class="content-inner">
				<? print views_embed_view('paihangbang', $display_id = 'paihang_page');?>
			</div>
		</div>
	</div>
	
	<div id="over_shoucang" class="overlayer">
		<div class="arrow">
			
		</div>
		
		<div class="content">
			<div class="content-inner">
				<? print views_embed_view('flag_bookmarks_lishi', $display_id = 'shoucang_page');?>
			</div>
		</div>
	</div>
	
	<div id="over_info" class="overlayer">
		<div class="arrow">
			
		</div>
		
		<div class="content">
			<div class="content-inner">
				<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;本版是外研社iLearning外语自主学习资源库的移动学习客户端，iLearning以全球化的国际视野，与国际顶尖合作伙伴共同打造非母语环境下的外语学习解决方案。资源整合了国内外知名媒体（BBC、VOA、ITN
CHINADAILY等），顶尖教育出版机构（剑桥、牛津、培生、麦克米伦等）的优质专业内容，为广大学习者构建了一个自主学习的多媒体、多语种、多终端外语学习平台。</p>

			</div>
		</div>
	</div>
	
	<div id="over_lishi" class="overlayer">
		<div class="arrow">
			
		</div>
		
		<div class="content">
			<div class="content-inner">
				<? print views_embed_view('flag_bookmarks_lishi', $display_id = 'lishi_page');?>
			
			</div>
		</div>
	</div>
	
	
	<div id="over_yanzheng" class="overlayer">
		<div class="arrow">
			
		</div>
		
		<div class="content">
			<div class="content-inner">
				<?php 
					$block = module_invoke("iLearning_serial","block", "view",0);
		
					print $block["content"]; 
				?>
			
			</div>
		</div>
	</div>
	
</div>
<!--  end toolbar 中显示与隐藏的内容 -->	 
	 
	</div> <!-- /main -->


<script type="text/javascript">
/*
$(function(){
	var params ={"btnLeft" : "600", "btnwidth" : "60","btnstatus":"","machineID":"7ccc31e0ddd2a215938c0f8fbc223056"};//btnLeft:按钮位置，距离左侧边距绝对位置，btnwidth：按钮宽度大小，btnstatus：按钮状态，""或者"normal"表示未点击的按钮，"touched"或其他值表示已经点击过，再次点击，则收回正在显示的内容。
	performRequest( 'lishi', params);
});*/
</script>
	
<script type="text/javascript">
var _bdhmProtocol = (("https:" == document.location.protocol) ? " https://" : " http://");
document.write(unescape("%3Cscript src='" + _bdhmProtocol + "hm.baidu.com/h.js%3F116fea821e3bfb6c5a7d4b187a50b502' type='text/javascript'%3E%3C/script%3E"));
</script>

  </body>
</html>
