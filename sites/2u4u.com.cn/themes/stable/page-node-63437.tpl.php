<?php
// $Id: page.tpl.php,v 1.14.2.6 2009/02/13 16:28:33 johnalbin Exp $

/**
 * @file page.tpl.php
 *
 * Theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $css: An array of CSS files for the current page.
 * - $directory: The directory the theme is located in, e.g. themes/garland or
 *   themes/garland/minelli.
 * - $is_front: TRUE if the current page is the front page. Used to toggle the mission statement.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Page metadata:
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or 'rtl'.
 * - $head_title: A modified version of the page title, for use in the TITLE tag.
 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
 *   so on).
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *   for the page.
 * - $body_classes: A set of CSS classes for the BODY tag. This contains flags
 *   indicating the current layout (multiple columns, single column), the current
 *   path, whether the user is logged in, and so on.
 * - $body_classes_array: An array of the body classes. This is easier to
 *   manipulate then the string in $body_classes.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 * - $mission: The text of the site mission, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $search_box: HTML to display the search box, empty if search has been disabled.
 * - $primary_links (array): An array containing primary navigation links for the
 *   site, if they have been configured.
 * - $secondary_links (array): An array containing secondary navigation links for
 *   the site, if they have been configured.
 *
 * Page content (in order of occurrance in the default page.tpl.php):
 * - $left: The HTML for the left sidebar.
 *
 * - $breadcrumb: The breadcrumb trail for the current page.
 * - $title: The page title, for use in the actual HTML content.
 * - $help: Dynamic help text, mostly for admin pages.
 * - $messages: HTML for status and error messages. Should be displayed prominently.
 * - $tabs: Tabs linking to any sub-pages beneath the current page (e.g., the view
 *   and edit tabs when displaying a node).
 *
 * - $content: The main content of the current Drupal page.
 *
 * - $right: The HTML for the right sidebar.
 *
 * Footer/closing data:
 * - $feed_icons: A string of all feed icons for the current page.
 * - $footer_message: The footer message as defined in the admin settings.
 * - $footer : The footer region.
 * - $closure: Final closing markup from any modules that have altered the page.
 *   This variable should always be output last, after all other dynamic content.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 */
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>外研社暑期图书大放送-热销图书8.5折-悠游网特别专题</title>
<link href="http://2u4u.com.cn/sites/2u4u.com.cn/themes/stable/css/cuxiao/css.css" rel="stylesheet" type="text/css" />
<script src="http://static.tieba.baidu.com/tb/js/ac_runactivecontent.js"></script>
<script>
function setTab(m,n){
var tli=document.getElementById("menu"+m).getElementsByTagName("li");
var mli=document.getElementById("main"+m).getElementsByTagName("ul");
for(i=0;i<tli.length;i++){
   tli[i].className=i==n?"hover":"";
   mli[i].style.display=i==n?"block":"none";
}
}
</script>
</head>

