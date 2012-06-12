
function markHistory(histroyUrl,gotoUrl){
	
	//var unflagUrl = "/flag/unflag/lishi/"+nid;
	//var flagUrl = "/flag/flag/lishi/"+nid;
	
		// 提交到后台进行验证
	$.ajax({ 
		type: "get",// 指定是post还是get,当然此处要提交,当然就要用post了   
		cache: "false",// 默认: true,dataType为script时默认为false) jQuery 1.2 新功能，设置为 false 将不会从浏览器缓存中加载请求信息。   
		url: histroyUrl,// 发送请求的地址。   
		//data: 'uid='+uid+'&sess_id='+session+'&key=aa',//发送到服务器的数据   
		dataType: "text",// 返回纯文本字符串 
		timeout:20000,// 设置请求超时时间（毫秒）。 
		complete:function(){
			
			location.href = gotoUrl;
		}
	}); 
		
	return false;
		
}


function markClick(that){
	
	var gotoUrl = $(that).attr('gotoUrl');
	var histroyUrl = '';
	var nid = $(that).attr('nid');
	
	if(gotoUrl==undefined || gotoUrl=='')
		gotoUrl = $(that).attr('href');
	
	histroyUrl = $(that).parents('.termrow').find('.flag-nid-'+nid+' .flag-lishi a.flag-action').attr('href');
	
	markHistory(histroyUrl,gotoUrl);
	
}

$(function(){
	$('.term-search .views-field-cover a').click(function (){
		markClick(this);
	});
});

$(function(){
	$('.term-search .views-field-title a').click(function (){
		markClick(this);
	});
});



$(function(){
	$('.redirect-url-view .views-field-title a').click(function (){
		//alert('ad');
		markClick(this);
	});
});

	
	