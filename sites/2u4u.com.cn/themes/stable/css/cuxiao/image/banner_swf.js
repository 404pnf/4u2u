

function banner_gundong(img_str,url_str,title_str,w,h){
        var swf_width = w
        var swf_height = h
		var pics = img_str
		var links = url_str
		var texts = title_str

        document.write('<object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000" codebase="http://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0" width="'+ swf_width +'" height="'+ swf_height +'">');
        document.write('<param name="movie" value="http://www.jjl.cn/edu/images/bcastr.swf"><param name="quality" value="high">');
        document.write('<param name="menu" value="false"><param name=wmode value="opaque">');
        document.write('<param name="FlashVars" value="bcastr_file='+pics+'&bcastr_link='+links+'&bcastr_title='+texts+'">');
        document.write('<embed src="/edu/images/bcastr.swf" wmode="opaque" FlashVars="bcastr_file='+pics+'&bcastr_link='+links+'&bcastr_title='+texts+'& menu="false" quality="high" width="'+ swf_width +'" height="'+ swf_height +'" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer" />'); 
        document.write('</object>');
        
}