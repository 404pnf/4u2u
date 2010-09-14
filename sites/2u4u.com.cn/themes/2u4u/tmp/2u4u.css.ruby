@charset "utf-8";

/* $Id: zen.css,v 1.14.2.1 2009/02/13 07:46:04 johnalbin Exp $ */



/*

* ZEN STYLES

*

* This is an example stylesheet. Sub-themes should NOT include the zen/zen.css

* file, but instead copy this CSS to their own stylesheets.

*

* In this stylesheet, we have included all of the classes and IDs from this

* theme's tpl.php files. We have also included many of the useful Drupal core

* styles to make it easier for theme developers to see them.

*

* Many of these styles are over-riding Drupal's core stylesheets, so if you

* remove a declaration from here, the styles may still not be what you want

* since Drupal's core stylesheets are still styling the element. See the

* drupal6-reference.css file for a list of all Drupal 5.x core styles.

*

* In addition to the style declarations in this file, other Drupal styles that

* you might want to override or augment are those for:

*

*   Book Navigation  See line 74  of Zen's drupal6-reference.css file

*   Forum            See line 197 of Zen's drupal6-reference.css file

*   Menus            See line 667 of Zen's drupal6-reference.css file

*   News Aggregator  See line 20  of Zen's drupal6-reference.css file

*   Polls            See line 287 of Zen's drupal6-reference.css file

*   Search           See line 320 of Zen's drupal6-reference.css file

*   User Profiles    See line 945 of Zen's drupal6-reference.css file

*/





/** body **/

body, div, span, p, blockquote, pre, code, ul, ol, li, h1, h2, h3, h4, h5, h6, form, fieldset, legend, label, input, textarea {

margin: 0;

padding: 0;

}

h1 {

font-size: 2.5em;

font-weight: normal;

}

h2 {

font-size: 1.75em;

font-weight: normal;

}

h3 {

font-size: 1.25em;

font-weight: bold;

}

h4 {

font-size: 1.1em;

font-weight: bold;

}

h5 {

font-size: 1em;

font-weight: bold;

}

h6 {

font-size: 0.8em;

font-weight: bold;

}

img {

border: 0;

}

a{

color: #27638C;

margin: 0;

padding: 0;

text-decoration: none;

}

a:link, a:visited {

color: #27638C;

}

a:hover, a:active {

text-decoration: underline;

}

body {

background: #FFF;

font-family: 宋体, 黑体;    /* web safe fonts */

font-size: 75%;    /* 12px */

font-weight: normal;

line-height: 160%;    /* 19.2px */

}

#page {

width:975px;

margin-left:auto;

margin-right:auto;

font-size:12px;

}

#page-inner {

}

/** header **/

#header {

}

#header-inner {

}

#logo-title /* Wrapper for logo, website name, and slogan */ {

}

#logo /* Wrapper for logo */ {

margin: 0;

padding: 0;

}

#logo-image /* The actual logo image */ {

}

h1#site-name, div#site-name /* The name of the website */ {

margin: 0;

font-size: 2em;

line-height: 1.3em;

}

#site-name a:link, #site-name a:visited {

color: #000;

text-decoration: none;

}

#site-name a:hover {

text-decoration: underline;

}

#site-slogan /* The slogan (or tagline) of a website */ {

}

#header-blocks /* Wrapper for any blocks placed in the header region */ {

}

/** main (container for everything else) **/

#main {

width:975px;

margin-left:auto;

margin-right:auto;

}

#main-inner {

width:975px;

}

/** content **/

#content-inner {

}

.node-type-ebook #main #main-inner #content  #content-inner #content-header{ width:975px;height:35px;background-image: url(images/video_titleall2.jpg);text-align:center;}

.node-type-ebook #page #page-inner #main #main-inner #content  #content-inner #content-header h1.title{text-align:center; color:#32A442; font-size:14px; font-weight:700; line-height:35px; margin:0 auto;}

.section-yuedu  #main #main-inner #content  #content-inner #content-header{height:35px;background-image: url(images/video_titleall.jpg); line-height:35px;}

.section-yuedu  #main #main-inner #content{border:#D1D1D1 1px solid;width:610px; border-top:none;}

.section-yuedu  #main #main-inner #content #content-inner #content-header{ border:none; border:0px;}

 

.section-yuedu  #main #main-inner #content  #content-inner #content-header .title{

margin-left:15px;

height:35px;

line-height:35px;

clear:both;

font-size:14px;

color:#ffffff;

font-weight:700;}

.section-yuedu  #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-left{background-image: url(images/yuedu-title-left.jpg); background-repeat:no-repeat;height:35px;width:12px;display:block; float:left;}

.section-yuedu  #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-content{background-image: url(images/yuedu-title-content.jpg); background-repeat:repeat-x;height:35px;line-height:35px;display:block; float:left;}

.section-yuedu  #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-right{background-image: url(images/yuedu-title-right.jpg); background-repeat:no-repeat;height:35px; width:13px;display:block; float:left;}











.page-yuedu  #main #main-inner #content{border-top:#D1D1D1 1px solid;}



#mission /* The mission statement of the site (displayed on homepage) */ {

}

#content-top /* Wrapper for any blocks placed in the "content top" region */ {

}

#content-header /* Wrapper for breadcrumb, title, messages, tabs, and help */ {

}

.breadcrumb /* The path to the current page in the form of a list of links */ {

padding-bottom: 0; /* Undo system.css */

}

h1.title, /* The title of the page */ h2.title, /* Block title or the title of a piece of content when it is given in a list of content */ h3.title /* Comment title */ {

margin: 0;

}

div.messages /* Important messages (status, warning, and error) for the user */ {

}

div.status /* Normal priority messages */ {

}

div.warning, tr.warning /* Medium priority messages */ {

/* border: 1px solid #f0c020; */ /* Drupal core uses: 1px solid #f0c020 */

}

div.error, tr.error /* High priority messages. See also the .error declaration below. */ {

}

div.tabs /* See also the tabs.css file. */ {

}

.help /* Help text on a page */ {

margin: 1em 0;

}

.more-help-link /* Link to more help */ {

font-size: 0.85em;

text-align: right;

}

#content-area /* Wrapper for the actual page content */ {

}

*html .section-quiz .pager{ width:200px; margin:0 auto; float:right; margin-left:200px;}





.pager /* A list of page numbers when more than 1 page of content is available */ {

clear: both;

margin: 1em 0;

text-align: center;

}

.pager a, .pager strong.pager-current {



}

.feed-icons /* The links to the RSS or Atom feeds for the current list of content */ {

margin: 1em 0;

}

#content-bottom #block-views-tag_yuedu-block_2{border-left:#D1D1D1 1px solid;border-right:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid; margin-bottom:10px;margin-top:10px; border-top:0px;}

#content-bottom #block-views-tag_yuedu-block_2 .content .view-content .views-field-tid .field-content a{ color:#000000;}

#content-bottom #block-views-tag_yuedu-block_2 .h2Container .title{height:35px;background-image: url(images/video_titleall.jpg); font-size:12px; 

color:#32A442; text-indent:26px; font-weight:700; line-height:35px;}

/*xiugai-------------------------------------------------------------------------------------------------------------------------*/

#content-bottom #block-views-yuedu-block_1{ width:610px;border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;;border-top:none;}

#content-bottom #block-views-yuedu-block_1 .block-inner .h2Container{height:35px;background-image: url(images/video_titleall.jpg);}

*html #content-bottom #block-views-yuedu-block_1 .block-inner .h2Container{height:35px;background-image: url(images/video_titleall.jpg); z-index:1;}

#content-bottom #block-views-yuedu-block_1 .block-inner .h2Container .title{

background-image:url(images/remph_titilebg.jpg);

background-repeat:no-repeat;

height:35px;

line-height:35px;

text-indent:30px;

clear:both;

font-size:14px;

color:#ffffff;

font-weight:700;

z-index:2;

}

#content-bottom #block-views-yuedu-block_1 .block-inner .content .view-content .item-list ul{  list-style:none; clear:both;line-height:22px;}

#content-bottom #block-views-yuedu-block_1 .block-inner .content .view-content .item-list ul li{

width:285px;

float:left;

line-height:180%;

overflow:hidden;

display:block;

margin:10px;

color:#666666;

}

*html #content-bottom #block-views-yuedu-block_1 .block-inner .content .view-content .item-list ul li {

color:#666666;

float:left;

margin:5px 0px 10px 5px;

width:290px;

overflow:hidden;

}

*+html #content-bottom #block-views-yuedu-block_1 .block-inner .content .view-content .item-list ul li{

width:290px;

float:left;

line-height:180%;

overflow:hidden;

display:block;

margin:10px 5px 10px 5px;

color:#666666;

}

#content-bottom #block-views-yuedu-block_1 .block-inner .content .view-content .item-list ul li .views-field-field-yuedu-cover-fid{

float:left;

margin-right:10px;

text-align:center;

width:100px;

height:155px;}

*html #content-bottom #block-views-yuedu-block_1 .block-inner .content .view-content .item-list ul li .views-field-field-yuedu-cover-fid{

float:left;

margin-right:0px;

text-align:center;

width:110px;

margin-left:5px;

height:155px;

}

*html .section-quiz #page #page-inner #main #main-inner #content #content-inner #quiz-taxomory-content #content-top{ position:relative;}

.section-quizcenter #content-bottom #block-block-46 .h2Container{ border-top:0px;}

.section-quiz #page #page-inner #main #main-inner #content #content-inner #quiz-taxomory-content #content-area .view-content .item-list ul li .views-field-name .field-content a{color:#2AAB47;}

.section-quiz #page #page-inner #main #main-inner #content #content-inner #quiz-taxomory-content #content-area .view-content .item-list ul li .views-field-title a{ font-weight:100;}

.section-quiz #page #page-inner #main #main-inner #content #content-inner #quiz-taxomory-content #content-area .view-content .item-list ul li .views-field-title .field-content a{ font-weight:100;}

.section-quiz #page #page-inner #main #main-inner #content #content-inner #quiz-taxomory-content #content-area .view-content .item-list ul li .views-field-name{ float:left; width:110px; text-align:left;}

.section-quiz #page #page-inner #main #main-inner #content #content-inner #quiz-taxomory-content #content-area .view-content .item-list ul li .views-field-title{ white-space:nowrap; overflow:hidden; text-align:left; margin-left:0px; text-indent:0px; display:inline;}

.section-quiz #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list .ul .views-row .views-field-title{ width:220px; overflow:hidden;}

.section-quiz #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list .ul .views-row .views-field-teaser{ height:50px;}





.section-quiz #main #main-inner #content #content-inner #quiz-taxomory-content #content-area .view-content .item-list ul li .views-field-teaser .field-content p{ color:#555555;}

#content-bottom #block-views-yuedu-block_1 .block-inner .content .view-content .item-list ul li .views-field-title{float:right;font-weight:700; width:170px; white-space:nowrap;overflow:hidden;}

#content-bottom #block-views-yuedu-block_1 .block-inner .content .view-content .item-list ul li .views-field-field-yuedu-author-value{float:left; width:170px;overflow:hidden; white-space:nowrap;}

#content-bottom #block-views-yuedu-block_1 .block-inner .content .view-content .item-list ul li .views-field-field-yuedu-author-value .field-content{ color:#000000; }

#content-bottom #block-views-yuedu-block_1 .block-inner .content .view-content .item-list ul li .views-field-field-yuedu-isbn-valu{float:left; width:170px;}

#content-bottom #block-views-yuedu-block_1 .block-inner .content .view-content .item-list ul li .views-field-field-yuedu-isbn-valu .field-content{ color:#000000;}



#content-bottom #block-views-yuedu-block_1 .block-inner .content .view-content .item-list ul li .views-field-field-yuedu-summary-value{float:left; width:170px; text-indent:26px;height:95px; overflow:hidden;}

*html #block-views-yuedu-block_1 .block-inner .content .view-content .item-list ul li .views-field-field-yuedu-summary-value .field-content {float:left; width:170px;height:100px; line-height:22px;word-wrap:break-word; white-space:normal; overflow:hidden;}

*+html #content-bottom #block-views-yuedu-block_1 .block-inner .content .view-content .item-list ul li .views-field-field-yuedu-summary-value{float:left; width:170px;height:95px; line-height:22px;word-wrap:break-word; overflow:hidden;}

.section-yuedulibrary  #page #page-inner #main #main-inner #content #content-inner #content-bottom .block .block-inner .content .view-yuedu .more-link a{color:#666666;}

/*-------tushufelei----------*/

.section-yuedulibrary #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-2{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;border-top:none; width:99.5%;}

.section-yuedulibrary #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-2 .block-inner .h2Container{

height:35px;

line-height:35px;

text-indent:10px;

clear:both;

background-image: url(images/video_titleall.jpg);

font-size:14px;

color:#32A442;

font-weight:700;

}

.section-yuedulibrary #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-2 .block-inner .content{width:300px; margin:0 auto; margin-bottom:10px; margin-left:10px;}

.section-yuedulibrary #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-2 .block-inner .content ul{ width:260px; margin:0 auto; margin-left:20px;}

.section-yuedulibrary #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-2 .block-inner .content ul li a{ color:#000000; font-size:12px; line-height:20px;}

.section-yuedulibrary #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-2 .block-inner .content ul li ul li a{ color:#666666; font-size:12px; line-height:20px;}



.section-yuedu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-2{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;border-top:none; width:99.5%;}

.section-yuedu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-2 .h2Container{

height: 35px;

line-height:35px;

text-indent:10px;

clear:both;

background-image: url(images/video_titleall.jpg);

font-size:14px;

color:#32A442;

font-weight:700;

}

.section-yuedu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-2 .block-inner .content{width:310px; margin:0 auto; margin-bottom:10px; margin-left:10px;}

.section-yuedu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-2 .block-inner .content ul{ width:270px; margin:0 auto; margin-left:20px;}

.section-yuedu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-2 .block-inner .content ul li a{ color:#000000; font-size:12px; line-height:20px;}

.section-yuedu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-2 .block-inner .content ul li ul li a{ color:#666666; font-size:12px; line-height:20px;}



/*-------tushufelei----------*/

#content-bottom .block-inner .content .view-content .views-field-tid .field-content a{float:left; margin-left:10px; height:25px; line-height:25px;}

#content-bottom #block-views-yuedu-block_1 .block-inner .content .view-content .item-list ul li .views-field-view-node{ float:right; padding-right:26px;}

#content-bottom #block-views-yuedu-block_1 .block-inner .content .view-content .item-list ul li .views-field-view-node .field-content a{ color:#FF0000;}

.section-yuedulibrary  #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-yuedu-block_1 .block-inner .content .view-dom-id-3 .more-link {

background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

height:35px;

line-height:34px;

margin-left:500px;

margin-top:-394px;

padding-top:2px;

text-align:center;

width:75px;

float:right;

} 

*html .section-yuedulibrary  #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-yuedu-block_1 .block-inner .content .view-dom-id-3 .more-link {

position:absolute;

background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

height:35px;

line-height:34px;

margin-left:510px;

margin-top:-382px;

padding-top:2px;

text-align:center;

width:75px;

float:left;

z-index:3;

display:block;

} 

*+html .section-yuedulibrary  #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-yuedu-block_1 .block-inner .content .view-dom-id-3 .more-link {

background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

height:35px;

line-height:34px;

margin-left:500px;

margin-top:-390px;

padding-top:2px;

text-align:center;

width:75px;

float:right;

} 

.section-yuedulibrary  #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-yuedu-block_1 .block-inner .content .view-id-yuedu .more-link {

background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

height:35px;

line-height:34px;

margin-left:500px;

margin-top:-394px;

padding-top:2px;

text-align:center;

width:75px;

float:right;

} 

*html .section-yuedulibrary  #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-yuedu-block_1 .block-inner .content .view-id-yuedu .more-link {

position:absolute;

background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

height:35px;

line-height:34px;

margin-left:510px;

margin-top:-382px;

padding-top:2px;

text-align:center;

width:75px;

float:left;

z-index:3;

display:block;

} 

*+html .section-yuedulibrary  #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-yuedu-block_1 .block-inner .content .view-id-yuedu .more-link {

background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

height:35px;

line-height:34px;

margin-left:500px;

margin-top:-390px;

padding-top:2px;

text-align:center;

width:75px;

float:right;

} 

#content-bottom #block-views-yuedu-block_2 .block-inner .content .more-link {

background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

height:35px;

line-height:34px;

margin-left:500px;

margin-top:-184px;

padding-top:2px;

text-align:center;

width:75px;

float:right;

} 

*html #content-bottom #block-views-yuedu-block_2 .block-inner .content .more-link {

background-image:url(images/class_more.jpg);

position:absolute;

background-position:center top;

background-repeat:no-repeat;

clear:both;

height:35px;

line-height:34px;

margin-left:500px;

margin-top:-184px;

padding-top:2px;

text-align:center;

width:75px;

float:right;

} 

#content-bottom #block-views-yuedu-block_3 .block-inner .content .more-link {

background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

height:35px;

line-height:34px;

margin-left:500px;

margin-top:-184px;

padding-top:2px;

text-align:center;

width:75px;

float:right;

} 

*html #content-bottom #block-views-yuedu-block_3 .block-inner .content .more-link {

position:absolute;

background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

height:35px;

line-height:34px;

margin-left:500px;

margin-top:-184px;

padding-top:2px;

text-align:center;

width:75px;

float:right;

}

*html .section-quizcenter #block-block-47 .content #quiz_zhuanxiang #quiz_zhuanxiang_content .more-link{

position:absolute;

background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

height:35px;

line-height:34px;

margin-left:400px;

margin-top:-159px;

padding-top:2px;

text-align:center;

width:75px;

float:right;}

.section-quizcenter #page #page-inner #main #main-inner #content #content-inner #content-bottom .block-block .block-inner .content .quiz_content .view-quiz .more-link a{color:#666666;}

.section-quizcenter #block-block-48 .content #quiz_kaoshi #quiz_kaoshi_content .more-link{

background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

height:35px;

line-height:34px;

margin-left:400px;

margin-top:-159px;

padding-top:2px;

text-align:center;

width:75px;

float:right;}

*html .section-quizcenter #block-block-48 .content #quiz_kaoshi #quiz_kaoshi_content .more-link{

position:absolute;

background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

height:35px;

line-height:34px;

margin-left:400px;

margin-top:-159px;

padding-top:2px;

text-align:center;

width:75px;

float:right;}

#block-block-47 .block-inner .content #quiz_zhuanxiang #quiz_zhuanxiang_content .view-content .item-list ul li .views-field-title{white-space:nowrap; width:150px; overflow:hidden; text-align:left;float:left;}

.section-quizcenter #block-block-49 .content #quiz_quwei #quiz_quwei_content .view-dom-id-7 .view-content .item-list ul li .views-field-name{margin:0

px;float:left;}

.section-quizcenter #block-block-49 .content #quiz_quwei #quiz_quwei_content .view-dom-id-7 .view-content .item-list ul li .views-field-title{ margin:0; width:150px; white-space:nowrap; overflow:hidden; float:left; display:inline;}



.section-quizcenter #block-block-49 .content #quiz_quwei #quiz_quwei_content .more-link{

background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

height:35px;

line-height:34px;

margin-left:400px;

margin-top:-159px;

padding-top:2px;

text-align:center;

width:75px;

float:right;}

*html .section-quizcenter #block-block-49 .content #quiz_quwei #quiz_quwei_content .more-link{

position:absolute;

background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

height:35px;

line-height:34px;

margin-left:400px;

margin-top:-159px;

padding-top:2px;

text-align:center;

width:75px;

float:right;}

*+html .section-quizcenter #block-block-49 .content #quiz_quwei #quiz_quwei_content .more-link{

background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

height:35px;

line-height:34px;

margin-left:410px;

margin-top:-159px;

padding-top:2px;

text-align:center;

width:75px;

float:right;}

.section-quizcenter .views-field-name span a{color:#2AAB47;} 

#sidebar-right #sidebar-right-inner #block-block-53 .block-inner .content .view-header{ height:25px}

#sidebar-right #sidebar-right-inner #block-block-53 .block-inner .content .view-header p a{color:#000000; font-weight:700; margin-left:5px; line-height:25px;}

#sidebar-right #sidebar-right-inner #block-block-53 .block-inner .content .view-content .views-field-name .field-content a{ color:#000000; margin-left:5px; margin-right:5px;}

#content-bottom #block-views-yuedu-block_2 .block-inner .content .view-content .item-list ul li .views-field-field-yuedu-cover-fid{ margin-top:10px;}

#content-bottom #block-views-yuedu-block_2 .block-inner .content .view-content .item-list ul{list-style:none;}

#content-bottom #block-views-yuedu-block_2 .block-inner .content .view-content .item-list ul li{

width:115px;

float:left;

text-align:center;

line-height:180%;

height:150px;

overflow:hidden;

display:block;

margin-left:5px;

}



#content-bottom #block-views-yuedu-block_3 .block-inner .content .view-content .item-list ul{list-style:none;}

#content-bottom #block-views-yuedu-block_3 .block-inner .content .view-content .item-list ul li{

width:115px;

float:left;

text-align:center;

line-height:180%;

height:150px;

overflow:hidden;

display:block;

margin-left:5px;

}

#content-bottom #block-views-yuedu-block_3 .block-inner .content .view-content .item-list ul li .views-field-field-yuedu-cover-fid{margin-top:10px; height:110px;} 

#content-bottom #block-views-yuedu-block_3 .block-inner .content .view-content .item-list ul li .views-field-field-yuedu-cover-fid .field-content{height:112px;}

*html #content-bottom #block-views-yuedu-block_3 .block-inner .content .view-content .item-list ul li .views-field-field-yuedu-cover-fid .field-content{height:112px;}

*+html #content-bottom #block-views-yuedu-block_3 .block-inner .content .view-content .item-list ul li .views-field-field-yuedu-cover-fid .field-content{height:112px;}

#content-bottom #block-views-yuedu-block_2{width:610px;border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;border-top:none;}

#content-bottom #block-views-yuedu-block_2 .block-inner .h2Container .title{

height: 35px;

line-height:35px;

text-indent:10px;

clear:both;

background-image: url(images/video_titleall.jpg);

font-size:14px;

color:#32A442;

font-weight:700;

}





#content-bottom #block-views-yuedu-block_3{width:610px;border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;border-top:none;}

#content-bottom #block-views-yuedu-block_3 .block-inner .h2Container .title{

height: 35px;

line-height:35px;

text-indent:10px;

clear:both;

background-image: url(images/video_titleall.jpg);

font-size:14px;

color:#32A442;

font-weight:700;

}

#block-block-45{width:610px;border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;border-top:none;}

#block-block-45 .h2Container .title{

height: 35px;

line-height:35px;

text-indent:10px;

clear:both;

background-image: url(images/video_titleall.jpg);

font-size:14px;

color:#32A442;

font-weight:700;

}

#block-block-45 .content .newlibrary{ width:610px; height:170px;}

#block-block-45 .content .newlibrary .newcont .Scrnewcont #newlist1 .view-content .item-list ul{ width:600px;overflow:hidden;}

#block-block-45 .content .newlibrary .newcont .Scrnewcont #newlist1 .view-content .item-list ul li{ margin-right:5px; margin-left:5px;}

#block-block-45 .content .newlibrary .newcont{

	width:500px;

	overflow:hidden;

	padding-top:10px;

	float: left;

}

.section-yuedu #page #page-inner #main #main-inner  #content #content-inne #content-area .view-dom-id-1 .view-content .item-list ul li .views-field-field-yuedu-summary-value .field-content{float:left; height:100px; line-height:30px;word-wrap:break-word; margin-left:5px; margin-right:5px; text-indent:26px;}

*html .section-yuedu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-field-yuedu-summary-value .field-content{float:left; height:100px; line-height:30px;word-wrap:break-word; margin-left:5px; margin-right:5px; text-indent:26px;}

.section-yuedu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-field-yuedu-summary-value .field-content{float:left; height:115px; line-height:30px;word-wrap:break-word; text-indent:26px; width:460px;}

*html .section-yuedu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-field-yuedu-summary-value .field-content{float:left; height:115px; line-height:30px;word-wrap:break-word; margin-left:5px; margin-right:5px; text-indent:26px;}

*+html .section-yuedu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-field-yuedu-summary-value .field-content{float:left; height:115px; line-height:30px;word-wrap:break-word; text-indent:26px; width:465px;}

.section-yuedu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li{width:600px;}

*html .section-yuedu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li {width:600px;}

*+html .section-yuedu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li {width:600px;}

*html .section-yuedu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-title{ width:450px;}

*html .section-yuedu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-title .field-content{width:450px;}

*html .section-yuedu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-title span.field-content a{line-height:25px; width:450px; height:25px; display:inline;white-space:nowrap;}

*html .section-yuedu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-field-yuedu-author-value{ width:450px;}

*html .section-yuedu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-field-yuedu-isbn-value{ width:450px;}

*html .section-yuedu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-field-yuedu-isbn-value{ width:450px;}





.section-yuedu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .item-list ul.pager .pager-item { margin-left:5px;}













#sidebar-right #sidebar-right-inner #block-views-quiz-block_6 .content .view-content .item-list .views-summary{color:#000000;clear:both;}

#sidebar-right #sidebar-right-inner #block-views-quiz-block_6 .content .view-content .item-list .views-summary li{ float:left; color:#000000; margin-left:5px;width:105px;overflow:hidden;

}

#sidebar-right #block-views-yuedu-block_8 .content .view-content{ margin-right:5px; margin-left:5px;}

#sidebar-right #block-views-yuedu-block_8 .content .view-content span{ margin-left:2px;}

#sidebar-right #block-views-yuedu-block_8 .content .view-content span a{ color:#000000;}

.field-field-yuedu-yuanzhushangxi .field-label {border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;}

.field-field-yuedu-yuanzhushangxi .field-items{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid; padding-left:20px;}

.field-field-yuedu-yuanzhushangxi .field-items .odd p a{color:#000000; font-size:12px;margin:0 10px;white-space:nowrap;}

.field-field-yuedu-yuanzhushangxi .field-items .odd p {

text-indent:0px;font-size:12px;

}

#page #page-inner #main #main-inner #content #content-inner #content-area .node-type-ebook .node-inner .content .field-field-yuedu-summary .field-label{height: 35px;

line-height:190%;

text-indent:26px;

clear:both;

background-image: url(images/video_titleall.jpg);

font-size:12px;

color:#32A442;

font-weight:700;}

#page #page-inner #main #main-inner #content #content-inner #content-area .node-type-ebook .node-inner .content .field-field-yuedu-yuanzhushangxi{ margin-top:10PX;}

#page #page-inner #main #main-inner #content #content-inner #content-area .node-type-ebook .node-inner .content .field-field-yuedu-yuanzhushangxi .field-label{height: 35px;

line-height:190%;

text-indent:26px;

clear:both;

background-image: url(images/video_titleall.jpg);

font-size:12px;

color:#32A442;

font-weight:700;}

.field-field-yuedu-summary .field-items .odd p{ width:960px; margin:0 auto;}

.field-field-yuedu-summary{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;} 

.field-field-yuedu-summary .field-items .odd{ margin-left:10px; margin-right:10px;}



/*xiugai------------------------------------------------------------------------------------------------------------------------------------*/

/** navbar **/

#navbar {

}

#navbar-inner {

}

#search-box /* Wrapper for the search form */ {

width:975px;

clear:both;

background-image: url(images/search_bg.jpg);

height: 31px;

text-indent:15px;

font-size:12px;

font-weight:normal;

}

#edit-search-theme-form-1-wrapper label /* Label that says "Search this site:" */ {

display: none;

}

#primary /* Primary links */ {

}

#secondary /* Secondary links */ {

}

/** sidebar-left **/

#sidebar-left {

}

#sidebar-left-inner {

}

/** sidebar-right **/

#sidebar-right{

float:left;

margin-left:615px;

margin-right:-975px;

padding:0;

width:360px;

}



#sidebar-right #block-tagadelic-18 .content a {}

#sidebar-right-inner {

}

/** footer **/

#footer {

clear:both;

width:975px;

margin-left:auto;

margin-right:auto;

}

#footer-inner {

}

#footer-message /* Wrapper for the footer message from Drupal's "Site information"

and for any blocks placed in the footer region */ {

}

/** closure **/

#closure-blocks /* Wrapper for any blocks placed in the closure region */ {

}

/** Drupal nodes **/

.node /* Node wrapper */ {

}

.node-inner /* Additional wrapper for node */ {

}

.sticky /* A sticky node (displayed before others in a list) */ {

}

.node-unpublished /* Unpublished nodes */ {

/* background-color: #fff4f4; */ /* Drupal core uses a #fff4f4 background */

}

.node-unpublished div.unpublished, /* The word "Unpublished" displayed beneath the content. */ .comment-unpublished div.unpublished {

height: 0;

overflow: visible;

color: #d8d8d8;

font-size: 75px;

line-height: 1;

font-family: Impact, "Arial Narrow", Helvetica, sans-serif;

font-weight: bold;

text-transform: uppercase;

text-align: center;

word-wrap: break-word; /* A very nice CSS3 property */

}

.node-mine /* A node created by the current user */ {

}

.node-teaser /* A node displayed as teaser */ {

}

/* All nodes are given a node-type-FOO class that describes the type of

* content that it is. If you create a new content type called

* "my-custom-type", it will receive a "node-type-my-custom-type" class.

*/

.node-type-page /* Page content node */ {

}

.node-type-story /* Story content node */ {

}

.node h2.title /* Node title */ {

}

.marker /* "New" or "Updated" marker for content that is new or updated for the current user */ {

color: #c00;

}

.node .picture /* The picture of the node author */ {

}

.node.node-unpublished .picture, .comment.comment-unpublished .picture {

position: relative; /* Otherwise floated pictures will appear below the "Unpublished" text. */

}

.node .meta /* Wrapper for submitted and terms data */ {

}

.node .submitted /* The "posted by" information */ {

}

.node .terms /* Node terms (taxonomy) */ {

}

.node .content /* Node's content wrapper */ {

}

.node div.links /* Wrapper for node links */ {

margin: 1em 0;

}

ul.links /* Taxonomy links, node links, comment links */ {

margin: 0;

padding: 0;

}

ul.links.inline {

clear:both;

}

.content .inline {}

ul.links li {

display: inline;

list-style-type: none;

padding: 0 0.5em;

height:30px; line-height:30px;

}