<body>
	<div class="bg">
   <div class="top"><a href="http://2u4u.com.cn/" target="_blank">悠游首页</a><span class="text">│<a href="http://ebook.2u4u.com.cn/" target="_blank">电子图书馆</a><span class="text">│</span><a href="http://2u4u.com.cn/bangzhuzhongxin#yanzhengma" target="_blank">积分充值</a><span class="text">│</span><a href="http://shop.2u4u.com.cn/libao" target="_blank">积分换礼</a><span class="text">│</span><a href="http://quiz.2u4u.com.cn/" target="_blank">测试中心</a><span class="text">│</span><a href="http://u.2u4u.com.cn/bbs/" target="_blank">小组</a><span class="text">│</span><a href="http://video.2u4u.com.cn/" target="_blank">多媒体课堂</a><span class="text">│</span><a href="http://test.2u4u.com.cn/online/" target="_blank">在线词典</a><span class="text">│</span><a href="http://2u4u.com.cn/wenda" target="_blank">有问有答</a><span class="text">│</span><a href="http://2u4u.com.cn/node/51779" target="_blank">按需印刷</a> </div>
   <div class="jiaodiantu"></div>
   <div class="content-bg">
      <div class="lunnbotu-bg">
	  <div class="flash"><script language="javascript">
				if (AC_FL_RunContent == 0)
				{
					alert('此页需要 AC_RunActiveContent.js。在 Flash 中，运行"命令"菜单中的"应用活动内容更新"，以将 AC_RunActiveContent.js 复制到 HTML 输出文件夹。');
				}
				else
				{
					 var pUrl = 'http://60.10.4.99/flash/viewer?t=' + new Date().getTime();
				AC_FL_RunContent(
						'codebase', 'http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=8,0,0,0',
						'width', '340',
						'height', '200',
						'src', 'viewer',
						'quality', 'high',
						
						'pluginspage', 'http://www.macromedia.com/go/getflashplayer',
						//'align', 'middle',
						'play', 'true',
						'loop', 'false',
						//'scale', 'showall',
						//'wmode', 'window',
							
						
						'devicefont', 'false',
						'id', 'viewer',
						'bgcolor', '#ffffff',
						'name', 'viewer',
						'menu', 'true',
						'allowScriptAccess','always',
						'movie', pUrl,
						//'salign', 'top',
						
						'FlashVars', 'xmlPath=http://60.10.4.99/flash/scroll1.xml?t='+Math.random()
							
						);
				}
				
			</script>
	  </div>
      </div>
	  <div class="huodongdongtai-bg"></div>
	  <div class="huodongdongtai-text">
	    <ul>
        <li><a href="http://2u4u.com.cn/node/63423" target="_blank">外研社10种图书荣获“首届中国大学出版社图书奖” </a> </li>
        <li><a href="http://2u4u.com.cn/node/63421" target="_blank">“歆语工程”延安市骨干英语教师高级研修班开学典礼举行</a></li>
        <li><a href="http://2u4u.com.cn/node/63422" target="_blank">《季羡林全集》现身香港书展</a></li>
        <li><a href="http://2u4u.com.cn/node/62447" target="_blank">外研社承办的“汉语桥——法国中学生夏令营”正式开营</a></li>
        <li><a href="http://2u4u.com.cn/node/62296" target="_blank">科普图书读者需求调研活动</a></li>
        <li><a href="http://2u4u.com.cn/node/63207" target="_blank">剑桥大学出版社主题演讲会在外研大厦举办</a></li>
	    </ul>
     </div>
  <div id="tabs1">
	    <div class="menu1box">
          <ul id="menu1">
            <li onmouseover="setTab(1,0)">辞书</li>
            <li onmouseover="setTab(1,1)">汉语</li>
            <li onmouseover="setTab(1,2)">少儿</li>
            <li onmouseover="setTab(1,3)">综合语种</li>
          </ul>
      </div>
	    <div class="main1box">
   <div class="main" id="main1">
    <ul class="block">
	   <div class="tab-book"><img src="http://2u4u.com.cn/sites/2u4u.com.cn/themes/stable/css/cuxiao/image/book1.gif" /></div>
	   <div class="tab-text">
	    <div class="textarea">
        <p>朗文当代高级英语辞典（英英·英汉双解）（缩印本）</p>
        <p> 朗文当代高级英语辞典（英英·英汉双解）（第四版）（配全文光盘）</p>
        <p> 朗文当代高级英语辞典（英英·英汉双解）（第四版）（大字版）（配全文光盘）</p>
        <p> 外研社英汉多功能词典</p>
        <p> 汉英词典（第三版）</p>
        <p> 书虫套装版（MP3版） </p>
        </div>
	   
	   </div>
      
    </ul>
    <ul>
	<div class="tab-book"><img src="http://2u4u.com.cn/sites/2u4u.com.cn/themes/stable/css/cuxiao/image/book2.gif" /></div>
	   <div class="tab-text">
	   <div class="textarea" ><p>学生古汉语词典</p>
<p> 汉语成语学习词典</p>
<p> 现代汉语规范词典（新版） </p>
</div>
	   
	   </div>
	
	</ul>
    
	
	<ul><div class="tab-book"><img src="http://2u4u.com.cn/sites/2u4u.com.cn/themes/stable/css/cuxiao/image/book3.gif" /></div>
	   <div class="tab-text">
	   <div class="textarea" >
       
       <H1>萤火虫·世界经典童话双语绘本</H1>
