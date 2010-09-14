

if(Drupal.jsEnabled) {

	$(document).ready(function(){ 
	
		$('a.points-linka').click(function(){

		var pointsmes = function(data){
					$('div.points-message').html(data.message);
					$('#points-link').hide();
				}
		
		$.ajax({
			
			type: 'POST',
			url: this.href,
			dataType: 'json',
			success: pointsmes,
			data: 'js=1',
		
		});

		return false;

		});
	
	});

}