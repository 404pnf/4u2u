function performRequest( cmdName, params){
	
	
	
	switch(cmdName){
		case "paihang":
		;
		case "shoucang":	
		;
		case "info":	
		;
		case "lishi":	
			var btnleft = params.btnLeft;
			var btnwidth = params.btnwidth;
			var btnstatus = params.btnstatus;
			var re = displayOverlayer(cmdName, btnleft, btnwidth, btnstatus);
		break;
		case "yanzheng":
			var btnleft = params.btnLeft;
			var btnwidth = params.btnwidth;
			var btnstatus = params.btnstatus;
			var machineID = params.machineID;
			yanzhengAddMachineID(cmdName, machineID)
			var re = displayOverlayer(cmdName, btnleft, btnwidth, btnstatus);
		break;
		default:
			alert('cmdName:'+cmdName);
		break;
	}
	
	return re;
}


function displayOverlayer(cmdName, btnleft, btnwidth, btnstatus){
	
	
	
	var contentId = $('#over_'+cmdName+' .content');
	var contentW = contentId.width()>300?contentId.width():300;
	var arrowleft = Number(btnleft) + btnwidth/2-8;
	var contentleft = Number(btnleft)+contentW;
//alert(' cmdName:'+cmdName+' btnleft:'+btnleft+' contentleft:'+contentleft+' btnstatus:'+btnstatus);

	$('#over_'+cmdName+' .arrow').css({'left':arrowleft+'px'});

	if(contentleft>600){
		contentId.css({'right':'20px'});
		
	}
	else{
		contentId.css({'left':btnleft+'px'});
	}
	
	if(btnstatus == '' || btnstatus == 'normal' || btnstatus == 'touched'){
		
		$('.overlayer').hide('fast');
		
		$('#over_'+cmdName).toggle('slow');
	}				
	else {
		$('.overlayer').hide('fast');
	}
	
	return 'success';
}

function yanzhengAddMachineID(cmdName, machineID){
	var machineIDinput = $('#over_'+cmdName+' .content #edit-machineID');
	
	machineIDinput.val(machineID);
	alert(' machineID:'+machineID);
	
}