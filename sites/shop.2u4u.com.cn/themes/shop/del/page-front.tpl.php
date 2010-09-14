<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

  <head>
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>
    <?php print $styles; ?>  
<script>
function setTab(m,n){
var tli=document.getElementById("menu"+m).getElementsByTagName("li"); /*获取选项卡的LI对象*/
var mli=document.getElementById("main"+m).getElementsByTagName("ul"); /*获取主显示区域对象*/
for(i=0;i<tli.length;i++){
  tli[i].className=i==n?"hover":""; /*更改选项卡的LI对象的样式，如果是选定的项则使用.hover样式*/
  mli[i].style.display=i==n?"block":"none"; /*确定主区域显示哪一个对象*/
}
}
</script>
	
	<link href="<?php print $base_path.$directory?>/css/fp.css" media="all" rel="stylesheet" type="text/css">
    <!--[if lte IE 6]><style type="text/css" media="all">@import "<?php print $base_path . path_to_theme() ?>/css/ie6.css";</style><![endif]-->
    <!--[if IE 7]><style type="text/css" media="all">@import "<?php print $base_path . path_to_theme() ?>/css/ie7.css";</style><![endif]-->

  </head>

  <body class="<?php print $body_classes; ?>">
    
    <div id="skip"><a href="#content">Skip to Content</a> <a href="#navigation">Skip to Navigation</a></div>  
    <div id="page">

    <!-- ______________________ HEADER _______________________ -->

    <!-- whx 修改logo的alt以及rel-->
    <div id="header">
	<div id="header-middle"><!--whx添加-->
      <div id="logo-title">
	
        <?php if (!empty($logo)): ?>
          <!-- <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
            <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>"/>
          </a> -->
		  <a href="<?php print $front_page; ?>" title="<?php print $site_name; ?>" rel="home" id="logo">
            <img src="<?php print $logo; ?>" alt="<?php print $site_name; ?>"/>
          </a>
        <?php endif; ?>
<!--
        <div id="name-and-slogan">
          <?php if (!empty($site_name)): ?>
            <h1 id="site-name">
              <a href="<?php print $front_page ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
            </h1>
          <?php endif; ?>
          <?php if (!empty($site_slogan)): ?>
            <div id="site-slogan"><?php print $site_slogan; ?></div>
          <?php endif; ?>
        </div> /name-and-slogan -->

      </div> <!-- /logo-title -->

      <?php if ($header): ?>
        <div id="header-region">
          <?php print $header; ?>
        </div>
      <?php endif; ?>

      <?php print $search_box; ?>
	</div><!--whx添加-->
	
	<!-- /王海霞whx迁移navigation -->
        <?php if (!empty($primary_links) or !empty($secondary_links)): ?>
          <div id="navigation" class="menu <?php if (!empty($primary_links)) { print "with-main-menu"; } if (!empty($secondary_links)) { print " with-sub-menu"; } ?>">
            <?php if (!empty($primary_links)){ print theme('links', $primary_links, array('id' => 'primary', 'class' => 'links main-menu')); } ?>
            <?php if (!empty($secondary_links)){ print theme('links', $secondary_links, array('id' => 'secondary', 'class' => 'links sub-menu')); } ?>
          </div> <!-- /navigation -->
        <?php endif; ?>

    </div> <!-- /header -->

    <!-- ______________________ MAIN _______________________ -->

    <div id="main" class="clearfix">
    
      <div id="content">
        <div id="content-inner" class="inner column center">

          <?php if ($messages || $help ): ?>
            <div id="content-header">
			
              <?php  print $messages; ?>

              <?php print $help; ?> 

            </div> <!-- /#content-header -->
          <?php endif; ?>
		  
		  <!--我们的内容 start-->
		  <div id="font-content-area" class="content-area">


	<div id="main_top" class="clearfix top"> 
	
		<div id="user_login_chzh_zhx" class="top-left">
		<div class="login">
			<div id="tabs0" class="tab_area" >
                          <ul id="menu0" class="menu0 dl-tabs">
                            <li id="ltab1" class="tabs hover">注册登录</li>
                            <li id="ltab2" class="tabs">积分充值</li>
                          </ul>
                          <div class="main dl-panes clear">
							<div id="pane_ltab1" class="pane">
                              <!--未登录-->
				<?php $block = module_invoke('user', 'block', 'view', 0); ?>	
				<?php print $block['content']; ?>

				
				<!--已登录-->
				<?php $block = module_invoke('block', 'block', 'view', 44); ?>
				<?php print $block['content']; ?>
				
                            </div>
							<div id="pane_ltab2" class="pane">
                              <!--积分充值-->
				<?php $block = module_invoke('gift_points', 'block', 'view', 0); ?>
				<?php print $block['content']; ?>
                            </div>

							
                          </div>
                </div>
		</div> 
		        <div class="recommend">用户积分中心</div>
      
       <!--积分中心标签页-->
        <div class="jifen">
                  <div id="tabs0">