<p> 萤火虫·世界经典童话双语绘本－－木偶奇遇记</p>
<p> 萤火虫·世界经典童话双语绘本－－绿野仙踪</p>
<p> 萤火虫·世界经典童话双语绘本－－野天鹅</p>
<p> 萤火虫·世界经典童话双语绘本－－灰姑娘</p>
<p> 萤火虫·世界经典童话双语绘本－－小红帽</p>
<p> 萤火虫·世界经典童话双语绘本－－青蛙王子</p>
<p> 萤火虫·世界经典童话双语绘本－－渔夫和金鱼</p>
<p> 萤火虫·世界经典童话双语绘本－－皇帝的新装</p>
<p> 萤火虫·世界经典童话双语绘本－－白雪公主</p>
<p> 萤火虫·世界经典童话双语绘本－－狼和七只小羊</p>
<p> 萤火虫·世界经典童话双语绘本－－三只小猪</p>
<p> 萤火虫·世界经典童话双语绘本－－丑小鸭</p>
<p> 萤火虫·世界经典童话双语绘本－－拇指姑娘</p>
<p> 萤火虫·世界经典童话双语绘本－－美女与野兽</p>
<p> 萤火虫·世界经典童话双语绘本－－海的女儿</p>
<p> 萤火虫·世界经典童话双语绘本第二辑——尼尔斯骑鹅旅行记 </p>
<p> 萤火虫·世界经典童话双语绘本第二辑——卖火柴的小女孩儿 </p>
<p> 萤火虫·世界经典童话双语绘本第二辑——睡美人 </p>
<p> 萤火虫·世界经典童话双语绘本第二辑——龟兔赛跑 </p>
<p> 萤火虫·世界经典童话双语绘本第二辑——杰克与魔豆 </p>
<p> 萤火虫·世界经典童话双语绘本第二辑——阿里巴巴和四十大盗 </p>
<p> 萤火虫·世界经典童话双语绘本第二辑——宝莲灯 </p>
<p> 萤火虫·世界经典童话双语绘本第二辑——花木兰 </p>
<p> 萤火虫·世界经典童话双语绘本第二辑——爱丽丝漫游奇境记 </p>
<p> 萤火虫·世界经典童话双语绘本第二辑——小王子 </p>
<H1> 迪士尼双语系列（汉英双语）</H1>
<H2> （1）迪士尼双语小影院系列</H2>
<p> 迪士尼双语小影院－－白雪公主</p>
<p> 迪士尼双语小影院－－阿拉丁</p>
<p> 迪士尼双语小影院－－美女与野兽</p>
<p> 迪士尼双语小影院－－花木兰</p>
<p> 迪士尼双语小影院－－仙履奇缘</p>
<p>语小影院－－木偶奇遇记</p>
<p> 迪士尼双语小影院－－狮子王</p>
<p> 迪士尼双语小影院－－爱丽丝梦游仙境</p>
<p> 迪士尼双语小影院－－睡美人</p>
<p> 迪士尼双语小影院－－小美人鱼</p>
<p> 迪士尼双语小影院－－小飞侠</p>
<p> 迪士尼双语小影院－－101忠狗</p>
<H2> （2）小熊维尼温馨双语故事系列</H2>
<p> 小熊维尼温馨双语故事－－维尼小园丁·风儿吹,风筝飞</p>
<p> 小熊维尼温馨双语故事－－百亩林历险记·小豆爱妈妈</p>
<p> 小熊维尼温馨双语故事－－屹耳，生日快乐·逃跑的彩蛋</p>
<p> 小熊维尼温馨双语故事－－维尼的蜂蜜大战·小猪皮杰的烦恼</p>
<H2> （3）米奇妙妙屋智慧双语故事系列</H2>
<p> 米奇妙妙屋智慧双语故事－－热气球奇妙之旅·黛丝医生</p>
<p> 米奇妙妙屋智慧双语故事－－大家一起去兜风·布鲁托的最佳表现</p>
<p> 米奇妙妙屋智慧双语故事－－米奇的野外大冒险·唐老鸭丢失的狮子</p>
<p> 米奇妙妙屋智慧双语故事－－米妮的快乐野餐会·高飞向前冲</p>
<H1> 聪明豆系列</H1>
<p> 聪明豆绘本系列－－咕噜牛</p>
<p> 聪明豆绘本系列－－咕噜牛小妞妞</p>
<p> 聪明豆绘本系列－－城里最漂亮的巨人</p>
<p> 聪明豆绘本系列－－小海螺和大鲸鱼</p>
<p> 聪明豆绘本系列－－女巫扫帚排排坐</p>
<p> 聪明豆绘本系列－－小房子变大房子</p>
<p> 聪明豆绘本系列－－小熊孵蛋</p>
<p> 聪明豆绘本系列－－愿望树</p>
<p> 聪明豆绘本系列－－我永远爱你</p>
<p> 聪明豆绘本系列－－长大做个好爷爷</p>
<p> 聪明豆绘本系列－－忘了说我爱你</p>
<p> 聪明豆绘本系列－－火龙爸爸戒烟记</p>
<p> 聪明豆绘本系列－－猫头鹰喔喔呼！</p>
<p> 聪明豆绘本系列－－小猪变形记</p>
<p> 聪明豆绘本系列－－乱七八糟的变色龙</p>
<p> 聪明豆绘本系列－－美宝的魔法花园</p>
<p> 聪明豆绘本系列－－我们是一家</p>
<p> 聪明豆绘本系列－－狐狸爸爸鸭儿子</p>
<p> 聪明豆绘本系列－－狮子烫头发</p>
<p> 聪明豆绘本系列－－小狗阿疤想变羊</p>
<p> 聪明豆绘本系列－－你是我最好的朋友</p>
<p> 聪明豆绘本系列－－小憨，抱抱！</p>
<p> 聪明豆绘本系列－－小老鼠分果果</p>
<p> 聪明豆绘本系列－－小羊睡不着</p>
<p> 聪明豆绘本系列－－看我！看我！ </p>
<p> 聪明豆绘本系列－－如果嗅嗅丢了</p>
<p> 聪明豆绘本系列－－雪孩子</p>
<p> 聪明豆绘本系列－－噼里啪啦打屁股</p>
<p> 聪明豆绘本系列－－当我们同在一起 </p>
<p> 聪明豆绘本系列－－一只很饿很饿的小猪</p>
<H1> 奥比岛超级明星档案系列</H1>
<p> 海宝有约·奥比岛超级明星档案－－纳多王子的成长之路</p>
<p> 海宝有约·奥比岛超级明星档案－－黑莲的公主养成计划</p>
<p> 海宝有约·奥比岛超级明星档案－－小耶的魅力时装秀</p>
<p> 海宝有约·奥比岛超级明星档案－－阿拉斯的魔法学院</p>
<p> 海宝有约·奥比岛超级明星档案－－水颜公主的爱心日记</p>
<p> 海宝有约·奥比岛超级明星档案－－龙娃的神秘身世</p>
<p> 海宝博览·世界经典童话写真派对系列</p>
<p> 海宝博览·世界经典童话写真派对－－路上历险</p>
<p> 海宝博览·世界经典童话写真派对－－公主传说</p>
<p> 海宝博览·世界经典童话写真派对－－魔法幻境</p>
<p> 海宝博览·世界经典童话写真派对－－追梦奇迹</p>
<p> 海宝有约·奥比岛神秘宝物大搜索系列</p>
<p> 海宝有约·奥比岛神秘宝物大搜索——黄金海岸之谜 </p>
<p> 海宝有约·奥比岛神秘宝物大搜索——勇闯遗忘之岛 </p>
<p> 海宝有约·奥比岛神秘宝物大搜索——征服奥比斯山 </p>
<p> 海宝有约·奥比岛神秘宝物大搜索——青木森林魔法对决 </p>
<p> 海宝有约·奥比岛神秘宝物大搜索——魔法搜查令 </p>
<p> 海宝有约·奥比岛神秘宝物大搜索——拯救纳多王子 </p>
<H1> 小书房世界经典文库系列</H1>
<p> 小书房·世界经典文库－－福尔摩斯探案选</p>
<p> 小书房·世界经典文库－－三十六计</p>
<p> 小书房·世界经典文库－－史记故事</p>
<p> 小书房·世界经典文库－－老人与海</p>
<p> 小书房·世界经典文库－－鲁滨孙漂流记</p>
<p> 小书房·世界经典文库－－海底两万里  </p>
<p>小书房·世界经典文库－－八十天环游地球</p>
<p> 小书房·世界经典文库－－红楼梦</p>
<p> 小书房·世界经典文库－－西游记</p>
<p> 小书房·世界经典文库－－水浒传</p>
<p> 小书房·世界经典文库－－三国演义</p>
<p> 小书房·世界经典文库－－汤姆·索亚历险记</p>
<p> 小书房·世界经典文库－－木偶奇遇记</p>
<p> 小书房·世界经典文库－－格列佛游游记</p>
<p> 小书房·世界经典文库－－昆虫记</p>
<p> 小书房·世界经典文库－－童年·在人间·我的大学 </p>
<p> 小书房·世界经典文库－－钢铁是怎样炼成的</p>
<p> 小书房·世界经典文库－－爱的教育</p>
<p> 小书房·世界经典文库－－绿野仙踪</p>
<p> 小书房·世界经典文库－－伊索寓言</p>
<p> 小书房·世界经典文库－－格林童话</p>
<p> 小书房·世界经典文库－－一千零一夜</p>
<p> 小书房·世界经典文库－－安徒生童话</p>
<p> 小书房·世界经典文库－－希腊神话</p>
<p> 小书房·世界经典文库－－秘密花园</p>
<H1> 快乐侦探在行动系列</H1>
<p> 快乐侦探在行动－－离奇失踪案</p>
<p> 快乐侦探在行动－－手机短信之谜</p>
<p> 快乐侦探在行动－－谁是告密者</p>
<p> 快乐侦探在行动－－神秘枯井</p>
<p> 快乐侦探在行动－－图书馆奇案</p>
<p> 快乐侦探在行动－－校园涂鸦事件</p>
<p> 快乐侦探在行动－－焰火迷案</p>
<p> 快乐侦探在行动－－智解连环套 </p>
       
