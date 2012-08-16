// $Id: jplayer.js,v 1.3 2010/11/04 12:50:18 blazey Exp $

/**
 * @file
 * Drupal behaviors for the jPlayer audio player.
 */

(function ($) {

Drupal.jPlayer = Drupal.jPlayer || { active: false };

Drupal.behaviors.jPlayer = function(context) {
  $('.jplayer', context).each(function() {
    var wrapper = $(this).parent().get(0);
    var player = this;
    var playerId = this.id;
    var playerType = $(this).attr('rel') ? 'single' : 'playlist';
    var playerPlayTime = $(wrapper).find('.jp-play-time').get(0);
    var playerTotalTime = $(wrapper).find('.jp-total-time').get(0);
    var active = 0; // The current playlist item.
    var playlist = []; // An array of DOM element links.

    // Multi-player specific code.
    if (playerType == 'playlist') {

      // Enable clicking links within the playlist.
      $(wrapper).find('.jp-playlist li a').each(function(n) {
        if ($(player).attr('rel') == '') {
          $(player).attr('rel', this.href);
        }
        playlist.push(this);
        $(this).click(function() {
          active = n;
          Drupal.jPlayer.setActive(wrapper, player, playlist, n);
          Drupal.jPlayer.play(wrapper, player);
          return false;
        });
      });

      // Enable play, pause, and stop buttons.
      $(wrapper).find('a.jp-play').click(function() {
        Drupal.jPlayer.play(wrapper, player);
        return false;
      });
      $(wrapper).find('a.jp-pause').click(function() {
        Drupal.jPlayer.pause(wrapper, player);
        return false;
      });
      $(wrapper).find('a.jp-stop').click(function() {
        Drupal.jPlayer.stop(wrapper, player);
        return false;
      });

      // Enable next and previous buttons.
      $(wrapper).find('a.jp-next').click(function() {
        active = Drupal.jPlayer.next(wrapper, player, playlist, active);
        Drupal.jPlayer.play(wrapper, player);
        return false;
      });
      $(wrapper).find('a.jp-previous').click(function() {
        active = Drupal.jPlayer.previous(wrapper, player, playlist, active);
        Drupal.jPlayer.play(wrapper, player);
        return false;
      });
    }

    // Actually initialize the player.
    $(player).jPlayer({
      ready: function() { 
        this.element.jPlayer('setFile', this.element.attr('rel'));
        if (Drupal.settings.jPlayer.autoPlay && !Drupal.jPlayer.active) {
          if (playerType == 'playlist') {
            Drupal.jPlayer.setActive(wrapper, player, playlist, active);
          }
          Drupal.jPlayer.play(wrapper, player);
        }
      },
      swfPath: Drupal.settings.jPlayer.swfPath,
      volume: 50,
      oggSupport: false,
      nativeSupprt: true
    })
    // Set all our custom IDs.
    .jPlayer('cssId', 'play', playerId + '-play')
    .jPlayer('cssId', 'pause', playerId + '-pause')
    .jPlayer('cssId', 'stop', playerId + '-stop')
    .jPlayer('cssId', 'loadBar', playerId + '-load-bar')
    .jPlayer('cssId', 'playBar', playerId + '-play-bar')
    .jPlayer('cssId', 'volumeMin', playerId + '-volume-min')
    .jPlayer('cssId', 'volumeMax', playerId + '-volume-max')
    .jPlayer('cssId', 'volumeBar', playerId + '-volume-bar')
    .jPlayer('cssId', 'volumeBarValue', playerId + '-volume-bar-value')
    // Register progress functions.
    .jPlayer('onProgressChange', function(loadPercent, playedPercentRelative, playedPercentAbsolute, playedTime, totalTime) {
      $(playerPlayTime).text($.jPlayer.convertTime(playedTime));  
      if (totalTime != 0 && totalTime != Number.POSITIVE_INFINITY) {
        $(playerTotalTime).text($.jPlayer.convertTime(totalTime));
      }
     
      	mytime = $.jPlayer.convertTime(playedTime);
		mytime = mytime.replace(/:/g, "");
		
		findsubtitles = this.element.parents('.smart_blog_audio').next('.smart_blog_subtitle').children('.subtitles');
		
		//console.log('onProgressChange');
		highlight(findsubtitles,mytime);
      
    })
    .jPlayer('onSoundComplete', function() {
      if (playerType == 'playlist') {
        Drupal.jPlayer.next(wrapper, player, playlist, active);
      }
    });
    $.jPlayer.timeFormat.showHour = true;
    $.jPlayer.timeFormat.padHour = true;
  });
};

Drupal.jPlayer.setActive = function(wrapper, player, playlist, index) {
  $(wrapper).find('.jplayer_playlist_current').removeClass('jplayer_playlist_current');
  $(playlist[index]).parent().addClass('jplayer_playlist_current');
  $(player).jPlayer('setFile', playlist[index].href);
};

Drupal.jPlayer.play = function(wrapper, player) {
  $(player).jPlayer('play');
  Drupal.jPlayer.active = true;
}

Drupal.jPlayer.pause = function(wrapper, player) {
  $(player).jPlayer('pause');
  Drupal.jPlayer.active = false;
}

Drupal.jPlayer.stop = function(wrapper, player) {
  $(player).jPlayer('stop');
  Drupal.jPlayer.active = false;
}

Drupal.jPlayer.next = function(wrapper, player, playlist, current) {
  var index = (current + 1 < playlist.length) ? current + 1 : 0;
  Drupal.jPlayer.setActive(wrapper, player, playlist, index);
  Drupal.jPlayer.play(wrapper, player);
  return index;
}

Drupal.jPlayer.previous = function(wrapper, player, playlist, current) {
  var index = (current - 1 >= 0) ? current - 1 : playlist.length - 1;
  Drupal.jPlayer.setActive(wrapper, player, playlist, index);
  Drupal.jPlayer.play(wrapper, player);
  return index;
}

})(jQuery);