<ul class="menu1" id="menu1">
  <li onclick="setTab(1,0)" class="hover">我要....<br />
  花积分！</li>
  <li onclick="setTab(1,1)">我要....<br />
  挣积分！</li>
</ul>
<div class="main" id="main1">
  <ul class="main_block">
      <li><a href="http://2u4u.com.cn/yueduwhx">在线阅读电子书</a></li>
      <li><a href="http://2u4u.com.cn/shipinwhx">在线观看外语视频</a></li>
      <li><a href="http://2u4u.com.cn/dlcenter">下载共享资源</a></li>
  </ul>
  
  <ul><li><a href="http://2u4u.com.cn/bangzhuzhongxin#yanzhengma">图书验证码充值</a></li>
      <li><a href="http://2u4u.com.cn/bangzhuzhongxin#goumai">购买悠游网积分</a></li>
      <li><a href="http://2u4u.com.cn/bangzhuzhongxin#huodong">参与活动得积分</a></li>
  </ul>
</div>
</div>
       </div>
		</div> 
		
		
		
		
		<div id="huandeng_jifen"  class="top-middle">
			<!--幻灯片-->
			<div id= "huandengpian" >
				<? print views_embed_view('whx_frontpage', $display_id = 'attachment_10');?>	
			</div>
		
			<!--积分换礼图片-->
			<div class="ad"><a href="libao"><img src="/sites/2u4u.com.cn/themes/stable/css/fp_images/jifenhuanli.gif" width="478" height="90" border="0" /></a></div>
			
			<!--如果上jQuery，去掉上面的，改成以下内容即可
				积分换礼图片
			<div id="adcontainer">
				<?php $block_search = module_invoke('block', 'block', 'view', 76); ?>
				<?php print $block_search['content']; ?>
			</div>-->
		</div>
		
		
		<div id="search_tuijian" class="top-right"> 
		
			<!--搜索框-->
			<div id= "block_search" class="search">
				<?php $block_search = module_invoke('search', 'block', 'view', 0); ?>
				<?php print $block_search['content']; ?>
			</div>
			
			
			<!--热点推荐-->
			<div class="recommend"><a href="/rediantuijian" target="_blank">热点推荐</a></div> 
			<div id= "rediantuijian" class="clearfix recommend-bg">
				<div class="redian_new">
					<? print views_embed_view('whx_frontpage', $display_id = 'attachment_12');?>				
				</div>	
				<? print views_embed_view('whx_frontpage', $display_id = 'attachment_11');?>				
			
			</div>
		</div> 
	</div>
	
	
	
		  <div id= "view_yuedu" class="clearfix library-bg">
			<div id="yuedu_title" class="redline-title"><a href="/yueduwhx" target="_blank" class="h">电子图书馆</a></div>
			<div id="yuedu_left" class="left">
				<div id="yuedu_hover" class="dlcontent tab_area" >
                          <ul id="dl-tabs0" class="dl-tabs">
                            <li id="tab1" class="tabs active"><h3><a href="yuedu/tuijian" target="_blank">编辑推荐</a></h3></li>
                            <li id="tab2" class="tabs"><h3><a href="yuedu/freebie" target="_blank">现在免费</a></h3></li>
                            <li id="tab3" class="tabs"><h3><a href="yuedu/remen" target="_blank">热门排行榜</a></h3></li>
                          </ul>
                          <div id="dl-panes0" class="dl-panes clear">
							<div id="pane_tab1" class="pane">
                              <? print views_embed_view('whx_frontpage', $display_id = 'attachment_4');?>
							  <div id="yuedu_xinshu">
								<? print views_embed_view('whx_frontpage', $display_id = 'attachment_3');?>
							  </div>
                            </div>
							<div id="pane_tab2" class="pane">
                              <? print views_embed_view('whx_frontpage', $display_id = 'attachment_1');?>
							  <div id="yuedu_xinshu">
								<? print views_embed_view('whx_frontpage', $display_id = 'attachment_14');?>
							  </div>
                            </div>
							<div id="pane_tab3" class="pane">
                              <? print views_embed_view('whx_frontpage', $display_id = 'attachment_5');?>
							  <div id="yuedu_xinshu">
								<? print views_embed_view('whx_frontpage', $display_id = 'attachment_16');?>
							  </div>
                            </div>
							
                          </div>
                </div>		  
			</div>
			
			
			
			
			
			
			<div id="yuedu_right" class="book-right">
			<div class="book-title">分类阅读</div>
			<div class="media-line"></div>
				<div id= "block_yuedu_term">
					<?php /* $block_search = module_invoke('taxonomyblocks', 'block', 'view', 2);  */?>
					<?php /* print $block_search['content'];  */?>
					<? /* print views_embed_view('yuedu', $display_id = 'block_8'); */?> 
					 
					 
					 <!-- 佩怡内容 -->
					 
					 <div class="book-fl">
					<ul>
					     <li><a title="儿童英语 " href="http://2u4u.com.cn/yuedu/2012" target="_blank">儿童英语</a></li>
					     <li><a title="大学英语教程 " href="http://2u4u.com.cn/yuedu/2015" target="_blank">大学英语教程</a></li>
					     <li><a title="英汉对照读物 " href="http://2u4u.com.cn/yuedu/9307" target="_blank">英汉对照读物</a></li>
					     <li><a title="大众英语读物 " href="http://2u4u.com.cn/yuedu/9309" target="_blank">大众英语读物</a></li>
					     <li><a title="英语考试 " href="http://2u4u.com.cn/yuedu/2018" target="_blank">英语考试</a></li>
					     <li><a title="日语电子书 " href="http://2u4u.com.cn/yuedu/2031" target="_blank">日语电子书</a></li>
					     <li><a title="韩语电子书 " href="http://2u4u.com.cn/yuedu/2034" target="_blank">韩语电子书</a></li>
					     <li><a title="法语电子书 " href="http://2u4u.com.cn/yuedu/2032" target="_blank">法语电子书</a></li>
					</ul>
					 </div>
					   <div class="book-fl2">
					   <ul>
					     <li><a title="中小学英语 " href="http://2u4u.com.cn/yuedu/2013" target="_blank">中小学英语</a></li>
					     <li><a title="英语专业教程 " href="http://2u4u.com.cn/yuedu/2016" target="_blank">英语专业教程</a></li>
					     <li><a title="简易英语读物 " href="http://2u4u.com.cn/yuedu/9308" target="_blank">简易英语读物</a></li>
					     <li><a title="精选英文原著 " href="http://2u4u.com.cn/yuedu/9310" target="_blank">精选英文原著</a></li>
					     <li><a title="英语学术文集 " href="http://2u4u.com.cn/yuedu/2019" target="_blank">英语学术文集</a></li>
					     <li><a title="德语电子书 " href="http://2u4u.com.cn/yuedu/2030" target="_blank">德语电子书</a></li>
					     <li><a title="俄语电子书 " href="http://2u4u.com.cn/yuedu/2033" target="_blank">俄语电子书</a></li>
					   <li><a title="汉语电子书 " href="http://2u4u.com.cn/yuedu/2035" target="_blank">汉语电子书</a></li>
					   </ul>
					   </div> 
				</div>
			</div>
		  </div>

		  <div id= "view_shipin" class="clearfix library-bg">
			<div id="shipin_title" class="redline-title"><a href="/shipinwhx" target="_blank" class="h">多媒体课堂</a></div>
			<div id="shipin_left" class="left">
				<div id="shipin_bofang">
					<? print views_embed_view('whx_frontpage', $display_id = 'attachment_2');?>
				</div>
				<div id="shipin_liebiao">
					<? print views_embed_view('whx_frontpage', $display_id = 'attachment_6');?>
				</div>
			</div>
			<div id="shipin_right"class="newfilm">
				<div class="newfilm-head"><a href="/mtag/9921" target="_blank">新片热译</a></div>  
					<div class="media-line"></div>  
					<? print views_embed_view('whx_frontpage', $display_id = 'attachment_13');?>
			</div>
		  </div>
		  
		  <div id= "view_quiz" class="clearfix library-bg">
			<div id="quiz_title" class="redline-title"><a href="/quizcenterwhx" target="_blank" class="h">测试中心</a></div>
			<div id="quiz_content">
				<div id="quiz_zhuanxiang" class="testcenter-content1">
					<h3><a href="/quizwhx/1978">专项测试</a><span>——测试您的专项英语水平</span></h3>
					<div class="testestcentr-pic"><a href="/quizwhx/1978" target="_blank"><img src="/sites/2u4u.com.cn/themes/stable/css/fp_images/test2.gif" border="0" /></a></div>
					<div class="testcenter-list">
						<? print views_embed_view('whx_frontpage', $display_id = 'attachment_7','1978');?>	
					</div>
				</div>
				<div id="quiz_kaoshi" class="testcenter-content1">
					<h3><a href="/quizwhx/8587">考试测试</a><span>——考试临近，来摸底测试吧</span></h3>
					<div class="testestcentr-pic"><a href="/quizwhx/8587" target="_blank"><img src="/sites/2u4u.com.cn/themes/stable/css/fp_images/test3.gif" border="0" /></a></div>
					<div class="testcenter-list">
						<? print views_embed_view('whx_frontpage', $display_id = 'attachment_7','8587');?>
					</div>
				</div>
				<div id="quiz_quwei" class="testcenter-content1">
					<h3><a href="/quizwhx/1977">趣味测试</a><span>——测试万花筒</span></h3>
					<div class="testestcentr-pic"><a href="/quizwhx/1977" target="_blank"><img src="/sites/2u4u.com.cn/themes/stable/css/fp_images/test4.gif" border="0" /></a></div>
					<div class="testcenter-list">
						<? print views_embed_view('whx_frontpage', $display_id = 'attachment_7','1977');?>
					</div>
				</div>
			</div>
		  </div>
		  

		  
		  <!--“通栏广告”的占位符-->		  
		  <div id="guanggao" class=" clearfix">
		  </div>
			
			  <div class="qz-head"> 
    <div class="qz-title">·<a href="/xiaozuwhx" target="_blank"  class="h">互动圈子</a>·</div>