</div>
	   
	   </div>
	   </ul>
	
	
	
	
	<ul>
	<div class="tab-book"><img src="http://2u4u.com.cn/sites/2u4u.com.cn/themes/stable/css/cuxiao/image/book4.gif" /></div>
	   <div class="tab-text">
	   <div class="textarea" >
       	<p>速成日语（精品盒装）</p>
        <p> 速成韩语（精品盒装）</p>
        <p> 速成德语（精品盒装）</p>
        <p> 速成法语（精品盒装）</p>
        <p> 速成俄语（精品盒装）</p>
        <p> 速成西语（精品盒装）</p>
        <p> 速成意大利语（精品盒装）</p>
        <p> 速成葡语（精品盒装）</p>
        <p> 实用速成阿拉伯语（精品盒装）</p>
</div>
	   
	   </div></ul>
   </div>
</div>
</div>
	
	
	

     <div class="book">
    <div class="bookstore">参与8.5折惠馈活动书店名单</div>
	</div>
     <div class="address-bg">
       <div class="address-text">
	     <p><strong>安徽图书城</strong> (合肥市长江路279号)<br />
	       <strong>合肥四牌楼新华书店</strong> (合肥市长江路152号)<br />
	       <strong>蚌埠市新华书店</strong> (安徽省蚌埠市东市区国强路) <br />
	       <strong>淮南市新华书店</strong> (淮南市谢家集区唐山路，232052)<br />
	       <strong>芜湖市新华书店</strong> (安徽芜湖市康复路101号)<br />
	       <strong>吉林联合书城</strong> (长春市宽城区芙蓉路36号)<br />
	       <strong>沈阳北方图书城</strong> (沈阳市沈河区青年大街270号)<br />
	       <strong>沈阳市店</strong> (辽宁省沈阳市和平区中山路70号沈阳新华书店大厦)<br />
	       <strong>大连市店</strong> (辽宁省大连市中山区同兴街69号新华书店大厦)<br />
	       <strong>内蒙古图书大厦</strong> (内蒙古呼和浩特中山西路94号) <br />
	       <strong>济南市新华书店泉城路店</strong> (济南市泉城路185号)<br /> 
	       <strong>济南市新华书店东图书店</strong> (南市市中区经四路269号)<br />
	       <strong>青岛市店</strong> (青岛市香港中路青岛书城)<br />
	     <br />
	     </p>
       </div>
	    <div class="address-text">
	      <p><strong>鞍山市店</strong> (鞍山市铁东区北三道街)<br />
	        <strong>哈尔滨学府书店</strong> (哈尔滨市南岗区学府路74号) <br />
	        <strong>厦门外图书城</strong> (厦门市嘉禾路468号)<br />
	        <strong>福州市店安泰书城</strong> (福州市织缎巷附近)<br />
            <strong>福州市店洋桥书城</strong> (鼓楼区杨桥中路231号)<br />
            <strong>上海外文书店</strong> (上海市福州路390号)<br />
            <strong>嘉兴市爱杰莱特教育科技书店</strong>(建国北路嘉禾北京城北100米)<br />
            <strong>郑州市购书中心</strong> (郑州西太康路19号)<br />
            <strong>王府井新华书店</strong> (北京市东城区王府井大街218号)<br />
            <strong>烟台书城</strong> (烟台市西大街附近)<br />
            <strong>潍坊奎文书城</strong> (山东省潍坊市奎文区胜利东街285号)<br />
            <strong>泰安书城</strong> (泰安市青年路80号)   <br />
            <strong>临沂中心</strong> (临沂市的沂蒙路136号) <br />
            <br />
          </p>
       </div>
	 
	 </div>
	<div class="vote-bg">
	<div class="postmessage firstpost">