.preview .node /* Preview of the content before submitting new or updated content */ {

/* background-color: #ffffea; */ /* Drupal core uses a #ffffea background */

}

/** Drupal comments **/

#comments /* Wrapper for the list of comments and its title */ {

margin: 1em 0;

}

#comments-title /* Heading for the list of comments */ {

}

.comment /* Wrapper for a single comment */ {

}

.comment-inner /* Additional wrapper for a single comment */ {

}

.comment-preview /* Preview of the comment before submitting new or updated comment */ {

}

.comment.new /* A new comment since the user last viewed the page. */ {

}

.comment.odd /* An odd-numbered comment in the list of comments */ {

}

.comment.even /* An even-numbered comment in the list of comments */ {

}

.comment.first /* The first comment in the list of comments */ {

}

.comment.last /* The last comment in the list of comments */ {

}

.comment-unpublished /* Unpublished comments */ {

/* background-color: #fff4f4; */ /* Drupal core uses a #fff4f4 background */

}

.comment-unpublished div.unpublished /* The word "Unpublished" displayed beneath the content. See also the div.unpublished declaration in the node section above. */ {

}

.comment-published /* Published comments */ {

}

.comment-by-anon /* A comment created by an anonymous user */ {

}

.comment-by-author /* A comment created by the node's author */ {

}

.comment-mine /* A comment created by the current user */ {

}

.comment h3.title /* Comment title */ {

}

.new /* "New" marker for comments that are new for the current user */ {

color: #c00;

}

.comment .picture /* The picture of the comment author */ {

}

.comment .submitted /* The "posted by" information */ {

}

.comment .content /* Comment's content wrapper */ {

}

.comment .user-signature /* The user's signature */ {

}

.comment div.links /* Wrapper for comment links. See also the ul.links declaration in the node section above. */ {

margin: 1em 0;

}

.indented /* Nested comments are indented */ {

/* margin-left: 25px; */ /* Drupal core uses a 25px left margin */

}

.preview .comment /* Preview of the comment before submitting new or updated comment */ {

/* background-color: #ffffea; */ /* Drupal core uses a #ffffea background */

}

/** Drupal blocks **/

.front #f_main-top {

clear:both;

}

.front #f_main-middle {

clear:both

}

.block /* Block wrapper */ {

margin-bottom: 6px;

}

.block.region-odd /* Zebra striping for each block in the region */ {

}

.block.region-even /* Zebra striping for each block in the region */ {

}

.block.odd /* Zebra striping independent of each region */ {

}

.block.even /* Zebra striping independent of each region */ {

}

.region-count-1 /* Incremental count for each block in the region */ {

}

.count-1 /* Incremental count independent of each region */ {

}

.block-inner /* Additional wrapper for block */ {

}

.block h2.title /* Block title */ {

}

.block .content /* Block's content wrapper */ {

}

#block-aggregator-category-1 /* Block for the latest news items in the first category */ {

}

#block-aggregator-feed-1 /* Block for the latest news items in the first feed */ {

}

#block-block-1 /* First administrator-defined block */ {

}

/*  #block-block-43 {

line-height:180%;

clear:both;

}*/

#block-block-27 {

line-height:180%;

}

/* user login */

#block-block-44 {

width:225px;

float:left;

}

#block-block-44 h2.title {

font-size:14px;

line-height:26px;

background-image: url(images/userlogintitle.jpg);

background-repeat: repeat-x;

height: 26px;

border-top-width: 4px;

border-top-style: solid;

border-top-color: #299738;

border-right-width: 1px;

border-bottom-width: 1px;

border-left-width: 1px;

border-right-style: solid;

border-bottom-style: solid;

border-left-style: solid;

border-right-color: #D1D1D1;

border-bottom-color: #D1D1D1;

border-left-color: #D1D1D1;

color: #299C3D;

font-weight: bold;

line-height: 26px;

text-align: left;

text-indent: 8px;

}

#block-block-44 div.content {

font-size:14px;

background-image: url(images/userlogincontentbg.jpg);

background-repeat: repeat-x;

border-right-width: 1px;

border-bottom-width: 1px;

border-left-width: 1px;

border-top-style: none;

border-right-style: solid;

border-bottom-style: solid;

border-left-style: solid;

border-right-color: #D1D1D1;

border-bottom-color: #D1D1D1;

border-left-color: #D1D1D1;

height: 243px;

line-height:200%;

text-align:center;

padding-top:15px;

}

#block-block-44 div.user_block_content {

padding-top:10px;

line-height:200%;

}

#block-block-44 .user_welcome {

font-weight:bold;

}

/* user login over */

#block-block-26 /* First administrator-defined block */ {

float:left;

width:520px;

text-align: center;

height: 290px;

overflow:hidden;

}

/* swf over

userpay */

#block-block-34 /* First administrator-defined block */ {

float:left;

width:230px;

}

#block-block-34 h2.title {

font-size:14px;

line-height:26px;

background-image: url(images/userlogintitle.jpg);

background-repeat: repeat-x;

height: 26px;

border-top-width: 4px;

border-top-style: solid;

border-top-color: #299738;

border-right-width: 1px;

border-bottom-width: 1px;

border-left-width: 1px;

border-right-style: solid;

border-bottom-style: solid;

border-left-style: solid;

border-right-color: #D1D1D1;

border-bottom-color: #D1D1D1;

border-left-color: #D1D1D1;

color: #299C3D;

font-weight: bold;

line-height: 26px;

text-align: left;

text-indent: 8px;

}

#block-block-34 div.content {

padding:4px;

font-size:12px;

background-image: url(images/userlogincontentbg.jpg);

background-repeat: repeat-x;

border-right-width: 1px;

border-bottom-width: 1px;

border-left-width: 1px;

border-top-style: none;

border-right-style: solid;

border-bottom-style: solid;

border-left-style: solid;

border-right-color: #D1D1D1;

border-bottom-color: #D1D1D1;

border-left-color: #D1D1D1;

height: 248px;

}

#block-block-34 div.content h5 {

margin-top:3px;

color:#33A641;

border-top:1px dashed #C6C6C6;

clear:both;

font-size:14px;

padding:3px;

}

#block-block-34 div.content p {

padding:3px;

clear:both;

line-height:170%;

}

#block-block-34 label {

font-size:12px;

font-weight:normal;

line-height:180%;

}

#block-block-34 #edit-gcode {

width:160px;

clear:both;

height:22px;

border:1px solid #C4C4C4;

line-height:20px;

}

#block-block-34 #edit-submit {

font-size:12px;

color:#FFFFFF;

background-image: url(images/userpay_bg.jpg);

background-repeat: repeat-x;

height:22px;

line-height:20px;

border:0px;

width:64px;

text-align:center;

float:left;

margin-left:28px;

cursor:pointer;

}

#block-block-34 #edit-submit-1{

font-size:12px;

color:#FFFFFF;

background-image: url(images/userpay_bg.jpg);

background-repeat: repeat-x;

height:22px;

line-height:20px;

border:0px;

width:64px;

text-align:center;

float:left;

margin-left:28px;

cursor:pointer;

}

#block-block-34 .form-item a {

}

#block-block-34 div.userpay_height {

height:3px;

clear:both;

}

#block-block-34 .form-item {

text-align:center;

}

#block-block-34 #edit-gcode-wrapper {

text-align:center;

}

/* 

userpay over

center ad*/

#block-block-35 {

clear:both;

width:975px;

height:90px;

margin-bottom:8px;

}

/* ad over

library */



#block-block-36 {

float:left;

width:480px;

}

#block-block-36 div.h2Container {

height: 35px;

line-height:35px;

clear:both;

background-image: url(images/video_titleall.jpg);

border-right-width: 1px;

border-left-width: 1px;

border-top-style: none;

border-right-style: solid;

border-bottom-style: none;

border-left-style: solid;

border-right-color: #DBDBDB;

border-left-color: #DBDBDB;

font-size:14px;

color:#2A2A2A;

}

#block-block-36 h2 {

font-size:14px;

font-weight:bold;

text-align:center;

width:117px;

background-image:url(images/class_titlebg.jpg);

float:left;

height: 34px;

line-height: 34px;

color: #FFFFFF;

margin-top: 1px;

margin-left: 1px;

}

#block-block-36 div.content {

border:1px solid #CECECE;

border-top:0px;

clear:both;

height:210px;

text-align: center;

overflow:hidden;

display:block;

}

#block-block-36 li {

list-style-type:none;

}

#library_frame_left {

float:left;

padding-top: 33px;

padding-bottom: 25px;

width: 50px;

text-align: center;

}

#library_frame_right {

float:right;

width: 50px;

padding-top: 33px;

padding-bottom: 25px;

text-align: center;

}

#librarycontent {

float: left;

padding: 5px;

width: 300%;

height:200px;

overflow:hidden;

}

#librarycontent ul {

float:left;

list-style:none;

}

#librarycontent ul li {

width: 125px;

float: left;

text-align:center;

line-height:180%;

height:185px;

overflow:hidden;

display:block;

}

#librarycontent ul li span {

font-weight:bold;

height:24px;

line-height:24px;

}





#block-views-yuedu_buyers-block_1 div.h2Container h2 {

background-image:url(images/video_titleall.jpg);

border-left:1px solid #D1D1D1;

border-right:1px solid #D1D1D1;

color:#32A442;

font-size:12px;

font-weight:700;

height:35px;

line-height:35px;

margin-top:10px;

text-indent:26px;

}

#block-views-yuedu_buyers-block_1 .view-content .views-row {

float:left;

margin:5px 0 5px 20px;

}

#block-views-yuedu_buyers-block_1 .view-yuedu-buyers {

border-bottom:1px solid #D1D1D1;

border-left:1px solid #D1D1D1;

border-right:1px solid #D1D1D1;

clear:both;

width:99.8%;

}



#librarycontent #library_l_cont #llist1.views-row,#librarycontent #library_l_cont #llist1.views-row-1,#librarycontent #library_l_cont #llist1.views-row-odd,#librarycontent #library_l_cont #llist1.views-row-first

{ border:0px;}

#librarycontent #library_l_cont #llist1 .views-field-name{ height:23px; line-height:23px; overflow:hidden;}

#block-block-36 div.more_link {

background-image:url(images/class_more.jpg);

clear:both;

float:left;

height:35px;

line-height:34px;

margin-left:400px;

margin-top:-230px;

padding-top:2px;

text-align:center;

width:75px;

display:none;

}

/*library new style*/

.newlibrary{

	width:476px;

	overflow:hidden;

	margin:0;

}

.newlibrary .newcont{

	width:378px;

	overflow:hidden;

	padding-top:10px;

	float: left;

}

.newlibrary .newcont .ul{ padding:0px; margin:0px;}

.newlibrary .Scrnewcont{width:10000000px;}



.newlibrary .newcont ul li {

width:130px;

float:left;

text-align:center;

}

.newlibraryleft{

	float:left;

	width:48px;

	text-align:center;

	padding-top: 10px;

	cursor:pointer;

}

.newlibraryright{

	float:right;

	width:48px;

	text-align:center;

	padding-top: 10px;

	cursor:pointer;

}



.newlibrary .newcont ul li  img{padding:4px;background:#fff;border:1px solid #ccc;display:block;margin:0 auto;}

.newlibrary .newcont ul li  p{line-height:26px;color:#505050;}

.newlibrary .newcont a:link,.newlibrary .newcont a:visited{color:#626466;text-decoration:none;}

.newlibrary .newcont a:hover{color:#f00;text-decoration:underline;}

.newlibrary #newlist1,.newlibrary #newlist2{float:left;}

#content-area #node-50224 .node-inner .meta{ float:right;}

#content-area #node-50224 .node-inner .meta ul {text-align:right;}

#newlist1 ul{padding:0px; margin:0px}

/* library new over */

/* library over



test start */

#block-block-37 {

float:right;

width: 480px;

display:block;

overflow:hidden;

}

#block-block-37 div.h2Container {

height: 35px;

line-height:35px;

clear:both;

background-image: url(images/video_titleall.jpg);

border-right-width: 1px;

border-left-width: 1px;

border-top-style: none;

border-right-style: solid;

border-bottom-style: none;

border-left-style: solid;

border-right-color: #DBDBDB;

border-left-color: #DBDBDB;

font-size:14px;

color:#2A2A2A;

}

#block-block-37 h2 {

font-size:14px;

font-weight:bold;

text-align:center;

width:117px;

background-image:url(images/class_titlebg.jpg);

float:left;

height: 34px;

line-height: 34px;

color: #FFFFFF;

margin-top: 1px;

margin-left: 1px;

}

#block-block-37 div.content {

border:1px solid #CECECE;

border-top:0px;

clear:both;

height:200px;

text-align: center;

padding: 5px;

width:468px;

display:block;

}

#block-block-37 div.content ul {

float:left;

list-style:none;

height:180px;

}

#block-block-37 div.content ul li {

float:left;

width:105px;

padding-right: 5px;

padding-left: 5px;

line-height:160%;

}

#block-block-37 div.content ul li h1 {

font-size:12px;

font-weight:bold;

}

#block-block-37 div.content ul li span {

text-align:left;

font-weight:normal;

float:left;

padding-left:18px;

}

#block-block-37 div.more_link {

background-image:url(images/class_more.jpg);

clear:both;

float:left;

height:35px;

line-height:34px;

margin-left:390px;

margin-top:-39px;

padding-top:2px;

position:absolute;

text-align:center;

width:75px;

display:none;

}



/* test over*/

#block-block-38 {

width:975px;

float:left;

}

#block-block-38 div.content {

clear:both;

width:973px;

border:1px solid #CECECE;

border-top:0px;

height:155px;

overflow:hidden;

}

#block-block-38 div.h2Container {

height: 35px;

line-height:35px;

clear:both;

background-image: url(images/video_titleall.jpg);

border-right-width: 1px;

border-left-width: 1px;

border-top-style: none;

border-right-style: solid;

border-bottom-style: none;

border-left-style: solid;

border-right-color: #DBDBDB;

border-left-color: #DBDBDB;

font-size:14px;

color:#2A2A2A;

}

#block-block-38 h2 {

font-size:14px;

font-weight:bold;

text-align:center;

width:117px;

background-image:url(images/class_titlebg.jpg);

float:left;

height: 34px;

line-height: 34px;

color: #FFFFFF;

margin-top: 1px;

margin-left: 1px;

}

#block-block-38 div.content ul {

list-style-type:none;

}

#block-block-38 div.content ul li {

float:left;

padding:5px;

width: 124px;

margin: 5px;

text-align:center;

}

#block-block-38 div.content ul li img {

border:1px solid #CCCCCC;

padding:2px;

}

#block-block-38 .more_link {

background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

float:left;

height:35px;

line-height:34px;

margin-left:889px;

margin-top:-34px;

padding-top:2px;

position:absolute;

text-align:center;

width:75px;

}

#video_frame_left {

float:left;

padding-top: 25px;

padding-bottom: 25px;

width: 50px;

text-align: center;

}

#video_frame_right {

float:right;

width: 50px;

padding-top: 25px;

padding-bottom: 25px;

text-align: center;

}

#videocontent_list {

float:left;

text-align: center;

padding-top: 5px;

padding-bottom: 5px;

height: 160px;

width: 200%;

}

#videocontent_list ul {

list-style-type:none;

}

#videocontent_list ul li {

float:left;

padding:5px;

width: 124px;

margin: 5px;

}

#videocontent_list ul li img {

/*border:1px solid #CCCCCC;*/

padding:2px;

height:105px;

}

.library_swf {

width:480px;

overflow:hidden;

padding-top: 4px;

padding-right: 0;

padding-bottom: 0px;

height:195px;

}

.library_swf .l_leftbotton {

height:90px;

width:32px;

overflow:hidden;

float:left;

display:inline;

cursor:pointer;

margin-top: 30px;

margin-right: 0;

margin-bottom: 0;

margin-left: 0;

padding-right: 10px;

padding-left: 10px;

background-image: url(images/frame_left.jpg);

background-repeat: no-repeat;

background-position: 22px;

}

.library_swf .l_rightbotton {

height:90px;

width:32px;

overflow:hidden;

float:left;

display:inline;

cursor:pointer;

margin-top: 30px;

margin-right: 0;

margin-bottom: 0;

margin-left: 0;

padding-right: 10px;

padding-left: 10px;

background-image: url(images/frame_right.jpg);

background-repeat: no-repeat;

background-position: 10px;

}

.library_swf .l_cont {

width:375px;

overflow:hidden;

float:left;

}

.Scrl_cont {

width:70000px;

}

.library_swf #llist1, .library_swf #llist2 {

float:left;

}

.library_swf #llist1.ul {

float:left;

list-style:none;

}

.library_swf #llist1 ul li {

float:left;

width:125px;

line-height:180%;

text-align:center;

overflow:hidden;

height:190px;

}

.library_swf #llist1 ul li.views-row-odd{

border:0px;

}

.library_swf #llist1 ul li.views-row-even {

border:0px;

}

/*library swf*/

.rollBox {

width:975px;

overflow:hidden;

padding-top: 3px;

padding-right: 0;

padding-bottom: 3px;

}

.rollBox .LeftBotton {

height:90px;

width:32px;

overflow:hidden;

float:left;

display:inline;

cursor:pointer;

margin-top: 25px;

margin-right: 0;

margin-bottom: 0;

margin-left: 0;

padding-right: 10px;

padding-left: 10px;

background-image: url(images/frame_left.jpg);

background-repeat: no-repeat;

background-position: 22px;

}

.rollBox .RightBotton {

height:90px;

width:32px;

overflow:hidden;

float:left;

display:inline;

cursor:pointer;

margin-top: 25px;

margin-right: 0;

margin-bottom: 0;

margin-left: 0;

padding-right: 10px;

padding-left: 10px;

background-image: url(images/frame_right.jpg);

background-repeat: no-repeat;

background-position: 10px;

}

.rollBox .Cont {

width:870px;

overflow:hidden;

float:left;

padding-top:8px;

}

.rollBox .ScrCont {

width:10000000px;

}

.rollBox .Cont .ul {

float:left;

list-style:none;

padding:0px; margin:0px;

}

.rollBox .Cont .ul li {

width:145px;

float:left;

text-align:center;

}

.rollBox .Cont .ul li  img {

padding:4px;background:#fff;border:1px solid #ccc;display:block;margin:0 auto;

}



.rollBox .Cont a:link, .rollBox .Cont a:visited {

color:#626466;

text-decoration:none;

}

.rollBox .Cont a:hover {

color:#f00;

text-decoration:underline;

}

.rollBox #List1, .rollBox #List2 {

float:left;

}

#block-block-39 {

width:250px;

float:left;

height: 75px;

}

#block-block-40 {

width:470px;

float:left;

text-align: center;

height: 75px;

}

#block-block-41 {

float:right;

line-height:180%;

width:240px;

text-align:right;

height: 55px;

padding-top: 20px;

}

/* friend link start */

#block-block-42 {

width:975px;

float:left;

background-image: url(images/friendlink_bg.jpg);

background-repeat: repeat-x;

height: 30px;

border: 1px solid #E3E3E3;

borde-bottom:none;

line-height:190%;

overflow:hidden;

margin-top: 3px;

margin-bottom: 3px;

text-align: left;

text-indent: 5px;

font-size:12px;

}

#block-block-42 a {

margin:0.5em;

color:#000000;

}

#block-block-42 p img{}

*html #block-block-42 p img{ position:absolute; margin-left:-8px; margin-right:10px;}

*+html #block-block-42 p img{ position:absolute; margin-left:-8px; margin-right:10px;}



#block-block-42 h2.title {

height:30px;

line-height:30px;

float:left;

width:63px;

padding:0px;

margin:0px;

color:#2A2A2A;

font-size:14px;

}

#block-block-42 div.content {

float:right;

width:910px;

text-align:left;

line-height:30px;

height:30px;

}

*html #block-block-42 div.content {

float:right;

width:910px;

text-align:left;

line-height:30px;

padding-top:3px;

height:30px;

vertical-align:middle;

}

#block-block-42 div.content p {

line-height:30px;

height:30px;

}

/*friend link over*/

#block-block-43 {

line-height:180%;

font-size:12px;

text-align:left;

}

#block-blog-0 /* "Recent blog posts" block */ {

}

#block-book-0 /* "Book navigation" block for the current book's table of contents */ {

}

#block-comments-0 /* "Recent comments" block */ {

}

#block-forum-0 /* "Active forum topics" block */ {

}

#block-forum-1 /* "New forum topics" block */ {

}

#block-menu-2 /* "Primary links" block */ {

}

#block-node-0 /* "Syndicate" block for primary RSS feed */ {

}

#block-poll-0 /* "Most recent poll" block */ {

}

#block-profile-0 /* "Author information" block for the profile of the page's author */ {

}

#block-search-0 /* "Search form" block */ {

width:975px;

clear:both;

background-image: url(images/search_bg.jpg);

height: 31px;

line-height:30px;

text-indent:10px;

}

#block-search-0 #edit-search-block-form-1 label {

font-size:12px;

font-weight:normal;

line-height:28px;

}

#block-search-0 #edit-search-block-form-1-wrapper label {

font-size:12px;

font-weight:normal;

line-height:26px;

}

#block-search-0 .form-text {

height:20px;

line-height:18px;

border:1px solid #CCCCCC;

}

#block-search-0 #edit-submit-2 {

font-size:12px;

color:red;

background-image: url(images/user_search_bg.jpg);

background-repeat: repeat-x;

height:17px;

line-height:15px;

border:0px;

width:39px;

text-align:center;

padding:0px;

margin:0px;

}

#block-search .form-submit {

font-size:12px;

color:red;

background-image: url(images/user_search_bg.jpg);

background-repeat: repeat-x;

height:17px;

line-height:15px;

border:0px;

width:39px;

text-align:center;

padding:0px;

margin:0px;

cursor:pointer;

}

#block-statistics-0 /* "Popular content" block */ {

}

#block-user-0 /* "User login form" block */ {

width:225px;

float:left;

}

#block-user-0 h2 {

font-size:14px;

line-height:26px;

background-image: url(images/userlogintitle.jpg);

background-repeat: repeat-x;

height: 26px;

border-top-width: 4px;

border-top-style: solid;

border-top-color: #299738;

border-right-width: 1px;

border-bottom-width: 1px;

border-left-width: 1px;

border-right-style: solid;

border-bottom-style: solid;

border-left-style: solid;

border-right-color: #D1D1D1;

border-bottom-color: #D1D1D1;

border-left-color: #D1D1D1;

color: #299C3D;

font-weight: bold;

line-height: 26px;

text-align: left;

text-indent: 8px;

}

#block-user-0 div.content {

padding:10px;

font-size:14px;

background-image: url(images/userlogincontentbg.jpg);

background-repeat: repeat-x;

border-right-width: 1px;

border-bottom-width: 1px;

border-left-width: 1px;

border-top-style: none;

border-right-style: solid;

border-bottom-style: solid;

border-left-style: solid;

border-right-color: #D1D1D1;

border-bottom-color: #D1D1D1;

border-left-color: #D1D1D1;

height: 245px;

text-align:center;

line-height:260%;

padding-top:10px;

}

#block-user-0 ul {

float:left;

text-align:center list-style:none;

}

#block-user-0 ul li {

float:left;

text-align:center;

padding:5px;

width:70px;

margin:5px;

font-size:14px;

}

#block-user-0 label {

float:left;

width:80px;

font-size:14px;

font-weight:normal;

text-align:right;

padding-right:3px;

}

#block-user-0 #edit-submit {

font-size:12px;

color:#FFFFFF;

background-image: url(images/userlogin_bg.jpg);

background-repeat: repeat-x;

height:22px;

line-height:20px;

border:0px;

width:41px;

text-align:center;

padding:0px;

margin:0px;

}

#block-user-0 #edit-pass, #edit-name {

height:19px;

line-height:19px;

}

.page-user-register #edit-name{border:1px solid #83a4bd;

height:19px;

line-height:19px;}

#block-user-0 li.first {

text-align:right;

}

#block-user-0 li.last {

text-align:left;

}

#block-user-1 /* "Navigation" block for Drupal navigation menu */ {

}

#block-user-2 /* "Who's new" block for a list of the newest users */ {

}

#block-user-3 /* "Who's online" block for a list of the online users */ {

}

#block-menu-menu-new-primary-links ul /* "Primary links" block */ {

width:975px;

float:left;

clear:both;

height:33px;

line-height:33px;

background-image: url(images/menu_bg.jpg);

height:32px;

line-height:32px;

list-style:none;

padding:0px;

margin:0px;

list-style-type:none;

list-style-image:none;

background-repeat: repeat-x;

}

#block-menu-menu-new-primary-links ul li {

float:left;

width:96px;

text-align:center;

list-style:none;

border-right:1px solid #22837A;

}

#block-menu-menu-new-primary-links ul li a:link {

color:#ffffff;

font-size:12px;

font-weight:bold;

display:block;

}

#block-menu-menu-new-primary-links ul li a:visited {

color:#ffffff;

font-size:12px;

font-weight:bold;

display:block;

}

#block-menu-menu-new-primary-links ul li a:hover {

color:#ffffff;

font-size:12px;

font-weight:bold;

background-image:;

background-image: url(images/hover_bg.jpg);

background-repeat: repeat-x;

display:block;

}

#block-menu-menu-new-primary-links ul li a:active {

color:#ffffff;

font-size:12px;

font-weight:bold;

background-image:

background-image: url(images/hover_bg.jpg);

background-repeat: repeat-x;

display:block;

}

/*jifen duihuan*/

#block-menu-menu-dushu-tab {

-moz-background-clip:border;

-moz-background-inline-policy:continuous;

-moz-background-origin:padding;

background:transparent url(/sites/2u4u.com.cn/themes/uuonline/images/tab-bar.png) repeat-x scroll left bottom;

float:left;

line-height:normal;

width:100%;

}

#block-menu-menu-dushu-tab {

line-height:normal;

}

.block ul {

}

#block-menu-menu-dushu-tab ul.menu {

list-style-image:none;

list-style-position:outside;

list-style-type:none;

margin:0;

padding:0;

}

#block-menu-menu-dushu-tab li.leaf {

float:left;

list-style:none;

padding:8px;

margin:3px;

font-size:14px;

}

#block-menu-menu-dushu-tab div.h2Container {

display:none;

}

.view-jifenduihuan .views-row-odd {

float:left;

line-height:20px;

width:50%;

}

.view-jifenduihuan .views-row-odd {

float:left;

line-height:20px;

width:50%;

}

.view-jifenduihuan .views-row-even {

float:right;

line-height:20px;

width:50%;

}

.view-jifenduihuan .views-field-buyitnowbutton {

padding:10px 0;

}

.views-field-buyitnowbutton .field-content input{ display:none; overflow:hidden;}

.view, .block {

float:left;

width:100%;

}

.view-jifenduihuan .views-row-odd {

float:left;

line-height:20px;

width:48%;

}

/*.views-row-odd, .views-row-even {

border-bottom:1px solid #DDDDDD;

float:left;

padding:5px 0;

width:100%;

}*/

.uc-price {

white-space:nowrap;

}

.page-dushu #content-area .view-erp{

line-height:150%;}

.page-dushu #content-area .node-inner

{

clear:both;}

.page-dushu #content-area .node-inner h2.title{

font-size:14px;

clear:both;

height:24px;

line-height:24px;

}



.page-gushi #content-area .views-row {

line-height:160%;

}

.page-dushu #content-area .views-row {

line-height:160%;

}

.page-dushu #content-area .node_links {

clear:both

}

.page-dushu #content-area .content {

float:left;

margin-left:0;

margin-right:-975px;

padding:0;

width:975px;

}

.page-dushu #content-area .view-erp .views-row{

float:left;

width:49%;

display:block;

border-bottom:1px dotted #CCCCCC;}

#block-views-jifenduihuan-block_1 img.imagecache-product-fengmiang {

width:200px;

height:150px;

display:block;

}



/*ұ titleʽ  viewγɵblock  ½blockγɵblockֲͬʵַ*/

#sidebar-right .block-views .h2Container{

height: 35px;

line-height:35px;

clear:both;

background-image: url(images/video_titleall.jpg);

border-right-width: 1px;

border-left-width: 1px;

border-top-style: none;

border-right-style: solid;

border-bottom-style: none;

border-left-style: solid;

border-right-color: #DBDBDB;

border-left-color: #DBDBDB;

font-size:14px;

color:#2A2A2A;

}

#sidebar-right .block-block .h2Container{

height: 35px;

line-height:35px;

clear:both;

background-image: url(images/video_titleall.jpg);

font-size:14px;

color:#2A2A2A;

}

#sidebar-right #block-block-53{

border-bottom-width: 1px;

border-right-width: 1px;

border-left-width: 1px;

border-top-style: none;

border-right-style: solid;

border-bottom-style: solid;

border-left-style: solid;

border-right-color: #DBDBDB;

border-left-color: #DBDBDB;

border-bottom-color: #DBDBDB;

width:99.5%;

}

#sidebar-right .h2Container .title {

font-size:12px;

font-weight:bold;

color:#4AB740;

float:left;

height: 33px;

line-height: 33px;

padding-left: 8px;

}

#sidebar-right .block-tagadelic div.content {

border:1px solid #CECECE;

border-top:0px;

clear:both;

height:auto;

line-height:2em;

padding:1em;

}



#sidebar-right .block-tagadelic div.content a {

padding:10px;

}



#sidebar-right div.view-sidebar-rem4men2xiao3zu4, 

#sidebar-right div.view-yuedu, 

#sidebar-right div.view-quiz,#sidebar-right div.view-tag-yuedu

{

border:1px solid #CECECE;

border-top:0px;

clear:both;

height:auto;

width:99.5%;

line-height:2em;



}

#sidebar-right #sidebar-right-inner #block-views-tag_yuedu-block_1 .content .view-content .views-field-tid{float:left;margin-left:10px;}

*html #sidebar-right #sidebar-right-inner #block-views-tag_yuedu-block_1 .content .view-content .views-field-tid{float:left; width:auto; margin-left:5px;}

*+html #sidebar-right #sidebar-right-inner #block-views-tag_yuedu-block_1 .content .view-content .views-field-tid{float:left; width:auto; margin-left:10px;display:inline;}

#block-views-yuedu-block_6 .content .view-content 

{ clear:both;}

#block-views-yuedu-block_6 .content .view-content .more-link

{ clear:both; margin-right:10px;}