</div>
  <div class="qz-bg">
			<div id="xiaozu_remenziyuan" class="qz-xz">
				<div id="xiaozu">				<!--小组-->		  
					<? print views_embed_view('whx_frontpage', $display_id = 'attachment_8');?>					
				</div>				
			</div>
			
			<div class="qz-zy">
				<div class="qz-zy-title clear"><a href="http://u.2u4u.com.cn/bbs/forumdisplay.php?fid=43" target="_blank" class="h">热门资源</a></div>
				<div class="qz-zy-text">
				<?php $block = module_invoke('drupal_discuz', 'block', 'view', 1); ?>
				<?php print $block['content']; ?>
				</div>
			</div>
			
			<div class="dashed"></div>
			<div class="qz-sq clear"><!--社区-->
				<div class="qz-zy-title clear"><a href="http://u.2u4u.com.cn/bbs" target="_blank" class="h">社区</a></div>
				<div class="qz-zy-neirong clear">
				<?php $block = module_invoke('drupal_discuz', 'block', 'view', 0); ?>
				<?php print $block['content']; ?>
				</div>
			</div>
				
			<div class="qz-sq qz-blog"><!--博客-->	
				<div class="qz-zy-title clear"><a href="http://u.2u4u.com.cn/home" target="_blank" class="h">博客精华</a></div>				
				<div class="qz-zy-neirong clear">
				<?php $block = module_invoke('drupal_discuz', 'block', 'view', 2); ?>
				<?php print $block['content']; ?>
				</div>
			</div>
   
			<div class="qz-ywyd"><!--有问有答-->		
				<div class="qz-zy-title"><a href="/wenda" target="_blank" class="h">有问有答</a> </div>
				<div class="qz-ywyd-text"> 
					<? print views_embed_view('whx_frontpage', $display_id = 'attachment_9');?>	
				</div>
			</div>
		  </div>
		
		
		<div id= "block_hezuo">
			<?php $block = module_invoke('block', 'block', 'view', 74); ?>
			<?php print $block['content']; ?>
		</div>
		
		
		
			</div><!--我们的内容 end-->
          <?php print $feed_icons; ?>


          </div>
        </div> <!-- /content-inner /content -->

		
		<?php if ($right): ?>
          <div id="sidebar-second" class="column sidebar second">
            <div id="sidebar-second-inner" class="inner">
              <?php print $right; ?>
            </div>
          </div>
        <?php endif; ?> <!-- /sidebar-second -->
		
      </div> <!-- /main -->

      <!-- ______________________ FOOTER _______________________ -->

      <?php if(!empty($footer_message) || !empty($footer_block)): ?>
        <div id="footer">
          <?php print $footer_message; ?>
          <?php print $footer_block; ?>
        </div> <!-- /footer -->
      <?php endif; ?>

    </div> <!-- /page -->
	
    <?php print $scripts; ?>
	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery.tools.min.js"></SCRIPT>
	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery-ui.min.js"></SCRIPT>
	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery.spasticNav.js"></SCRIPT>
	<SCRIPT type="text/javascript" src="<?php print $base_path.$directory?>/js/jquery.innerfade.js"></SCRIPT>
	
 <script type="text/javascript">
