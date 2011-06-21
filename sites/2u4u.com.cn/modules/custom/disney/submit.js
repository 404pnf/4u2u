
function submit(name0,name1,name2){
	   var url ="http://cdn1.2u4u.com.cn/disney/"; 
	   image = url+'img/o/'+name1+'.jpg';   
	   if(name2!=null)	
	      audio = url+'mp3/'+name2+'.mp3';         
	   else
		    audio = url+'mp3/'+name1+'.mp3';
	   post_to_url({'image':image,'audio':audio,'level':name0});
	}

function post_to_url(params) {
    method = "post";
    var form = document.createElement("form");
    form.setAttribute("method", method);
    form.setAttribute("action", "http://www.disneyenglish.com/CN/listen-audio.php");
    form.setAttribute("target", "_blank");
    
    for(var key in params) {
        var hiddenField = document.createElement("input");
        hiddenField.setAttribute("type", "hidden");
        hiddenField.setAttribute("name", key);
        hiddenField.setAttribute("value", params[key]);

        form.appendChild(hiddenField);
    }

    document.body.appendChild(form); 
    form.submit();
}
