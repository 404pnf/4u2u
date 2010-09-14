if (Drupal.jsEnabled) {	
	$(document).ready(function(){
			$('#test-userreg-page-link').click(function () {
			//alert(window.location.host);
			//var mailField = $("#edit-mail");
			var requestUrl = $("#test-userreg-page-input").val();
			//alert(requestUrl);
			$.ajax({
				url:requestUrl,
				dataType: 'json',
				success: function(ret){
          if(ret['status']){
            alert('注册状态：' + ret['status']);
          }
          else {
						alert('注册状态：' + ret['status']);
						alert(ret['errors']);
          }
         
        }
			});
			
			return false;
			
		});
	});
}