var _bdhmProtocol = (("https:" == document.location.protocol) ? " https://" : " http://");
document.write(unescape("%3Cscript src='" + _bdhmProtocol + "hm.baidu.com/h.js%3F3a7af4b2789603cd3a64483ca3d1f193' type='text/javascript'%3E%3C/script%3E"));
</script>	
	
	<?php if($closure_region): ?>
		<div id="closure_region">
			<?php print $closure_region; ?>
			<script type="text/javascript">
var e_addhover1='.views-field-field-shipin-cover-fid';
var e_hidden1='.views-field-field-shipin-neirong-value';
var e_neirong1='div.neirong';
var e_addhover2='#yuedu_hover .item-list h3';
var e_hidden2='#yuedu_hover .item-list ul';
var e_neirong2='#yuedu_hover ul.neirong li';


function element_shipin_hover(e_addhover,e_hidden,e_neirong){
$(e_addhover).hover(function(){
	$(this).nextAll().filter(e_hidden).addClass('neirong');
	$(e_neirong).before('<div class="detail-tip shadow-right"></div>');
    $('.detail-tip').html($(e_neirong).html());
    $('.detail-tip').append('<span class="arrow-left"></span>');
},function(){
	$(this).nextAll().filter(e_hidden).removeClass('neirong');
	$('.detail-tip').remove();
});
}

