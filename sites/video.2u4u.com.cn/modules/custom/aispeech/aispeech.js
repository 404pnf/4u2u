    var word = $("#spell-wrapper").html();
    
    function initRecorder(){
        var serverList = ["rtmp://cn.api.aispeech.com:443/v1.1/aistream.enscore"];
        
        window.recorder1 = new aispeech.AiRecorder({
            id: "aiRecorder",
            serverList: serverList,
						showFlash: true,
						height:183,
            appKey: "1300675449010",
            secretKey: "50b87599fcc2bd7bd27cb2799759eba59c56aaf8",
						onMicStatusChange: function(code, message){
				    //alert(code);
					  if(code == '50001'){
					     recorder1.transparentFlash();
							 recorder1.hideVolumeBar(); 
							 $('#aiRecorder').css('height',1).css('width',1);
					  }
          //recorder1AiDebug.info("JS: onMicStatusChange callback. code=" + code + ", message=" + JSON.stringify(message));
            }
        });
				//alert('开始录音！');
				//startRecord();
    }
		
    function initPlayer(){
	
			window.player1 = new aispeech.AiPlayer({
				id: "aiPlayer1",
				appKey: "1300675449010",
				secretKey: "50b87599fcc2bd7bd27cb2799759eba59c56aaf8",
				width: 1,
				height: 1,
				wmode:"Window",
				onFlashLoad: function(code, message){
						//player1AiDebug.info("JS: onFlashLoad callback, code=" + code + ", message=" + JSON.stringify(message));
				},
				onError: function(code, message){
					 // player1AiDebug.info("JS: onError callback, code=" + code + ", message=" + JSON.stringify(message));
				}
			});
			
				/*
			 window.player1 = new aispeech.AiPlayer({
            id: "aiPlayer1",
            onFlashLoad: function(code, message){
                //player1AiDebug.info("JS: onFlashLoad callback, code=" + code + ", message=" + JSON.stringify(message));
            },
            onError: function(code, message){
                //player1AiDebug.info("JS: onError callback, code=" + code + ", message=" + JSON.stringify(message));
            }
        });
        */
				
    }
		
    function showChars(){
		    //var word = $("#spell-wrapper").html();
        var html = '';
        html += "word: <b>" + $("#aispeech-word").html() + "</b>";
        $("#charsContainer").html(html);
        
    }
    
    function showScore(r){
        //var html = '';
       // html += $("#charsContainer").html();
				//alert(r.overall+ '123');
				if(r.overall == 'A'){

					$.ajax({
						type: 'POST',
						url: 'http://video.2u4u.com.cn/oral/test/point/add',
						dataType: 'json',
						success: pointadd,
						data: 'js=1&word='+$("#aispeech-word").html()
					});
					//alert(r.overall +'1234');
					var pointadd = function(data){
						//alert(data.word.spell);
						//$('#chinese-wrapper').html(data.word.chinese);
						showChars();
					}
					$("#aispeech-result2").css('display','block');
				}
        //html += "&nbsp;score: <b>" + r.overall + "</b>";
				

				if(r.overall =='A'){
				  $("#aispeech-result-A").css('display','block');

				}else if(r.overall =='B'){

					$("#aispeech-result-B").css('display','block');

				}else if(r.overall =='C'){

					$("#aispeech-result-C").css('display','block');

				}else if(r.overall =='D'){

					$("#aispeech-result-D").css('display','block');
				}else{

					$("#aispeech-result-D").css('display','block');
				}
        //$("#charsContainer").html(html);
        
    }
    
    var lastRecordId = null;
    
    function startRecord(){
    
        
        //alert('startRecord');
        var refText = $("#aispeech-word").html();
        aispeech.SpeechResource.setScoreType("4");
        aispeech.SpeechResource.setCoreType("enword");
        aispeech.SpeechResource.setRefText(refText);
        recorder1.record({
            duration: 3000 + 200 * refText.lenght,
            playNotifyAudio: true,
            serverParams: aispeech.SpeechResource.get(),
            onRecordIdGenerated: function(code, message){
                lastRecordId = message.recordId;
            },
            onStart: function(code, message){
                //startRecord callback
            },
            onStop: function(code, message){
                //stopRecord callback
								//alert('stop');
            }
        });
    }
    
    function stopRecord(){
		    //alert('recorder1 stop');
        recorder1.stop();
    }
    
    
    
    function getScore(){
        var recordId = lastRecordId;
				
        if (recordId != null) {
				    
            recorder1.getScores({
                recordId: recordId,
                success: function(data){
								    // alert(recorder1);
                    try {
                        if (typeof recordId === "string" && recordId != "") {
                            var r = "";
                            if (typeof data[recordId].result == "string") {
                                r = JSON.parse(data[recordId].result);
                            } else {
                                r = data[recordId].result;
                            }
                            //window.R = r;
														// alert("show Scroe");
                            showScore(r);
                        }else{

					                $("#aispeech-result-D").css('display','block');
												}
                    } catch (e) {

					            $("#aispeech-result-D").css('display','block');
                    }
                }
            });
        }else{

					$("#aispeech-result-D").css('display','block');
				}
    }
		
		function loadplayer(url){
		  //alert(url);
			 
			player1.load({
				url: url,
				//success: function(code, message){
						//player1AiDebug.info("JS: player1.load-success callback, code=" + code + ", message=" + JSON.stringify(message));
						//alert("JS: player1.load-success callback, code=" + code + ", message=" + JSON.stringify(message));
				//}
				success: playplayer
			});
			//alert('');
			
		}
				
				
			function playplayer(){
			  //alert('playplayer');
				//$('#charsContainer1').html('play');
				player1.play({
					onStart: function(code, message){
							//player1AiDebug.info("JS: player1.play-onStart callback, code=" + code + " message=" + JSON.stringify(message));
							//alert("JS1: player1.load-success callback, code=" + code + ", message=" + JSON.stringify(message));
					},
					onStop: function(code, message){
							//player1AiDebug.info("JS: player1.play-onStop callback, code=" + code + " message=" + JSON.stringify(message));
							//alert("JS: player1.load-success callback, code=" + code + ", message=" + JSON.stringify(message));
							showChars();
		          //initRecorder();
					}
				});
			}
    function showstep1button(){
		  $('#aispeech-table-step-1').css('display','block');
			$('#aispeech-table-step-2').css('display','none');
			$('#aispeech-table-step-3').css('display','none');
			$('#aispeech-table-step-4').css('display','none');
			$('#aispeech-footer').css('display','none');
		}
		function showstep2button(){
		  $('#aispeech-table-step-1').css('display','none');
			$('#aispeech-table-step-2').css('display','block');
			$('#aispeech-table-step-3').css('display','none');
			$('#aispeech-table-step-4').css('display','none');
		}
		function showstep3button(){
		  $('#aispeech-table-step-1').css('display','none');
			$('#aispeech-table-step-2').css('display','none');
			$('#aispeech-table-step-3').css('display','block');
			$('#aispeech-table-step-4').css('display','none');
		}
	  function showstep4button(){
		  $('#aispeech-table-step-1').css('display','none');
			$('#aispeech-table-step-2').css('display','none');
			$('#aispeech-table-step-3').css('display','none');
			$('#aispeech-table-step-4').css('display','block');
			$('#aispeech-footer').css('display','block');
		}
		
		function autotestit(){
		  $("#aispeech-center").css('display','none');
		  $("#aispeech-result").css('display','block');
		  $("#aispeech-result-A").css('display','none');
		  $("#aispeech-result-B").css('display','none');
		  $("#aispeech-result-C").css('display','none');
		  $("#aispeech-result-D").css('display','none');
			$('#defaultCountdown').removeClass('hasCountdown');
			//$(this).removeClass("one");
		  stopRecord();  
			showstep4button();
			getScore();
		}