<div class="vote-title">
在悠游网你最喜欢做什么？
</div>
<script type="text/javascript">
	var max_obj = 3;
	var p = 0;
	function $(id) {return document.getElementById(id);}
	function checkbox(obj) {
		if(obj.checked) {
			p++;
			for (var i = 0; i < $('poll').elements.length; i++) {
			var e = $('poll').elements[i];
				if(p == max_obj) {
					if(e.name.match('pollanswers') && !e.checked) {
					e.disabled = true;
					}
				}
			}
		} else {
			p--;
			for (var i = 0; i < $('poll').elements.length; i++) {
				var e = $('poll').elements[i];
				if(e.name.match('pollanswers') && e.disabled) {
					e.disabled = false;
				}
			}
		}
		$('pollsubmit').disabled = p <= max_obj && p > 0 ? false : true;
	}
</script>
<form onsubmit="ajaxpost('poll', 'post_1550', 'post_1550');return false" action="http://u.2u4u.com.cn/bbs/misc.php?action=votepoll&amp;fid=20&amp;tid=900&amp;pollsubmit=yes&amp;quickforward=yes" method="post" name="poll" id="poll" target="_blank">
<input type="hidden" value="857b06ec" name="formhash">
<div class="pollinfo">
<strong>多选投票</strong>:  最多可选 3 项 
<a onclick="showWindow('viewvote', this.href);doane(event);" href="http://u.2u4u.com.cn/bbs/misc.php?action=viewvote&amp;tid=900">查看投票参与人</a>
</div>
<div class="pollchart">
<table width="100%" cellspacing="0" cellpadding="0" summary="poll panel"><tbody><tr>
<td class="selector"><input type="checkbox" onclick="checkbox(this)" value="1" name="pollanswers[]" id="option_0" class="checkbox"></td>
<td class="polloption vote">
<label for="option_0">1. &nbsp;在线阅读电子书</label></td>
<td class="optionvotes"></td>
</tr><tr>
<td class="selector"><input type="checkbox" onclick="checkbox(this)" value="2" name="pollanswers[]" id="option_1" class="checkbox"></td>
<td class="polloption vote">
<label for="option_1">2. &nbsp;通过在线音视频进行外语学习</label></td>
<td class="optionvotes"></td>
</tr><tr>
<td class="selector"><input type="checkbox" onclick="checkbox(this)" value="3" name="pollanswers[]" id="option_2" class="checkbox"></td>
<td class="polloption vote">
<label for="option_2">3. &nbsp;做悠游网的测试题</label></td>
<td class="optionvotes"></td>
</tr><tr>
<td class="selector"><input type="checkbox" onclick="checkbox(this)" value="4" name="pollanswers[]" id="option_3" class="checkbox"></td>
<td class="polloption vote">
<label for="option_3">4. &nbsp;在有问有答提问或回答其它用户的问题</label></td>
<td class="optionvotes"></td>
</tr><tr>
<td class="selector"><input type="checkbox" onclick="checkbox(this)" value="5" name="pollanswers[]" id="option_4" class="checkbox"></td>
<td class="polloption vote">
<label for="option_4">5. &nbsp;泡泡悠游网论坛</label></td>
<td class="optionvotes"></td>
</tr><tr>
<td class="selector">&nbsp;</td><td colspan="2">
<button value="true" id="pollsubmit" name="pollsubmit" disabled="disabled" type="submit" class="submit">提交</button>
(此为公开投票，其他人可看到你的投票项目)				
</td>
</tr>
</tbody></table>
</div>
</form><div class="specialmsg"></div>

