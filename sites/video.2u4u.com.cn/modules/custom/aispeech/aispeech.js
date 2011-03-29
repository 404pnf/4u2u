    var word = $("#spell-wrapper").html();
    
    function initRecorder(){
        var serverList = ["rtmp://sandbox.api.aispeech.com/aistream.enscore.v1.0"];
        
        window.recorder1 = new aispeech.AiRecorder({
            id: "aiRecorder",
            serverList: serverList,
						// showFlash: false,
						height:200,
            appKey: "1300675449010",
            secretKey: "50b87599fcc2bd7bd27cb2799759eba59c56aaf8"
        });
				alert('开始录音！');
				startRecord();
    }
    
    function showChars(){
		    //var word = $("#spell-wrapper").html();
        var html = '';
        html += "word: <b>" + $("#aispeech-word").html() + "</b>";
        $("#charsContainer").html(html);
        
    }
    
    function showScore(r){
        var html = '';
        html += $("#charsContainer").html();
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
        html += "&nbsp;score: <b>" + r.overall + "</b>";
				
				$("#aispeech-center").css('display','none');
				$("#aispeech-result").css('display','block');
				if(r.overall =='A'){
				  $("#aispeech-result-A").css('display','block');
					$("#aispeech-result-B").css('display','none');
					$("#aispeech-result-C").css('display','none');
					$("#aispeech-result-D").css('display','none');
				}else if(r.overall =='B'){
				  $("#aispeech-result-A").css('display','none');
					$("#aispeech-result-B").css('display','block');
					$("#aispeech-result-C").css('display','none');
					$("#aispeech-result-D").css('display','none');
				}else if(r.overall =='C'){
				   $("#aispeech-result-A").css('display','none');
					$("#aispeech-result-B").css('display','none');
					$("#aispeech-result-C").css('display','block');
					$("#aispeech-result-D").css('display','none');
				}else if(r.overall =='D'){
				   $("#aispeech-result-A").css('display','none');
					$("#aispeech-result-B").css('display','none');
					$("#aispeech-result-C").css('display','none');
					$("#aispeech-result-D").css('display','block');
				}else{
				  $("#aispeech-result-A").css('display','none');
					$("#aispeech-result-B").css('display','none');
					$("#aispeech-result-C").css('display','none');
					$("#aispeech-result-D").css('display','block');
				}
        //$("#charsContainer").html(html);
        
    }
    
    var lastRecordId = null;
    
    function startRecord(){
    
        
        //alert('showChars();');
        var refText = $("#aispeech-word").html();
        aispeech.SpeechResource.setScoreType("4");
        aispeech.SpeechResource.setCoreType("enword");
        aispeech.SpeechResource.setRefText(refText);
        recorder1.record({
            duration: 3000,
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
		    alert('recorder1 stop');
        recorder1.stop();
    }
    
    
    
    function getScore(){
        var recordId = lastRecordId;
				//alert(recordId);
        if (recordId != null) {
            recorder1.getScores({
                recordId: recordId,
                success: function(data){
                    try {
                        if (typeof recordId === "string" && recordId != "") {
                            var r = "";
                            if (typeof data[recordId].result == "string") {
                                r = JSON.parse(data[recordId].result);
                            } else {
                                r = data[recordId].result;
                            }
                            //window.R = r;
                            showScore(r);
                        }
                    } catch (e) {
                    }
                }
            });
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
				success: playplayer,
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
		}

if (Drupal.jsEnabled) {

 $(document).ready(function () { 
	
	showstep1button();
  
	$('#followit').click(function(){	
    initRecorder();	
		
		showstep3button();
	});
	$('#testit').click(function(){		
		getScore();
		$('#aiRecorder-wrapper').html('<div id="aiRecorder"> </div>');
		showstep4button();
	});
	
	//alert($("#spell-wrapper").html());
	$('#next-word').click(function(){
	  
	  var wordnext = function(data){
		  //alert(data.word.spell);
		  $('#aispeech-word').html(data.word.spell);
			$('#aispeech-explain').html(data.word.explaination);
			//$('#chinese-wrapper').html(data.word.chinese);
			$('#aiRecorder-wrapper').html('<div id="aiRecorder"> </div>');
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
			$('#aiRecorder-wrapper').html('<div id="aiRecorder"> </div>');
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
		
		window.player1 = new aispeech.AiPlayer({
			id: "aiPlayer1",
			appKey: "1298426941825",
			secretKey: "595fd7706b9a96bd892a0c88a2e772b0d0565316",
			width: 10,
			height: 10,
			wmode:"Window",
			onFlashLoad: function(code, message){
					//player1AiDebug.info("JS: onFlashLoad callback, code=" + code + ", message=" + JSON.stringify(message));
			},
			onError: function(code, message){
				 // player1AiDebug.info("JS: onError callback, code=" + code + ", message=" + JSON.stringify(message));
			}
	  });
		
		var getsessionkey = function(data){
		  //alert(data.error);
	    var sessionkey = data.result.session_key;
			//alert('1234');
			//alert(sessionkey);
      // return sessionkey;
			//$('#chinese-wrapper').html(data.result.session_key);
			//alert('session:'+sessionkey);
			
			//alert(getsessionkey);
			var appKey = "1298426941825";
			var secretkey = "595fd7706b9a96bd892a0c88a2e772b0d0565316";
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
		
		
		
		
		
		$.ajax({
		  type: 'POST',
			url: 'http://video.2u4u.com.cn/oral/test/session/key',
			dataType: 'json',
			success: getsessionkey,
			data: 'js=1'
		});
		
		
	
	});
	
 });	


}