function tabs_hover(tab_area) {
        var hl=$(tab_area+" li.tabs"),content=$(tab_area+" .pane");
        hl.mouseover(function() {
			
            $(tab_area+" .dl-tabs li.tabs").removeClass("active");
            $(this).addClass("active");
            content.hide();
            $(tab_area+" #pane_"+this.id).show();
            return false;
            });
        $(hl[0]).addClass("active");
	} 
	
	
	function tabs_click(tab_area) {
        var hl=$(tab_area+" li.tabs"),content=$(tab_area+" .pane");
        hl.click(function() {
			
            $(tab_area+" .dl-tabs li.tabs").removeClass("hover");
            $(this).addClass("hover");
            content.hide();
            $(tab_area+" #pane_"+this.id).show();
            return false;
            });
        $(hl[0]).addClass("hover");
	}

        var h2=$("#huandengpian .views-row .views-field-title"),
			content1=$("#huandengpian .views-row .views-field-field-fpflash-image-fid"),
			content2=$("#huandengpian .views-row .views-field-field-fpflash-description-value");
			

$(function(){
			$('a:[href^=http][href*=2u4u.com.cn]').attr('target','_blank');
			
			$('#ad').innerfade({
						//animationtype: 'slide',
						speed: 1000,
						timeout: 5000,
						type: 'sequence',
						containerheight: '90px'
			});

	$('#huandengpian .views-row-1').addClass('on');	
	h2.mouseover(function() {			
        $(".views-row").removeClass("on");
		$(this).parent().addClass("on");
        content1.hide();content2.hide();
		$("div.on .views-field-field-fpflash-image-fid").show();
		$("div.on .views-field-field-fpflash-description-value").show();
        return false;
    });  
		
	
	
	tabs_click("#tabs0");
	tabs_hover("#yuedu_hover");


	element_shipin_hover(e_addhover1,e_hidden1,e_neirong1);
	element_shipin_hover(e_addhover2,e_hidden2,e_neirong2);
});
</script>

		</div>
	<?php endif; ?>
	
	<?php print $closure; ?>
  </body>
</html>
