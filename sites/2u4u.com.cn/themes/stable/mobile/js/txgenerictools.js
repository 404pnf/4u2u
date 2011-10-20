<!--
// TXGenericToolsJS V0.9a


function TXGenericToolsJS()
{
};

TXGenericToolsJS.prototype = 
{
	type: "TXGenericToolsJS",
	//createTime: new Date(),
	showError: function(msg)
	{
		alert("发生错误：" + msg);
	},
	
	stringContains: function(strOrigin, strSearch)
	{
		if ((strOrigin == undefined) || (strSearch == undefined))
		{
			return false;
		}
		
		if (strOrigin.indexOf(strSearch) != -1)
		{
			return true;
		}
		else
		{
			return false;
		}
	},
	
	showConsoleMessage: function(msg)
	{
		if (Boolean(window.console && window.console.firebug))
		{
			console.log(msg);
		}
	},
	
	//页面调用只要引进这个文件

	//$.cookie("name"); //根据cookie名字取到cookie值

	//$.cookie("name", "value");//设置cookie 名字，值


	//$.cookie("name", value, { expires: 7 }); //设置cookie 名字，值，生命周期等属性

	//$.cookie("name", null); //根据cookie名移除cookie

	setCookie: function(name, value, options) 
	{
		if (typeof value != 'undefined') 
		{
   			options = options || {};
   			if (value === null) 
			{
    			value = '';
    			options = $.extend({}, options);
    			options.expires = -1;
   			}
   			
			var expires = '';
   			if (options.expires && (typeof options.expires == 'number' || options.expires.toUTCString)) 
			{
    			var date;
    			if (typeof options.expires == 'number') 
				{
     				date = new Date();
     				date.setTime(date.getTime() + (options.expires * 24 * 60 * 60 * 1000));
    			} 
				else 
				{
     				date = options.expires;
    			}
    			expires = '; expires=' + date.toUTCString();
   			}
   			var path = options.path ? '; path=' + (options.path) : '';
   			var domain = options.domain ? '; domain=' + (options.domain) : '';
   			var secure = options.secure ? '; secure' : '';
   			document.cookie = [name, '=', encodeURIComponent(value), expires, path, domain, secure].join('');
		} 
		else 
		{
   			var cookieValue = null;
   			if (document.cookie && document.cookie != '') 
			{
    			var cookies = document.cookie.split(';');
    			for (var i = 0; i < cookies.length; i++) 
				{
     				var cookie = jQuery.trim(cookies[i]);
     				if (cookie.substring(0, name.length + 1) == (name + '=')) 
					{
      					cookieValue = decodeURIComponent(cookie.substring(name.length + 1));
      					break;
     				}
    			}
   			}
   			return cookieValue;
		}
	}
}

var tx = new TXGenericToolsJS();

-->