#block-views-yuedu-block_6 .content .view-content .item-list ul li{

width:300px; word-break:keep-all; clear:both;overflow:hidden;}

#block-views-yuedu-block_6 .content .view-content .item-list ul li .views-field-counter{ float:left;}

#block-views-yuedu-block_6 .content .view-content .item-list ul li .views-field-title{ float:left;}







#block-views-yuedu-block_7 .content .view-content 

{ clear:both;}

#block-views-yuedu-block_7  .content .view-content .more-link

{ clear:both; margin-right:10px;}

#block-views-yuedu-block_7  .content .view-content .item-list ul li{

width:300px; word-break:keep-all; clear:both;overflow:hidden;}

#block-views-yuedu-block_7 .content .view-content .item-list ul li .views-field-counter{ float:left;}

#block-views-yuedu-block_7  .content .view-content .item-list ul li .views-field-title{ float:left;}

#block-views-quiz-block_5 .content .view-content .item-list ul li{

width:300px; word-break:keep-all; clear:both;}

#block-views-quiz-block_5 .content .view-content .item-list ul li .views-field-counter{ float:left;}

#block-views-quiz-block_5 .content .view-content .item-list ul li .views-field-title{ float:left;}



#content .field-items .field-label{line-height:35px; font-weight:700;height:35px;background:url(images/video_titleall.jpg); margin-top:10px;}

#content .field-items .field-item { line-height:22px; text-indent:26px;}

.node-type-ebook  #content .field-items .field-item {line-height:22px;}

#content .field-items .swftools{ margin:10px 0 10px 0;}

.node-type-ebook fieldset {

border:0 none;

}

.node-type-ebook fieldset .field-items{float:left; border:0px; border:none; color:#000000;}

.node-type-ebook fieldset a img{ display:block;float:left;margin:-30px auto 0 120px;position:absolute;}

*html .node-type-ebook fieldset a img{width:30px; height:30px; display:block; float:left; margin:0 auto; position:absolute; margin-top:-5px;}

*+html .node-type-ebook fieldset a img{width:30px; height:30px; display:block; float:left; margin:0 auto; position:absolute; margin-top:-10px;margin-left:0px;}

.node-type-ebook #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-ebook .node-inner .meta .terms-inline ul li a{color:#32A441;}

/*---sanji-wangyoupinglun---------------*/

.node-type-ebook #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-id-nodecomments_threaded  .view-header{ font-size:14px; font-weight:700; height:30px; margin-top:10px; margin-bottom:10px;line-height:30px;background-color:#F6F8F3; text-indent:10px;}

.node-type-ebook #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-id-nodecomments_threaded .view-content .node-type-comment-blog{ width:970px; margin:0 auto;}

.node-type-ebook #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-id-nodecomments_threaded .view-content .indented{ width:970px; margin:0 auto;}





.node-type-ebook #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-id-nodecomments_threaded .view-content .node-type-comment-blog .node-inner .picture{float:left;}

.node-type-ebook #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-id-nodecomments_threaded .view-content .node-type-comment-blog .node-inner .picture img{ margin:0 auto;width:50px; height:50px;}

.node-type-ebook #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-id-nodecomments_threaded .view-content .node-type-comment-blog .node-inner h2.title{ float:right; width:910px; HEIGHT:22px; line-height:22px;}

.node-type-ebook #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-id-nodecomments_threaded .view-content .node-type-comment-blog .node-inner .meta{float:right; width:910px; HEIGHT:22px; line-height:22px;color:#666666;}

.node-type-ebook #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-id-nodecomments_threaded .view-content .node-type-comment-blog .node-inner .content{clear:both; width:900px; margin-left:60px;}

.node-type-ebook #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-id-nodecomments_threaded .view-content .node-type-comment-blog .node-inner .content p{ font-size:12px; color:#000000;}

.node-type-ebook #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-id-nodecomments_threaded .view-content .node-type-comment-blog .node-inner ul.links{border-bottom:#CCCCCC 1px dashed;width:970px;}

.node-type-ebook #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-id-nodecomments_threaded .view-content .node-type-comment-blog .node-inner ul.links li{ height:22px; line-height:22px;}

.node-type-ebook #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-id-nodecomments_threaded .view-content .node-type-comment-blog .node-inner ul.links li a{ float:right;color:#32A441;}

/*---sanji-wangyoupinglun---------------*/

#quiz_quwei_content .view-content .item-list ul li .views-field-name{ float:left;}

#quiz_quwei_content .view-content .item-list ul li .views-field-title{ float:left;}

/* group */

#thmr_2.views-table {

background-color:#ffffff;

}

#thmr_154 #thmr_265 h2.title {

font-size:14px;

font-weight:normal;

padding-top:8px;

}

#thmr_154 #thmr_257.views-view-grid {

text-align:center;

}

#thmr_161.views-field-title {

height:23px;

line-height:23px;

overflow:hidden;

}

#thmr_161 #thmr_2.views-table {

padding-top:8px;

}

#thmr_257.views-field-title {

height:23px;

line-height:23px;

overflow:hidden;

}

/* group over */

/** Drupal boxes **/

/* Wrapper for Comment form, Comment viewing options, Menu admin, and

* Search results.

*/

.box /* Wrapper for box */ {

}

.box-inner /* Additional wrapper for box */ {

}

.box h2.title /* Box title */ {

}

.box .content /* Box's content wrapper */ {

}

/** Miscellaneous Drupal styles **/

.error /* Errors that are separate from div.messages status messages (see above.) */ {

/* color: #e55; */ /* Drupal core uses a #e55 background */

}

.warning /* Warnings that are separate from div.messages status messages (see above.) */ {

/* color: #e09010; */ /* Drupal core uses a #e09010 background */

}

.more-link /* Aggregator, blog, and forum more link */ {

}

#user-login-form /* Drupal's default login form */ {

text-align: left;

}

tr.even /* Some tables have rows marked even or odd. */ {

/* background-color: #eee; */ /* Drupal core uses a #eee background */

}

tr.odd {

/* background-color: #eee; */ /* Drupal core uses a #eee background */

}

li a.active /* The active item in a Drupal menu */ {

color: #000;

}

/** Drupal forms **/

.form-item /* Wrapper for a form element (or group of form elements) and its label */ {

}

.form-checkboxes, .form-radios {

margin: 1em 0;

}

.form-item input.error, /* Highlight the form elements that caused a form submission error */ .form-item textarea.error, .form-item select.error {

border: 2px solid #c00;

}

.form-item label /* The label for a form element */ {

}

.form-item label.option /* The label for a radio button or checkbox */ {

}

.form-required /* The part of the label that indicates a required field */ {

color: #c00;

font-weight:normal;

}

.form-item .description /* The descriptive help text (separate from the label) */ {

font-size: 0.85em;

font-weight:normal;

}

.form-checkboxes .form-item, /* Pack groups of checkboxes and radio buttons closer together */ .form-radios .form-item {

}

.form-submit /* The submit button */ {

}

.container-inline div, .container-inline label /* Inline labels and form divs */ {

display: inline;

}

.tips /* Tips for Drupal's input formats */ {

margin: 0;

padding: 0;

}

/** OpenID **/

/* The default styling for the OpenID login link seems to assume Garland's

* styling of list items.

*/

#gift-points-chongzhi-form {

text-align:center;

}

#user-login-form ul /* OpenID creates a new ul above the login form's links. */ {

margin-bottom: 0; /* Position OpenID's ul next to the rest of the links. */

}

#user-login-form {

text-align:center;

}

#user-login-form li.openid-link, /* The "Log in using OpenID" links. */ #user-login li.openid-link {

margin-top: 1em;

margin-left: -20px; /* Un-do some of the padding on the ul list. */

padding-left: 20px;

background-position: left center;

}

#user-login-form li.user-link, /* The "Cancel OpenID login" links. */ #user-login li.user-link {

/* margin-top: 1em;

list-style-type: disc;

list-style-position: outside;*/

}

#user-login li.openid-link, /* The OpenID links on the /user form. */ #user-login li.user-link {

/* margin-left: -2em;*/ /* Un-do all of the padding on the ul list. */

}

/** Drupal admin tables **/

/* We overrode these styles in html-elements.css, but restore them for the

* forms on the site.

*/

form tbody {

border-top: 1px solid #ccc;

}

form th {

text-align: left;

padding-right: 1em;

border-bottom: 3px solid #ccc;

}

form tbody th {

border-bottom: 1px solid #ccc;

}

form thead th {

text-align: left;

padding-right: 1em;

border-bottom: 3px solid #ccc;

}

.block ul {

list-style:none;

margin:0px;

padding:0px;

list-style-type:none;

list-style-image:none;

}

/*chong zhi */

.page-chongzhi #content-header h1.title {

font-size:1.5em;

padding-top:8px;

}

.page-chongzhi #content-inner div.form-item {

line-height:200%;

}

.page-chongzhi #content-inner.form-text {

width:200px;

border:1px solid #CCCCCC;

line-height:21px;

height:20px;

color:#000000;

}

.page-chongzhi #content-inner #edit-caution {

padding:5px;

color:#000000;

border:1px solid #CCCCCC;

background-color:#FFFFFF;

font-size:12px;

}

.section-chongzhi #page #page-inner #main #main-inner #content #content-inner #content-area form div #edit-caution-wrapper #edit-caution{ color:#000000; font-size:12px; line-height:22px;overflow-y:scroll;scrollbar-arrow-color:#C3C3C3;scrollbar-base-color:#F6F6F6;scrollbar-darkshadow-color:#F6F6F6;scrollbar-3dlight-color:#F6F6F6; height:160px;} 

*html .section-chongzhi #page #page-inner #main #main-inner #content #content-inner #content-area form div #edit-caution-wrapper #edit-caution{ color:#000000; font-size:12px; line-height:22px;overflow-y:scroll;scrollbar-arrow-color:#C3C3C3;scrollbar-base-color:#F6F6F6;scrollbar-darkshadow-color:#F6F6F6;scrollbar-3dlight-color:#F6F6F6; height:160px;} 

*+html .section-chongzhi #page #page-inner #main #main-inner #content #content-inner #content-area form div #edit-caution-wrapper #edit-caution{ color:#000000; font-size:12px; line-height:22px;overflow-y:scroll;scrollbar-arrow-color:#C3C3C3;scrollbar-base-color:#F6F6F6;scrollbar-darkshadow-color:#F6F6F6;scrollbar-3dlight-color:#F6F6F6; height:160px;} 

.section-chongzhi #page #page-inner #main #main-inner #content #content-inner #content-area form div #edit-caution-wrapper #edit-caution{color:#000000;}

*html .section-chongzhi #page #page-inner #main #main-inner #content #content-inner #content-area form div #edit-caution-wrapper #edit-caution{color:#000000;}

*+html .section-chongzhi #page #page-inner #main #main-inner #content #content-inner #content-area form div #edit-caution-wrapper #edit-caution{color:#000000;}

.page-chongzhi #block-block-27 .content {

line-height:170%;

}

.page-chongzhi #block-block-27 .content p {

margin-bottom:3px;

}

.page-chongzhi #content-area input.form-text{

width:200px; border:1px solid #CCCCCC;  height:20px; line-height:22px;}

/*whx shipin*/

.page-shipin-bbc #content-header, 

.page-shipin-followme #content-header, 

.page-shipin-itn #content-header, 

.page-shipin-bianlunsai #content-header, 

.page-shipin-yanjiangsai #content-header .title {

display:none;

}

/*

** HTML elements

*/

body.drag {

cursor: move;

}

table {

background-color:#FFFFFF;

margin-top:5px;

}

th.active img {

display: inline;

}









std.active {

background-color: #ddd;

}

td.checkbox, th.checkbox {

text-align: center;

}

tbody {

border-top: 1px solid #ccc;

}

tbody th {

border-bottom: 1px solid #ccc;

}

thead th {

text-align: left; /* LTR */

padding-right: 1em; /* LTR */

border-bottom: 3px solid #ccc;

}

.node-type-quiz #content-inner {

min-height:395px;

}

#multichoice-render-question-form {

font-size:1.2em;

}



.views-field-title .field-content a{color:#000000;}

.page-xiaozu #main-inner{ margin-top:5px;}

.page-xiaozu #content-area table.views-table{ width:95%;}

.page-xiaozu #content #content-header h1{ font-size:14px; font-weight:bold;}

.library_swf.item-list ul{ float:left; list-style:none;}

.library_swf.item-list ul li { float:left;}

.library_swf.views-row{ float:left;}

.library_swf.views-row-odd,.library_swf .views-row-last{ float:left;}

.library_swf.views-field-title{ width:125px; overflow:hidden;}

.library_swf.field-content{ height:23px; line-height:23px; overflow:hidden}

#ask_question a {

background-image:url(images/ask_question.png);

background-position:left top;

background-repeat:no-repeat;

height:47px;

text-indent:-9999px;

width:121px;

}

tr.even, tr.odd {

background-color:#EEEEEE;

border-bottom:1px dashed  #CCCCCC;

padding:0.1em 0.6em;

}





.view-sidebar-rem4men2xiao3zu4 table {

background-color:#FFFFFF;

margin-top:5px;

text-align:center;

width:100%;

}



.page-xiaozu td {

background-color: #ffffff;

padding:6px 2px;

line-height:2em;

border-bottom-width: 1px;

border-bottom-style: dashed;

border-bottom-color: #CCCCCC;

}



.page-xiaozu h1.title {

font-size:1.5em;

font-weight:bold;

color:#666666;

margin:0 1em;

}

.view-xiaozu-frontpage .view-content {

margin-bottom:3em;

}





.item-list .pager {

clear:both;

line-height:3em;

text-align:center;

}

.section-yuedu #content .view-content .item-list{ width:100%; clear:both;}

.section-yuedu #content .view-content .item-list ul li {

color:#666666;

border-bottom:1px dashed #DDDDDD;

float:left;

line-height:180%;

padding:10px 0px 20px 10px;

clear:both;

overflow:hidden;

width:603px;

margin:0 auto;

}







.section-yuedu #content .view-content .item-list ul li img{ margin-left:5px;}

*html .section-yuedu #content .view-content .item-list ul li {

width:603px;

color:#666666;

border-bottom:1px dashed #DDDDDD;

float:left;

line-height:180%;

padding:10px 0px 20px 10px;

clear:both;

}

.section-yuedu #content .view-content .item-list ul li .views-field-title .field-content a:hover{color:#666666;}

.section-yuedu #sidebar-right .view-yuedu .item-list ul li{

clear:both;

float:left;

white-space:nowrap;

color:#666666;

width:605px;

}

.section-yuedu #sidebar-right  .view-yuedu .view-content{clear:both;}

.section-yuedu #sidebar-right  .view-yuedu .more-link{clear:both;}

.section-yuedu #sidebar-right  .view-yuedu .more-link a{color:#32A441;}

*html .section-yuedu #sidebar-right .view-yuedu .more-link a{color:#32A441;}

.section-yuedu #content .view-content .views-field-field-yuedu-cover-fid{

float:left;

margin-right:25px;

text-align:center;

width:100px;

}

.section-yuedu #sidebar-right .view-yuedu .view-content{

padding-left:4px;}

.node-type-blog #content-inner{

margin:1em;

}



.node-type-blog #content .picture {

float:left;

text-align:center;

margin-right:1.5em;

}



.node-type-blog #content-header h1{ color:#494949;

display:block;

font-size:22px;

font-weight:700;

line-height:1.1em;

padding:5px 0 15px;

}

.node-type-blog #content .meta{color:#666666;

float:left;

font-size:14px;

line-height:160%;}

.node-type-blog #content .meta .submitted{

clear:both;

float:left;}

.node-type-blog #content .meta  .terms{

float:left;

clear:both;}

.node-type-blog #content .content {

clear:both;

font-size:12px;

line-height:180%;

padding:1em 0;

}

.node-type-blog #content .content p{

margin-bottom:8px;}

.node-type-blog #content .groups{ font-size:12px; line-height:150%;}

.node-type-blog #comments .content {

padding:5px 0;

}

#comments {

border-top:1px dashed #CCCCCC;

margin:1em 0;

padding:1em 0;

}

.section-node-add #content-area .links{ line-height:150%;}

.section-node-add #content-area{ line-height:150%;}

.section-node-add #content-area .node-form{ line-height:150%;}

.section-node-add #content #content-header h1{

line-height:150%; font-size:14px; font-weight:bold;}

.section-node-add #content h2{

line-height:150%; font-size:14px;}

.section-node-add #content .meta{

line-height:150%; font-size:14px;}

.section-node-add #content .content{

line-height:150%; font-size:14px;}





.page-jifenduihuan #content .views-row{

margin-bottom:10px;}

.page-jifenduihuan #content .views-field-sell-price{

color:#CC3300;}

.node-type-book-100-classics .node-type-book-100-classics .node-inner .content .field-type-filefield .field-item{

float:left; width:100px;}

.node-type-book-100-classics .node-type-book-100-classics .node-inner ul{ clear:both;}

.node-type-book-100-classics .content {

line-height:150%;}





#content-area .view-content .item-list ul li .views-field-title .field-content a{ color:#000000; font-weight:700;}

#content-area .view-content .item-list ul li .views-label-field-yuedu-author-value{ color:#666666;} 

#content-area .view-content .item-list ul li .views-field-field-yuedu-summary-value .field-content{color:#666666;}

#content-area .view-content .item-list ul li .views-field-field-yuedu-author-value .field-content{color:#000000; word-break:keep-all;}

#content-area .view-content .item-list ul li .views-label-field-yuedu-isbn-value{ color:#666666;} 

#content-area .view-content .item-list ul li .field-content{ color:#000000;} 

#content-area .view-content .item-list ul li .views-field-view-node .field-content a{color:#FF0000; float:right; padding-right:30px;}

#block-menu-menu-new-primary-links ul li.last {border-right:0px;}



#block-views-yuedu-block_6 .content .view-content .item-list

{ clear:both; width:100%;}

#block-views-yuedu-block_6 .content .view-content .item-list ul li

{ clear:both; width:100%; word-break:keep-all; overflow:hidden;}

#block-views-yuedu-block_6 .content .view-content .item-list .views-field-counter

{ width:20px; float:left; margin-left:10px;}

#block-views-yuedu-block_6 .content .view-content .item-list .views-field-title

{ width:300px; float:right;}

#block-views-yuedu-block_6 .content .view-content .more-link

{ clear:both; width:380px; float:left;}

*#block-views-yuedu-block_6 .content .view-content .item-list

{ clear:both; width:100%;}

*html #block-views-yuedu-block_6 .content .view-content .item-list ul li

{ clear:both; width:100%; word-break:keep-all; overflow:hidden;}

*html #block-views-yuedu-block_6 .content .view-content .item-list .views-field-counter

{ width:15px; float:left; margin-left:5px;}

*html #block-views-yuedu-block_6 .content .view-content .item-list .views-field-title

{ width:300px; float:right;}





#block-views-yuedu-block_7 .content .view-content .item-list

{ clear:both; width:100%;}

#block-views-yuedu-block_7 .content .view-content .item-list ul li

{ clear:both; width:100%; word-break:keep-all; overflow:hidden;}

#block-views-yuedu-block_7 .content .view-content .item-list .views-field-counter

{ width:20px; float:left; margin-left:10px;}

#block-views-yuedu-block_7 .content .view-content .item-list .views-field-title

{ width:300px; float:right;}

#block-views-yuedu-block_7 .content .view-content .more-link

{ clear:both; width:380px; float:left;}

*#block-views-yuedu-block_7 .content .view-content .item-list

{ clear:both; width:100%;}

*html #block-views-yuedu-block_7 .content .view-content .item-list ul li

{ clear:both; width:100%; word-break:keep-all; overflow:hidden;}

*html #block-views-yuedu-block_7 .content .view-content .item-list .views-field-counter

{ width:15px; float:left; margin-left:5px;}

*html #block-views-yuedu-block_7 .content .view-content .item-list .views-field-title

{ width:300px; float:right;}



#block-views-quiz-block_5 .content .view-content .item-list

{ clear:both; width:100%;}

#block-views-quiz-block_5 .content .view-content .item-list ul li

{ clear:both; width:100%; word-break:keep-all; overflow:hidden;}

#block-views-quiz-block_5 .content .view-content .item-list .views-field-counter

{ width:20px; float:left; margin-left:10px;}

#block-views-quiz-block_5 .content .view-content .item-list .views-field-title

{ width:300px; float:right;}

*html #block-views-quiz-block_5 .content .view-content .item-list

{ clear:both; width:100%;}

*html #block-views-quiz-block_5 .content .view-content .item-list ul li

{ clear:both; width:100%; word-break:keep-all; overflow:hidden;}

*html #block-views-quiz-block_5 .content .view-content .item-list .views-field-counter{ width:15px; float:left; margin-left:5px;}

*html #block-views-quiz-block_5 .content .view-content .item-list .views-field-title{ width:300px; float:right;}

*html #block-views-yuedu-block_6 .content .view-content .more-link

{ clear:both; width:380px; float:left;}

.page-quizcenter #content-bottom .block-block{width:610px;border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;border-top:none;}



.page-quizcenter #content-bottom .block-block .h2Container .title {

height: 35px;

line-height:35px;

text-indent:10px;

clear:both;

background-image: url(images/video_titleall.jpg);

font-size:14px;

color:#32A442;

font-weight:700;

}

.page-quizcenter  #content-bottom .block-block .content .view-quiz .more-link{

background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

height:35px;

line-height:34px;

margin-top:-159px;

margin-right:10px;

padding-top:2px;

text-align:center;

width:75px;

float:right;

} 

.page-quizcenter .quiz_image{

float:left; 

width:90px; 

padding:25px 5px;

}



.page-quizcenter #content-bottom .block-block .block-inner .content .quiz_content{float:left; width:510px; line-height:25px;} 

.page-quizcenter #content-bottom .block-block .block-inner .content .quiz_content .view-content .item-list ul li{ width:230px; float:left;margin-right:15px;}

.page-quizcenter #content-bottom .block-block .block-inner .content .quiz_content .view-content .item-list ul li .views-field-name{float:left;}

.page-quizcenter #content-bottom .block-block .block-inner .content .quiz_content .view-content .item-list ul li .views-field-title{float:left;}







#content-bottom .content #quiz_jingzhun .quiz_image{ float:left; width:90px; margin-left:10px; margin-right:10px; }

#content-bottom .content #quiz_jingzhun .quiz_content{ font-size:12px; float:left; width:460px; margin-right:10px; line-height:25px;}

#content-bottom .content #quiz_jingzhun .quiz_content p a{ color:#32A442;font-weight:700;}

#content-bottom .content #quiz_jingzhun .quiz_content ul{ list-style:disc; list-style-position:inside; color:#666666;}





#content .field-items .field-item  .swftools{

text-indent:0px;

}



.section-quiz #content-header{

background-image:url(images/video_titleall.jpg);

height:35px;

line-height:35px;

margin:0;

padding-left:20px;

}

.section-quiz #content-header h1.title{

color:#4AB740;

font-size:14px;

font-weight:bold;

height:35px;

line-height:35px;

padding-left:20px;

}

.section-quiz #page #main #content{

border-bottom:1px solid #D1D1D1;

border-left:1px solid #D1D1D1;

border-right:1px solid #D1D1D1;

margin-left:0;

margin-right:-975px;

width:615px;

}



.quiz-taxomory-image {

text-align:center;

}

.section-quiz #quiz-taxomory-content .view-quiz ul {

width:600px;

}

.section-quiz #quiz-taxomory-content .view-quiz .view-content li{

float:left;

line-height:22px;

margin:15px 0 0 20px;

width:255px;

}

.section-quiz #quiz-taxomory-content .view-quiz .views-field-teaser{

clear:left;

text-indent:26px;

line-height:23px;

height:46px;

overflow:hidden;

}

*html .section-quiz #quiz-taxomory-content .view-quiz .views-field-teaser .field-content{

text-indent:26px;

line-height:23px;

word-wrap:break-word; 

overflow:hidden;

height:55px;

}



#block-block-53 .content{

line-height:23px;

margin:0 10px;

}

#block-block-53 .content .view-content .views-row .views-field-name .field-content {

margin-left:5px;

float:left;

}

#block-block-53 .content .view-content .views-row a{ white-space:nowrap;

clear:both;

}

#content-bottom #block-similarterms-19 .block-inner .h2Container .title{height:35px;background-image: url(images/video_titleall.jpg); font-size:12px; color:#32A442; text-indent:26px; font-weight:700; line-height:35px; border:none;}

#content-bottom #block-similarterms-19{

border-left:1px solid #D1D1D1;

border-right:1px solid #D1D1D1;

border-bottom:1px solid #D1D1D1;

width:99.8%;

}

/*----qiuz-sanji-----*/

.section-quiz #page #page-inner #main #main-inner #content #content-inner #content-area .view-display-id-page_5 .view-content .item-list ul{margin-bottom:20px;} 

.section-quiz #page #page-inner #main #main-inner #content #content-inner #content-area .view-display-id-page_5 .view-content .item-list ul li.views-row{ width:255px; float:left; margin-left:30px;}





section-quiz #page #page-inner #main #main-inner #content #content-inner #content-area .view-display-id-page_5 .view-content .item-list ul li.views-row .views-field-title .field-content a{ text-indent:25px; height:25px; line-height:25px;}

.section-quiz #page #page-inner #main #main-inner #content #content-inner #content-area .view-display-id-page_5 .view-content .item-list ul li.views-row .views-field-teaser .field-content p{ text-indent:26px; line-height:22px;}



.section-quiz #page #page-inner #main #main-inner #content #content-inner #content-top{line-height:1px;font-size:0px; display:inline;}

*html .section-quiz #page #page-inner #main #main-inner #content #content-inner #content-top{line-height:1px;font-size:0px; display:inline; position:absolute;}

.section-quiz #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul .views-row .views-field-title{width:240px;white-space:nowrap; line-height:22px;}

*html .section-quiz #page #page-inner #main #main-inner #content #content-inner #content-area .view-display-id-page_5 .view-content .item-list ul li.views-row{ width:270px; float:left; margin-left:10px;}

*html .section-quiz #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul .views-row .views-field-title{width:240px; white-space:nowrap; line-height:22px;}

*html .section-quiz #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul .views-row .views-field-title a{ width:240px; white-space:nowrap;}

*html .section-quiz #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul .views-row .views-field-teaser{height:50px;}

*html .section-quiz #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-teaser .field-content{ height:50px;}

*html .section-quiz #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-teaser .field-content p{text-indent:26px; line-height:22px; height:50px;WORD-BREAK:break-all; white-space:normal;}



/*----qiuz-sanji-----*/

.section-node #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-similarterms-19 .block-inner .content .item-list ul li{ float:left;width:450px;white-space:nowrap; margin-left:20px; height:25px; line-height:25px;text-indent:15px;background-image:url(images/list_style_type_disc.jpg); background-repeat:no-repeat; margin-left:10px;overflow: hidden;

white-space: nowrap;

-o-text-overflow: ellipsis;

text-overflow: ellipsis;

}

*html .section-node #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-similarterms-19 .block-inner .content .item-list ul li{ float:left;width:450px;white-space:nowrap;height:25px; line-height:25px;text-indent:15px;background-image:url(images/list_style_type_disc.jpg); background-repeat:no-repeat; margin-left:20px; overflow: hidden;

white-space: nowrap;

-o-text-overflow: ellipsis;

text-overflow: ellipsis;

}

#content-bottom #block-similarterms-19 .block-inner .content .item-list ul li a{color:#000000; font-size:12px;}



.section-node #page #page-inner #main #main-inner #content #content-inner #content-header h1.title{ font-size:14px; color:#32A442; text-align:center; font-weight:700; height:40px; line-height:40px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-similarterms-16 .block-inner .h2Container h2.title{ font-size:14px; color:#32A442;font-weight:700; border-bottom:#999999 1px solid; margin-top:20px; line-height:30px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-similarterms-16 .content .item-list ul{}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-similarterms-16 .content .item-list ul li{background-image:url(images/list_style_type_disc.jpg);width:240px; float:left;height:30px; line-height:30px;background-repeat:no-repeat; padding-left:10px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-similarterms-16 .content .item-list ul li a{ color:#000000;line-height:30px;}

.section-node #page #page-inner #main #main-inner #content #content-inner .content div p{ font-size:14px; line-height:30px;}

.section-node #page #page-inner #main #main-inner #content #content-inner .content .form-submit{ background:url(images/submitbg.jpg); background-repeat:no-repeat; border:none; font-size:14px; font-weight:700; color:#FFFFFF; text-align:center; width:57px; height:22px; margin:0 auto; width:57px; height:22px;}

.node-type-quiz #page #page-inner #main #main-inner #content #content-inner #content-area .meta{text-align:right; border-bottom:dashed 1px #555555; width:600px; line-height:25px; height:25px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .meta div{float:right; height:30px; line-height:30px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node-inner .content  td .quiz_summary_question {margin-left:10px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node-inner .content  td .quiz_summary_question p{float:left; width:400px; overflow:hidden;line-height:25px; height:25px;}

.node-type-quiz #page #page-inner #main #main-inner #content{margin-left:15px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node-inner .content #quiz_progress {

font-size:12px; margin-top:10px;

font-style:normal;

}

.node-type-quiz #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-quiz .node-inner .meta .terms ul li a{color:#32A442;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node-inner .content #quiz_progress em{font-size:12px; margin-top:10px;

