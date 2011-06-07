 
 $(funciton(){
 	alert('123');
 	
 	$('.subtitles').click(function(event){
	
		var thisclass = $(event.target).attr('class');
		thisclass = thisclass.replace("time_", "");
		alert(thisclass);
		/*
		thisclass = thisclass.replace(/\d\d/g, function(word){
 			 return word+':';
  			});
  		thisclass = thisclass.replace(/:$/, '');
  		*/
  		thishours = thisclass.substring(0,2);
  		thisminutes = thisclass.substring(2,4);
  		thisseconds = thisclass.substring(4,6);
  		thistime = (thishours*60*60 + thisminutes*60 + thisseconds)*1000;
		//alert(thishours+':'+thisminutes+':'+thisseconds+' time'+thistime);
		
		findjPlayer = $(event.target).parents('.views-field-field-subtitles-value').prev('.views-field-field-audio-fid').children().children('.jplayer');
		
		findjPlayer.jPlayer("playHeadTime", thistime); 
	});
	
 });