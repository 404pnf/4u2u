<?php 

/**
 * online_dict_new.php页面的控制
 *
 */




class common
{
	public $link = '';
	public $lang = '';
	public $word = '';
	public $uid = '';
	public $msg = '';
	public $str = '';
	public $radio = '';	
    public  $meta='';
/**
 * 验证是否包含特殊字符，
 *
 * @param 用户输入的字符串
 * @return 返回true,flase
 */	
	
function check($str){		
     if(preg_match("/[\':;*?~`!@#$%^&+=)(<>{}]|\]|\[|\/|\\\|\"|\|/",$str))  //不允许特殊字符
			return false;
	 else  
	        return true;
  }
  
  
  /**
   * 从GET数组获取相关参数，并根据语言选择字典
   *
   * @param GET数组
   * @return 查询参数
   */
 function get_url_pra($arr){
 
		  //url参数
		$this->str = '';
		if($arr[lang]!=""){
			$d= addslashes(trim($arr[lang]));
			   switch($d){
			    case "en": 
			       $this->str .="d=mced,mecd,ancced,meed,zhongshan-ec,zhongshan-ce";
			       break;
			    case "fr":
			      $this->str .="d=fh,hf,xsjfh";
			       break;
			    case "jp":
			      $this->str .="d=rh,hr";
			       break;     
			  }
		}else{
		     $this->str ="d=mced,mecd,fh,hf,rh,hr";
		}
	
			$d = addslashes(trim($arr[d]));
		   if($d) $this->str .="&d=".$d;
	
		  
		$l = addslashes(trim($arr[l]));
		   if($l) $this->str .="&l=".$l;
		$dl = addslashes(trim($arr[dl]));
		   if($dl) $this->str .="&dl=".$dl;
		$o = addslashes(trim($arr[o]));
		   if($o) $this->str .="&o=".$l;
		$t= addslashes(trim($arr[t]));
		   if($t) $this->str .="&t=".$l;
		$fs= addslashes(trim($arr[fs]));
		    if($fs) $this->str .="&fs=".$fs;
		$p= addslashes(trim($arr[p]));
		   if($p) $this->str .="&p=".$l;
		$s= addslashes(trim($arr[s]));
		  if($s) $this->str .="&s=".$s;
		 
		 return $this->str;
		 
}


/**
 *   获取用户ip
 *
 * @return unknown
 */

function getuserip(){
	global $_SERVER; 
	if (isset($_SERVER["HTTP_X_FORWARDED_FOR"])) { 
	$realip = $_SERVER["HTTP_X_FORWARDED_FOR"]; 
	} elseif (isset($_SERVER["HTTP_CLIENT_IP"])) { 
	$realip = $_SERVER["HTTP_CLIENT_IP"]; 
	} else { 
	$realip = $_SERVER["REMOTE_ADDR"]; 
	} 
	return $realip; 
}




/**
 *   相近词列表
 *
 * @param unknown_type $word
 * @param unknown_type $lang
 * @param unknown_type $num
 * @return unknown
 */



function get_words_list($word,$lang,$num=10){
	
	
	
    $lang = addslashes(trim($lang));
	$word = addslashes(trim($word));
	$query11 = "SELECT id FROM `dict_words` WHERE lang='$lang' AND word LIKE '$word' LIMIT 1";
	@$result = mysql_fetch_object(mysql_query($query11));
	if($result->id!=''){
	    $sql11 = "SELECT word FROM `dict_words` WHERE lang='$lang' AND id>'$result->id' AND id<'$result->id'+15 GROUP BY word ORDER BY word LIMIT $num";
	}else{
		$word = substr($word,0,3);
		$sql11 = "SELECT word FROM `dict_words` WHERE lang='$lang' AND word LIKE '$word%' GROUP BY word ORDER BY word LIMIT $num";
	}
  //  var_dump($sql11);
	$res = mysql_query($sql11);
	while($row = mysql_fetch_object($res)){
		
		$words_list .="<a href=online_dict_new.php?word=".urlencode($row->word)."&lang=$lang>".$row->word."</a><br>";  
	}
	
	return $words_list;
	
}




/*
*    从129上获取查询结果，提供两种方式：normal，sameas
*    对于sameas方式，会对结果自动添加访问链接
*
* 
* */






function get_result($word,$arr,$type,$ip){
	$this->msg = '';
	$str = self::get_url_pra($arr);
	
	$word = strip_tags($word);
	$word = urlencode(addslashes(trim($word)));
	/**
	 *  查询单词和法语变位之间使用了--
	 */

	if($arr['lang']=='fr'){
			
		if(strpos($word,"--")){
			$new = explode("--",$word);
			$word = $new[1];
			$show_word = $new[0];			
	   }else{
		   $new_sql = "SELECT word,`change` FROM dict_words WHERE lang='fr' AND word LIKE '$word%' LIMIT 1";
		   $result = mysql_fetch_object(mysql_query($new_sql));
				if($result->change!=''){
					$show_word = $word;					
					$word = $result->change;	
			}	

	   }	
	   
	
			
	}
	
	
			       
			       
  if($type=='normal'){
		
		/**
		 *   为法语单词找到原形
		 */
		
	    $url = "http://124.193.83.241:8180/dictweb/".$word.".html?s=style.css&l=zh_CN&ip=".$ip."&".$str;
//echo $url;

		$fp = fsockopen("124.193.83.241", 8180, $errno, $errstr, 3);     
		if (!$fp) {  
		  $this->msg .= "当前服务不可用.";
		}else{
		  $this->msg .= @file_get_contents($url);
    }
	/*
		$opts = array(  
      'http'=>array(  
       'method'=>"GET",  
        'timeout'=>3,  
      )  
		);  
		$context = stream_context_create($opts);  
		ob_start();  
		   $this->msg .= file_get_contents($url, false, $context);  
		ob_end_clean(); 
			*/
		
		


	    
    if(strlen($this->msg)>4&&$arr['lang']=='fr'){
    	$xie_word = '';
    	$xie_word = urldecode($word);
    	if(preg_match("/^[\x{4e00}-\x{9fa5}]+$/u",$xie_word)){  //匹配汉字
       	  	$xie_fr = self::xie_fr_dict($xie_word);
    	}else{     
    		$xie_word = urlencode(" ".$xie_word." ");   //是字母的话，前后加上空格进行查询

    		$xie_fr = self::xie_fr_dict($xie_word);    		
    	}
	        $this->msg .= $xie_fr;
	   }  


	}
	
    if($type=='sameas'){

			$word = $show_word;
			
    //	$url = " http://192.168.16.101:8080/dictweb/".$word.".html?s=style.css&t=sameas&".$str;  //该单词相近的单词
	
		$url = "http://124.193.83.241:8180/dictweb/".$word.".html?s=style.css&t=sameas&l=zh_CN&ip=".$ip."&".$str;  //该单词相近的单词
	// $this->msg = file_get_contents($url);
	 


 $string = @file_get_contents($url);
	  if(strlen($string)>5){
			$new_string = explode(",",$string);
			foreach($new_string as $key=>$value){
			   if($value!=''){
			   	if($arr[lang]=='')
			   	   $language = 'en';
			   	 else
			   	    $language = $arr[lang];
			      $this->msg .= "<a href=online_dict_new.php?lang=$language&word=".urlencode($value).">".trim($value)."</a>&nbsp;&nbsp;";
			   	  if($key>0&&($key+1)%10==0){
			   	  	$this->msg .="<br><br>&nbsp;&nbsp;&nbsp;&nbsp;";
			   	  }  
			   }
			}		
}else
   		$this->msg ='';

    }
 
   return $this->msg;
}  


