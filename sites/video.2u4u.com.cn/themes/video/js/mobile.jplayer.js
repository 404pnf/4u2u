$(function(){

	$.jPlayer.timeFormat.showHour = true;
	$.jPlayer.timeFormat.padHour = true;
	
	$('.jp-jplayer').each(function() {
	
		var player = this;
		var playerId = this.id;
		var nid = playerId.replace("jplayer_", "");
		var jp_interfaceId = "jp_interface_"+nid;
		var playerurl = $(this).attr('alt');
		var swfPath = "/sites/video.2u4u.com.cn/themes/video/js/jplayer200";
		
		$(player).jPlayer({
			ready: function (event) {
				$(event.target).jPlayer("setMedia", {
					mp3: playerurl
				}).jPlayer("load");
			},
			ended: function (event) {
				//$(event.target).jPlayer("pause",event.jPlayer.status.duration);
			},
			swfPath: swfPath,
			supplied: "mp3",
			volume:1, 
			cssSelectorAncestor: "#"+jp_interfaceId
		})    
		.bind($.jPlayer.event.timeupdate, function(event) {
		
			nowtime = parseInt(event.jPlayer.status.currentTime,10);
			
			
			mytime = $.jPlayer.convertTime(nowtime); 
			mytime = mytime.replace(/:/g, "");
			
			findsubtitles = $(event.target).parents('.smart_blog_audio').next('.smart_blog_subtitle').children('.subtitles');
			
			//console.log(findsubtitles.html());
   			 if(event.jPlayer.status.currentTime > 0){
				highlight(findsubtitles,mytime);
			 }
		})
		.bind($.jPlayer.event.play, function() { // Using a jPlayer event to avoid both jPlayers playing together.
				$(this).jPlayer("pauseOthers");
		});	
	
	});


	$('.subtitles span').click(function(event){
				
		that = $(event.target);
		if(!$(event.target).is('span')){
			that = $(event.target).parent('span');
		}
	
		var thisclass = that.attr('class');
		thisclass = thisclass.replace("time_", "");

		thishours = parseInt(thisclass.substring(0,2), 10);
		thisminutes = parseInt(thisclass.substring(2,4), 10);
		thisseconds = parseInt(thisclass.substring(4,6), 10);
		thistime = thishours*60*60 + thisminutes*60 + thisseconds;
		
		
		findjPlayer = that.parents('.smart_blog_subtitle').prev('.smart_blog_audio').children('.jp-jplayer');
		
		findjPlayer.jPlayer('play', thistime);
		
	});
	
	$('.anniu').toggle(
		function(){
			$(this).next('.smart_audio_button').slideDown('slow');
			$(this).removeClass('anniu_down');
			$(this).addClass('anniu_up');

		},function(){
			$(this).next('.smart_audio_button').slideUp('slow');
			$(this).removeClass('anniu_up');
			$(this).addClass('anniu_down');
			$(this).next('.smart_audio_button').children('.smart_blog_subtitle').find('.highlight').removeClass('highlight');

			//findjPlayer.jPlayer("stop"); 
		}
		
	);
	//$('.views-row-1 .anniu').addClass('anniu_up');
	$('.views-row-1 .anniu').click();
	//$(document).scrollTop(0);	
});



function highlight(findsubtitles,id){
	scrolltop = $(document).scrollTop();
		
	var subtitle_line = findsubtitles.children('.time_'+id);
	var offset = $(subtitle_line).offset();
	var top_val=offset.top;
	$(document).scrollTop(top_val-100);	
	
	if(navigator.platform == 'iPad' || navigator.platform == 'iPhone' || navigator.platform == 'iPod')
	{
		findsubtitles.parents('.smart_blog_subtitle').prev('.smart_blog_audio').children('.jp-audio').attr('style','position:absolute;top:'+(scrolltop+10)+'px;left:16px;');
	};
	

	if(subtitle_line.length > 0)
	{
		findsubtitles.children('.highlight').removeClass("highlight");
		subtitle_line.addClass("highlight");
	}
		

}


	$(window).scroll(function () { 
		//alert('scroll');
		scrolltop = $(document).scrollTop();
		
		$('.smart_blog_subtitle').each(function(){
			zimuTop = $(this).offset().top;
  			zimuHeight = $(this)[0].offsetHeight;
  			
  			audiotop = $(this).prev('.smart_blog_audio').offset().top;

			/*
			console.group("组");
			console.log('audiotop::'+audiotop);
			console.log('zimuTop::'+zimuTop);
			console.log('scrolltop::'+scrolltop);
			
			console.groupEnd();
			*/
			
			if(scrolltop >= (audiotop-9) && scrolltop >= (zimuTop-74) && scrolltop <=(zimuTop+zimuHeight)){
				$(this).prev('.smart_blog_audio').children('.jp-audio').attr('style','position:fixed;top:10px;left:16px;');
				if(navigator.platform == 'iPad' || navigator.platform == 'iPhone' || navigator.platform == 'iPod')
				{
					$(this).prev('.smart_blog_audio').children('.jp-audio').attr('style','position:absolute;top:'+(scrolltop+10)+'px;left:16px;');
				};
			}	
			if(scrolltop < audiotop || scrolltop >(zimuTop+zimuHeight - 35))
				$(this).prev('.smart_blog_audio').children('.jp-audio').removeAttr('style');
				
		});
		
	
	});