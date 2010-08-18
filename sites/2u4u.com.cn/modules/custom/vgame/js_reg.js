Drupal.behaviors.vgame = function () {

	$(document).ready(function(){
		 $("#edit-profile-school-wrapper").hide();
		 $("#edit-profile-school-iother-wrapper").hide();
		 $("#edit-profile-vgame-cat-wrapper").hide();
		 $("#edit-profile-vgame-entry").change(function () {
	          var str = "";
	          
	          str =$("#edit-profile-vgame-entry option:selected").text();
	            
	          if(str == "集体"){
	        	  $("#edit-profile-vgame-cat-wrapper").show();
	        	  $("#edit-profile-vgame-cat option").remove();
	        	  $("#edit-profile-vgame-cat").append("<option value='小学'>小学</option>");
	        	  $("#edit-profile-vgame-cat").append("<option value='初中'>初中</option>");
	        	  $("#edit-profile-vgame-cat").append("<option value='高中'>高中</option>");
	          }
	          if(str == "个人"){
	        	  $("#edit-profile-vgame-cat-wrapper").show();
	        	  $("#edit-profile-vgame-cat option").remove();
	        	  $("#edit-profile-vgame-cat").append("<option value='大学'>大学</option>");
	        	  $("#edit-profile-vgame-cat").append("<option value='社会'>社会</option>");
	          }
	     });
		 $("#edit-profile-city").change(function () {
			 $("#edit-profile-school-wrapper").show();
			 $("#edit-profile-school-iother-wrapper").show();
	          var city = "";
	          
	          city =$("#edit-profile-city option:selected").text();
	          var city_long=city.length;
	          $("#edit-profile-city option").each(function() {

	        	  if ($( this ).text() != city  ){
	        		 
	        			  $( this ).remove();
	        		 
	        		 
	        	  }
	           });
	          $("#edit-profile-school option").each(function() {
	        	  var school="";
	        	  school = $( this ).text();
	        	  
	        	  var pos = school.indexOf(city);
	        	  
	        	  if (pos == "-1"  ){
	        		  if(school != "我不是学生"){
	        			  $( this ).remove();
	        		  }
	        		 
	        	  }
	           });

	     });
    	
	});

};