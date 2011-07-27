// $Id: sina_open.js,v 1.2 2011/02/11 03:52:44 eastcn Exp $

Drupal.behaviors.sina_open = function (context) {
	
	function c() {
		var _c = 140;
		var b = $('#edit-sina-open-tweet-text').val();
		if (b.length < _c) {
			_c -= b.length;
		} else if (b.length > _c) {
			_c -= b.length;
			//alert('太长了');
		} else {
			_c = 0;
		}
		$('#sina_open_tweet_text_count').text(_c);
	};
	
	c();
	
	$('#edit-sina-open-tweet-text').bind('keyup', c);
	$('#edit-sina-open-tweet-text').bind('mouseup', c);
}