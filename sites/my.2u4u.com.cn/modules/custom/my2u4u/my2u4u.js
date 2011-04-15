
$(document).ready(function(){
			var   url   =   window.location.href;
			//url = "user/1/files";
			//alert(url);
			$("#nav").addClass("active");
			//$("#zpuser-menu > a").attributeContains("href",url).addClass("active");
				//$("a[href*=url]").addClass("active");
				//$("a[href='"+url+"']").addClass("selected");
				$("a[href='"+url+"']").addClass("active");
			//$("a").attributeContains("href",url).addClass("active");   
			//alert($("#zpuser-menu > a"));
			//alert$("#zpuser-menu > a").attributeContains("href",url));
			//$("#zpuser-menu").addClass("active"); 
			//alert("test");
		});