$(document).ready(function(){
	
		
	$('.subtitles span').click(function(event){
			//	alert('456');
		that = $(event.target);
		if(!$(event.target).is('span')){
			that = $(event.target).parent('span');
		}
	
		var thisclass = that.attr('class');
		thisclass = thisclass.replace("time_", "");

		thishours = parseInt(thisclass.substring(0,2), 10);
		thisminutes = parseInt(thisclass.substring(2,4), 10);
		thisseconds = parseInt(thisclass.substring(4,6), 10);
		thistime = (thishours*60*60 + thisminutes*60 + thisseconds)*1000;
		
		findjPlayer = that.parents('.smart_blog_subtitle').prev('.smart_blog_audio').children('.jplayer');
		
		//thistime = 0;
		
		//$('#'+findjPlayer.attr('id')).jPlayer("play").jPlayer("stop").jPlayer("playHeadTime", thistime); 
		findjPlayer.jPlayer("playHeadTime", thistime);
		//findjPlayer.playHeadTime(thistime);
		//alert(thisclass+"time:::"+thistime);
		
	});
		
	/*
	$('.anniu').toggle(
		function(){
			$(this).next('.smart_audio_button').slideUp('slow');
			$(this).removeClass('anniu_up');
			$(this).addClass('anniu_down');
			$(this).next('.smart_audio_button').children('.smart_blog_subtitle').find('.highlight').removeClass('highlight');

			//findjPlayer.jPlayer("stop"); 
		},
		function(){
			$(this).next('.smart_audio_button').slideDown('slow');
			$(this).removeClass('anniu_down');
			$(this).addClass('anniu_up');

		}
	);
	$('.views-row-2 .anniu').click();
	$('.views-row-3 .anniu').click();
	*/	
	
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
	//$('.views-row-1 .anniu').click();
	//$('.views-row-1 .anniu').next('.smart_audio_button').slideDown('slow');
	//$('.views-row-1 .anniu').removeClass('anniu_down');
	$('.views-row-1 .anniu').addClass('anniu_up');
	//$('.views-row-3 .anniu').click();
	
	$('.subtitles span').hover(function(event){
			that = $(event.target);
			if(!$(event.target).is('span')){
				that = $(event.target).parent('span');
			}
				
			$('.hover').removeClass('hover');	
			that.addClass('hover');
			
		},function(event){
			//$('.hover').removeClass('hover');	
			
	});
	
});


function highlight(findsubtitles,id){
	var subtitle_line = findsubtitles.children('.time_'+id);

	if(subtitle_line.length > 0)
	{
		findsubtitles.children('.highlight').removeClass("highlight");
		subtitle_line.addClass("highlight");
	}
	
		
}