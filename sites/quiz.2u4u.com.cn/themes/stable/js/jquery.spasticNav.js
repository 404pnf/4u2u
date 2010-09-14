(function($) {

	$.fn.spasticNav = function(options) {
	
		options = $.extend({
			overlap : 20,
			speed : 500,
			reset : 500,
			//color : '#0b2b61',
			easing : 'easeOutExpo'
		}, options);
	
		return this.each(function() {
		
		 	var nav = $(this),
		 		currentPageItem = $('li.menu-41193', nav),
		 		blob,
		 		reset;
				
		 	if(currentPageItem.width()==null){
				currentPageItem = $('li.first', nav);
				 
				$('<li class="blob"><a class="bloba" href="#"></a></li>').css({
		 		left : -9999
				}).appendTo(this);
				
			}
			else{				
				$('<li class="blob"></li>').css({
					width : currentPageItem.width(),
					height : currentPageItem.outerHeight(),
					left : currentPageItem.position().left
				}).appendTo(this);
			 	$('<a class="bloba" href="#"></a>').css({
					width : currentPageItem.outerWidth()-15		 		
				}).appendTo('li.blob');	 	
		 	}
			
		 	blob = $('.blob', nav);
			var blob_a=$('.blob a.bloba', nav);
					 	
			$('li:not(.blob)', nav).hover(function(event) {
				// mouse over
				clearTimeout(reset);
				blob.css({width : $(this).width()});
				blob_a.css({width : $(this).outerWidth()-15});
				blob.animate(
					{
						left : $(this).position().left
						/* width : $(this).width() */
					},
					{
						duration : options.speed,
						easing : options.easing,
						queue : false
					}
				);
				//event.stopPropagation();
				
			}, function() {
				// mouse out	
				reset = setTimeout(function() {
					blob.css({width : currentPageItem.width()});
					blob_a.css({width : currentPageItem.outerWidth()-15});
					blob.animate({
						/* width : currentPageItem.outerWidth(), */
						left : currentPageItem.position().left
					}, options.speed)
				}, options.reset);
				
			});
		 
		
		}); // end each
	
	};

})(jQuery);