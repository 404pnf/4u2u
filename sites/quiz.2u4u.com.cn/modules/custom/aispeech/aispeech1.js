    var player1AiDebug = new aispeech.AiDebug("player1AiDebug");
    
    function jsLog(text){
        var html = $("#player1AiDebug").html();
        $("#player1AiDebug").html(text + "<br />" + html);
    }
    
    window.onload = function(){
        
        window.player1 = new aispeech.AiPlayer({
            id: "aiPlayer1",
            appKey: "1298426941825",
            secretKey: "595fd7706b9a96bd892a0c88a2e772b0d0565316",
						width: 200,
						height: 200,
						wmode:"Window",
            onFlashLoad: function(code, message){
                //player1AiDebug.info("JS: onFlashLoad callback, code=" + code + ", message=" + JSON.stringify(message));
            },
            onError: function(code, message){
               // player1AiDebug.info("JS: onError callback, code=" + code + ", message=" + JSON.stringify(message));
            }
        });
        //=====================================================================
        
        $("#player1Load").click(function(){//º”‘ÿ“Ù∆µ
            var r = player1.load({
                url: $("#player1LoadUrl").val(),
                success: function(code, message){
                    player1AiDebug.info("JS: player1.load-success callback, code=" + code + ", message=" + JSON.stringify(message));
                }
            });
            player1AiDebug.log("JS: player1.load clicked ", r);
        });
        
        $("#player1Play").click(function(){//≤•∑≈“Ù∆µ
            var position = ($("#player1PlayPosition").val() == "") ? "" : parseFloat($("#player1PlayPosition").val());
            var duration = ($("#player1PlayDuration").val() == "") ? "" : parseFloat($("#player1PlayDuration").val());
            var r = player1.play({
                position: position,
                duration: duration,
                onStart: function(code, message){
                    player1AiDebug.info("JS: player1.play-onStart callback, code=" + code + " message=" + JSON.stringify(message));
                },
                onStop: function(code, message){
                    player1AiDebug.info("JS: player1.play-onStop callback, code=" + code + " message=" + JSON.stringify(message));
                }
            });
            player1AiDebug.log("JS: player1.play clicked ", r);
        });
        
        $("#player1Stop").click(function(){//Õ£÷π≤•∑≈“Ù∆µ
            var r = player1.stop({
                onStop: function(code, message){
                    player1AiDebug.info("JS: player1.stop-onStop callback, code=" + code + " message=" + JSON.stringify(message));
                }
            });
            player1AiDebug.log("JS: player1.stop clicked ", r);
        });
        


        //=====================================================================
    }