<div id="post_rate_div_1550"></div>
<div class="useraction"></div>
</div>


	
	</div>  
	<div class="vote-bg">
	<div class="postmessage firstpost">
<div class="vote-title">你更需要外研社的哪种出版图书？</div>
<script type="text/javascript">
var max_obj1 = 2;
var p1 = 0;
function checkbox1(obj) {
	if(obj.checked) {
		p1++;
		for (var i = 0; i < $('poll1').elements.length; i++) {
			var e = $('poll1').elements[i];
			if(p1 == max_obj1) {
				if(e.name.match('pollanswers') && !e.checked) {
				e.disabled = true;
				}
			}
		}
	} else {
		p1--;
		for (var i = 0; i < $('poll1').elements.length; i++) {
			var e = $('poll1').elements[i];
				if(e.name.match('pollanswers') && e.disabled) {
					e.disabled = false;
				}
			}
		}
		$('pollsubmit1').disabled = p1 <= max_obj1 && p1 > 0 ? false : true;
	}
</script>
<form id="poll1" name="poll1" method="post" action="http://u.2u4u.com.cn/bbs/misc.php?action=votepoll&amp;fid=22&amp;tid=901&amp;pollsubmit=yes&amp;quickforward=yes" onsubmit="ajaxpost('poll', 'post_1551', 'post_1551');return false"  target="_blank">
<input type="hidden" name="formhash" value="9abe1365" />
<div class="pollinfo">
<strong>多选投票</strong>:  最多可选 2 项 
<a href="http://u.2u4u.com.cn/bbs/misc.php?action=viewvote&amp;tid=901" onclick="showWindow('viewvote', this.href);doane(event);" target="_blank">查看投票参与人</a>
</div>


