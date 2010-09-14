<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title><?php print $action; ?></title>
<style type="text/css">
.login_body {
	margin: 0 auto;
	width: 853px;
	padding: 50px;
}

.login_content {
	width: 600px;
	margin: 0 auto;
	padding: 0px;
	text-align: center;
}

.login_content h3 {
	border-bottom: 1px solid #CCC;
	padding: 5px;
}
.proccess { 
BACKGROUND: #ffffff; BORDER-BOTTOM: 1px solid; BORDER-LEFT: 1px solid; BORDER-RIGHT: 1px solid; BORDER-TOP: 1px solid; HEIGHT: 15px; MARGIN: 3px; WIDTH: 10px 
} 
.login_body .login_content .content_text {
	font-size: 12px;
	line-height: 20px;
	color: #FF6600;
	height: 60px;
	width: 550px;
	margin-top: 0px;
	margin-right: auto;
	margin-bottom: 0px;
	margin-left: auto;
	border: 1px solid #FF9966;
	background-color: #f2f2f2;
}
</style>
</head>

<body>
<div class="login_body">
<div class="login_content">
<div class='content_text'><?php print $content ?></div>

<br />
<FORM method=post name=proccess> 
	<SCRIPT language=javascript> 
    	for(i=0;i<30;i++)document.write("<input class=proccess>") 
    </SCRIPT> 
</FORM> 
<SCRIPT language=JavaScript><!-- 
	var p=0,j=0; 
	var c=new Array("BurlyWood","white") 
	var int = setInterval('proccess();',50) 
	function proccess(){ 
		document.forms.proccess.elements[p].style.background=c[j]; 
		p+=1; 
		if(p==30){
			//p=0;j=1-j;
			clearInterval(int);
		}
	} 
--></SCRIPT> 
</div>
</div>
</body>
</html>