if (Drupal.jsEnabled) {

 $(document).ready(function () { 
	window.recorder1 = undefined;
	window.player1 = undefined;
	showstep1button();
	initPlayer();
	initRecorder();
	
	$('.aispeech-tdbutton').mouseover(function(){	
	    //alert('123456');
      $(this).css("background-image","url(http://video.2u4u.com.cn/sites/video.2u4u.com.cn/modules/custom/aispeech/images/test3_light.jpg)");
			//alert($(this).css('background-image'));
	});
	$('.aispeech-tdbutton').mouseout(function(){	
	    //alert('123456');
      $(this).css("background-image","url(http://video.2u4u.com.cn/sites/video.2u4u.com.cn/modules/custom/aispeech/images/test3.jpg)");
			//alert($(this).css('background-image'));
	});
	  $('.aispeech-tdbutton2').mouseover(function(){	
	    //alert('123456');
      $(this).css("background-image","url(http://video.2u4u.com.cn/sites/video.2u4u.com.cn/modules/custom/aispeech/images/test5_light.jpg)");
			//alert($(this).css('background-image'));
	});
	$('.aispeech-tdbutton2').mouseout(function(){	
	    //alert('123456');
      $(this).css("background-image","url(http://video.2u4u.com.cn/sites/video.2u4u.com.cn/modules/custom/aispeech/images/test5.jpg)");
			//alert($(this).css('background-image'));
	});
  
	$('#followit').click(function(){	
    
		startRecord();
		showstep3button();
		var refText = $("#aispeech-word").html();
		$('#defaultCountdown').countdown({
		  until: '+'+ Math.ceil(3+0.2*refText.length)+'s',
			format: 'YOWDHMS',
			significant: 1,
			layout: '{d<}{dn} {dl} {d>}{h<}{hn} {hl} {h>}{m<}{mn} {ml} {m>}{s<}{sn} {sl}{s>}',
			onExpiry: autotestit
		}); 
	});
	$('#testit').click(function(){		
		$("#aispeech-center").css('display','none');
		$("#aispeech-result").css('display','block');
		$("#aispeech-result-A").css('display','none');
		$("#aispeech-result-B").css('display','none');
		$("#aispeech-result-C").css('display','none');
		$("#aispeech-result-D").css('display','none');
		stopRecord();
		getScore();
		//$('#aiRecorder-wrapper').html('<div id="aiRecorder"> </div>');
		//if($("#aispeech-result-A").css('display') == 'none' && $("#aispeech-result-B").css('display') == 'none' && $("#aispeech-result-C").css('display') == 'none'  && $("#aispeech-result-D").css('display') == 'none' ){
		//  $("#aispeech-result-D").css('display','block');
		//}
		showstep4button();
	});
	
	//alert($("#spell-wrapper").html());
	$('#next-word').click(function(){
	  
	  var wordnext = function(data){
		  //alert(data.word.spell);
		  $('#aispeech-word').html(data.word.spell);
			$('#aispeech-explain').html(data.word.explaination);
			//$('#chinese-wrapper').html(data.word.chinese);
			//$('#aiRecorder-wrapper').html('<div id="aiRecorder"> </div>');
			showChars();
			showstep1button();
		}
		$.ajax({
		  type: 'POST',
			url: 'http://video.2u4u.com.cn/oral/next',
			dataType: 'json',
			success: wordnext,
			data: 'js=1'
		});
		//stopRecord();
		
		
		return false;
	});
	//alert($("#spell-wrapper").html());
	$('#next-word1').click(function(){
	  
	  var wordnext = function(data){
		  //alert(data.word.spell);
			
      $("#aispeech-result").css('display','none');
      $("#aispeech-result2").css('display','none');
			$("#aispeech-result-A").css('display','none');
			$("#aispeech-result-B").css('display','none');
			$("#aispeech-result-C").css('display','none');
			$("#aispeech-result-D").css('display','none');
      $("#aispeech-center").css('display','block');
		  $('#aispeech-word').html(data.word.spell);
			$('#aispeech-explain').html(data.word.explaination);
			//$('#chinese-wrapper').html(data.word.chinese);
			//$('#aiRecorder-wrapper').html('<div id="aiRecorder"> </div>');
			//showChars();
			showstep1button();
		}
		$.ajax({
		  type: 'POST',
			url: 'http://video.2u4u.com.cn/oral/next',
			dataType: 'json',
			success: wordnext,
			data: 'js=1'
		});
		//stopRecord();
		
		
		return false;
	});
	$('#readit').click(function(){
		//alert('read it');
    if($('#aispeech-user-login').html() > 0){
		  //alert('登录用户');
		}else{
		  alert('只有登录用户才能测评，请现在登录。');
		  window.location.href = 'http://2u4u.com.cn/user/login';
		}
		/*
		var getsessionkey = function(data){
		  //alert(data.error);
	    var sessionkey = data.result.session_key;
			//alert('1234');
			//alert(sessionkey);
      // return sessionkey;
			//$('#chinese-wrapper').html(data.result.session_key);
			//alert('session:'+sessionkey);
			
			//alert(getsessionkey);
			var appKey = "1300675449010";
			var secretkey = "50b87599fcc2bd7bd27cb2799759eba59c56aaf8";
			var apiHost = "http://sandbox.api.aispeech.com";
			var apiVersion = "v1.0";
			//var apiSessionKey = null;
			//http://host/api/v1.0/synth/appkey/1295337509540/sessionkey/be7e8adc8899ba04efa41d7b3d5b1f7dfbd36cda/lang/en/text/good/model/1?rdm=001
			var rand = Math.floor(Math.random()*10+1);
			var text = $("#aispeech-word").html();
			//var  sessionkey = "12123123";
			var url = apiHost + '/api/' + apiVersion + '/synth/appkey/' + appKey + '/sessionkey/' + sessionkey +'/lang/en/text/' + text + '/model/1?rdm=00'+rand;
			loadplayer(url);
			// playplayer();	
			showstep2button();
			
			
		}
		*/
		//initRecorder();	
		if(recorder1 === undefined){
		 // alert('init');
		   initRecorder();	
			
		}else{
		  //alert("已经存在");
		}
		
		if(player1 === undefined){
		 // alert('init');
		   initPlayer();	
			
		}else{
		  //alert("已经存在");
		}
		
		/*
		
		$.ajax({
		  type: 'POST',
			url: 'http://video.2u4u.com.cn/oral/test/session/key',
			dataType: 'json',
			success: getsessionkey,
			data: 'js=1'
		});
		*/
		var appKey = "1300675449010";
		var sessionKey = "null";

		var lang = 'en';
		var text = $("#aispeech-word").html();
		var coreType = 'en.sent.syn';
		var resource = 'syn_enwds_liuyim';
		//alert(text);
		var r = player1.synth({
				applicationId: appKey,
				ttsUrl: "http://video.2u4u.com.cn/sites/video.2u4u.com.cn/modules/custom/aispeech/tts-v1.1.php",
			//ttsUrl: "http://video.2u4u.com.cn/oral/test/session/key",
				
				lang: lang,
				text: text,
				coreType: coreType,
				resource: resource,
				player: player1,
				onGetSessionSuccess: function(data){
				//alert('success');
				//alert(data.session);
						//$("#sessionKey").html(data.session);
				},
				onPlayStop: function(code, message){
				 // alert('123');
				   showstep2button();
						//player1AiDebug.info("JS: playStop callback, code=" + code + ", message=" + JSON.stringify(message));
				}
		});
		//showstep2button();
		return false;
		
	
	});
	
 });	


}
