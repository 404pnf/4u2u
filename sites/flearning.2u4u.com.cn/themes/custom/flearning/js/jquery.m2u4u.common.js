

$(function(){
	/*alert('qwe');
	$('a:[href^=/]').each(function(){
		$(this).attr('href',$(this).attr('href')+'?clienttype=' + clienttype);
	});
	
	$(window).scroll(function (){   
		var offsetTop = $(window).scrollTop() ; $(".toolbar").animate({top : offsetTop },{ duration:50 , queue:false }); 
	 }); 
	*/
	
	$('#rediantuijian .views-row').click(function(){
		location.href = $(this).find('a').attr('href');
	});
	
	$('.view-mobile-taxonomy-term .views-row').click(function(){
		location.href = $(this).find('a').attr('href');
	});
	
	$('.mobile .view-digital .views-row').click(function(){
		//location.href = $(this).find('a').attr('href');
		window.open($(this).find('a').attr('href'), "_blank");	 
		//$(this).find('a').click();
	});
	
	
	var pager = $('ul.pager').parent().clone();
	//$('.view-smart-mobile').prepend(pager);
	$('li.pager-first a').html('«首页');
	$('li.pager-previous a').html('‹前页');
	$('li.pager-next a').html('后页›');
	$('li.pager-last a').html('末页»');

});