font-style:normal;

}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node-inner .content form div p{font-family:Times New Roman;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node-inner .content .sticky-enabled td   .quiz_summary_question .quiz_question_bullet{ width:30px; float:left;height:25px; line-height:25px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node-inner .content table.sticky-enabled{ background-color:#FFFFFF; width:600px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node-inner .content .sticky-enabled tbody{background-color:#FFFFFF;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node-inner .content{background-color:#FFFFFF;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node-inner .content table.sticky-enabled table.sticky-enabled{ width:420px;margin-left:30px;background-color:#FFFFFF;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node-inner .content table.sticky-enabled table.sticky-enabled tdbody td{ font-weight:700;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node-inner .content table.sticky-enabled table.sticky-enabled thead tr th{ border:none;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node-inner .content table.sticky-enabled table.sticky-enabled tr{ background-color:#FFFFFF;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node-inner .content table.sticky-enabled table.sticky-enabled tdbody .quiz_summary_qrow{border-bottom:#CCCCCC 1px dashed;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node-inner .content table.sticky-enabled .quiz_summary_qrow{background-color:#FFFFFF;}

.section-quiz #page #page-inner #content-area .view-content .item-list ul li .views-field-title .field-content a{color:#32A442;}

#block-search-0 .content #search-block-form div .container-inline .form-submit{ background:url(images/sousuobg.gif); background-repeat:no-repeat; border:none; font-size:12px; color:#FF0000; width:45px; height:24px; cursor:pointer;}

.section-chongzhi #page #page-inner #main{background:url(images/jifenchongzhibg.jpg); padding:1px; background-repeat:repeat-x; margin-top:0px; text-align:center;}

*html .section-chongzhi #page #page-inner #main{background:url(images/jifenchongzhibg.jpg); padding:1px; background-repeat:repeat-x; margin-top:0px;}

*+html .section-chongzhi #page #page-inner #main{background:url(images/jifenchongzhibg.jpg); padding:1px; background-repeat:repeat-x; margin-top:0px;}

.section-chongzhi #page #page-inner #main #main-inner{ display:inline-block;width:930px; margin:0 auto; margin-top:30px;background:#FFFFFF; border:1px solid #E7E7E5; text-align:left;}

.section-chongzhi #page #page-inner #main #main-inner{ height:470px;}

.section-chongzhi #page #page-inner #main #main-inner #content #content-inner #content-header h1.title{ font-size:14px;color:#32A442; font-weight:700; text-indent:0px;}

.section-chongzhi #page #page-inner #main #main-inner #content{ width:520px;}

.section-chongzhi #page #page-inner #main #main-inner #content #content-inner{width:490px; margin:0 auto; margin-left:20px;}

*html .section-chongzhi #page #page-inner #main #main-inner #content #content-inner{width:490px; margin:0 auto;}

*+html .section-chongzhi #page #page-inner #main #main-inner #content #content-inner{width:490px; margin:0 auto;}

.section-chongzhi #page #page-inner #main #main-inner #content #content-inner #content-area div .form-submit{ background:url(images/submitbg.jpg); background-repeat:no-repeat; border:none; font-size:12px; font-weight:700; color:#FFFFFF; text-align:center; width:57px; height:22px;}

.section-chongzhi #page #page-inner #main #main-inner #content #content-inner #content-area div label{font-size:12px;color:#32A442; font-weight:700;border-bottom:#CCCCCC solid 1px; margin-bottom:10px;}

.section-chongzhi #page #page-inner #main #main-inner #content #content-inner #content-area div #edit-caution-wrapper #edit-caution{ color:#000000;}

.section-chongzhi #page #page-inner #main #main-inner #content #content-inner #content-area div .form-item{ text-indent:26px;}

.section-chongzhi #page #page-inner #main #main-inner #content #content-inner #content-area div #edit-caution-wrapper label{}

.section-chongzhi #page #page-inner #main #main-inner #content #content-inner #content-area div .form-item textarea{height:161px; line-height:22px;  color:#000000;}

*html .section-chongzhi #page #page-inner #main #main-inner #content #content-inner #content-area div .form-item textarea{height:161px; line-height:22px;  color:#000000;}

*+html .section-chongzhi #page #page-inner #main #main-inner #content #content-inner #content-area div .form-item textarea{height:161px; line-height:22px;  color:#000000;}

.section-chongzhi #page #page-inner #main #main-inner #content #content-inner #content-area form #edit-gcode-wrapper{text-indent:0px;}

.section-chongzhi #page #page-inner #main #main-inner #sidebar-right{width:410px; float:left;margin-left:530px; position:absolute;}

.section-chongzhi #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner{width:380px; float:left;}

.section-chongzhi #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-27{ width:345px; float:left; margin-top:5px;}

.section-chongzhi #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-27 .block-inner .content #jifen_uses #jifen_uses_title{font-size:14px;color:#32A442; font-weight:700; line-height:30px; height:30px;}

.section-chongzhi #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-27 .block-inner .content #jifen_uses #jifen_uses_content{ text-indent:26px;}

.section-chongzhi #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-27 .block-inner .content #jifen_get #jifen_get_title{font-size:14px;color:#32A442; font-weight:700;line-height:30px; height:30px;}

.section-chongzhi #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-27 .block-inner .content #jifen_get  #jifen_get_content p{ text-indent:26px;}

.section-chongzhi #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-27 .block-inner .content #jifen_rules #jifen_rules_title{font-size:14px;color:#32A442; font-weight:700;line-height:30px; height:30px;}

.section-chongzhi #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-27 .block-inner .content #jifen_rules #jifen_rules_content{text-indent:25px;}

.section-chongzhi #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-27 .block-inner .content #jifen_uses_content

ul{background:url(images/jifen_uses_contentbg.jpg); background-repeat:no-repeat; width:345px; height:42px; margin-top:10px;}

*html .section-chongzhi #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-27 .block-inner .content #jifen_uses_content ul{background:url(images/jifen_uses_contentbgie6.jpg); background-repeat:no-repeat; width:345px; height:42px; margin-top:10px;}

.section-chongzhi #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-27 .block-inner .content #jifen_uses_content ul li{float:left; margin-left:52px; margin-top:20px; height:42px; padding-bottom:60px; margin-top:10px;}

.section-chongzhi #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-27 .block-inner .content #jifen_uses_content ul li a{ color:#000000; font-weight:700;}

*html .section-chongzhi #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-27 .block-inner .content #jifen_uses_content ul li{ float:left; margin-left:24px;height:42px;margin-right:22px;}

*+html .section-chongzhi #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-27 .block-inner .content #jifen_uses_content ul li{ float:left; margin-left:50px;height:42px; padding-bottom:55px;}



.page-user-register #page #page-inner #main{padding-top:1px;background:url(images/jifenchongzhibg.jpg); background-repeat:repeat-x; margin-top:0px; text-align:center;}

.page-user-register #page #page-inner #main #main-inner{width:810px; margin:0 auto; margin-top:30px; background:#FFFFFF; border:1px solid #E7E7E5;}

.page-user-register #page #page-inner #main #main-inner #content{ width:810px;}

.page-user-register #page #page-inner #main #main-inner #content #content-inner{ width:810px;}

.page-user-register #page #page-inner #main #main-inner #content #content-inner #content-area{ width:810px;}

.page-user-register #page #page-inner #main #main-inner #content #content-inner #content-area form {width:791px;margin:0 auto;}

.page-user-register #page #page-inner #main #main-inner #content-header{ width:800px; margin:0 auto;}

.page-user-register #page #page-inner #main #main-inner #content-header h1.title{ text-align:center; font-size:16px;color:#32A442; font-weight:700; height:50px; line-height:50px;width:790px; margin:0 auto;}

.page-user-register #page #page-inner #main #main-inner #content-header .tabs{width:786px;margin:0 auto;}

.page-user-register #page #page-inner #main #main-inner #content-header .tabs ul li .tab{border:none; line-height:100%;}

.page-user-register #page #page-inner #main #main-inner #content #content-inner #content-area form div{ width:791px;margin:0 auto;}

.page-user-register #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset{ text-align:center; width:790px; margin:0 auto;}



.page-user-password #page #page-inner #main{background:url(images/jifenchongzhibg.jpg);padding-top:1px; background-repeat:repeat-x; margin-top:0px;height:450px;}

.page-user-password #page #page-inner #main #main-inner{display:inline-block; width:400px; margin:0 auto;margin-top:30px; background:#FFFFFF; border:1px solid #E7E7E5; height:230px;margin-left:280px;}

*html .page-user-password #page #page-inner #main #main-inner{display:inline-block; width:400px; margin:0 auto;margin-top:30px; background:#FFFFFF; border:1px solid #E7E7E5; height:230px;}

*+html .page-user-password #page #page-inner #main #main-inner{display:inline-block; width:400px; margin:0 auto;margin-top:30px; background:#FFFFFF; border:1px solid #E7E7E5; height:230px;}

.page-user-password #page #page-inner #main #main-inner #content-header{width:380px;}

.page-user-register #page #page-inner #main #main-inner #content #content-inner #content-area form#user-register {display:inline;}

.page-user-register #page #page-inner #main #main-inner{ margin-bottom:30px;}

.page-user-register #page #page-inner #main #main-inner #content #content-inner #content-area form#user-register div #edit-name-wrapper{ margin-top:55px;} 

*html .page-user-register #page #page-inner #main #main-inner #content #content-inner #content-area form#user-register div #edit-name-wrapper{ margin-top:10px;} 

*html .page-user-register #page #page-inner #main #main-inner #content #content-inner #content-area form#user-register div #edit-name-wrapper{ margin-top:10px;}

.page-user-register #page #page-inner #main #main-inner #content #content-inner #content-area form#user-register div .form-item { margin-top:10px;}

.page-user-register #page #page-inner #main #main-inner #content #content-inner #content-area form#user-register div .form-item  label{ width:140px; float:left; text-align:right; margin-right:10px;}

.page-user-register #page #page-inner #main #main-inner #content #content-inner #content-area form#user-register div .form-item #edit-name{ width:245px; float:left; display:block;}

.page-user-register #page #page-inner #main #main-inner #content #content-inner #content-area form#user-register div .form-item #edit-mail{ width:245px; float:left;display:block;}

.page-user-register #page #page-inner #main #main-inner #content #content-inner #content-area form#user-register div .form-item #edit-conf-mail{ width:245px; float:left;display:block;}

.page-user-register #page #page-inner #main #main-inner #content #content-inner #content-area form#user-register div .form-item #edit-pass-pass1{ width:245px; float:left;display:block;}

.page-user-register #page #page-inner #main #main-inner #content #content-inner #content-area form#user-register div .form-item #edit-pass-pass2{ width:245px; float:left;display:block;}



.page-user-register #page #page-inner #main #main-inner #content #content-inner #content-area form#user-register div .form-item  .description{ margin-left:410px;text-align:left;width:340px;}





/*-----dengluzhuceanniu-------*/





.page-user-password  #page #page-inner #main #main-inner #content-header .tabs{ margin-top:7px;}

*html .page-user-password  #page #page-inner #main #main-inner #content-header .tabs{ margin-top:10px;}

*+html .page-user-password  #page #page-inner #main #main-inner #content-header .tabs{ margin-top:10px;}



.page-user-password #page #page-inner #main #main-inner #content-header h1.title{ text-align:center; font-size:14px;color:#32A442; height:50px; line-height:50px; font-weight:700;}

.page-user-password #page #page-inner #main #main-inner #content #content-inner #content-area form div{text-align:center; width:380px;}

.page-user-password #page #page-inner #main #main-inner #content #content-inner #content-area form div .form-item{ width:300px; margin:0 auto; margin-top:90px;}

*html .page-user-password #page #page-inner #main #main-inner #content #content-inner #content-area form div .form-item{ width:300px; margin:0 auto; margin-top:30px;}

*+html .page-user-password #page #page-inner #main #main-inner #content #content-inner #content-area form div .form-item{ width:300px; margin:0 auto; margin-top:30px;}

.page-user-password #page #page-inner #main #main-inner #content #content-inner #content-area form div .form-item label{width:80px;height:65px; float:left; text-align:right;}

.page-user-password #page #page-inner #main #main-inner #content #content-inner #content-area form div .form-item input{ width:180px; float:left; margin-top:0px;margin:0px;}

.page-user-password #page #page-inner #main #main-inner #content #content-inner #content-area form .form-submit{width:180px;margin-top:50px; font-size:14px; position:absolute; margin-left:-220px;}

*html .page-user-password #page #page-inner #main #main-inner #content #content-inner #content-area form .form-submit{width:180px; margin-left:-70px; margin-top:-20px; position:absolute; font-size:14px;}

*+html .page-user-password #page #page-inner #main #main-inner #content #content-inner #content-area form .form-submit{width:180px; margin-left:-70px; margin-top:-20px; position:absolute; font-size:14px;}

.page-user-password #page #page-inner #main #main-inner #content #content-inner #content-area form div .container-inline #edit-submit-1{ background:none;}



.page-user-password #page #page-inner #main #main-inner #content #content-inner #content-area #user-pass div #edit-submit{background:url(images/jifenhuanlitianjia.jpg); background-repeat:no-repeat; border:none; font-size:12px; font-weight:700; color:#FFFFFF; text-align:center; width:96px; height:22px; line-height:22px; margin-top:60px;} 

*html .page-user-password #page #page-inner #main #main-inner #content #content-inner #content-area #user-pass div #edit-submit{background:url(images/jifenhuanlitianjia.jpg); background-repeat:no-repeat; border:none; font-size:12px; font-weight:700; color:#FFFFFF; text-align:center; width:96px; height:22px; line-height:22px; margin-top:30px;} 

*+html .page-user-password #page #page-inner #main #main-inner #content #content-inner #content-area #user-pass div #edit-submit{background:url(images/jifenhuanlitianjia.jpg); background-repeat:no-repeat; border:none; font-size:12px; font-weight:700; color:#FFFFFF; text-align:center; width:96px; height:22px; line-height:22px; margin-top:30px;} 







.page-user #page #page-inner #main{background:url(images/jifenchongzhibg.jpg);padding-top:1px;background-repeat:repeat-x; margin-top:0px;height:450px;}

.page-user #page #page-inner #main #main-inner{display:inline-block; width:400px; margin:0 auto;margin-top:30px; background:#FFFFFF; border:1px solid #E7E7E5; height:260px; margin-left:280px;}

*html .page-user #page #page-inner #main #main-inner{display:inline-block; width:400px; margin:0 auto;margin-top:30px; background:#FFFFFF; border:1px solid #E7E7E5; height:260px;}

*+html .page-user #page #page-inner #main #main-inner{display:inline-block; width:400px; margin:0 auto;margin-top:30px; background:#FFFFFF; border:1px solid #E7E7E5; height:260px;}

.page-user #page #page-inner #main #main-inner #content-header{width:380px;}

.page-user #page #page-inner #main #main-inner #content-header .tabs{ margin-top:7px;}

*html .page-user #page #page-inner #main #main-inner #content-header .tabs{ margin-top:10px;}

*+html .page-user #page #page-inner #main #main-inner #content-header .tabs{ margin-top:10px;}

.page-user #page #page-inner #main #main-inner #content-header h1.title{ text-align:center; font-size:14px;color:#32A442; font-weight:700;border-bottom:#CCCCCC solid 1px; height:50px; line-height:50px;}

.page-user #page #page-inner #main #main-inner #content #content-inner #content-area form div{text-align:center; width:380px;}

.page-user #page #page-inner #main #main-inner #content #content-inner #content-area form div #edit-name-wrapper{ width:380px; display:block; height:33px; text-align:center; margin-top:15px;}

.page-user #page #page-inner #main #main-inner #content #content-inner #content-area form div #edit-name-wrapper label{width:91px; float:left; text-align:right;}

.page-user #page #page-inner #main #main-inner #content #content-inner #content-area form div #edit-name-wrapper input{ width:137px; float:left;}

.page-user #page #page-inner #main #main-inner #content #content-inner #content-area form div #edit-name-wrapper .description{width:120px; float:left;margin-left:6px; font-family:Arial, Helvetica, sans-serif; line-height:20px; text-align:left;font-size:12px;}

.page-user #page #page-inner #main #main-inner #content #content-inner #content-area form div #edit-pass-wrapper .description{width:120px; float:left;margin-left:6px; font-family:Arial, Helvetica, sans-serif; line-height:20px; font-size:12px; text-align:left;}

.page-user #page #page-inner #main #main-inner #content #content-inner #content-area form div #edit-pass-wrapper{width:380px;display:block;height:43px; text-align:center; margin-top:10px;}

.page-user #page #page-inner #main #main-inner #content #content-inner #content-area form div #edit-pass-wrapper label{width:91px; float:left; text-align:right;}

.page-user #page #page-inner #main #main-inner #content #content-inner #content-area form div #edit-pass-wrapper input{width:137px; float:left;}

.page-user #page #page-inner #main #main-inner #content #content-inner #content-area form div #edit-submit{background:url(images/submitbg.jpg); background-repeat:no-repeat; border:none; font-size:12px; font-weight:700; color:#FFFFFF; text-align:center; width:57px; height:22px;}

#tishi_title_img {

background-image:url(images/jifenchzhnote.jpg);

margin-bottom:-30px;

width:20px;

height:20px;

font-size:0px;

position:absolute;

z-index:3;

margin-left:-10px;

}

*html #tishi_title_img {

background-image:url(images/jifenchzhnote.jpg);

background-repeat:no-repeat;

position:absolute;

margin-left:-35px;

width:20px;

height:20px;

z-index:3;

font-size:0px;}

*+html #tishi_title_img {

z-index:3;

background-image:url(images/jifenchzhnote.jpg);

background-repeat:no-repeat;

position:absolute;

margin-left:-25px;

width:20px;

height:20px;

font-size:0px;}

#sidebar-right .attachment-before div.view-sidebar-rem4men2xiao3zu4,#sidebar-right .attachment-before div.view-display-id-attachment_1 {

float:right;

margin-top:-30px;

border:0px;

}

#sidebar-right .view-sidebar-rem4men2xiao3zu4 .attachment-before .view-display-id-attachment_1 a {

color:#4AB740;

float:right;

font-size:13px;

font-weight:bold;

margin-right:20px;

border:0px;

}

.view-og-ghp-ron .attachment-before .view-display-id-attachment_1 {

float:left;

margin-top:-120px;

}

.view-og-ghp-ron .view-content {

margin-top:120px;

}