		/*
        *     根据用户选择的语种，推荐至不同的网站
        *     只限于那些能提供url的网站
        *     目前只有英语、法语和日语
              要注意语言代码的统一
       * */

function dict_link($word,$lang){
  	$this->link ='';
  	$this->word = $word;

	$msg .="<br>你还可以去以下词典中查询该单词<br>"; 
 	$this->lang = self::default_lang($lang);

  	if($this->lang=='en'){
  	//	$this->link .= "&nbsp;&nbsp;&nbsp;&nbsp;<a href=http://wordnetweb.princeton.edu/perl/webwn?s=".$this->word." target='_blank'>普林斯顿WORDNET</a><br>";
		$this->link .="&nbsp;&nbsp;&nbsp;&nbsp;<a href=http://en.wiktionary.org/wiki/".$this->word." target='_blank'>维基百科词典</a><br>";
		$this->link .= "&nbsp;&nbsp;&nbsp;&nbsp;<a href=http://www.google.cn/search?q=define%3A".$this->word." target='_blank'>google词典</a><br>";

  	}
  	if($this->lang=='fr'){
  		$this->link .= "&nbsp;&nbsp;&nbsp;&nbsp;<a href=http://fr.wiktionary.org/wiki/".$this->word." target='_blank'>维基百科词典</a><br>";
		$this->link .="&nbsp;&nbsp;&nbsp;&nbsp;<a href=http://www.wordreference.com/fren/".$this->word." target='_blank'>wordreference.com</a><br>";
   //  	$this->link .="&nbsp;&nbsp;&nbsp;&nbsp;<a href=http://www.larousse.fr/dictionnaires/francais/".$this->word." target='_blank'>http://www.larousse.fr/dictionnaires/francais/".$this->word."</a><br>";
     	$this->link .="&nbsp;&nbsp;&nbsp;&nbsp;<a href=http://www.frdic.com/SearchDic.aspx?word=".$this->word." target='_blank'>法语助手</a><br>";
   	}
  	if($this->lang=='jp'){
  		$this->link .= "&nbsp;&nbsp;&nbsp;&nbsp;<a href=http://dict.hjenglish.com/jp/w/".$this->word."&type=jc target='_blank'>沪江小D词典</a><br>";
  	}
  	
  	if($this->link!=''){
  		$this->link = $msg.$this->link;
  	}
  	
  	  	return $this->link;
  	  	
  }
  
  
  /**
   *    检查用户查询的单词有无发音文件
   *    
   *     return：TRUE OR FALSE
   */
  