<div class="pollchart">
<table width="100%" cellspacing="0" cellpadding="0" summary="poll panel"><tr>
<td class="selector"><input class="checkbox" type="checkbox" id="option_0" name="pollanswers[]" value="6" onclick="checkbox1(this)" /></td>
<td class="polloption vote">
<label for="option_0">1. &nbsp;辞书类（朗文、牛津、英汉等辞典等）</label></td>
<td class="optionvotes"></td>
</tr><tr>
<td class="selector"><input class="checkbox" type="checkbox" id="option_1" name="pollanswers[]" value="7" onclick="checkbox1(this)" /></td>
<td class="polloption vote">
<label for="option_1">2. &nbsp;教学类（新概念、新标准、新视野等）</label></td>
<td class="optionvotes"></td>
</tr><tr>
<td class="selector"><input class="checkbox" type="checkbox" id="option_2" name="pollanswers[]" value="8" onclick="checkbox1(this)" /></td>
<td class="polloption vote">
<label for="option_2">3. &nbsp;读物类（类似于书虫系列的读物）</label></td>
<td class="optionvotes"></td>
</tr><tr>
<td class="selector"><input class="checkbox" type="checkbox" id="option_3" name="pollanswers[]" value="9" onclick="checkbox1(this)" /></td>
<td class="polloption vote">
<label for="option_3">4. &nbsp;原著类（英文原版书籍）</label></td>
<td class="optionvotes"></td>
</tr><tr>
<td class="selector"><input class="checkbox" type="checkbox" id="option_4" name="pollanswers[]" value="10" onclick="checkbox1(this)" /></td>
<td class="polloption vote">
<label for="option_4">5. &nbsp;小语种（法语、德语、西班牙语或其他）</label></td>
<td class="optionvotes"></td>
</tr><tr>
<td class="selector">&nbsp;</td><td colspan="2">
<button class="submit" type="submit" disabled="disabled" name="pollsubmit" id="pollsubmit1" value="true">提交</button>
(此为公开投票，其他人可看到你的投票项目)
				
</td>
</tr>
</table>
</div>
</form>

<div class="specialmsg"></div>

<div id="post_rate_div_1550"></div>
<div class="useraction"></div>
</div>


	
	</div></div>
	</div>
</div> 
</body>
</html>