.section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1{ border:1px solid #E5EBE1;}

*html .section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1{ border:1px solid #E5EBE1; width:99.5%;}

.section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content{ border:none;}

.section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table{margin:0 auto; border:none;}



.section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tr{border-bottom:2px solid #E5EBE1;}

.section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tr th{height:33px; line-height:33px;}

.section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody tr{border-bottom:1px solid #E5EBE1;}

.section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-title{height:33px; line-height:33px; width:280px; white-space:nowrap; overflow:hidden;}

*html .section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-title{height:25px; line-height:25px; width:280px; white-space:nowrap; overflow:hidden;}



.section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-title a{color:#32A444; font-size:12px;}

.section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-changed{ color:#7d7d7d; font-size:12px; width:100px; white-space:nowrap; overflow:hidden;height:33px; line-height:33px;text-align:left;}

*html .section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-changed{ color:#7d7d7d; font-size:12px; width:100px; white-space:nowrap; overflow:hidden;height:25px; line-height:25px;text-align:left;}

.section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-name-2{ width:130px;color:#7d7d7d; font-size:12px;height:33px; line-height:33px;text-align:left;}

.section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table th.views-field-title{ font-size:14px; font-weight:700; color:#32A444; width:300px; white-space:nowrap; text-align:left; padding-left:10px;}

.section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table th.views-field-title{ font-size:14px; font-weight:700; color:#32A444; width:300px; white-space:nowrap; text-align:left;}

.section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table th.views-field-name-2,th.views-field-changed{ font-size:12px; font-weight:100; color:#7c7c7c; font-weight:100; text-align:left;}

.section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .item-list{ line-height:35px; line-height:35px; margin-top:10px;}

*html .section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .item-list{line-height:25px; margin-top:5px;}

*+html .section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .item-list{line-height:35px; margin-top:20px;}

.section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .item-list ul.pager{ margin:0 auto;}

*html .section-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .item-list ul.pager{ margin-left:30px;}



.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112{width:99.5%;}

.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner .content .view-dom-id-2 .view-content table.views-view-grid{width:330px;}

.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner .content .view-dom-id-2 .view-content table.views-view-grid tbody tr td{width:82px; text-align:center;}

.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner .content .view-dom-id-2 .view-content table.views-view-grid tbody tr td .views-field-field-group-profile-picture-fid .field-content{ height:60px;}

.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner .content .view-dom-id-2 .view-content table.views-view-grid tbody tr td .views-field-title{ width:80px;}



.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content{border:1px solid #E5EBE1; border-top:none;}

.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list{ clear:both; width:100%;}

*html .section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list{ margin-top:0px; height:50px; line-height:50px;}

.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list ul li{clear:both; width:100%; word-break:keep-all; overflow:hidden; height:25px; line-height:25px;}

.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list .views-field-counter{width:20px; float:left; margin-left:10px;}

.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list .views-field-title{width:300px; float:right;}

.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list{ clear:both; width:100%;}

*html .section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list ul li{ clear:both; width:100%; word-break:keep-all; overflow:hidden;}

*html .section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list .views-field-counter{width:15px; float:left; margin-left:5px;}

*html .section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list .views-field-title{ width:300px; float:right; text-align:left;}







/*---------notlogin----------*/



.section-node #page #page-inner #main #main-inner #content #content-inner #content-area{ vertical-align:top;clear:both;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1{background-color:#FFFFFF; vertical-align:top; margin-top:0px;}

*html .section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1{width:99.5%;vertical-align:top;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content{background-color:#FFFFFF; vertical-align:top;margin-top:0px; padding-top:0px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table{margin:0 auto; border:none;background-color:#FFFFFF; margin-top:0px;border-top:1px solid #E5EBE1; width:605px; margin:0 auto;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tr{border-bottom:2px solid #E5EBE1;background-color:#FFFFFF;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tr th{height:33px; line-height:33px;background-color:#FFFFFF;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody tr td{border-bottom:1px solid #E5EBE1;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-title{height:33px; line-height:33px; width:280px; white-space:nowrap; overflow:hidden;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-title a{color:#32A444;}

*html .section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-title{height:25px; line-height:25px; width:280px; white-space:nowrap; overflow:hidden;}

*html .section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-title a{color:#32A444;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-changed{ color:#7d7d7d; font-size:12px; width:120px; white-space:nowrap; overflow:hidden;height:33px; line-height:33px;text-align:left;margin-left:10px;}

*html .section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-changed{ color:#7d7d7d; font-size:12px; width:120px; white-space:nowrap; overflow:hidden;height:25px; line-height:25px;text-align:left;margin-left:10px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-name{ width:110px;color:#7d7d7d; font-size:12px;height:33px; line-height:33px;text-align:left; margin-left:10px;}



.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-changed{ color:#B45736; font-size:12px; text-align:left;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table th.views-field-title{ font-size:12px;color:#7c7c7c; width:300px; white-space:nowrap; text-align:left; padding-left:10px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table th.views-field-title{ font-size:12px;color:#7c7c7c; width:300px; white-space:nowrap; text-align:left;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table th.views-field-name,th.views-field-changed{ font-size:12px; font-weight:100; color:#7c7c7c; font-weight:100; text-align:left;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table th.views-field-name a{color:#7c7c7c; font-size:12px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .item-list{ line-height:35px; line-height:35px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .item-list ul.pager{ margin:0 auto;}

*html .section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .item-list ul.pager{ margin-left:100px;}



..section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1{ border:none;}

.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content{border:1px solid #E5EBE1; border-top:none;}

.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list{clear:both; width:100%;}

*html .section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list{ margin-top:0px; height:50px; line-height:50px;}

.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list ul li{clear:both; width:100%; word-break:keep-all; overflow:hidden; height:25px; line-height:25px;}

.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list .views-field-counter{width:20px; float:left; margin-left:10px;}

.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list .views-field-title{width:300px; float:right;}

.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list{ clear:both; width:100%;}

*html .section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list ul li{ clear:both; width:100%; word-break:keep-all; overflow:hidden;}

*html .section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list .views-field-counter{width:15px; float:left; margin-left:5px;}

*html .section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list .views-field-title{ width:300px; float:right; text-align:left;}



.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner .content .view-dom-id-2 .view-content table.views-view-grid{width:330px;}

.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner .content .view-dom-id-2 .view-content table.views-view-grid tbody tr td{width:82px; text-align:center;}

.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner .content .view-dom-id-2 .view-content table.views-view-grid tbody tr td .views-field-field-group-profile-picture-fid .field-content{ height:60px;}

.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner .content .view-dom-id-2 .view-content table.views-view-grid tbody tr td .views-field-title{ width:80px;}

.page-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-id-xiaozu_frontpage .view-content table.views-table thead tr .views-field-title{background-image:url(images/lastnewslist.jpg);background-repeat:no-repeat; text-indent:15px;}

.page-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-id-xiaozu_frontpage .view-content table.views-table tbody tr.odd td.views-field-changed{ color:#AE6000;}

.page-xiaozu #page #page-inner #main #main-inner #content #content-inner #content-area .view-id-xiaozu_frontpage .view-content table.views-table tbody tr.even td.views-field-changed{ color:#AE6000;}

/*-------------------*/

/*---------shouyesidebar-right----------*/

.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112{width:99.5%;}



.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112 .view-content{ border:none;}

.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112  .block-inner .content .view-content .item-list{ clear:both; width:100%;}

*html .section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112 .block-inner .content .view-content .item-list{ margin-top:0px; height:50px; line-height:50px;}

.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112  .block-inner .content .view-content .item-list ul li{clear:both; width:100%; word-break:keep-all; overflow:hidden; height:25px; line-height:25px;}

.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112  .block-inner .content .view-content .item-list .views-field-counter{width:20px; float:left; margin-left:10px;}

.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112  .block-inner .content .view-content .item-list .views-field-title{width:300px; float:right;}

.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list{ clear:both; width:100%;}

*html .section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112  .block-inner .content .view-content .item-list ul li{ clear:both; width:100%; word-break:keep-all; overflow:hidden;}

*html .section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112  .block-inner .content .view-content .item-list .views-field-counter{width:15px; float:left; margin-left:5px;}

*html .section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112  .block-inner .content .view-content .item-list .views-field-title{ width:300px; float:right; text-align:left;}



.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112  .block-inner .content .view-content table.views-view-grid{width:330px;}

.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112  .block-inner .content .view-content table.views-view-grid tbody tr td{width:82px; text-align:center;}

.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112  .block-inner .content .view-content table.views-view-grid tbody tr td .views-field-field-group-profile-picture-fid .field-content{ height:60px;}

.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112  .block-inner .content .view-content table.views-view-grid tbody tr td .views-field-title{ width:80px;}



.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112  .block-inner .content .view-content .item-list ul.pager{height:50px; line-height:50px;}

*html .section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112  .block-inner .content .view-content .item-list ul.pager{height:30px; line-height:30px;}

/*---------shouyesidebar-right----------*/



/*-------chuanjianxiaozu------*/ 

*html .section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112 .content .view-content .views-field-nothing{ position:absolute;} 

*html .section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112 .content .view-content .views-field-nothing{ position:absolute;} 

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area #node-form div .node-form .standard .form-item .description{ font-size:12px; color:#7c7c7c;}





/*------chuangjianxiaozu-------*/

/*--------login-----------*/

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2{background-color:#FFFFFF; clear:both;}

*html .section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2{width:99.5%;clear:both;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .view-content{background-color:#FFFFFF; vertical-align:top;margin-top:0px; padding-top:0px;clear:both;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .view-content .views-table{margin:0 auto; border:none;background-color:#FFFFFF; margin-top:0px;border-top:1px solid #E5EBE1; width:605px; margin:0 auto;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .view-content .views-table tr{border-bottom:2px solid #E5EBE1;background-color:#FFFFFF;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .view-content .views-table tr th{height:33px; line-height:33px;background-color:#FFFFFF;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .view-content .views-table tbody tr td{border-bottom:1px solid #E5EBE1;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .view-content .views-table tbody td.views-field-title{height:33px; line-height:33px; width:280px; white-space:nowrap; overflow:hidden;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .view-content .views-table tbody td.views-field-title a{color:#32A444;}

*html .section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .view-content .views-table tbody td.views-field-title{height:25px; line-height:25px; width:280px; white-space:nowrap; overflow:hidden;}

*html .section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .view-content .views-table tbody td.views-field-title a{color:#32A444;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .view-content .views-table tbody td.views-field-changed{ color:#7d7d7d; font-size:12px; width:120px; white-space:nowrap; overflow:hidden;height:33px; line-height:33px;text-align:left;}

*html .section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .view-content .views-table tbody td.views-field-changed{ color:#7d7d7d; font-size:12px; width:120px; white-space:nowrap; overflow:hidden;height:25px; line-height:25px;text-align:left;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .view-content .views-table tbody td.views-field-name{ width:110px;color:#7d7d7d; font-size:12px;height:33px; line-height:33px;text-align:left;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .view-content .views-table th.views-field-title{ font-size:12px;color:#7c7c7c; width:300px; white-space:nowrap; text-align:left; padding-left:10px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .view-content .views-table th.views-field-title{ font-size:12px;color:#7c7c7c;width:300px; white-space:nowrap; text-align:left;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .view-content .views-table th.views-field-name,th.views-field-changed{ font-size:12px; font-weight:100; color:#7c7c7c; font-weight:100; text-align:left;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .view-content .views-table th.views-field-name a{color:#7c7c7c; font-size:12px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .item-list{ line-height:35px; line-height:35px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .item-list ul.pager{ margin:0 auto;}

*html .section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .item-list ul.pager{ margin-left:20px;}





.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112{width:99.5%;}



.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112 .view-content{ border:none;}



#page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .item-list{}

*html #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .item-list{}

*html #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .item-list .pager{ padding-left:120px; line-height:32px;}

*html #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .item-list .pager .pager-current{ line-height:20px;}

*+html #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .item-list{ margin-top:10px;}



.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112 .block-inner .content .view-content .item-list .views-field-counter{width:20px; float:left; margin-left:10px;}

.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112 .block-inner .content .view-content .item-list .views-field-title{width:300px; float:right;}

.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-xiaozu_frontpage-block_1 .content .view-content .item-list{ clear:both; width:100%;}

*html .section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112 .block-inner .content .view-content .item-list ul li{ clear:both; width:100%; word-break:keep-all; overflow:hidden;}

*html .section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112 .block-inner .content .view-content .item-list .views-field-counter{width:15px; float:left; margin-left:5px;}

*html .section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112 .block-inner .content .view-content .item-list .views-field-title{ width:300px; float:right; text-align:left;}



.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112 .block-inner .content .view-content table.views-view-grid{width:330px;}

.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112 .block-inner .content .view-content table.views-view-grid tbody tr td{width:82px; text-align:center;}

.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112 .block-inner .content .view-content table.views-view-grid tbody tr td .views-field-field-group-profile-picture-fid .field-content{ height:60px;}

.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112 .block-inner .content .view-content table.views-view-grid tbody tr td .views-field-title{ width:80px;}



.section-node #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-7e36fb207fa56d341b6cec04fbf2c112 .block-inner .content .view-content .item-list ul.pager{height:50px; line-height:50px;}



.section-xiaozu #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-31 a img{ width:338px; height:100px;}





/*-------------------*/

/*--xiaozubiaozhi--*/

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area  .content .field-field-group-profile-picture .field-items{}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area  .content .field-field-group-profile-picture .field-label{height:35px;font-size:12px; color:#000000; text-indent:26px; font-weight:700; line-height:35px; background-image:none;}



.section-node #page #page-inner #main #main-inner #content #content-inner #content-area  ul.links li.flag-bookmarks span .flag-wrapper a{color:#32A442; text-indent:24px;} 

.section-node #page #page-inner #main #main-inner #content #content-inner .feed-icons{ text-indent:24px;}

/*--xiaozubiaozhi--*/



/*----------erji--------*/

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .content{ clear:both; margin-bottom:10px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .content .view-content{ line-height:30px; text-align:left; clear:both}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content #mission p{ font-size:12px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-1 .view-content .views-field-field-group-profile-picture-fid{float:left; width:70px; line-height:22px; text-align:center;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-1 .view-content .views-field-title{ float:right; font-size:14px; color:#32A444; font-weight:700;width:530px; line-height:22px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area  .content .view-dom-id-1 .view-content .views-field-timestamp{ float:right; width:530px; line-height:22px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-1 .view-content .views-field-timestamp .field-content{color:#555555; line-height:22px;}



.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-1 .view-content .views-field-subscribe{float:right; width:515px;padding-left:15px;background-repeat:no-repeat; line-height:22px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-1 .view-content .views-field-subscribe .field-content a{font-size:12px; font-weight:700; color:#ffffff;background:url(images/submitbg.jpg); background-repeat:no-repeat; text-align:left; line-height:22px; display:block; width:65px; height:22px; text-align:center;}



.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-1 .view-content .views-field-description{float:right; width:530px; line-height:22px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-1 .view-content .views-field-description label{ float:left;line-height:30px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-1 .view-content .views-field-description .field-content{float:left;line-height:22px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-1 .view-content .views-field-description .field-content p{ font-size:12px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-1 .view-content .views-field-nothing{float:left; width:600px; height:30px; text-align:right;background:url(images/submitbg-say.jpg);height:22px; line-height:30px; background-repeat:no-repeat; background-position:right;}



.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-1 .view-content .views-field-nothing .field-content a{font-size:12px; font-weight:700; color:#FFFFFF; padding-right:11px;}

*html .section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-1 .view-content .views-field-nothing .field-content a{font-size:12px; font-weight:700; color:#FFFFFF; padding-right:6px; padding-bottom:-10px;}

*+html .section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-1 .view-content .views-field-nothing .field-content a{font-size:12px; font-weight:700; color:#FFFFFF; padding-right:6px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-header .tabs ul li{ width:38px;}





.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-comment-blog .node-inner .title{ display:none; height:0px; line-height:0px;}

.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1.view-content .node-type-comment-blog .node-inner .title a{display:none; height:0px; line-height:0px;}

.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-header{color:#000000; font-size:14px; font-weight:700; height:30px; line-height:30px;}

.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-comment-blog .node-inner .title a{color:#666666; font-size:12px;height:30px; line-height:30px;}

.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-comment-blog .node-inner .meta{width:970px; margin:0 auto;}







.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-comment-blog .node-inner .meta .submitted{HEIGHT:22px; line-height:22px; background-color:#F6F8F3; color:#666666;width:970px; margin:0 auto;font-size:12px;}

.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-comment-blog {width:970px; margin:0 auto;}

.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-comment-blog .node-inner .meta .submitted a{color:#32A441; font-size:12px;}

.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-comment-blog .node-inner .content p{ height:22px; line-height:22px;font-size:12px;}

.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-comment-blog .node-inner ul li{ height:22px; line-height:22px;}

.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-comment-blog .node-inner ul li a{ float:right;color:#32A441;font-size:12px; margin-right:10px;}







/*---------erji-----------*/

.section-node-add #page #page-inner #main #main-inner{width:975px; margin:0 auto; margin-top:10px;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner{border-bottom:1px solid #E5EBE1;border-left:1px solid #E5EBE1;border-right:1px solid #E5EBE1;}

*html .section-node-add #page #page-inner #main #main-inner #content #content-inner{border-bottom:1px solid #E5EBE1;border-left:1px solid #E5EBE1;border-right:1px solid #E5EBE1; width:99.5%;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area form div .node-form .standard .form-item{ width:940px;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area form div .node-form .standard .form-item .form-text{ width:740px;height:20px;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-header{height:35px;background-image: url(images/video_titleall.jpg); background-repeat:repeat-x; line-height:35px;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-header h1.title{ font-size:14px; color:#32A444; font-weight:700; line-height:35px; text-indent:10px;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area{width:945px; margin:0 auto;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area form{width:940px; margin:0 auto;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area form div .node-form .standard #edit-taxonomy-14-wrapper label{ width:82px; height:30px; line-height:30px; text-align:right; float:left; font-weight:100;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area form div .node-form .standard #edit-title-wrapper label,

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area form div .node-form .standard #edit-field-dhg-fubiaoti-0-value-wrapper label

{ width:150px; height:20px; line-height:20px;float:left; font-weight:700;}



.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area form div .node-form .standard #edit-og-description-wrapper label{ width:82px; height:30px; line-height:30px; text-align:right; float:left; font-weight:100;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area form div .node-form .standard #edit-title-wrapper  #edit-taxonomy-14{ width:151px; float:left;}



.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area form div .node-form .standard #edit-og-description-wrapper input{ width:435px; margin:20px 10px 10px; border: solid 1px #7F8992; height:20px;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area form div .node-form .standard #edit-og-description-wrapper .description{width:300px; font-size:12px; color:#7c7c7c; display:inline-block;}



.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area .node-form #edit-submit{background:url(images/submitbg.jpg); background-repeat:no-repeat; border:none; font-size:14px; font-weight:700; color:#FFFFFF; text-align:center; width:57px; height:22px; margin-left:390px; margin-bottom:10px;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area .node-form #edit-preview{background:url(images/submitbg.jpg); background-repeat:no-repeat; border:none; font-size:14px; font-weight:700; color:#FFFFFF; text-align:center; width:57px; height:22px;margin-bottom:10px;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area .node-form .standard fieldset{border:#1FB348 1px solid;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area .node-form .standard fieldset legend a{ color:#1FB348;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area .node-form .standard fieldset .sticky-enabled{ width:900px; background-color:#FFFFFF; margin:0 auto;line-height:35px; margin-bottom:15px;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area .node-form .standard fieldset  .description{ text-indent:22px; height:35px; line-height:35px;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area .node-form .standard fieldset .sticky-enabled thead th{ background-color:#FFFFFF;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area .node-form .standard fieldset .sticky-enabled td{ background-color:#FFFFFF;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area .node-form .standard fieldset .sticky-enabled tr.odd,tr.even,tr.odd  .form-item{ white-space:nowrap;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area .node-form .standard fieldset .sticky-enabled tr{border-bottom:1px dashed #CCCCCC;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area .node-form .standard fieldset .sticky-enabled tr .form-item label{float:left; margin-right:10px;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area .node-form .standard fieldset .sticky-enabled tr .form-item em{ float:left;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-blog .node-inner h2.title a{ font-size:14px; color:#000000; font-weight:700; height:25px; line-height:25px;} 

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-blog .node-inner .meta .submitted a{color:#32A442;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-blog .node-inner ul li{ font-size:12px;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-blog .node-inner ul li a{ color:#000000;}

.section-node-add #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-blog .node-inner ul li.active a{color:#32A442;}

/*---------sanji----------*/

.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-header{ width:100%;}

.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-header h1.title{text-align:left;}

.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-comment-blog .node-inner .meta{ width:950px;background-color:#F6F8F3; height:22px; line-height:22px; border-bottom:none; margin:0 auto;}

.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-comment-blog .node-inner .meta .submitted{ font-size:12px; color:#666666; height:22px; line-height:22px; width:100%; text-align:left; border-bottom:none;}

.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-comment-blog .content{color:#666666; line-height:22px;}

.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-area #comments{ width:960px;}

.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-area #comments .view-dom-id-1 .view-content .node .node-inner div{ text-align:left; text-indent:0px;}

.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-area #comments .view-dom-id-1 .view-content .node div{ border-bottom:none;}

.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-area #comments .view-dom-id-1 .view-content .node .node-inner h2.title{ margin-top:5px;}

.node-type-blog #page #page-inner #main #main-inner #content #content-inner #content-area #comments .view-dom-id-1 .view-content .node .node-inner h2.title a{width:950px; color:#000000;font-weight:700; font-size:14px; height:30px; line-height:30px; text-align:left;margin:0 auto;}





.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .clear-block .meta{float:left; width:600px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .clear-block .picture{float:left; width:65px; height:55px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .clear-block .meta  span.submitted{display:block;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .clear-block  .meta div.terms-inline{ margin-left:-315px; margin-top:23px; height:30px ; line-height:30px; position:absolute;}

*html .section-node #page #page-inner #main #main-inner #content #content-inner #content-area .clear-block  .meta div.terms-inline{ position:inherit;height:30px ; line-height:30px; position:relative; margin-left:-605px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node  .clear-block div.terms-inline ul{text-align:left;height:30px; left:30px;} 

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node  .clear-block ul li a{color:#32A442;width:50px; margin-left:0px;}



.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .clear-block.node-inner .content{color:#000000; line-height:22px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .clear-block .node-inner ul{width:950px;text-align:right;margin:0 auto;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .clear-block .node-inner ul li{width:950px; text-align:right;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .clear-block .node-inner ul li a{color:#32A442;width:50px; margin-left:900px;}



.section-node #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-similarterms-5{border-bottom:1px solid #E5EBE1;border-left:1px solid #E5EBE1;border-right:1px solid #E5EBE1; width:950px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-similarterms-5 .h2Container h2.title{height: 35px;

line-height:35px;

text-indent:10px;

clear:both;

background-image: url(images/video_titleall.jpg);

font-size:14px;

color:#32A442;

font-weight:700;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-similarterms-5 .content .item-list ul{ width:930px; margin:0 auto; margin-bottom:10px; text-align:center;}

*html .section-node #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-similarterms-5 .content .item-list ul{ width:930px;margin-bottom:40px; text-align:center; padding-bottom:10px;}

*html .section-node #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-similarterms-5 .content .item-list{ }

.section-node #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-similarterms-5 .content .item-list ul li{background-image:url(images/list_style_type_disc1.jpg); height:30px; line-height:30px;background-repeat:no-repeat;width:900px; border-bottom:#E9EAE4 1px solid;margin:0 auto; text-align:left; padding-left:13px;}

*html .section-node #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-similarterms-5 .content .item-list ul li{background-image:url(images/list_style_type_disc1.jpg); height:30px; line-height:30px;background-repeat:no-repeat; width:900px; border-bottom:#E9EAE4 1px solid;margin-left:13px;padding-left:20px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-similarterms-5 .content .item-list ul li a{ color:#000000;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node .groups .links ul.links li a{color:#32A442; line-height:22px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node ul .flag-bookmarks span span a{color:#32A442;line-height:22px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node ul .comment_add a{color:#32A442;line-height:22px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node ul .blog_usernames_blog a{color:#000000;line-height:22px;}



/*----------sanji---------*/

/*-----------jianchadingdan-----------*/

.page-cart-checkout-review #page #page-inner #main #main-inner #content #content-inner #content-area p{ font-size:14px; font-weight:700; background-image:url(images/checkoutreviewtitle.jpg); background-repeat:repeat-x; width:960px; border:1px solid #e7eae1; line-height:33PX; margin:0 auto; text-indent:15px; height:33px;} 

.page-cart-checkout-review #page #page-inner #main #main-inner #content #content-inner #content-area table.order-review-table{ margin:0 auto; width:355px; height:385px; border:1px solid #cccccc; margin-top:15px; margin-bottom:20px; border-collapse:collapse;}

.page-cart-checkout-review #page #page-inner #main #main-inner #content #content-inner #content-area table.order-review-table tr.pane-title-row{ height:31px; text-align:center; font-size:14px; font-weight:700;background-image:url(images/pane-title-rowbg.jpg); background-repeat:repeat-x;   margin-top:0px; padding:0px; border-left:none; border-right:none; border-bottom:none; border-top:none;}

.page-cart-checkout-review #page #page-inner #main #main-inner #content #content-inner #content-area table.order-review-table{ font-size:12px;}

.page-cart-checkout-review #page #page-inner #main #main-inner #content #content-inner #content-area table.order-review-table tr td tabl{ font-size:12px;}

.page-cart-checkout-review #page #page-inner #main #main-inner #content #content-inner #content-area table.order-review-table tr.pane-title-row td{border-collapse:collapse; margin-top:0px; padding:0px;}

.page-cart-checkout-review #page #page-inner #main #main-inner #content #content-inner #content-area table.order-review-table  tr.review-button-row td form#uc-cart-checkout-review-form{height:31px; line-height:190%; overflow:hidden; text-align:center; font-weight:700;background-image:url(images/pane-title-rowbg.jpg); background-repeat:repeat-x; border-bottom:none; border-top:none; border-left:none; border-right:none; border-collapse:collapse; margin:0px; padding:0px;}

.page-cart-checkout-review #page #page-inner #main #main-inner #content #content-inner #content-area table.order-review-table  tr.review-button-row td form#uc-cart-checkout-review-form div{height:29px; line-height:190%; overflow:hidden; text-align:center; font-weight:700;background-image:url(images/pane-title-rowbg.jpg); background-repeat:repeat-x;border-collapse:collapse; margin:0px; padding:0px;border-bottom:none; border-left:none; border-right:none; border-top:none;}

.page-cart-checkout-review #page #page-inner #main #main-inner #content #content-inner #content-area table.order-review-table tr td table{ background-color:#FFFFFF; border:none;border-collapse:collapse; margin:0px; padding:0px; height:25px; line-height:25px;}

.page-cart-checkout-review #page #page-inner #main #main-inner #content #content-inner #content-area table.order-review-table tr td table .ow-border-top{background-color:#FFFFFF; border-collapse:collapse; margin:0px; padding:0px; font-size:12px;height:25px; line-height:25px;}

.page-cart-checkout-review #page #page-inner #main #main-inner #content #content-inner #content-area table.order-review-table td{height:25px; line-height:25px;}

.page-cart-checkout-review #page #page-inner #main #main-inner #content #content-inner #content-area table.order-review-table .title-col{ font-size:12px; font-weight:700; overflow:hidden;height:25px; line-height:25px;}

.page-cart-checkout-review #page #page-inner #main #main-inner #content #content-inner #content-area table.order-review-table tr td table .uc-price{ text-align:left;}

.page-cart-checkout-review #page #page-inner #main #main-inner #content #content-inner #content-area table.order-review-table tr.review-button-row td form#uc-cart-checkout-review-form div #edit-back{background:url(images/submitbg.jpg); background-repeat:no-repeat; border:none; font-size:14px; font-weight:700; color:#FFFFFF; text-align:center; width:57px; height:22px; margin:0 auto; width:57px; height:22px;background-color: Transparent; margin-top:2px;}

.page-cart-checkout-review #page #page-inner #main #main-inner #content #content-inner #content-area table.order-review-table tr.review-button-row td form#uc-cart-checkout-review-form div #edit-submit{color:#FFFFFF; font-size:14px; background-image:url(images/jifenhuanlitianjia.jpg);background-repeat:no-repeat; font-weight:700; border:none; width:96px; height:24px;background-color: Transparent;margin-top:2px; } 

.page-cart-checkout-review #page #page-inner #main #main-inner #content #content-inner #content-area table.order-review-table tr .nowrap{ width:120px;}

/*-----------jianchadingdan-----------*/



.page-cart-checkout-complete #page #page-inner #main #main-inner #content #content-inner #content-header .status{font-size:14px; font-weight:700; background-image:url(images/checkoutreviewtitle.jpg); background-repeat:repeat-x; width:960px; border:1px solid #e7eae1; line-height:33PX; margin:0 auto; text-indent:15px; height:33px;overflow:hidden; display:block; margin-bottom:20px;}

.page-cart-checkout-complete #page #page-inner #main #main-inner #content #content-inner #content-area{ margin-top:35px; border:1px solid #e7eae1; width:960px; margin:0 auto;background-image:url(images/page-cart-checkout-completebg.jpg); background-repeat:repeat-x; text-align:center; clear:both; margin-bottom:10px;}



.page-cart-checkout-complete #page #page-inner #main #main-inner #content #content-inner  #content-area p{ line-height:25px; font-size:14px; text-align:center;} 



.section-quickbuy #page #page-inner #main #main-inner #content #content-inner #content-header{font-size:14px; font-weight:700; background-image:url(images/checkoutreviewtitle.jpg); background-repeat:repeat-x; width:960px; border:1px solid #e7eae1; line-height:33PX; margin:0 auto; text-align:center; height:33px;overflow:hidden; display:block; margin-bottom:20px;}

.section-quickbuy #page #page-inner #main #main-inner #content #content-inner #content-header h1 span.title-content{ font-size:14px; font-weight:700; line-height:33PX;height:33px;}

.section-quickbuy #page #page-inner #main #main-inner #content #content-inner #content-area{margin-top:35px; border:1px solid #e7eae1; width:960px; margin:0 auto;background-image:url(images/page-cart-checkout-completebg.jpg); background-repeat:repeat-x; text-align:center; clear:both; margin-bottom:10px; height:50px; line-height:50px; font-size:14px;}



.section-quickbuy #page #page-inner #main #main-inner #content #content-inner #content-area a{color:#32A442;font-size:14px;}



/*------jifenhuanli-------*/

.section-jifenduihuan #page #page-inner #main #main-inner #content {border:1px solid #E5EBE1; background-image:url(images/jifenhuanlibg.jpg); background-repeat:repeat-x; margin:0 auto; text-align:center;}

.section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom{clear:both; overflow:hidden;}

.section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-jifenduihuan-block_1{margin:0 auto; text-align:center;}

.section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-jifenduihuan-block_1 .block-inner .content .view-dom-id-1{ width:610px;; margin:0 auto; text-align:center;}

.section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-jifenduihuan-block_1 .block-inner .content .view-dom-id-1 .view-content {width:600px;; margin:0 auto;}

.section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-jifenduihuan-block_1 .block-inner .content .view-dom-id-1 .view-content .views-row{width:190px; height:210px; float:left; margin-left:10px; margin-top:10px;}

*html .section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-jifenduihuan-block_1 .block-inner .content .view-dom-id-1 .view-content .views-row{width:190px;float:left; margin-left:5px;margin-top:10px;}

.section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-jifenduihuan-block_1 .block-inner .content .view-dom-id-1 .view-content .views-row .views-field-title{ text-align:left; width:190px; }

*html .section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-jifenduihuan-block_1 .block-inner .content .view-dom-id-1 .view-content .views-row .views-field-title{text-align:left; white-space:nowrap; width:190px;}

.section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-jifenduihuan-block_1 .block-inner .content .view-dom-id-1 .view-content .views-row .views-field-sell-price{text-align:left;}

.section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-jifenduihuan-block_1 .block-inner .content .view-dom-id-1 .view-content .views-row .views-field-sell-price .views-label-sell-price{ color:#000000;}

.section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-jifenduihuan-block_1 .block-inner .content .view-dom-id-1 .view-content .views-row .views-field-sell-price span.field-content .uc-price{color:#32A442;}

.section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-jifenduihuan-block_1 .block-inner .content .view-dom-id-1 .view-content .views-row .views-field-addtocartlink-1{ width:190px;text-align:left;}

.section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-jifenduihuan-block_1 .block-inner .content .view-dom-id-1 .view-content .views-row .views-field-addtocartlink-1 form{ width:190px;}

.section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-jifenduihuan-block_1 .block-inner .content .view-dom-id-1 .view-content .views-row .views-field-field-product-fengmian-fid {width:190px; text-align:left;}

.section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-jifenduihuan-block_1 .block-inner .content .view-dom-id-1 .view-content .views-row .views-field-field-product-fengmian-fid .field-content a.imagecache img{width:160px; height:120px; text-align:left;}

.section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-jifenduihuan-block_1 .block-inner .content .view-dom-id-1 .view-content .views-row .views-field-addtocartlink-1 .field-content .add-to-cart{ width:190px;}

.section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-jifenduihuan-block_1 .block-inner .content .view-dom-id-1 .view-content .views-row .views-field-addtocartlink-1 .field-content .add-to-cart form div{ width:180px;}

.section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-jifenduihuan-block_1 .block-inner .content .view-dom-id-1 .view-content .views-row .views-field-addtocartlink-1 .field-content .add-to-cart form div .form-submit{color:#FFFFFF; font-size:12px; background-image:url(images/jifenhuanlitianjia.jpg);background-repeat:no-repeat; font-weight:700px; border:none; width:96px; height:24px;background-color: Transparent;}

*html .section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-jifenduihuan-block_1 .block-inner .content .view-dom-id-1 .item-list{}

*html .section-jifenduihuan #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-jifenduihuan-block_1 .block-inner .content .view-dom-id-1 .item-list .pager{text-align:center; padding-left:200px;}







/*----------------youwenyouda-------------------*/

.section-wenda #page #page-inner #main #main-inner #content{border:1px solid #E5EBE1;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1{background-color:#FFFFFF; clear:both;}

*html .section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1{width:99.5%;clear:both;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content{background-color:#FFFFFF; vertical-align:top;margin-top:0px; padding-top:0px;clear:both;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table{margin:0 auto; border:none;background-color:#FFFFFF; margin-top:0px;width:600px; margin:0 auto;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tr{border-bottom:2px solid #E5EBE1;background-color:#FFFFFF;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tr th{height:33px; line-height:33px;background-color:#FFFFFF;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody tr td{border-bottom:1px solid #E5EBE1;background-color:#FFFFFF;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-title{height:33px; line-height:33px; width:310px; text-indent:10px;white-space:nowrap; overflow:hidden;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-title a{color:#000000;}

*html .section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-title{text-indent:10px;height:25px; line-height:25px; width:280px; white-space:nowrap; overflow:hidden;}

*html .section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-title a{color:#000000;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.active{ color:#32A442; font-size:12px; width:80px; white-space:nowrap; overflow:hidden;height:33px; line-height:33px;text-align:center;}

*html .section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.active{color:#32A442; font-size:12px; width:80px; white-space:nowrap; overflow:hidden;height:25px; line-height:25px;text-align:center;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-name{ width:150px;color:#7d7d7d; font-size:12px;height:33px; line-height:33px;text-align:left;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-name a{color:#7d7d7d;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-field-best-answer-award-value{color:#32A442; background-image:url(images/youwenyouda_xuanshangfenshu.jpg); background-repeat:no-repeat; background-position:left; padding-left:30px; line-height:190%; overflow:hidden;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table th.views-field-title{ font-size:14px;color:#000000; width:310px; white-space:nowrap; text-align:left; text-indent:10px;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table th.views-field-name,th.active{ font-size:14px; font-weight:700; color:#000000; font-weight:700; text-align:left;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table th.views-field-name a{color:#000000; font-size:14px;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table th.views-field-field-best-answer-award-value{font-size:14px;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .item-list{line-height:35px; line-height:35px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .item-list ul.pager{ margin:0 auto;}

*html .section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-dom-id-2 .item-list{text-align:center;}

*html .section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .item-list{text-align:center;}

*html .section-wenda #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .item-list .pager{ margin:0 auto; min-width:400px;}

/*------rightbar------*/

.section-wenda #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-54 .block-inner .content{background-image:url(images/wanttoanswer.jpg); background-repeat:repeat-x;border:1px solid #E5EBE1; height:34px;}

.section-wenda #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-54 .block-inner .content #tiwen{height:34px; line-height:34px; background-image:url(images/wanttoask.jpg); background-repeat:no-repeat; background-position:0px 6px; width:280px;line-height:190%; text-indent:22px; margin:0 auto;}

.section-wenda #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-54 .block-inner .content #tiwen a{color:#32A442; font-size:14px; font-weight:700; line-height:190%;}

.section-wenda #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-3{border-left:1px solid #D1D1D1;border-right:1px solid #D1D1D1;border-bottom:1px solid #D1D1D1; width:99.5%;}

.section-wenda #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-3 .block-inner .h2Container{height:35px;background-image: url(images/video_titleall.jpg);}

.section-wenda #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-3 .block-inner .h2Container .title{ font-size:14px; color:#32A442; text-indent:26px; font-weight:700; line-height:35px; border:none;}

.section-wenda #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-3 .block-inner .content{height:180px; clear:both;}

.section-wenda #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-3 .block-inner .content ul{ height:100px; margin-top:10px;}

.section-wenda #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-3 .block-inner .content ul li{ height:30px; line-height:30px; text-align:left; width:270px; margin:0 auto;background-image:url(images/youwenyouda_right-barlist.jpg); background-repeat:no-repeat; padding-left:20px;}

*html .section-wenda #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-3 .block-inner .content ul li{ height:30px; line-height:30px; text-align:left; width:270px; margin:0 auto;background-image:url(images/youwenyouda_right-barlist.jpg); background-repeat:no-repeat;}

*+html .section-wenda #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-3 .block-inner .content ul li{ height:30px; line-height:30px; text-align:left; width:270px; margin:0 auto;background-image:url(images/youwenyouda_right-barlist.jpg); background-repeat:no-repeat;}

.section-wenda #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-3 .block-inner .content ul li a{ font-size:14px; font-weight:700; color:#000000;}

/*------rightbar2sanji------*/

.node-type-best-answer #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-54 .block-inner .content{background-image:url(images/wanttoanswer.jpg); background-repeat:repeat-x;border:1px solid #E5EBE1; height:34px;}

.node-type-best-answer #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-54 .block-inner .content #tiwen{height:34px; line-height:34px; background-image:url(images/wanttoask.jpg); background-repeat:no-repeat; background-position:0px 6px; width:280px;line-height:190%; text-indent:22px; margin:0 auto;}

.node-type-best-answer #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-54 .block-inner .content #tiwen a{color:#32A442; font-size:14px; font-weight:700;height:35px; line-height:190%;}

.node-type-best-answer #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-3{border-left:1px solid #D1D1D1;border-right:1px solid #D1D1D1;border-bottom:1px solid #D1D1D1; width:99.5%;}

.node-type-best-answer #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-3 .block-inner .h2Container{height:35px;background-image: url(images/video_titleall.jpg);}

.node-type-best-answer #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-3 .block-inner .h2Container .title{ font-size:14px; color:#32A442; text-indent:26px; font-weight:700; line-height:35px; border:none;}

.node-type-best-answer #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-3 .block-inner .content{height:180px; clear:both;}

.node-type-best-answer #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-3 .block-inner .content ul{ height:100px; margin-top:10px;}

.node-type-best-answer #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-3 .block-inner .content ul li{ height:30px; line-height:30px; text-align:left; width:270px; margin:0 auto;background-image:url(images/youwenyouda_right-barlist.jpg); background-repeat:no-repeat; padding-left:20px;}

*html .node-type-best-answer #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-3 .block-inner .content ul li{ height:30px; line-height:30px; text-align:left; width:270px; margin:0 auto;background-image:url(images/youwenyouda_right-barlist.jpg); background-repeat:no-repeat;}

*+html .node-type-best-answer #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-3 .block-inner .content ul li{ height:30px; line-height:30px; text-align:left; width:270px; margin:0 auto;background-image:url(images/youwenyouda_right-barlist.jpg); background-repeat:no-repeat;}

.node-type-best-answer #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-3 .block-inner .content ul li a{ font-size:14px; font-weight:700; color:#000000;}

/*------erji-------*/

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-header{height:35px;background-image: url(images/video_titleall.jpg); line-height:190%; overflow:hidden;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-header .title{

background-image:url(images/remph_titilebg.jpg);

background-repeat:no-repeat;

height:35px;

line-height:35px;

text-indent:26px;

clear:both;

font-size:14px;

color:#ffffff;

font-weight:700;

z-index:2;

line-height:190%; 

overflow:hidden;

}

/*---------title--------*/

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-header .tabs ul{height:35px;background-image: url(images/video_titleall.jpg); line-height:35px;line-height:190%; overflow:hidden;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-header .tabs ul li.active a{height:35px;background-image: url(images/remph_titilebg2.jpg); line-height:35px;line-height:190%;overflow:hidden;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-header .tabs ul li.active a span{height:35px;background-image: url(images/remph_titilebg1.jpg); line-height:22px; color:#FFFFFF; font-size:14px; font-weight:700;line-height:190%; overflow:hidden;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-header .tabs ul li a{height:35px;background-image:none; line-height:35px;line-height:190%; overflow:hidden;}

.section-wenda #page #page-inner #main #main-inner #content #content-inner #content-header .tabs ul li a .tab{height:35px;background-image:none; line-height:22px; font-size:12px; font-weight:100; color:#000000;line-height:190%; overflow:hidden;}

/*----------------youwenyouda-------------------*/

/*-----sanji--------*/

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_1 .block-inner .content .view-dom-id-1 {border:#D1D1D1 1px solid;}

*html .node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_1 .block-inner .content .view-dom-id-1 {border:#D1D1D1 1px solid; width:99.5%;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_1 .block-inner .content .view-dom-id-1 .view-header{ border-bottom:#D1D1D1 1px solid; background-color:#F8F9F4; height:35px; line-height:190%; overflow:hidden;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_1 .block-inner .content .view-dom-id-1 .view-header p{ color:#1FB456; font-size:14px; font-weight:700; text-indent:26px; background-image:url(images/wait-to-answer.jpg);background-repeat:no-repeat; height:33px; line-height:33px; }



.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-dom-id-2 {border:#D1D1D1 1px solid;}

*html .node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-dom-id-2 {border:#D1D1D1 1px solid; width:99.5%;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-dom-id-2 .view-header{border-bottom:#D1D1D1 1px solid; background-color:#F8F9F4; height:35px; line-height:190%; overflow:hidden;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-dom-id-2 .view-header p{ color:#1FB456; font-size:14px; font-weight:700; text-indent:26px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_1 .block-inner .content .view-best-answer .view-content .views-row .node-type-best-answer .node-inner .meta .submitted a{color:#32A442;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_1 .block-inner .content .view-best-answer .view-content .views-row .node-type-best-answer .node-inner .meta div.terms ul.links{display:inline;height:30px; line-height:30px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_1 .block-inner .content .view-best-answer .view-content .views-row .node-type-best-answer .node-inner .meta div.terms ul.links li{display:inline;height:30px; line-height:30px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_1 .block-inner .content .view-best-answer .view-content .views-row .node-type-best-answer .node-inner .meta div.terms ul.links li.comment_add a{color:#32A442; display:inline;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-2{border:#D1D1D1 1px solid;}

*html .node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1{border:#D1D1D1 1px solid;width:99.5%;}



.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1{border:#D1D1D1 1px solid;}



.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_1 .block-inner .content .view-best-answer .view-content .views-row .node-type-best-answer .node-inner .content .field-field-best-answer-award .field-items .field-item{color:#32A442;display:inline;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-2 .view-content .node-type-node-comment .node-inner h2.title a{display:none;font-size:0px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-2 .view-header{color:#1FB456; font-size:14px; font-weight:700; width:100%; border-bottom:#D1D1D1 1px solid; background-color:#F8F9F4; height:35px; line-height:190%; overflow:hidden; text-indent:26px;}



.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-node-comment .node-inner h2.title a{display:none;font-size:0px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-header{color:#1FB456; font-size:14px; font-weight:700; width:100%; border-bottom:#D1D1D1 1px solid; background-color:#F8F9F4; height:35px; line-height:190%; overflow:hidden; text-indent:26px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-3 .view-header{color:#1FB456; font-size:14px; font-weight:700; width:100%; border-bottom:#D1D1D1 1px solid; background-color:#F8F9F4; height:35px; line-height:190%; overflow:hidden; text-indent:26px;}





.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_1 .block-inner .content .view-dom-id-1 .view-content{ margin-left:10px;margin-right:10px; line-height:25px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-2 .view-content{ margin-left:10px; margin-right:10px;line-height:25px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-best-answer .node-inner .title a{ font-size:14px; color:#000000; font-weight:700;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-best-answer .node-type-best-answer .node-inner .content .field-field-best-answer-award{ background-image:none;}



.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-node-comment .node-inner .picture{float:left; margin:10px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-node-comment .node-inner h2.title a{font-size:14px; color:#000000; font-weight:700; text-decoration:none;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-node-comment .node-inner .meta{ float:right; width:500px;margin-top:20px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-node-comment .node-inner .meta .submitted a{color:#32A442; }

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-node-comment .node-inner .meta  div ul li a{color:#32A442;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-node-comment .node-inner .content{ clear:both; width:540px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-node-comment .node-inner .content p{ font-size:12px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-node-comment .node-inner ul.links{text-align:right;width:580px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-node-comment .node-inner ul.links li a{color:#32A442; float:right; text-decoration:underline;}





.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-2 .view-content .node-type-node-comment .node-inner .picture{float:left; margin:10px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-2 .view-content .node-type-node-comment .node-inner h2.title a{font-size:14px; color:#000000; font-weight:700; text-decoration:none;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-2 .view-content .node-type-node-comment .node-inner .meta{ float:right; width:500px;margin-top:20px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-2 .view-content .node-type-node-comment .node-inner .meta .submitted a{color:#32A442; }

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-2 .view-content .node-type-node-comment .node-inner .meta  div ul li a{color:#32A442;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-2 .view-content .node-type-node-comment .node-inner .content{ clear:both; width:540px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-2 .view-content .node-type-node-comment .node-inner .content p{ font-size:12px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-2 .view-content .node-type-node-comment .node-inner ul.links{text-align:right;width:580px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-2 .view-content .node-type-node-comment .node-inner ul.links li a{color:#32A442; float:right; text-decoration:underline;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view .view-content .node-type-node-comment .node-inner{ border-bottom:1px #CCCCCC dashed;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view .view-content .node-type-node-comment .node-inner ul{ width:550px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-dom-id-2 .view-content .views-row  .node-type-best-answer .node-inner .title a{ font-size:14px; color:#000000; font-weight:700;} 



.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-dom-id-2 .view-content .views-row  .node-type-best-answer .node-inner .content .field-field-best-answer-award{width:250px; float:left;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-dom-id-2 .view-content .views-row  .node-type-best-answer .node-inner .content .field-field-best-answer-award .field-label{width:90px; float:left;height:25px; line-height:190%; font-weight:100; background-image:url(images/youwenyouda_xuanshangfenshu.jpg); background-repeat:no-repeat; padding-left:20px; margin-left:20px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-dom-id-2 .view-content .views-row  .node-type-best-answer .node-inner .content .field-field-best-answer-award .field-items{width:30px;float:left; text-align:left;height:25px; line-height:190%;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-dom-id-2 .view-content .views-row  .node-type-best-answer .node-inner .content .field-field-best-answer-award .field-items .field-item{color:#32A442; position:absolute; margin-left:-28px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-dom-id-2 .view-content .views-row  .node-type-best-answer .node-inner .picture{float:left;margin:10px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-dom-id-2 .view-content .views-row  .node-type-best-answer .node-inner h2.title a{font-size:14px; color:#000000; font-weight:700; text-decoration:none;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-dom-id-2 .view-content .views-row  .node-type-best-answer .node-inner .meta{float:right; width:530px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-dom-id-2 .view-content .views-row  .node-type-best-answer .node-inner .meta .submitted a{color:#32A442; }

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-3 .view-content .node-type-node-comment .node-inner .meta  div ul li a{color:#32A442;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-3 .view-content .node-type-node-comment .node-inner .meta  div ul li{ display:inline;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-dom-id-2 .view-content .views-row  .node-type-best-answer .node-inner .content{ clear:both; width:540px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-dom-id-2 .view-content .views-row  .node-type-best-answer .node-inner .content p{ font-size:14px; text-indent:25px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-dom-id-2 .view-content .views-row  .node-type-best-answer .node-inner .meta div.terms-inline{ height:30px; line-height:30px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-dom-id-2 .view-content .views-row  .node-type-best-answer .node-inner .meta div.terms-inline  ul.links{ margin-left:0px; position:absolute; height:30px; line-height:30px;}

*html .content .view-dom-id-2 .view-content .views-row  .node-type-best-answer .node-inner .meta div.terms-inline  ul.links{ margin-left:0px; position:absolute; height:30px; line-height:30px; margin-top:-8px;}

*+html .content .view-dom-id-2 .view-content .views-row  .node-type-best-answer .node-inner .meta div.terms-inline  ul.links{ margin-left:0px; position:absolute; height:30px; line-height:30px; margin-top:-8px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-dom-id-2 .view-content .views-row  .node-type-best-answer .node-inner .meta div.terms-inline  ul.links li a{text-decoration:underline;color:#32A442;}





.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_1 .block-inner .view-dom-id-1 .view-content .views-row .node-type-best-answer .node-inner .content .field-field-best-answer-award .field-label{width:100px; float:left;background-image:url(images/youwenyouda_xuanshangfenshu.jpg); background-repeat:no-repeat; padding-left:30px; font-weight:100;height:22px; line-height:22px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_1 .block-inner .view-dom-id-1 .view-content .views-row .node-type-best-answer .node-inner .content .field-field-best-answer-award .field-items{width:400px;float:left; height:30px; line-height:30px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_1 .block-inner .view-dom-id-1 .view-content .views-row .node-type-best-answer .node-inner .content .field-field-best-answer-award .field-items .field-item{ position:absolute; margin-left:-38px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_1 .block-inner .view-dom-id-1 .view-content .views-row .node-type-best-answer .node-inner .content .field-field-best-answer-award .field-items .field-item a{text-align:left; float:left;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-best-answer .view-content .views-row .node-type-best-answer .node-inner .content .best_answer{width:609px; clear:both;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-best-answer .view-content .views-row .node-type-best-answer .node-inner .content .best_answer fieldset{width:550px; line-height:22px; float:left; margin-left:20px; margin-bottom:20px;clear:both;}

*html .node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-best-answer .view-content .views-row .node-type-best-answer .node-inner .content .best_answer fieldset{width:550px; line-height:22px; float:left; margin-left:10px; margin-bottom:20px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-best-answer .view-content .views-row .node-type-best-answer .node-inner .content .best_answer fieldset div.best_answer_body{ line-height:22px; text-indent:25px; margin-left:5px; margin-right:5px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-best-answer .view-content .views-row .node-type-best-answer .node-inner .content .best_answer fieldset div div{ line-height:22px; text-indent:25px;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-best-answer .view-content .views-row .node-type-best-answer .node-inner ul{width:600px; height:30px; clear:left;white-space:normal;float:left;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-id-best_answer .view-content .views-row .node-inner .content .best_answer fieldset legend{color:#32A442;}

.node-type-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-id-best_answer .view-content .views-row .node-inner .content .best_answer fieldset .best_answer .form-item{ color:#999999;}

/*

.page-node-add-best-answer #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-best_answer-block_2 .block-inner .content .view-dom-id-2 .view-content .views-row .node-type-best-answer .node-inner .content .field-field-best-answer-award{}



/*-----------chuangjianwenzhang-----------*/

.page-node-add-best-answer #page #page-inner #main #main-inner #content #content-inner #content-area form  div .node-form .standard #edit-field-best-answer-award-0-value-wrapper label{ float:left; width:100px;}

.page-node-add-best-answer #page #page-inner #main #main-inner #content #content-inner #content-area form  div .node-form .standard #edit-field-best-answer-award-0-value-wrapper input{float:left; width:130px;}

.page-node-add-best-answer #page #page-inner #main #main-inner #content #content-inner #content-area form  div .node-form .standard #edit-field-best-answer-award-0-value-wrapper .description{float:left; width:700px; line-height:20px; height:35px; margin-left:10px;}

.page-node-add-best-answer #page #page-inner #main #main-inner #content #content-inner #content-area form  div .node-form .standard #edit-taxonomy-8-wrapper label{ float:left; width:130px;height:44px;}

.page-node-add-best-answer #page #page-inner #main #main-inner #content #content-inner #content-area form  div .node-form .standard #edit-taxonomy-8-wrapper select{ width:90px;float:left; margin-left:10px;}

.page-node-add-best-answer #page #page-inner #main #main-inner #content #content-inner #content-area form div .node-form #edit-submit{margin-left:150px; margin-top:20px;}

.page-node-add-best-answer #page #page-inner #main #main-inner #content #content-inner #content-area form div .node-form #edit-preview{ margin-left:0px;margin-top:20px;}



/*-------rightbar-------*/

.section-jifenduihuan #page #page-inner #main #main-inner #sidebar-right{clear:both;margin-top:-729px;}

*html .section-jifenduihuan #page #page-inner #main #main-inner #sidebar-right{clear:both;margin-top:-727px;}

*+html .section-jifenduihuan #page #page-inner #main #main-inner #sidebar-right{clear:both;margin-top:-717px;}

.section-jifenduihuan #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-31 .block-inner{}

.section-jifenduihuan #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-55 .block-inner .content p{ text-align:center; margin:0 auto;}

.section-jifenduihuan #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-56 .block-inner .content p{ text-align:center; margin:0 auto;}

.section-jifenduihuan #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-57 .block-inner .content p{ text-align:center; margin:0 auto;}

.section-jifenduihuan #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-55 .block-inner .content h2{font-size:14px;}

.section-jifenduihuan #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-block-55 .block-inner .content h2 a{color:#04B038;}

.section-dalibao #page #page-inner #main #main-inner #content #content-inner #content-header .title{ color:#04B038; font-size:14px; font-weight:700; height:35px; line-height:35px;}

.section-dalibao #page #page-inner #main #main-inner #content-area .node-type-product .node-inner .meta ul{ display:inline;height:35px; line-height:35px;}

.section-dalibao #page #page-inner #main #main-inner #content-area .node-type-product .node-inner .meta ul li a{ color:#04B038;height:35px; line-height:35px;}

.section-dalibao #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-product .node-inner .content .field-field-product-fengmian{border:#D1D1D1 1px solid; width:530px; height:370px; float:left;}

.section-dalibao #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-product .node-inner .content .field-field-product-fengmian .field-label{ height:25px; line-height:25px; text-indent:25px;}

.section-dalibao #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-product .node-inner .content .field-field-product-fengmian .field-items .field-item img{width:460px; height:330px; margin:0 auto;}

.section-dalibao #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-product .node-inner .content .sell_price{ display:none; height:0px; line-height:0px; font-size:0px;}

.section-dalibao #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-product .node-inner .content .display_price,.product-info,.add-to-cart{ width:380px; float:right; text-align:left; height:30px; line-height:30px;}

.section-dalibao #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-product .node-inner .content .display_price,.add-to-cart{ width:380px; float:right; text-align:left; height:30px; line-height:30px; color:#04B038;}

.section-dalibao #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-product .node-inner .content .product-info{ display:none; height:0px; line-height:0px;}

.section-dalibao #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-product .node-inner .content   .field-field-product-neirongtiyao{ clear:both; float:left;}

.section-dalibao #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-product .node-inner .content .add-to-cart form div .node-add-to-cart{color:#FFFFFF; font-size:14px; background-image:url(images/jifenhuanlitianjia.jpg);background-repeat:no-repeat; font-weight:700; border:none; width:96px; height:24px;background-color: Transparent;}

.section-dalibao #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-product .node-inner .content .field-field-product-neirongtiyao{ width:960px; margin-top:10px;border-left:#D1D1D1 1px solid;border-right:#D1D1D1 1px solid; border-bottom:#D1D1D1 1px solid; margin-top:10px;}

.section-dalibao #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-product .node-inner .content .field-field-product-neirongtiyao .field-label{height:35px;background-image: url(images/video_titleall.jpg); line-height:35px; font-size:14px; color:#04B038;font-weight:700; text-indent:26px;}

.section-dalibao #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-product .node-inner .content .field-field-product-neirongtiyao .field-items .field-item p{text-indent:15px;background-image:url(images/list_style_type_disc.jpg); background-repeat:no-repeat; margin-left:10px; line-height:25px; font-size:14px;}  



/*----gouwuche---*/

.section-cart #page #page-inner #main #main-inner #content #content-inner #content-header h1.title{color:#04B038; font-size:14px; font-weight:700; height:35px; line-height:35px;text-indent:10px;}

*html .section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div{vertical-align:top;}

.section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products{border:#D1D1D1 1px solid;}

*html .section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products{width:99.5%; border:none;}

.section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products table.sticky-enabled{text-align:left; margin-top:0px;border:#D1D1D1 1px solid;}

*html .section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products table.sticky-enabled{text-align:left; margin-top:0px;}

.section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products table.sticky-enabled thead {height:26px;}

.section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products table.sticky-enabled thead tr th{color:#04B038;font-weight:700;line-height:190%; overflow:hidden; height:26px; width:110px; border:none; text-indent:20px;background-image: url(images/carttablethbg.jpg);}

*html .section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products table.sticky-enabled thead tr th{color:#04B038;font-weight:700;height:26px; width:110px; border:none; text-indent:20px;background-image: url(images/carttablethbg.jpg);}

.section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products .sticky-enabled tbody{ border:none; border:0px;}

.section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products table.sticky-enabled tbody tr.even, tr.odd {

background-color:none;

border-bottom:none;



}

.section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products .sticky-enabled tbody tr td{ text-align:left; background-color:#FFFFFF; border:0px;text-indent:20px;line-height:25px;}

.section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products .sticky-enabled tbody tr .desc{ width:650px;}

.section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products .sticky-enabled tbody tr .desc a{ color:#000000;}

.section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products .sticky-enabled tbody tr .remove #edit-items-0-remove-wrapper{width:90px;text-indent:20px;}

.section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products .sticky-enabled tbody  tr.odd .subtotal{ text-align:right; height:25px; line-height:25px;}

.section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products .sticky-enabled tbody  tr.even .subtotal{ text-align:right; height:25px; line-height:25px;}

.section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-buttons{background-image: url(images/cart_goonbg.jpg); background-repeat:repeat-x; height:54px; line-height:54px;}

*html .section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-buttons{background-image: url(images/cart_goonbg.jpg); background-repeat:repeat-x; height:54px; width:99.5%;}

.section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-buttons #continue-shopping-link a{color:#04B038; font-size:14px; font-weight:700;}

.section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-buttons  #edit-update{color:#FFFFFF; font-size:14px; background-image:url(images/jifenhuanlitianjia.jpg);background-repeat:no-repeat; font-weight:700; border:none; width:96px; height:24px;background-color: Transparent;}

.section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-buttons #edit-checkout{

color:#FFFFFF; font-size:14px; background-image:url(images/jifenhuanlitianjiajiesuan.jpg);background-repeat:no-repeat; font-weight:700; border:none; width:96px; height:24px;background-color: Transparent; width:58px;}

*html .section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products{ width:99.5%;} 

.section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products table.sticky-enabled tbody  tr.odd,tr.even .qty .form-item{text-indent:20px;}

.section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products table.sticky-enabled tbody tr.odd .qty .form-item input.form-text{ width:20px; height:17px; text-align:center;}

.section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products table.sticky-enabled tbody tr.even .qty .form-item input.form-text{ width:20px; height:17px; text-align:center;}

*html .section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products table.sticky-enabled tbody tr.odd .qty .form-item input.form-text{ margin-left:20px; width:20px; height:17px; text-align:center;}

*html .section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products table.sticky-enabled tbody tr.even .qty .form-item input.form-text{ margin-left:20px; width:20px; height:17px; text-align:center;}

*+html .section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products table.sticky-enabled tbody tr.odd .qty .form-item input.form-text{ margin-left:20px; width:20px; height:17px; text-align:center;}

*+html .section-cart #page #page-inner #main #main-inner #content #content-inner  #content-area #cart-form-pane form div #cart-form-products table.sticky-enabled tbody tr.even .qty .form-item input.form-text{ margin-left:20px; width:20px; height:17px; text-align:center;}

/*----gouwuche---*/



/*------jifenhuanli-------*/

/*------yonghuguanli-------*/

.section-user #page #page-inner #main #main-inner #content #content-inner #content-header h1.title{ font-size:14px; color:#04B038;font-weight:700; height:25px; line-height:25px; text-indent:56px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .profile h3{font-size:14px; color:#000000;font-weight:700;height:25px; line-height:25px;background-image:url(images/youwenyouda_right-barlist.jpg); background-repeat:no-repeat;padding-left:20px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .profile dl dd a{font-size:12px; color:#04B038;font-weight:100;height:20px; line-height:20px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .profile dl{ margin-left:15px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .profile dl dt{font-size:12px; color:#000000;font-weight:700;height:25px; line-height:25px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .profile .user-member .form-item .label{font-size:12px; color:#000000;font-weight:700;height:25px; line-height:25px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .profile .user-member .form-item .item-list ul li a{font-size:12px; color:#04B038;font-weight:100;height:20px; line-height:20px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table{background-color:#FFFFFF; width:960px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table thead{ border:none;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table thead tr{border-bottom:1px #CCCCCC solid;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table thead tr th.views-field-type{font-size:14px; color:#000000;font-weight:700;height:30px; line-height:30px;background-image:url(images/youwenyouda_right-barlist.jpg); background-repeat:no-repeat;padding-left:15px; width:175px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table thead tr th.views-field-title{width:390px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table thead tr th a{font-size:14px; color:#000000;font-weight:700;height:30px; line-height:30px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody{ margin-left:10px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody tr{}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td{ background-color:#FFFFFF; height:30px; line-height:30px;border-bottom:1px #CCCCCC solid;}



.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody  .views-field-type{ width:175px; text-indent:15px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-title{width:390px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-title a{color:#32A442; }

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-name a{color:#32A442; }

.section-user #page #page-inner #main #main-inner #content #content-inner #content-header .title{}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset{position:relative !important; clear:both;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset legend{font-size:14px; color:#000000;font-weight:700;height:30px; line-height:30px;background-image:url(images/youwenyouda_right-barlist.jpg); background-repeat:no-repeat;padding-left:15px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset label{ height:30px; line-height:30px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset  #edit-mail,#edit-pass-pass1,#edit-pass-pass2,#edit-picture-upload{}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-signature-wrapper textarea {background-color:#F5F5F5; border:#CCCCCC 1px solid;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset .description{width:700px; font-size:12px; line-height:22px;color:#898989;} 

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset .form-item{ margin-left:15px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset .form-item #edit-pass-pass1-wrapper,#edit-pass-pass2-wrapper{margin-left:0px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset .form-item #edit-pass-pass2-wrapper{margin-left:0px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset .picture{margin-left:15px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-picture-upload-wrapper  #edit-picture-upload .description{ font-size:12px; line-height:22px;color:#898989; width:300px; float:left; display:inline;} 

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset.collapsible .sticky-enabled,.description{ margin-left:15px; width:600px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset.collapsible .sticky-enabled{ margin-left:15px; width:600px; margin-bottom:10px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset.collapsible .sticky-enabled td{ background-color:#FFFFFF;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .sticky-enabled{ width:600px; margin-bottom:20px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .sticky-enabled td{background-color:#FFFFFF;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .sticky-enabled thead tr th.views-field-title{font-size:14px; color:#000000;font-weight:700;height:30px; line-height:30px;background-image:url(images/youwenyouda_right-barlist.jpg); background-repeat:no-repeat;padding-left:15px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .sticky-enabled thead tr th.active{font-size:14px; color:#000000;font-weight:700;height:30px; line-height:30px;background-image:url(images/youwenyouda_right-barlist.jpg); background-repeat:no-repeat;padding-left:15px;}



.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .sticky-enabled thead tr th a{ color:#000000; font-size:14px; font-weight:700;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .sticky-enabled  tbody tr.odd,tr.even{ height:30px; left:30px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .sticky-enabled  tbody tr.odd td.active{ height:30px; left:30px; margin-left:15px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .sticky-enabled  tbody tr.odd td{ border-bottom:#CCCCCC 1px solid; height:30px; line-height:30px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .sticky-enabled  tbody tr.even td{ border-bottom:#CCCCCC 1px solid; height:30px; line-height:30px;}



.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .sticky-enabled thead tr th{color:#000000; font-size:14px; font-weight:700; height:30px; line-height:30px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .form-item .description{font-size:12px; line-height:22px;color:#898989;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .sticky-enabled  tbody tr td a{color:#000000; margin-left:15px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area .profile .picture{ margin-left:0px; position:absolute; margin-top:-65px;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-profile-tishi-wrapper  label{ width:250px; float:left; text-align:right; font-size:14px; height:30px; line-height:30px; padding-right:20px; font-weight:100;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-profile-gender-wrapper  label{ width:250px; float:left; text-align:right;font-size:14px; height:30px; line-height:30px; padding-right:20px; font-weight:100;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-profile-birthday-wrapper  label{ width:250px; float:left; text-align:right;font-size:14px; height:30px; line-height:30px; padding-right:20px; font-weight:100;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-profile-zhiye-wrapper  label{ width:250px; float:left; text-align:right;font-size:14px; height:30px; line-height:30px; padding-right:20px; font-weight:100;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-profile-hangye-wrapper  label{ width:250px; float:left; text-align:right;font-size:14px; height:30px; line-height:30px; padding-right:20px; font-weight:100;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-profile-waiyu-wrapper  label{ width:250px; float:left; text-align:right;font-size:14px; height:30px; line-height:30px; padding-right:20px; font-weight:100;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-profile-waiyu-wrapper  label{ width:250px; float:left; text-align:right;font-size:14px; height:30px; line-height:30px; padding-right:20px; font-weight:100;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-profile-waiyutigao-wrapper  label{ width:250px; float:left; text-align:right;font-size:14px; height:30px; line-height:30px; padding-right:20px; font-weight:100;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-profile-zizhi-huode-wrapper  label{ width:250px; float:left; text-align:right;font-size:14px; height:30px; line-height:30px; padding-right:20px; font-weight:100;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-profile-zizhi-xiwang-wrapper  label{ width:250px; float:left; text-align:right;font-size:14px; height:30px; line-height:30px; padding-right:20px; font-weight:100;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-profile-zhuti-wrapper  label{ width:250px; float:left; text-align:right;font-size:14px; height:30px; line-height:30px; padding-right:20px; font-weight:100;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-profile-address-wrapper  label{ width:250px; float:left; text-align:right;font-size:14px; height:30px; line-height:30px; padding-right:20px; font-weight:100;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-profile-telephone-wrapper  label{ width:250px; float:left; text-align:right;font-size:14px; height:30px; line-height:30px; padding-right:20px; font-weight:100;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-profile-qq-msn-gmail-wrapper  label{ width:250px; float:left; text-align:right;font-size:14px; height:30px; line-height:30px; padding-right:20px; font-weight:100;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-profile-xieyi-wrapper label{ width:250px; float:left; text-align:right;font-size:14px; height:30px; line-height:30px; padding-right:20px; font-weight:100;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-profile-address-wrapper .description{font-size:12px; line-height:22px;color:#898989; display:inline;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-profile-telephone-wrapper .description{font-size:12px; line-height:22px;color:#898989; display:inline;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div fieldset #edit-profile-qq-msn-gmail-wrapper .description{font-size:12px; line-height:22px;color:#898989; display:inline;}

.section-user #page #page-inner #main #main-inner #content #content-inner #content-area form div #edit-submit{background:url(images/submitbg.jpg); background-repeat:no-repeat; border:none; font-size:12px; font-weight:700; color:#FFFFFF; text-align:center; width:57px; height:22px; margin-top:10px; margin-bottom:10px;}



/*------yonghuguanli-------*/





/*------search-------*/

.section-search #page #page-inner #main #main-inner #content #content-inner #content-header h1.title{height:25px; line-height:25px; font-size:14px; color:#1EB149; font-weight:700; vertical-align:bottom;}

.section-search #page #page-inner #main #main-inner #content #content-inner #content-area{margin-left:10px; width:950px; margin:0 auto;}

.section-search #page #page-inner #main #main-inner #content #content-inner #content-header{margin-left:10px; width:950px; margin:0 auto;}

.section-search #page #page-inner #main #main-inner #content #content-inner #content-area form div .form-item label{font-size:12px; font-weight:700; height:30px; line-height:30px;}

.section-search #page #page-inner #main #main-inner #content #content-inner #content-area form div .form-item .container-inline{height:30px; line-height:30px;}

.section-search #page #page-inner #main #main-inner #content #content-inner #content-area .box .box-inner .title{font-size:14px; font-weight:700; height:22px; line-height:22px;}

.section-search #page #page-inner #main #main-inner #content #content-inner #content-area .box .box-inner .content ul li{ height:22px; line-height:22px; list-style:none; color:#666666;}

.section-search #page #page-inner #main #main-inner #content #content-inner dt.title a{ font-size:12px; color:#1EB149; height:22px; line-height:22px; font-weight:100;}

.section-search #page #page-inner #main #main-inner #content #content-inner #content-area .box .box-inner .content dl dd .search-snippet{line-height:22px;}

.section-search #page #page-inner #main #main-inner #content #content-inner #content-area .box .box-inner .content dl dd p.search-info{text-align:right; font-size:12px; color:#555555;line-height:22px;}

*html .section-search #page #page-inner #main #main-inner #content #content-inner #content-area .box .box-inner .content .item-list ul.pager{ padding-left:240px;}

.section-search #page #page-inner #main #main-inner #content-inner #content-area form div .form-item .container-inline .form-submit{background:url(images/submitbg.jpg); background-repeat:no-repeat; border:none; font-size:12px; font-weight:700; color:#FFFFFF; text-align:center; width:57px; height:22px; margin:0 auto; width:57px; height:22px;}

.section-search #page #page-inner #main #main-inner #content #content-inner #content-area .box .box-inner .content dl{ border-bottom:1px dashed #CCCCCC;}

.section-search #page #page-inner #main #main-inner #content #content-inner #content-area .box .box-inner .content dl dt{ border-top:1px dashed #CCCCCC;}

/*------search-------*/



/*--------foot-------*/



.section-uu #page #page-inner #main #main-inner #content #content-inner{ width:960px; margin:0 auto;}

.section-uu #page #page-inner #main #main-inner #content #content-inner #content-header{ border-bottom:1px #CCCCCC solid;}

.section-uu #page #page-inner #main #main-inner #content #content-inner #content-header .title{height:30px; line-height:30px; text-align:left; background-image:url(images/centerofhelp.jpg);background-repeat:no-repeat; font-size:16px; color:#1CB247; font-weight:700; padding-left:35px;}

.section-uu #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content p{}

.section-uu #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content p.MsoNormal font span{ font-size:12px;}

.section-uu #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content  p.MsoNormal strong font span{ height:25px; line-height:25px; font-size:14px; color:#1CB247;}

.section-uu #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content  p.MsoNormal strong font span font{ height:25px; line-height:25px; font-size:14px; color:#1CB247;}

.section-uu #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content p.MsoNormal font{font-size:12px; color:#000000;}

.section-uu #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content p.MsoNormal a{color:#1CB247;line-height:22px; font-size:12px;}

.section-uu #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content p.MsoNormal span font{font-size:12px;line-height:22px;}





.section-bangzhu #page #page-inner #main #main-inner #content #content-inner{ width:960px; margin:0 auto;}

.section-bangzhu #page #page-inner #main #main-inner #content #content-inner #content-header{ border-bottom:1px #CCCCCC solid;}

.section-bangzhu #page #page-inner #main #main-inner #content #content-inner #content-header .title{height:30px; line-height:30px; text-align:left; background-image:url(images/centerofhelp.jpg);background-repeat:no-repeat; font-size:16px; color:#1CB247; font-weight:700; padding-left:35px;}

.section-bangzhu #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content p{}

.section-bangzhu #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content p.MsoNormal font span{ font-size:12px;}

.section-bangzhu #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content  p.MsoNormal strong font span{ height:25px; line-height:25px; font-size:14px; color:#1CB247;}

.section-bangzhu #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content  p.MsoNormal strong font span font{ height:25px; line-height:25px; font-size:14px; color:#1CB247;}

.section-bangzhu #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content p.MsoNormal font{font-size:12px; color:#000000;}

.section-bangzhu #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content p.MsoNormal a{color:#1CB247;line-height:22px; font-size:12px;}

.section-bangzhu #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content p.MsoNormal span font{font-size:12px;line-height:22px;}





.section-yuanze #page #page-inner #main #main-inner #content #content-inner{ width:960px; margin:0 auto;}

.section-yuanze #page #page-inner #main #main-inner #content #content-inner #content-header{ border-bottom:1px #CCCCCC solid;}

.section-yuanze #page #page-inner #main #main-inner #content #content-inner #content-header .title{height:30px; line-height:30px; text-align:left; background-image:url(images/centerofhelp.jpg);background-repeat:no-repeat; font-size:16px; color:#1CB247; font-weight:700; padding-left:35px;}

.section-yuanze #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content  p.MsoNormal strong font span{height:25px; line-height:25px; font-size:14px; color:#1CB247;}

.section-yuanze #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content p.MsoNormal font{font-size:12px; color:#000000;}

.section-yuanze #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content p.MsoNormal a{color:#1CB247;line-height:22px; font-size:12px;}

.section-yuanze #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content p.MsoNormal span font{font-size:12px;line-height:22px;}





.section-lianxi #page #page-inner #main #main-inner #content #content-inner{ width:960px; margin:0 auto;}

.section-lianxi #page #page-inner #main #main-inner #content #content-inner #content-header{ border-bottom:1px #CCCCCC solid;}

.section-lianxi #page #page-inner #main #main-inner #content #content-inner #content-header .title{height:30px; line-height:30px; text-align:left; background-image:url(images/centerofhelp.jpg);background-repeat:no-repeat; font-size:16px; color:#1CB247; font-weight:700; padding-left:35px;}

.section-lianxi #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content h3 h2 span span{color:#1CB247;}

.section-lianxi #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-page .node-inner .content h3 h2{ border-bottom:#CCCCCC 1px dashed;}

.section-lianjie #page #page-inner #main #main-inner #content #content-inner{ width:960px; margin:0 auto;}

.section-lianjie #page #page-inner #main #main-inner #content #content-inner #content-header{ border-bottom:1px #CCCCCC solid; }

.section-lianjie #page #page-inner #main #main-inner #content #content-inner #content-header .title{height:30px; line-height:30px; text-align:left; background-image:url(images/centerofhelp.jpg);background-repeat:no-repeat; font-size:16px; color:#1CB247; font-weight:700; padding-left:35px;}

/*--------footr-------*/

/*--------riyuxiazai-------*/

.section-riyu-mp3 #page #page-inner #main #main-inner #content{margin:0 auto; border:#D1D1D1 1px solid;}

.section-riyu-mp3 #page #page-inner #main #main-inner #content #content-inner #content-area{ width:900px; margin:0 auto;}

.section-riyu-mp3 #page #page-inner #main #main-inner #content #content-inner #content-header{height:35px;background-image: url(images/video_titleall.jpg); line-height:35px;}

.section-riyu-mp3 #page #page-inner #main #main-inner #content #content-inner #content-header .title{

background-image:url(images/remph_titilebglong.jpg);

background-repeat:no-repeat;

height:35px;

line-height:35px;

text-indent:26px;

clear:both;

font-size:14px;

color:#ffffff;

font-weight:700;}

.section-riyu-mp3 #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row{border-bottom:1px #CCCCCC dashed;}

.section-riyu-mp3 #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row .views-field-title{ font-size:14px; line-height:30px;width:900px;}

.section-riyu-mp3 #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row .views-field-title .views-label-title{ color:#000000; font-size:14px;font-weight:700; width:}

.section-riyu-mp3 #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row .views-field-title span.field-content a{ font-size:14px;color:#1CB247; width:800px; display:inline; clear:both;}

*html .section-riyu-mp3 #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row .views-field-title span.field-content{width:800px; white-space:nowrap;}

.section-riyu-mp3 #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row .views-field-sell-price{ line-height:22px;width:900px;}

.section-riyu-mp3 #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row .views-field-sell-price label{ line-height:22px;}

.section-riyu-mp3 #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row .views-field-addtocartlink .field-content{ width:900px;}

.section-riyu-mp3 #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row .views-field-addtocartlink .field-content .add-to-cart{ height:30px;}

.section-riyu-mp3 #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row .views-field-addtocartlink .field-content .add-to-cart .form{height:30px; line-height:22px; text-align:right;}

.section-riyu-mp3 #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row  .views-field-addtocartlink .field-content .add-to-cart form div .form-submit{color:#FFFFFF; font-size:12px; background-image:url(images/jifenhuanlitianjia.jpg);background-repeat:no-repeat; font-weight:700px; border:none; width:96px; height:24px;background-color: Transparent;}

/*--------riyuxiazai-------*/

/*--------hougai----------*/

*html .section-yuedu #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .item-list ul.pager{ margin-left:30px;}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-ebook .node-inner .meta{ width:960px;}

/*--------hougai----------*/



/*-----------jiesuan------------*/

.section-cart #page #page-inner #main #main-inner #content #content-inner #content-area #uc-cart-checkout-form div fieldset legend{color:#000000; font-size:14px; height:30px; line-height:30px;text-align:left;}

.section-cart #page #page-inner #main #main-inner #content #content-inner #content-area #uc-cart-checkout-form div #cart-pane table.sticky-enabled{ width:940px; margin:0 auto; margin-bottom:20px;}

.section-cart #page #page-inner #main #main-inner #content #content-inner #content-area #uc-cart-checkout-form div #cart-pane table.sticky-enabled tbody tr td{ background-color:#FFFFFF;}

.section-cart #page #page-inner #main #main-inner #content #content-inner #content-area #uc-cart-checkout-form div #cart-pane table.sticky-enabled thead tr th{color:#04B038;font-weight:700;overflow:hidden;height:26px; line-height:26px;background-image: url(images/carttablethbg.jpg); white-space:nowrap; border:none;}

.section-cart #page #page-inne #main #main-inner #content #content-inner #content-area #uc-cart-checkout-form div fieldset .sticky-enabled thead tr th.qty{ height:26px; width:100px; overflow:hidden;}

.section-cart #page #page-inner #main #main-inner #content #content-inner #content-area #uc-cart-checkout-form div #cart-pane table.sticky-enabled thead tr th.products{ height:26px; width:600px;overflow:hidden;}

.section-cart #page #page-inner #main #main-inner #content #content-inner #content-area #uc-cart-checkout-form div #cart-pane table.sticky-enabled thead tr th.price{ height:26px; width:100px;overflow:hidden;}

.section-cart #page #page-inne #main #main-inner #content #content-inner #content-area #uc-cart-checkout-form div fieldset .sticky-enabled tbody tr.odd td.qty{ width:100px; white-space:nowrap;overflow:hidden;}

.section-cart #page #page-inne #main #main-inner #content #content-inner #content-area #uc-cart-checkout-form div fieldset .sticky-enabled tbody tr.even td.qty{ width:100px; white-space:nowrap;overflow:hidden;}





.section-cart #page #page-inner #main #main-inner #content #content-inner #content-area #uc-cart-checkout-form div fieldset  .description{ height:25px; line-height:25px; color:#555555;}

.section-cart #page #page-inner #main #main-inner #content #content-inner #content-area #uc-cart-checkout-form div #customer-pane div{text-indent:20px;line-height:25px;}

.section-cart #page #page-inner #main #main-inner #content #content-inner #content-area #uc-cart-checkout-form div #customer-pane div b{ text-indent:20px;}

.section-cart #page #page-inner #main #main-inner #content #content-inner #content-area #uc-cart-checkout-form div #customer-pane div a{color:#1CB247; }

.section-cart #page #page-inner #main #main-inner #content #content-inner #content-area #uc-cart-checkout-form div #customer-pane .next-button #edit-panes-customer-next{background:url(images/submitbg.jpg); background-repeat:no-repeat; border:none; font-size:12px; font-weight:700; color:#FFFFFF; text-align:center; width:57px; height:22px; margin-bottom:10px; margin-right:10px;}

.section-cart #page #page-inner #main #main-inner #content #content-inner #content-area form div #delivery-pane .address-pane-table table{ margin-left:20px;}

.section-cart #page #page-inner #main #main-inner #content #content-inner #content-area form div #delivery-pane .address-pane-table table tr{ height:30px;}

.section-cart #page #page-inner #main #main-inner #content #content-inner #content-area form div #delivery-pane .next-button #edit-panes-delivery-next{background:url(images/submitbg.jpg); background-repeat:no-repeat; border:none; font-size:12px; font-weight:700; color:#FFFFFF; text-align:center; width:57px; height:22px; margin-bottom:10px; margin-right:10px;}

.section-cart #page #page-inner #main #main-inner #content #content-inner #content-area #edit-cancel{background:url(images/submitbg.jpg); background-repeat:no-repeat; border:none; font-size:12px; font-weight:700; color:#FFFFFF; text-align:center; width:57px; height:22px; margin-bottom:10px; margin-right:10px;}

.section-cart #page #page-inner #main #main-inner #content #content-inner #content-area #edit-continue{background:url(images/submitbg.jpg); background-repeat:no-repeat; border:none; font-size:12px; font-weight:700; color:#FFFFFF; text-align:center; width:57px; height:22px; margin-bottom:10px;}



/*-----------jiesuan------------*/





/*-----tabs------*/



.section-search #page #page-inner #main #main-inner #content #content-inner #content-header{}



.view-shipin-list tr.even, .view-shipin-list tr.odd {

background-color:#FFFFFF;

border-bottom:1px dashed #CCCCCC;

line-height:2.5em;

padding:0.1em 0.6em;

}

.view-shipin-list td,.view-shipin-list th {

min-width:200px;

padding:0 30px;

}

/*----section-tag-----*/

.section-tag #page #page-inner #main #main-inner #content{border:1px solid #E5EBE1; border-top:none; width:610px;margin-bottom:10px;}

.section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1{background-color:#FFFFFF; clear:both; margin:0 auto;}

*html .section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1{width:99.5%;clear:both;}

.section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content{background-color:#FFFFFF; vertical-align:top;margin-top:0px; padding-top:0px;clear:both;}

.section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table{border:none;background-color:#FFFFFF; margin-top:0px;width:600px; margin:0 auto;}

.section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tr{border-bottom:2px solid #E5EBE1;background-color:#FFFFFF;}

.section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tr th{height:33px; line-height:33px;background-color:#FFFFFF;}

.section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody tr td{border-bottom:1px solid #E5EBE1;background-color:#FFFFFF;}

.section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-title{height:33px; line-height:33px; width:310px; text-indent:10px;white-space:nowrap; overflow:hidden;}

.section-tag  #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-title a{color:#000000;}

*html .section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-title{text-indent:10px;height:25px; line-height:25px; width:280px; white-space:nowrap; overflow:hidden;}

*html .section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-title a{color:#000000;}

.section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.active{ color:#32A442; font-size:12px; width:80px; white-space:nowrap; overflow:hidden;height:33px; line-height:33px;text-align:center;}

*html .section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.active{color:#32A442; font-size:12px; width:80px; white-space:nowrap; overflow:hidden;height:25px; line-height:25px;text-align:center;}

.section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-name a{color:#7d7d7d;}

.section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-field-best-answer-award-value{color:#32A442; background-image:url(images/youwenyouda_xuanshangfenshu.jpg); background-repeat:no-repeat; background-position:left; padding-left:30px; line-height:190%; overflow:hidden;}

.section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-name{color:#7d7d7d; font-size:12px;height:33px; line-height:33px;text-align:left;}

.section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-name a{color:#7d7d7d;}

.section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table tbody td.views-field-field-best-answer-award-value{color:#32A442; background-image:url(images/youwenyouda_xuanshangfenshu.jpg); background-repeat:no-repeat; background-position:left; padding-left:30px; line-height:190%; overflow:hidden;}

.section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table th.views-field-title{ font-size:14px;color:#000000; width:310px; white-space:nowrap; text-align:left; text-indent:10px;}

.section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table th.views-field-name,th.active{ font-size:14px; font-weight:700; color:#000000; font-weight:700; text-align:left;}

.section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table th.views-field-name a{color:#000000; font-size:14px;}

.section-tag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-table th.views-field-field-best-answer-award-value{font-size:14px;}

.section-tag #page #page-inner #main #main-inner #content #content-inner #content-header h1.title{

background-image:url(images/remph_titilebg.jpg);

background-repeat:no-repeat;

height:35px;

line-height:35px;

text-indent:36px;

clear:both;

font-size:14px;

color:#ffffff;

font-weight:700;}

.section-tag #page #page-inner #main #main-inner #content #content-inner #content-header{height:35px;background-image: url(images/video_titleall.jpg); line-height:35px;}

/*----section-tag-----*/



#chongzhichenggong{ width:974px; height:350px; margin:0 auto;}

#chongzhichenggong #chongzhichenggong-xianshi{width:449px; height:212px; margin:0 auto; margin-top:80px;}

#chongzhichenggong #jifentitletop{ width:449px; height:18px; background:url(images/jifentitle-top.jpg); background-repeat:no-repeat; margin-bottom:0px; padding-bottom:0px;}

#chongzhichenggong #chongzhichenggong-content{width:449px; height:179px; margin:0 auto;}

#chongzhichenggong #chongzhichenggong-content #chongzhichenggong-content1{float:left; background:url(images/jifencontent-middle1.jpg);width:11px;height:179px;background-repeat:no-repeat;}

#chongzhichenggong #chongzhichenggong-content #chongzhichenggong-content2{width:427px;float:left; background:url(images/jifencontent-middle2.jpg); background-repeat:repeat-x;height:179px;}

#chongzhichenggong #chongzhichenggong-content #chongzhichenggong-content3{float:left; background:url(images/jifencontent-middle3.jpg); width:11px;height:179px;background-repeat:no-repeat;}

#chongzhichenggong #chongzhichenggong-bottom{width:449px; height:15px; background:url(images/jifentitle-bottombg.jpg); background-repeat:no-repeat;} 

#chongzhichenggong #chongzhichenggong-content #chongzhichenggong-content2 #chonfzhichenggongtitle{font-weight:700px; width:320px; background:url(images/jiftitlebg.gif); background-repeat:no-repeat; margin:0 auto; text-align:center; height:35px; line-height:35px; color:#FFFFFF; font-size:14px; }

#chongzhichenggong #chongzhichenggong-content #chongzhichenggong-content2 #chonfzhichenggongtitle h1.title{ font-size:14px; color:#FFFFFF;  height:35px; margin-bottom:5px; line-height:30px;}

#chongzhichenggong #chongzhichenggong-content #chongzhichenggong-content2 #chonfzhichenggongtitle-bottom{ font-size:14px; text-align:center; width:100%; margin:0 auto; height:30px; margin-top:30px; margin-bottom:5px; line-height:30px;}

#chongzhichenggong #chongzhichenggong-content #chongzhichenggong-content2 #chonfzhichenggongtitle-bottom span{ font-weight:600; color:#FF0000;}

#chongzhichenggong #chongzhichenggong-content #chongzhichenggong-content2 #backindexbottom div{ width:400px; margin:0 auto; text-align:center; height:42px; line-height:42px; font-size:14px;}

#chongzhichenggong #chongzhichenggong-content #chongzhichenggong-content2 #backindexbottom div a{ font-weight:700;  margin-left:5px; margin-right:5px;color:#32A442;}

#chongzhichenggong #chongzhichenggong-content #chongzhichenggong-content2 #backindexbottom div #edit-submit-chongzh{ background:url(images/backindexbg.jpg); background-repeat:no-repeat; font-size:12px; color:#FFFFFF; width:71px; height:24px; border:none; font-weight:700;}



#chongzhichenggong #chongzhichenggong-content #chongzhichenggong-content2 #backindexbottomthree div{width:71px; height:24px;  margin:0 auto; text-align:center;line-height:24px; vertical-align:middle;background:url(images/backindexbg.jpg); background-repeat:no-repeat; }

*html #chongzhichenggong #chongzhichenggong-content #chongzhichenggong-content2 #backindexbottomthree div{width:71px; height:24px;  margin:0 auto; text-align:center;line-height:24px; vertical-align:middle;background:url(images/backindexbg.jpg); background-repeat:no-repeat; }

*+html #chongzhichenggong #chongzhichenggong-content #chongzhichenggong-content2 #backindexbottomthree div{ width:71px; height:24px;  margin:0 auto; text-align:center;line-height:24px; vertical-align:middle;background:url(images/backindexbg.jpg); background-repeat:no-repeat; }

#chongzhichenggong #chongzhichenggong-content #chongzhichenggong-content2 #backindexbottomthree div a{ font-size:12px;color:#FFFFFF; width:71px; height:24px; border:none; font-weight:700; text-decoration:none;}

/*---------tab------------*/



.section-user #page #page-inner #main #main-inner #content #content-inner #content-header .tabs {

      float:left;

      width:100%;

      font-size:93%;

	  overflow:hidden;

      }

.section-user #page #page-inner #main #main-inner #content #content-inner #content-header .tabs ul.primary {

height:22px;

	margin:0;

	padding:15px 10px 0 50px;

	overflow:hidden;

	list-style:none;

	overflow:hidden;

	border-bottom:#cccccc 1px solid;

	line-height:190%;

	overflow:hidden;

      }

.section-user #page #page-inner #main #main-inner #content #content-inner #content-header .tabs  ul.primary li {

display:table-row-group; 

      margin-left:4px;

      display:inline;

      margin:0;

      padding:0;

	  width:auto;

      }

.section-user #page #page-inner #main #main-inner #content #content-inner #content-header  .tabs ul.primary li a {

      margin-left:4px;

      float:left;

      background:url("images/tableftCleft.jpg") no-repeat left top;

      padding:0 0 0 4px;

      text-decoration:none;

	   background-color: transparent;

	     line-height:100%;

      }

.section-user #page #page-inner #main #main-inner #content #content-inner #content-header  .tabs ul.primary li a span.tab {

      font-size:12px;

      background:url("images/tabrightCright.jpg") no-repeat right top;

	   background-color: transparent;

      padding:5px 15px 4px 6px;

      color:#464E42;

	   line-height:100%;

      }

.section-user #page #page-inner #main #main-inner #content #content-inner #content-header  .tabs ul.primary li.active a {

  font-size:12px;

     margin-left:4px;

	 background-position:0% -42px;

	  color:#FFFFFF;

	    line-height:100%;

      }

.section-user #page #page-inner #main #main-inner #content #content-inner #content-header  .tabs ul.primary li.active a span.tab {

       background-position:100% -42px;

	   color:#FFFFFF;

	   font-size:12px;

	     line-height:100%;

      }

    /* Commented Backslash Hack hides rule from IE5-Mac \*/

.section-user #page #page-inner #main #main-inner #content #content-inner #content-header  .tabs ul.primary li a span.tab {float:none;  line-height:100%;}

    /* End IE5-Mac hack */

.section-user #page #page-inner #main #main-inner #content #content-inner #content-header  .tabs ul.primary li a:hover span.tab {

      color:#FFF;

	  font-size:12px;

	  line-height:100%;

      }

.section-user #page #page-inner #main #main-inner #content #content-inner #content-header  .tabs ul.primary li a:hover {

      background-position:0% -42px;

	  color:#FFFFFF;

	    line-height:100%;

      }

.section-user #page #page-inner #main #main-inner #content #content-inner #content-header  .tabs ul.primary li a:hover span.tab {

      background-position:100% -42px;

	  font-size:12px;

	  color:#FFFFFF;

	  line-height:100%;

      } 

.section-user #page #page-inner #main #main-inner #content #content-inner #content-header  .tabs ul.secondary li a span.tab{ font-size:12px;line-height:100%;}	  

.section-user #page #page-inner #main #main-inner #content #content-inner #content-header  .tabs ul.secondary li.active a span.tab{ font-size:12px; font-weight:700;line-height:100%;}	  

	  

	  

	  

	  /*--------search---------*/

.section-search #page #page-inner #main #main-inner #content #content-inner #content-header .tabs {

      float:left;

      width:100%;

      font-size:93%;

	  overflow:hidden;

      }

.section-search #page #page-inner #main #main-inner #content #content-inner #content-header .tabs ul.primary {

height:22px;

	margin:0;

	padding:15px 10px 0 50px;

	list-style:none;

	overflow:hidden;

	border-bottom:#cccccc 1px solid;

	line-height:190%;

	overflow:hidden;

      }

.section-search #page #page-inner #main #main-inner #content #content-inner #content-header .tabs  ul.primary li {

display:table-row-group; 

      margin-left:4px;

      display:inline;

      margin:0;

      padding:0;

	  width:auto;

      }

.section-search #page #page-inner #main #main-inner #content #content-inner #content-header  .tabs ul.primary li a {

      margin-left:4px;

      float:left;

      background:url("images/tableftCleft.jpg") no-repeat left top;

      padding:0 0 0 4px;

      text-decoration:none;

	   background-color: transparent;

	     line-height:100%;

      }

.section-search #page #page-inner #main #main-inner #content #content-inner #content-header  .tabs ul.primary li a span.tab {

      font-size:12px;

      background:url("images/tabrightCright.jpg") no-repeat right top;

	   background-color: transparent;

      padding:5px 15px 4px 6px;

      color:#464E42;

	  line-height:100%;

      }

.section-search #page #page-inner #main #main-inner #content #content-inner #content-header  .tabs ul.primary li.active a {

     margin-left:4px;

	 background-position:0% -42px;

	  color:#FFFFFF;

      }

.section-search #page #page-inner #main #main-inner #content #content-inner #content-header  .tabs ul.primary li.active a span.tab {

       background-position:100% -42px;

	   color:#FFFFFF;

	   font-size:12px;

	   line-height:100%;

      }

    /* Commented Backslash Hack hides rule from IE5-Mac \*/

.section-search #page #page-inner #main #main-inner #content #content-inner #content-header  .tabs ul.primary li a span.tab {float:none;line-height:100%;}

    /* End IE5-Mac hack */

.section-user #page #page-inner #main #main-inner #content #content-inner #content-header  .tabs ul.primary li a:hover span.tab {

      color:#FFF;

	  font-size:12px;

	  line-height:100%;

      }

.section-search #page #page-inner #main #main-inner #content #content-inner #content-header  .tabs ul.primary li a:hover {

      background-position:0% -42px;

	  color:#FFFFFF;

	  line-height:100%;

      }

.section-search #page #page-inner #main #main-inner #content #content-inner #content-header  .tabs ul.primary li a:hover span.tab {

      background-position:100% -42px;

	  font-size:12px;

	  line-height:100%;

	  color:#FFFFFF;

      } 

	  

/*-------video-------*/  

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-header{ display:none; line-height:0px; height:0px; font-size:0px;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_2{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;;border-top:none;}

*html .section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_2{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;;border-top:none; width:99.5%;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_2 .block-inner .h2Container{height:35px;background-image: url(images/video_titleall.jpg); z-index:1;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_2 .block-inner .h2Container .title{background-image:url(images/remph_titilebg.jpg);

background-repeat:no-repeat;

height:35px;

line-height:35px;

text-indent:30px;

clear:both;

font-size:14px;

color:#ffffff;

font-weight:700;

z-index:2;}



.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_1{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;;border-top:none;}

*html .section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_1{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;;border-top:none;width:99.5%;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_1 .block-inner .h2Container{height:35px;background-image: url(images/video_titleall.jpg); z-index:1;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_1 .block-inner .h2Container .title{background-image:url(images/remph_titilebg.jpg);

background-repeat:no-repeat;

height:35px;

line-height:35px;

text-indent:30px;

clear:both;

font-size:14px;

color:#ffffff;

font-weight:700;

z-index:2;}



.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_3{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;;border-top:none;}

*html .section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_3{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;;border-top:none;width:99.5%;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_3 .block-inner .h2Container{height:35px;background-image: url(images/video_titleall.jpg); z-index:1;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_3 .block-inner .h2Container .title{background-image:url(images/remph_titilebg.jpg);

background-repeat:no-repeat;

height:35px;

line-height:35px;

text-indent:30px;

clear:both;

font-size:14px;

color:#ffffff;

font-weight:700;

z-index:2;}



.section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;border-top:none;}

*html .section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;border-top:none; width:99.5%;}

.section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4 .block-inner .h2Container{

height:35px;

line-height:35px;

text-indent:10px;

clear:both;

background-image: url(images/video_titleall.jpg);

font-size:14px;

color:#32A442;

font-weight:700;

border:none;

}







.section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;border-top:none; width:99.5%;}

.section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .block-inner .h2Container{

height:35px;

line-height:35px;

text-indent:10px;

clear:both;

background-image: url(images/video_titleall.jpg);

font-size:14px;

color:#32A442;

font-weight:700;

}



.section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list{ clear:both; width:100%;}

.section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list ul li{ clear:both; width:100%; word-break:keep-all; overflow:hidden; line-height:22px;}

.section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list .views-field-counter{width:20px; float:left; margin-left:10px;}

.section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list .views-field-counter .field-content{ font-size:12px;}

.section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list .views-field-title{ width:300px; float:right;}

.section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list .views-field-title .field-content{font-size:12px;}

.section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .more-link{ clear:both; width:380px; float:left;}

.section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list{ clear:both; width:100%;}

*html .section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list ul li{ clear:both; width:100%; word-break:keep-all; overflow:hidden; line-height:22px;}

*html .section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list .views-field-counter{width:15px; float:left; margin-left:5px;}

*html .section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list .views-field-title{width:300px; float:right;}



.section-shipin #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;border-top:none; width:99.5%;}

.section-shipin #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4 .block-inner .h2Container{

height:35px;

line-height:35px;

text-indent:10px;

clear:both;

background-image: url(images/video_titleall.jpg);

font-size:14px;

color:#32A442;

font-weight:700;

border:none;

}







.section-shipin #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;border-top:none; width:99.5%;}

.section-shipin #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .block-inner .h2Container{

height:35px;

line-height:35px;

text-indent:10px;

clear:both;

background-image: url(images/video_titleall.jpg);

font-size:14px;

color:#32A442;

font-weight:700;

}



.section-shipin #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list{ clear:both; width:100%;}

.section-shipin #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list ul li{ clear:both; width:100%; word-break:keep-all; overflow:hidden; line-height:22px;}

.section-shipin #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list .views-field-counter{width:20px; float:left; margin-left:10px;}

.section-shipin #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list .views-field-title{width:300px;float:right;}

.section-shipin #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .more-link{ clear:both; width:380px; float:left;}

.section-shipin #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list{ clear:both; width:100%;}

*html .section-shipin #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list ul li{ clear:both; width:100%; word-break:keep-all; overflow:hidden; line-height:22px;}

*html .section-shipin #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list .views-field-counter{width:15px; float:left; margin-left:5px;}

*html .section-shipin #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list .views-field-title{width:300px; float:right;}





.section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4 .block-inner .content{width:310px; margin:0 auto; margin-bottom:10px; margin-left:10px;}

.section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4 .block-inner .content ul{ width:270px; margin:0 auto; margin-left:20px;}

.section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4 .block-inner .content ul li a{ color:#000000; font-size:12px; line-height:22px;}

.section-duomeiti #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4 .block-inner .content ul li ul li a{ color:#666666; font-size:12px; line-height:22px;}



.section-shipin #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4 .block-inner .content{width:310px; margin:0 auto; margin-bottom:10px; margin-left:10px;}

.section-shipin #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4 .block-inner .content ul{ width:270px; margin:0 auto; margin-left:20px;}

.section-shipin #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4 .block-inner .content ul li a{ color:#000000; font-size:12px; line-height:22px;}

.section-shipin #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4 .block-inner .content ul li ul li a{ color:#666666; font-size:12px; line-height:22px;}





.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-header{ display:none; line-height:0px; height:0px; font-size:0px;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_4{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;;border-top:none;}

*html .section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_4{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;;border-top:none; width:99.5%;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_4 .block-inner .h2Container{height:35px;background-image: url(images/video_titleall.jpg);}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_4 .block-inner .h2Container .title{background-image:url(images/remph_titilebg.jpg);

background-repeat:no-repeat;

height:35px;

line-height:35px;

text-indent:30px;

clear:both;

font-size:14px;

color:#ffffff;

font-weight:700;

}







.section-shipin #page #page-inner #main #main-inner #content{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;;border-top:none;}

.section-shipin #page #page-inner #main #main-inner #content #content-inner{ margin-bottom:10px;}

.section-shipin #page #page-inner #main #main-inner #content #content-inner #content-header{height:35px;background-image: url(images/video_titleall.jpg); z-index:1;}

.section-shipin #page #page-inner #main #main-inner #content #content-inner #content-header  h1.title{background-image:url(images/remph_titilebg.jpg);

background-repeat:no-repeat;

height:35px;

line-height:35px;

text-indent:30px;

clear:both;

font-size:14px;

color:#ffffff;

font-weight:700;

z-index:2;}



.section-shipin #page #page-inner #main #main-inner #content #content-inner #content-area .view-shipin-almost-all .view-content .item-list ul{margin:0 auto; text-align:center;}

.section-shipin #page #page-inner #main #main-inner #content #content-inner #content-area .view-shipin-almost-all .view-content .item-list ul li{width:135px; margin-bottom:10px; margin-top:10px; margin-left:15px; float:left;}

*html .section-shipin #page #page-inner #main #main-inner #content #content-inner #content-area .view-shipin-almost-all .view-content .item-list ul li{width:135px; margin-bottom:10px; margin-top:10px; margin-left:15px; float:left;}



.section-shipin #page #page-inner #main #main-inner #content #content-inner #content-area .view-shipin-almost-all .view-content .item-list ul li .views-field-field-shipin-cover-fid{ width:135px; height:77px;text-align:left; margin:0 auto;}



.section-shipin #page #page-inner #main #main-inner #content #content-inner #content-area .view-shipin-almost-all .view-content .item-list ul li .views-field-field-shipin-cover-fid img{border:#cdcbcc 1px solid;}

*html .section-shipin #page #page-inner #main #main-inner #content #content-inner #content-area .view-shipin-almost-all .view-content .item-list ul li .views-field-field-shipin-cover-fid img{border:#cdcbcc 1px solid; display:block;}

*html .section-shipin #page #page-inner #main #main-inner #content #content-inner #content-area  .view-shipin-almost-all item-list{ width:100%; text-align:center;}

*html .section-shipin #page #page-inner #main #main-inner #content #content-inner #content-area  .view-shipin-almost-all item-list ul{ margin:0 auto; width:380px;}

.section-shipin #page #page-inner #main #main-inner #content #content-inner #content-area .view-shipin-almost-all .view-content .item-list ul li .views-field-title{line-height:20px;width:135px;white-space:nowrap; word-break:keep-all; overflow:hidden; text-overflow:ellipsis; text-align:left;}

*html .section-shipin #page #page-inner #main #main-inner #content #content-inner #content-area .view-shipin-almost-all .view-content .item-list ul li .views-field-title{ line-height:20px; height:20px;width:135px; text-align:left;}

*html .section-shipin #page #page-inner #main #main-inner #content #content-inner #content-area .view-shipin-almost-all .view-content .item-list ul li .views-field-title .field-content{ line-height:20px;width:135px;white-space:nowrap; word-break:keep-all; overflow:hidden; text-overflow:ellipsis; text-align:left;}

*+html .section-shipin #page #page-inner #main #main-inner #content #content-inner #content-area .view-shipin-almost-all .view-content .item-list ul li .views-field-title{ line-height:20px;width:135px;white-space:nowrap; word-break:keep-all; overflow:hidden; text-overflow:ellipsis; text-align:left;}





.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_2 .block-inner .content .view-dom-id-2 .view-content .item-list ul{margin:0 auto; text-align:center;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_2 .block-inner .content .view-dom-id-2 .view-content .item-list ul li{width:135px; margin-bottom:10px; margin-top:10px; margin-left:13px; float:left;}

*html .section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_2 .block-inner .content .view-dom-id-2 .view-content .item-list ul li{width:135px; margin-bottom:10px; margin-top:10px; margin-left:10px; float:left;}





.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_2 .block-inner .content .view-dom-id-2 .more-link{ clear:both; margin-bottom:10px;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_2 .block-inner .content .view-dom-id-2 .view-content .item-list ul li .views-field-field-shipin-cover-fid{ width:135px; height:77px; text-align:left;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_2 .block-inner .content .view-dom-id-2 .view-content .item-list ul li .views-field-field-shipin-cover-fid img{border:#cdcbcc 1px solid;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_2 .block-inner .content .view-dom-id-2 .view-content .item-list ul li .views-field-title{ line-height:20px;width:135px;white-space:nowrap; word-break:keep-all; overflow:hidden; text-overflow:ellipsis; text-align:left;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_1 .block-inner .content .view-dom-id-3 .view-content .item-list ul{margin:0 auto; text-align:center;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_1 .block-inner .content .view-dom-id-3 .view-content .item-list ul li{width:135px; margin-bottom:10px; margin-top:10px; margin-left:15px; float:left;}

*html .section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_1 .block-inner .content .view-dom-id-3 .view-content .item-list ul li{width:135px; margin-bottom:10px; margin-top:10px; margin-left:10px; float:left;}



.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_1 .block-inner .content .view-dom-id-3 .more-link{ clear:both; margin-bottom:10px;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_1 .block-inner .content .view-dom-id-3 .view-content .item-list ul li .views-field-field-shipin-cover-fid{ width:135px; height:77px; text-align:left}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_1 .block-inner .content .view-dom-id-3 .view-content .item-list ul li .views-field-field-shipin-cover-fid img{border:#cdcbcc 1px solid;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_1 .block-inner .content .view-dom-id-3 .view-content .item-list ul li .views-field-title{ line-height:20px;width:135px;white-space:nowrap; word-break:keep-all; overflow:hidden; text-overflow:ellipsis; text-align:left;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_3 .block-inner .content .view-dom-id-4 .view-content .item-list ul{margin:0 auto; text-align:center;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_3 .block-inner .content .view-dom-id-4 .view-content .item-list ul li{width:135px; margin-bottom:10px; margin-top:10px; margin-left:15px; float:left;}

*html .section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_3 .block-inner .content .view-dom-id-4 .view-content .item-list ul li{width:135px; margin-bottom:10px; margin-top:10px; margin-left:10px; float:left;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_3 .block-inner .content .view-dom-id-4 .more-link{ clear:both; margin-bottom:10px;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_3 .block-inner .content .view-dom-id-4 .view-content .item-list ul li .views-field-field-shipin-cover-fid{ width:135px; height:77px;text-align:left;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_3 .block-inner .content .view-dom-id-4 .view-content .item-list ul li .views-field-field-shipin-cover-fid img{border:#cdcbcc 1px solid; }

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_3 .block-inner .content .view-dom-id-4 .view-content .item-list ul li .views-field-title{ line-height:20px;width:135px;white-space:nowrap; word-break:keep-all; overflow:hidden; text-overflow:ellipsis; text-align:left;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_4 .block-inner{ margin-bottom:30px;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_4 .block-inner .content .view-shipin-almost-all .view-content .item-list ul{margin:0 auto;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_4 .block-inner .content .view-shipin-almost-all .view-content .item-list ul li{ width:280px; float:left; margin-top:10px; margin-bottom:10px; margin-left:20px;}

*html .section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_4 .block-inner .content .view-shipin-almost-all .view-content .item-list ul li{ width:280px; float:left; margin-top:10px; margin-bottom:10px; margin-left:10px; height:90px;}



.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_4 .block-inner .content .view-shipin-almost-all .view-content .item-list ul li .views-field-name{ width:145px; float:right;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_4 .block-inner .content .view-shipin-almost-all .view-content .item-list ul li .views-field-name .field-content a{ font-weight:700; font-size:12px; color:#000000;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_4 .block-inner .content .view-shipin-almost-all .view-content .item-list ul li .views-field-field-shipin-cover-fid{width:120px; float:left; text-align:center;}

*html .section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_4 .block-inner .content .view-shipin-almost-all .view-content .item-list ul li .views-field-field-shipin-cover-fid{width:110px; float:left; text-align:center;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_4 .block-inner .content .view-shipin-almost-all .view-content .item-list ul li .views-field-field-shipin-cover-fid .field-content a img{}



.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_4 .block-inner .content .view-shipin-almost-all .view-content .item-list ul li .views-field-description{width:145px; float:right;height:60px;}

*html .section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_4 .block-inner .content .view-shipin-almost-all .view-content .item-list ul li .views-field-description{width:145px; float:right; height:60px;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_4 .block-inner .content .view-shipin-almost-all .view-content .item-list ul li .views-field-description .field-content p{width:145px;height:60px;line-height:20px;}

*HTML .section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_4 .block-inner .content .view-shipin-almost-all .view-content .item-list ul li .views-field-description .field-content{width:145px;height:60px;line-height:20px;word-wrap:break-word; white-space:normal; overflow:hidden;}

*html .section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-shipin_almost_all-block_4 .block-inner .content .view-shipin-almost-all .view-content .item-list ul li .views-field-description .field-content p{line-height:22px;line-height:20px;word-wrap:break-word; white-space:normal; overflow:hidden;height:60px;width:145px;height:60px;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom .block-views .block-inner .content .view-shipin-almost-all .more-link a{ color:#000000;}

.section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom .block-views .block-inner .content .view-shipin-almost-all .more-link{

background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

width:75px;

height:35px;

line-height:34px;

padding-top:2px;

text-align:center;

float:right;

margin-top:-151px;}

*html .section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom .block-views .block-inner .content .view-shipin-almost-all .more-link{background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

width:75px;

height:35px;

line-height:34px;

padding-top:2px;

text-align:center;

float:right;

margin-top:-147px;

position:absolute;

margin-left:530px;}

*+html .section-duomeiti #page #page-inner #main #main-inner #content #content-inner #content-bottom .block-views .block-inner .content .view-dom-id-2 .more-link{background-image:url(images/class_more.jpg);

background-position:center top;

background-repeat:no-repeat;

clear:both;

width:75px;

height:35px;

line-height:34px;

padding-top:2px;

text-align:center;

float:right;

margin-top:-151px;

position:absolute;

margin-left:540px;}







.section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;border-top:none; width:99.5%;}

.section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4 .block-inner .h2Container{

height:35px;

line-height:35px;

text-indent:10px;

clear:both;

background-image: url(images/video_titleall.jpg);

font-size:14px;

color:#32A442;

font-weight:700;

border:none;

}



.section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4 .block-inner .content{width:310px; margin:0 auto; margin-bottom:10px; margin-left:10px;}

.section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4 .block-inner .content ul{ width:270px; margin:0 auto; margin-left:20px;}

.section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4 .block-inner .content ul li a{ color:#000000; font-size:12px; line-height:22px;}

.section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4 .block-inner .content ul li ul li a{ color:#666666; font-size:12px; line-height:22px;}



.section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4 .block-inner .content{width:310px; margin:0 auto; margin-bottom:10px; margin-left:10px;}

.section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4 .block-inner .content ul{ width:270px; margin:0 auto; margin-left:20px;}

.section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4 .block-inner .content ul li a{ color:#000000; font-size:12px; line-height:22px;}

.section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-taxonomyblocks-4 .block-inner .content ul li ul li a{ color:#666666; font-size:12px; line-height:22px;}

.section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6{border-right:#D1D1D1 1px solid;border-left:#D1D1D1 1px solid;border-bottom:#D1D1D1 1px solid;border-top:none; width:99.5%;}

.section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .block-inner .h2Container{

height:35px;

line-height:35px;

text-indent:10px;

clear:both;

background-image: url(images/video_titleall.jpg);

font-size:14px;

color:#32A442;

font-weight:700;

}

.section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list{ clear:both; width:100%;}

.section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list ul li{ clear:both; width:100%; word-break:keep-all; overflow:hidden; line-height:22px;}

.section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list .views-field-counter{width:20px; float:left; margin-left:10px;}

.section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list .views-field-title{ width:300px; float:right;}

.section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .more-link{ clear:both; width:380px; float:left;}

.section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list{ clear:both; width:100%;}

*html .section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list ul li{ clear:both; width:100%; word-break:keep-all; overflow:hidden; line-height:22px;}

*html .section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list .views-field-counter{width:15px; float:left; margin-left:5px;}

*html .section-mtag #page #page-inner #main #main-inner #sidebar-right #sidebar-right-inner #block-views-shipin_almost_all-block_6 .content .view-content .item-list .views-field-title{width:300px; float:right;}



/*---------sanji*/

.section-mtag #page #page-inner #main #main-inner #content #content-inner #content-header{height:35px;background-image: url(images/video_titleall.jpg);height:35px;}

.section-mtag #page #page-inner #main #main-inner #content #content-inner #content-header h1.title{

margin-left:20px;

height:35px;

line-height:35px;

clear:both;

font-size:14px;

color:#ffffff;

font-weight:700;}

.section-mtag #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-left{background-image: url(images/yuedu-title-left.jpg); background-repeat:no-repeat;height:35px;width:12px;display:block; float:left;}

.section-mtag #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-content{background-image: url(images/yuedu-title-content.jpg); background-repeat:repeat-x;height:35px;line-height:35px;display:block; float:left;}

.section-mtag #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-right{background-image: url(images/yuedu-title-right.jpg); background-repeat:no-repeat;height:35px; width:13px;display:block; float:left;}





.section-mtag #page #page-inner #main #main-inner #content{border:1px solid #E5EBE1; border-top:none; width:610px;}

.section-mtag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row{ width:600px; margin:0 auto; margin-top:10px; clear:both;}

*html .section-mtag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row{ width:600px; margin:0 auto; margin-top:5px; clear:both;}

.section-mtag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row .views-field-field-shipin-cover-fid{ width:120px; height:95px;float:left;}

.section-mtag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row .views-field-field-shipin-cover-fid img{ margin:10px;}

.section-mtag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row .views-field-title{ width:450px; float:right;font-size:12px;}

.section-mtag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row .views-field-field-shipin-neirong-value{ width:450px; float:right; overflow:hidden; word-spacing:normal;}

.section-mtag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row .views-field-title .field-content{ font-weight:700; line-height:22px; font-size:12px;}

.section-mtag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row .views-field-field-shipin-neirong-value label{}



.section-mtag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row .views-field-field-shipin-neirong-value .field-content{ color:#666666;width:440px; height:60px; line-height:20px;word-wrap:break-word; white-space:normal; overflow:hidden; font-size:12px;}

.section-mtag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row .views-field-field-shipin-neirong-value .field-content p{ text-indent:25px;}

.section-mtag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row .views-field-field-shipin-neirong-value .field-content h2{ font-size:12px;line-height:20px; }

.section-mtag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .views-row .views-field-field-shipin-neirong-value .field-content p{font-size:12px;}

.section-mtag #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .item-list .pager{ margin:0 auto;}



.section-media #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-shipin .node-inner .content #shipin-tab_area{border:#32A442 3px solid;clear: both;height:100%}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-shipin .node-inner .content #shipin-tab_area #shipin_area{width:380px; float:left; margin-top:20px; margin-left:10px;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-shipin .node-inner .content #shipin-tab_area #shipin_area .field-field-shipin-upload{margin:0 auto; width:370px;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-shipin .node-inner .content #shipin-tab_area #shipin_area .field-field-shipin-neirong{margin:0 auto; width:370px;}

 

.section-media #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-shipin .node-inner .content #shipin-tab_area #tab_area{ width:540px;float:left; margin-top:20px; margin-left:20px;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-shipin .node-inner .content #shipin-tab_area #tab_area .shipin-tabs{ width:530px; margin:0 auto;} 



.section-media #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-shipin .node-inner .content ul.links{clear:both;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-header .title{ font-size:14px; color:#000000; font-weight:700;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-shipin .node-inner .meta{ text-align:right;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-shipin .node-inner .meta .terms-inline ul li a{color:#32A442;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-shipin .node-inner .content #shipin-tab_area #tab_area .shipin-panes div{ width:490px; margin:0 auto;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-shipin .node-inner .content #shipin-tab_area #tab_area .shipin-panes{border-top:0px;border-right:1px #cccccc solid; border-bottom:1px #cccccc solid; border-left:1px #cccccc solid;width:508px; margin:0 auto;

 margin-bottom:20px;

padding-right: 10px; 

overflow-y: auto; 

padding-left: 10px; 

padding-bottom: 0px; 

overflow:auto;

line-height: 100%; 

padding-top: 0px; 

font-family: 宋体; 

letter-spacing: 1pt; 

height:530px;

text-align: left; 

background-repeat: no-repeat;

}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-shipin .node-inner .content #shipin-tab_area #tab_area .shipin-panes div p{line-height:22px; font-size:14px;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-shipin .node-inner .content #shipin-tab_area #shipin_area .field-field-shipin-neirong .field-items{

padding-right: 10px; 

overflow-y: auto; 

padding-left: 10px; 

padding-bottom: 0px; 

overflow:auto;

width: 350px; 

line-height: 100%; 

padding-top: 0px; 

font-family: 宋体; 

letter-spacing: 1pt; 

height:250px;

text-align: left; 

background-repeat: no-repeat;}



.section-media #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-shipin .node-inner .content #shipin-tab_area #shipin_area .field-field-shipin-neirong .field-items .field-item p{ line-height:22px;font-size:14px;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-shipin .node-inner .content #shipin-tab_area  #shipin_area .field-field-shipin-upload h3.field-label{ font-size:14px; font-weight:700;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-area .node-type-shipin .node-inner .content #shipin-tab_area  #shipin_area .field-field-shipin-neirong h3.field-label{ font-size:14px; font-weight:700;}



.section-media #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-header{ font-size:14px; font-weight:700; height:30px; margin-top:10px; margin-bottom:10px;line-height:30px;background-color:#F6F8F3; text-indent:10px;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-comment-blog{ width:970px; margin:0 auto;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .indented{ width:970px; margin:0 auto;}



.section-media #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-comment-blog .node-inner .picture{float:left;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-comment-blog .node-inner .picture img{ margin:0 auto;width:50px; height:50px;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-comment-blog .node-inner h2.title{ float:right; width:910px; HEIGHT:22px; line-height:22px;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-comment-blog .node-inner .meta{float:right; width:910px; HEIGHT:22px; line-height:22px;color:#666666;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-comment-blog .node-inner .content{clear:both; width:900px; margin-left:60px;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-comment-blog .node-inner .content p{ font-size:12px; color:#000000;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-comment-blog .node-inner ul.links{}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-comment-blog .node-inner ul.links li{ height:22px; line-height:22px;}

.section-media #page #page-inner #main #main-inner #content #content-inner #content-bottom #block-views-nodecomments_threaded-block_1 .block-inner .content .view-dom-id-1 .view-content .node-type-comment-blog .node-inner ul.links li a{ float:right;color:#32A441;}



/*-------video-------*/  



.section-user #page #page-inner #main #main-inner #content #content-inner #content-area  table.sticky-table{ position:relative !important; clear:both;}



/* for duhougan --- bxy */



.view-duhougan-nodecomments .view-content{

float:left;

}





.view-duhougan-nodecomments .view-header {

font-size: 16px;

font: bold;

}



/* duhougan taxonomy */



/* .section-taxonomy #page #page-inner #main #main-inner  #content #content-inne #content-area .view-dom-id-1 .view-content .item-list ul li .views-field-field-yuedu-summary-value .field-content{float:left; height:100px; line-height:30px;word-wrap:break-word; margin-left:5px; margin-right:5px; text-indent:26px;}

*html .section-taxonomy #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-field-yuedu-summary-value .field-content{float:left; height:100px; line-height:30px;word-wrap:break-word; margin-left:5px; margin-right:5px; text-indent:26px;}

.section-taxonomy #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-field-yuedu-summary-value .field-content{float:left; height:115px; line-height:30px;word-wrap:break-word; text-indent:26px; width:460px;}

*html .section-taxonomy #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-field-yuedu-summary-value .field-content{float:left; height:115px; line-height:30px;word-wrap:break-word; margin-left:5px; margin-right:5px; text-indent:26px;}

*+html .section-taxonomy #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-field-yuedu-summary-value .field-content{float:left; height:115px; line-height:30px;word-wrap:break-word; text-indent:26px; width:465px;}

*/

.section-taxonomy #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li{width:600px;}

*html .section-taxonomy #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li {width:600px;}

*+html .section-taxonomy #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li {width:600px;}

*html .section-taxonomy #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-title{ width:450px;}

*html .section-taxonomy #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-title .field-content{width:450px;}

*html .section-taxonomy #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-title span.field-content a{line-height:25px; width:450px; height:25px; display:inline;white-space:nowrap;}

*html .section-taxonomy #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-field-yuedu-author-value{ width:450px;}

*html .section-taxonomy #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-field-yuedu-isbn-value{ width:450px;}

*html .section-taxonomy #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li.views-row .views-field-field-yuedu-isbn-value{ width:450px;}





.section-taxonomy #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .item-list ul.pager .pager-item { margin-left:5px;}



.section-taxonomy  #main #main-inner #content  #content-inner #content-header,

.section-my-duhougan #main #main-inner #content  #content-inner #content-header,

.section-fenlei #main #main-inner #content  #content-inner #content-header,

.section-list-all-duhougan-orig #main #main-inner #content  #content-inner #content-header,

.page-all-duhougan #main #main-inner #content  #content-inner #content-header

{height:35px;background-image: url(images/video_titleall.jpg); line-height:35px;}



.section-taxonomy  #main #main-inner #content,

.section-fenlei #main #main-inner #content,

.section-my-duhougan #main #main-inner #content,

.section-list-all-duhougan-orig #main #main-inner #content,

.page-all-duhougan #main #main-inner #content

{border:#D1D1D1 1px solid;width:610px; border-top:none;}



.section-taxonomy  #main #main-inner #content #content-inner #content-header,

.section-fenlei  #main #main-inner #content #content-inner #content-header,

.section-my-duhougan  #main #main-inner #content #content-inner #content-header,

.section-list-all-duhougan-orig  #main #main-inner #content #content-inner #content-header,

.page-all-duhougan  #main #main-inner #content #content-inner #content-header

{ border:none; border:0px;}



.section-taxonomy  #main #main-inner #content  #content-inner #content-header .title,

.section-fenlei #main #main-inner #content  #content-inner #content-header .title,

.section-my-duhougan #main #main-inner #content  #content-inner #content-header .title,

.section-list-all-duhougan-orig #main #main-inner #content  #content-inner #content-header .title,

.page-all-duhougan #main #main-inner #content  #content-inner #content-header .title{

margin-left:15px;

height:35px;

line-height:35px;

clear:both;

font-size:14px;

color:#ffffff;

font-weight:700;}



.section-taxonomy  #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-left,

.section-fenlei  #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-left,

.section-my-duhougan  #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-left,

.section-list-all-duhougan-orig  #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-left,

.page-all-duhougan  #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-left

{background-image: url(images/yuedu-title-left.jpg); background-repeat:no-repeat;height:35px;width:12px;display:block; float:left;}



.section-taxonomy  #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-content,

.section-fenlei  #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-content,

.section-my-duhougan  #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-content

.section-list-all-duhougan-orig  #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-content,

.page-all-duhougan  #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-content

{background-image: url(images/yuedu-title-content.jpg); background-repeat:repeat-x;height:35px;line-height:35px;display:block; float:left;}



.section-taxonomy  #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-right,

.section-fenlei  #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-right,

.section-my-duhougan  #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-right,

.section-list-all-duhougan-orig  #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-right,

.page-all-duhougan  #page #page-inner #main #main-inner #content #content-inner #content-header h1.title .title-right

{background-image: url(images/yuedu-title-right.jpg); background-repeat:no-repeat;height:35px; width:13px;display:block; float:left;}







.section-taxonomy #content .view-content .views-field-field-yuedu-cover-fid{

float:left;

margin-right:25px;

text-align:center;

width:100px;

}



.section-taxonomy #page #page-inner #main #main-inner #content #content-inner #content-area .view-dom-id-1 .view-content .item-list ul li {

width:600px;

}

.section-taxonomy #content .view-content .item-list ul li {

border-bottom:1px dashed #DDDDDD;

clear:both;

color:#666666;

float:left;

line-height:180%;

margin:0 auto;

overflow:hidden;

padding:10px 0 20px 10px;

width:603px;

}

#sidebar-right .view-duhougan .views-field-field-yuedu-cover-fid  {

float:left;

width:120px;

}



#sidebar-right #block-views-duhougan-block_2 .view-duhougan .item-list ul li {

height:10px; 

list-style-image:none;

list-style-position:outside;

list-style-type:none;

margin:0;

padding:10px;

}



#sidebar-right #block-views-duhougan-block_1 .view-duhougan .item-list ul li {

height:170px;

list-style-image:none;

list-style-position:outside;

list-style-type:none;

margin:0;

padding:5px 10px;

width:335px;

}





/* addtional (readthink)*/





.view-duhougan-taxonomy-term ul li.views-row{

    position:relative;

    float:left;

    height:210px;

    padding:15px 0;

	width:99%;

    border-bottom:1px dashed #DDDDDD;

	padding:10px 0 20px 10px;

	width:600px;

	line-height:180%;

}

#content-area .view-duhougan-taxonomy-term .item-list ul li .views-field-view-node span.field-content a  {

color:#FF0000;

position:absolute;

bottom:15px;

left:520px;

padding-right:15px;

}

#content-area .view-duhougan-taxonomy-term .item-list ul li .views-field-title .field-content a  {

color:#000000;

font-weight:700;

}

#content-area .view-duhougan-taxonomy-term .item-list ul li .views-field-title .field-content a:hover{

    color:#666;

}



#content-area .view-duhougan-taxonomy-term .item-list ul li .view-duhougan-taxonomy-term ul li.views-row{

margin-top: 5px;

line-height: 16px;

}



.view-duhougan-taxonomy-term li .views-field-field-yuedu-summary-value .field-content{

	text-indent:2em;

}

.view-duhougan-taxonomy-term .item-list li.views-row .views-field-title,

.view-duhougan-taxonomy-term .item-list li.views-row .views-field-field-yuedu-author-value,

.view-duhougan-taxonomy-term .item-list li.views-row .views-field-field-yuedu-isbn-value,

.view-duhougan-taxonomy-term .item-list li.views-row .views-field-field-yuedu-summary-value,

.view-duhougan-taxonomy-term .item-list li.views-row .views-field-tid,

.view-duhougan-taxonomy-term .item-list li.views-row > a

{

	width:460px;

	float:right;

	margin-right:10px;

}

.view-duhougan-taxonomy-term ul.pager{

	width:610px;

}

.view-duhougan-taxonomy-term ul .views-field-field-yuedu-cover-fid img{

    float:left;

    margin-right:25px;

	width:100px;

	padding-top:5px;

}

.li_hover{

	background:#F1F1F1;

}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-nodehierarchy-children-list .view-content .views-table {

background-color:#FFFFFF;

border:1px solid #E5EBE1;

margin:0 10px;

width:600px;

}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-nodehierarchy-children-list .view-content .views-table tbody tr td  {

	border:none;

}

.view-nodehierarchy-children-list thead th {

border-bottom:none;

}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .content .view-nodehierarchy-children-list .view-content .views-field-title  {

float:none;

padding:0 10px;

}

.view-nodehierarchy-children-list {

}

.section-node #page #page-inner #main #main-inner #content #content-inner .view-nodehierarchy-children-list .view-header p{

background-image:url("images/video_titleall.jpg");

clear:both;

color:#32A442;

font-size:12px;

font-weight:700;

height:35px;

line-height:190%;

text-indent:26px;

font-size:12px;

}

.section-node #page #page-inner #main #main-inner #content #content-inner #content-area .view-nodehierarchy-children-list {

background-color:#FFFFFF;

border-bottom:1px solid #D1D1D1;

border-left:1px solid #D1D1D1;

border-right:1px solid #D1D1D1;

margin:6px 0;

vertical-align:top;

width:99.8%;

}

ul.links.inline  {

padding-left:5px;

}

.view-all-duhougan .view-content .views-table,

.view-users-duhougan .view-content .views-table,

.view-duhougan-all-children .view-content .views-table{

background-color:#FFFFFF;

border:medium none;

margin-left:8px;

width:600px;

}

.view-all-duhougan .view-content .views-table tr th,

.view-users-duhougan .view-content .views-table tr th,

.view-duhougan-all-children .view-content .views-table tr th{

background-color:#FFFFFF;

height:33px;

line-height:33px;

font-size:14px;

}

.view-all-duhougan .view-content .views-field-title,

.view-users-duhougan .view-content .views-field-title,

.view-duhougan-all-children .view-content .views-field-title{

color:#000000;

font-size:14px;

text-align:left;

text-indent:10px;

white-space:nowrap;

width:230px;

}

.view-all-duhougan .view-content .views-table tr,

.view-users-duhougan .view-content .views-table tr,

.view-duhougan-all-children .view-content .views-table tr{

background-color:#FFFFFF;

border-bottom:2px solid #E5EBE1;

}

.view-all-duhougan .view-content .views-table tbody td.views-field-title,

.view-users-duhougan .view-content .views-table tbody td.views-field-title,

.view-duhougan-all-children .view-content .views-table tbody td.views-field-title{

height:33px;

line-height:33px;

overflow:hidden;

text-indent:10px;

white-space:nowrap;

width:230px;

}

.view-all-duhougan .view-content .views-table tbody td.views-field-name,

.view-users-duhougan .view-content .views-table tbody td.views-field-name,

.view-duhougan-all-children .view-content .views-table tbody td.views-field-name{

color:#7D7D7D;

font-size:12px;

height:33px;

line-height:33px;

text-align:left;

width:90px;

}

.view-all-duhougan .view-content .views-table tbody td.views-field-tid,

.view-users-duhougan .view-content .views-table tbody td.views-field-tid,

.view-duhougan-all-children .view-content .views-table tbody td.views-field-tid{

	width:120px;

}

.view-all-duhougan .view-content .views-table tbody td.views-field-timestamp,

.view-users-duhougan .view-content .views-table tbody td.views-field-timestamp,

.view-duhougan-all-children .view-content .views-table tbody td.views-field-timestamp{

	width:140px;

}

.view-all-duhougan .view-footer,

.view-users-duhougan .view-footer,

.view-duhougan-all-children .view-footer{

	font-weight:bold;

	font-size:14px;

	color:#32A444;

	width:610px;

	margin:10px 0;

	padding-left:8px;

}



.section-taxonomy #main #main-inner #content,

.section-fenlei #main #main-inner #content{

border-color:-moz-use-text-color #D1D1D1 #D1D1D1;

border-right:1px solid #D1D1D1;

border-style:none solid solid;

border-width:medium 1px 1px;

width:610px;

}

#edit-field-dhg-zhengwen-0-value-wrapper .resizable-textarea{

	margin-top:10px;

}

#views-exposed-form-duhougan-taxonomy-term-page-2 .views-exposed-widget,

#views-exposed-form-all-duhougan-page-1 .views-exposed-widget{

	float:left;

	display:inline;

	margin-right:20px;

}

#views-exposed-form-duhougan-taxonomy-term-page-2 .views-exposed-form,

#views-exposed-form-all-duhougan-page-1 .views-exposed-form{

	margin-left:10px;

	margin-top:15px;

}

#edit-submit-duhougan-taxonomy-term,

#edit-submit-all-duhougan{

	margin-top:1em;

}

#views-exposed-form-all-duhougan-page-1 .hierarchical-select-wrapper{

	margin:0;

}



/* addtional */

.title-content{background-image: url(images/yuedu-title-content.jpg); background-repeat:repeat-x;height:35px;line-height:35px;display:block; float:left;}

#content-area  {

min-height:500px;

height:auto !important;

height:500px;

}

li.login_duhougan a{

-moz-border-radius:5px 5px 5px 5px;

-moz-box-shadow:0 1px 3px rgba(0, 0, 0, 0.5);

background:none repeat scroll 0 0 #FF5C00;

border-color:-moz-use-text-color -moz-use-text-color rgba(0, 0, 0, 0.25);

border-style:none none solid;

border-width:medium medium 1px;

color:#FFFFFF;

cursor:pointer;

display:inline-block;

font-size:12px;

line-height:1;

padding:6px 14px 5px;

position:relative;

text-decoration:none;

text-shadow:0 -1px 1px rgba(0, 0, 0, 0.25);

}

li.login_duhougan a:hover{

background:#ffb515;

}

#confirm_message .confirm-links li{

	margin:10px 0;

	list-style:none;

	

}

#confirm_message .confirm-links li a{

-moz-border-radius:5px 5px 5px 5px;

-moz-box-shadow:0 1px 3px rgba(0, 0, 0, 0.5);

background:none repeat scroll 0 0 #58C16D;

border-color:-moz-use-text-color -moz-use-text-color rgba(0, 0, 0, 0.25);

border-style:none none solid;

border-width:medium medium 1px;

color:#FFFFFF;

cursor:pointer;

display:inline-block;

font-size:14px;

font-weight:bold;

line-height:1;

padding:8px 14px 9px;

position:relative;

text-decoration:none;

text-shadow:0 -1px 1px rgba(0, 0, 0, 0.25);

}

#confirm_message .confirm-links li a:hover{

	background:#67C124;

}



	

.node-type-readthink .field-field-dhg-zhengwen{

	width:390px;

}

.node-type-readthink .content,

.node-type-readthink .field-field-dhg-fubiaoti{

	margin-top:10px;

}