  function is_audio($word,$lang){
  	
  	$sql = "SELECT * FROM `words_audio` WHERE `word`='".$word."' AND `lang`='".$lang."'";
  	$num = @mysql_num_rows(mysql_query($sql));
  	if($num)
  	      return true;
  	 else 
  	      return false;	
  	
  	
  }
  


  /**
   * 法语之友网站词典
   *
   * 使用Json接口（by xieq)
   * 
   */
  
  
  function xie_fr_dict($word){
  	
  	
  	$xie_url = "http://frenchfriend.2u4u.com.cn/tx/xanadu/xanaduapi.ashx?txreq=get2u4uFFDictItem&word=".$word;
  	$string = @file_get_contents($xie_url);
  	$obj = self::my_json_decode($string); 
  //	var_dump($content);

  	$length = count($obj->exampleSentences);
  	$str .= "<ol class='exampleSentences'>";
  	
  	if($obj->exampleSentences[0]->sentenceTranslation!=''){
  	     $str .= "<div class='exampleTitle'>更多例句：</div>";
  	}
  	
  	for($i=0;$i<$length;$i++){
  		  		
  		$str .="<li class='exampleSentence'>";
  		if(preg_match("/^[\x{4e00}-\x{9fa5}]+$/u",trim(urldecode($word)))){
  		    $str .= "<div class='sentenceOriginal'>".$obj->exampleSentences[$i]->sentenceTranslation."</div>
  		         <div class='sentenceTranslation'>".$obj->exampleSentences[$i]->sentenceOriginal."</div></li>";
  		}else{
  			$str .= "<div class='sentenceOriginal'>".$obj->exampleSentences[$i]->sentenceOriginal."</div>
  		         <div class='sentenceTranslation'>".$obj->exampleSentences[$i]->sentenceTranslation."</div></li>";
  
  		}
  	}
  	$str .="</ol>";
    $word = urldecode($word);
  	$content = str_replace($word,"<span class='keyword' style='color:red;'>".$word."</span>",$str);  //关键词高亮
  	return $content;	  	
  	
  	
  }


  
  function word_audio($lang){
	  	
	$flash = "真人发音<div id=\"flashContent\">
<p>To view this page ensure that Adobe Flash Player version 10.0.0 or
greater is installed.</p>
<script type=\"text/javascript\"> 
				var pageHost = ((document.location.protocol == \"https:\") ? \"https://\" :	\"http://\"); 
				document.write(\"<a href='http://www.adobe.com/go/getflashplayer'><img src='\" 
								+ pageHost + \"www.adobe.com/images/shared/download_buttons/get_flash_player.gif' alt='Get Adobe Flash player' /></a>\" ); 
			</script></div>

<noscript><object classid=\"clsid:D27CDB6E-AE6D-11cf-96B8-444553540000\"
	width=\"48\" height=\"48\" id=\"XanaduSoundPlayer\">
	<param name=\"movie\" value=\"XanaduSoundPlayer.swf\" />
	<param name=\"quality\" value=\"high\" />
	<param name=\"bgcolor\" value=\"#ffffff\" />
	<param name=\"allowScriptAccess\" value=\"sameDomain\" />
	<param name=\"allowFullScreen\" value=\"true\" />
	<!--[if !IE]>--> <object type=\"application/x-shockwave-flash\"
		data=\"XanaduSoundPlayer.swf\" width=\"48\" height=\"48\">
		<param name=\"quality\" value=\"high\" />
		<param name=\"bgcolor\" value=\"#ffffff\" />
		<param name=\"allowScriptAccess\" value=\"sameDomain\" />
		<param name=\"allowFullScreen\" value=\"true\" />
		<!--<![endif]--> <!--[if gte IE 6]>-->
		<p>Either scripts and active content are not permitted to run or Adobe
		Flash Player version 10.0.0 or greater is not installed.</p>
		<!--<![endif]--> <a href=\"http://www.adobe.com/go/getflashplayer\"> <img
			src=\"http://www.adobe.com/images/shared/download_buttons/get_flash_player.gif\"
			alt=\"Get Adobe Flash Player\" /> </a> <!--[if !IE]>--> </object> <!--<![endif]-->
</object></noscript>";
	
	// 如果是英语，则加上美音
	
	if($lang =='en')
	    $flash .="真人发音(美音)<div id=\"flashContentUS\">
<p>To view this page ensure that Adobe Flash Player version 10.0.0 or
greater is installed.</p>
<script type=\"text/javascript\"> 
				var pageHost = ((document.location.protocol == \"https:\") ? \"https://\" :	\"http://\"); 
				document.write(\"<a href='http://www.adobe.com/go/getflashplayer'><img src='\" 
								+ pageHost + \"www.adobe.com/images/shared/download_buttons/get_flash_player.gif' alt='Get Adobe Flash player' /></a>\" ); 
			</script></div>

<noscript><object classid=\"clsid:D27CDB6E-AE6D-11cf-96B8-444553540000\"
	width=\"48\" height=\"48\" id=\"XanaduSoundPlayerUS\">
	<param name=\"movie\" value=\"XanaduSoundPlayerUS.swf\"/>
	<param name=\"quality\" value=\"high\" />
	<param name=\"bgcolor\" value=\"#ffffff\" />
	<param name=\"allowScriptAccess\" value=\"sameDomain\" />
	<param name=\"allowFullScreen\" value=\"true\" />
	<!--[if !IE]>--> <object type=\"application/x-shockwave-flash\"
		data=\"XanaduSoundPlayerUS.swf\" width=\"48\" height=\"48\">
		<param name=\"quality\" value=\"high\" />
		<param name=\"bgcolor\" value=\"#ffffff\" />
		<param name=\"allowScriptAccess\" value=\"sameDomain\" />
		<param name=\"allowFullScreen\" value=\"true\" />
		<!--<![endif]--> <!--[if gte IE 6]>-->
		<p>Either scripts and active content are not permitted to run or Adobe
		Flash Player version 10.0.0 or greater is not installed.</p>
		<!--<![endif]--> <a href=\"http://www.adobe.com/go/getflashplayer\"> <img
			src=\"http://www.adobe.com/images/shared/download_buttons/get_flash_player.gif\"
			alt=\"Get Adobe Flash Player\" /> </a> <!--[if !IE]>--> </object> <!--<![endif]-->
</object></noscript>";
	    
	    return $flash; 	
  	
  }
  
  
  
  

  /**
   *   当用户查询的单词不在库中时，系统可以自动记录该单词，并返回提示信息
   *   该单词只会插入一次
   * 
   * @param $uid   用户id
   * @param $word  查询的单词
   * 
   * @return 提示信息
   */
  
  
  
function add_words($uid='',$word,$lang){
		$this->msg = '';
		$sql = "SELECT uid FROM `dict_records` WHERE word='$word'";    //查看该单词是不是已经记录下来
		$num = @mysql_num_rows(mysql_query($sql));
	
		if($num==0){
			
		 		$time = time();
		 		$query = "INSERT INTO `dict_records`(uid,time,word,lang) VALUES('$uid',$time,'$word','$lang')";
		 		$rs = mysql_query($query);
		 		if($rs)
		 		  $this->msg = "该词条添加成功";
		 		
		}else 
		   $this->msg = "该词条已被添加";
		   
		   return $this->msg;
  
   }


/**
 * *   根据url中语言的值选择默认radio
 */
  function checked_lang($string){ 
  	  $str = self::default_lang($string);
      $this->radio = '';
	  $this->radio ="<input type='radio' id='lang' name='lang' value='en'  onclick='change_v(this.value)' ";
   if($str=='en'|$str!='')
	   $this->radio .= "checked";
	   $this->radio .=">英语 ";
	   $this->radio .="<input type='radio' id='lang' name='lang' value='fr'  onclick='change_v(this.value)' ";
   if($str=='fr')
	   $this->radio .= "checked";
	   $this->radio .=">法语 ";	
	   $this->radio .="<input type='radio' id='lang' name='lang' value='jp'  onclick='change_v(this.value)' ";
   if($str=='jp')
	   $this->radio .= "checked";
	   $this->radio .=">日语 ";
	   $this->radio .="<input id='lang' type='radio' name='lang' value='de' disabled />德语";
	   $this->radio .="<input id='lang' type='radio' name='lang' value='kr' disabled />韩语";
	   $this->radio .="<input id='lang' type='radio' name='lang' value='kr' disabled />俄语";	   
	   $this->radio .="<input id='lang' type='radio' name='lang' value='kr' disabled />意大利语";	
	   $this->radio .="<input id='lang' type='radio' name='lang' value='kr' disabled />西班牙语";   
	   
	   
	   
	 return $this->radio;
 }
 
 
 /*
  * 根据url的值选择语言
  * 默认为英文
  * 语种选择时需要，词典推荐时也需要
  * 
  */

 
 function default_lang($string){
 	$this->lang = $string;
  	if($this->lang=='')
	    $this->lang='en';
	if($this->lang!=''){	
		  $rs = in_array($this->lang,array('en','fr','jp'));		 //判断lang是否是默认的几个值，否则设为en  若语种增加要及时修改这里  
		  if(!$rs)
		   	  $this->lang='en';       	  		   	  
		}
 	return $this->lang;
 }
 
/**
 *  为SEO设计的meta关键词等
 *
 * @param  用户输入的单词
 * @return 页面中meta描述
 */
 
 
 function meta($str){
 	if($str!=''){
	 	$this->meta = "<meta name=\"keywords\" content=\"".$str."的意思、".$str."的解释、".$str."的翻译、".$str."例句\" />";
	 	$this->meta .=	"<meta name=\"description\" content=\"外研社在线词典支持英语、法语、日语等多语种的查询，为外语学习爱好者提供 ".$str."的意思、".$str."的解释、".$str."的真人发音、".$str."例句,外研社在线词典致力于为您提供优质的在线查词服务\"/>";
//	 	$this->meta .=	"<title>".$str."是什么意思_翻译_外研社在线词典</title>";
               	$this->meta .=	"<title>".$str."是什么意思_翻译_例句_真人发音_外研社在线词典</title>";
	}else 
	 	$this->meta .=	"<title>外研社在线词典 | 悠游</title>";  
 	return $this->meta;
 	
 }

 
 /**
  * 热门词汇
  *
  * 
  */
 
 function hot_words($lang){
 	if($lang == 'en'){
	 	$words  = "<a class='white' href='online_dict_new.php?lang=en&word=%E9%99%8D%E6%B8%A9'>降温</a>   &nbsp;";
		$words .= "<a class='white' href='online_dict_new.php?lang=en&word=%E6%B5%B7%E5%95%B8'>海啸</a>   &nbsp;";
		$words .= "<a class='white' href='online_dict_new.php?lang=en&word=%E7%AB%A0%E9%B1%BC'>章鱼</a>   &nbsp;";
		$words .= "<a class='white'  href='online_dict_new.php?lang=en&word=%E8%BE%BE%E4%BA%BA'>达人</a>   &nbsp;";
		$words .= "<a class='white' href='online_dict_new.php?lang=en&word=inception'>inception</a>   &nbsp;";
		$words .= "<a class='white' href='online_dict_new.php?lang=en&word=%E5%8D%8E%E5%B0%94%E8%A1%97'>华尔街</a>   &nbsp;";
 	}elseif($lang == 'jp'){
	 	$words  = "<a class='white' href='online_dict_new.php?lang=jp&word=%E3%81%8D%E3%82%93%E3%83%A1%E3%83%80%E3%83%AB'>きんメダル</a>   &nbsp;";
		$words .= "<a class='white' href='online_dict_new.php?lang=en&word=%E5%86%A0%E5%86%9B'>冠军</a>   &nbsp;";
		$words .= "<a class='white' href='online_dict_new.php?lang=jp&word=%E7%89%A9%E4%BB%B7'>物价</a>   &nbsp;";
		$words .= "<a class='white'  href='online_dict_new.php?lang=jp&word=%E5%AD%98%E6%AC%BE'>存款</a>   &nbsp;";
		$words .= "<a class='white' href='online_dict_new.php?lang=en&word=%E9%98%B2%E7%81%AB'>防火</a>   &nbsp;";
		$words .= "<a class='white' href='online_dict_new.php?lang=jp&word=%E6%99%8B%E7%BA%A7'>晋级</a>   &nbsp;";
 	}elseif($lang == 'fr'){
	 	$words  = "<a class='white' href='online_dict_new.php?lang=fr&word=%E9%98%B2%E7%81%AB'>防火</a>   &nbsp;";
		$words .= "<a class='white' href='online_dict_new.php?lang=fr&word=%E6%99%8B%E7%BA%A7'>晋级</a>   &nbsp;";
		$words .= "<a class='white' href='online_dict_new.php?lang=fr&word=%E9%87%91%E7%89%8C'>金牌</a>   &nbsp;";
		$words .= "<a class='white'  href='online_dict_new.php?lang=fr&word=%E5%88%A9%E7%8E%87'>利率</a>   &nbsp;";
		$words .= "<a class='white' href='online_dict_new.php?lang=fr&word=%E7%89%A9%E4%BB%B7'>物价</a>   &nbsp;";
	}
 	
 	
 	return $words;
 	
 }
 
 
 

 
function my_json_encode($arr){
	if (function_exists('json_encode')){
			
		  return json_encode($arr);
		  
		}else{
		 include("JSON.php");
		 $json = new Services_JSON();
		 
		 return $json->encode($arr);
		 
	  }	
	  
}	

function my_json_decode($arr){
	if (function_exists('json_encode')){
			
		  return json_decode($arr);
		  
		}else{
		 include("JSON.php");
		 $json = new Services_JSON();
		 
		 return $json->decode($arr);
		 
	  }	
	  
}
 
}
?>
