/*
 * AISpeech API provides AI Speech Ltd's (www.aispeech.com) world leading pronunciation
 * evaluation,speech recognition technologies, and text-to-speech technologies.
 *
 * AI Speech Ltd opens this API hoping make every programmer be capable to
 * implement speech enabled applicaitons.
 *
 * Copyright (c) 2008-2011 by AISpeech. All rights reserved.
 *
 */
window.aispeech = window.aispeech || {};
(function(){

    aispeech.getCss = function(src){
        document.write('<' + 'link href="' + src + '"' +
        ' rel="stylesheet" type="text/css" />');
    }
    
    aispeech.getScript = function(src){
        document.write('<' + 'script src="' + src + '"' +
        ' type="text/javascript"><' +
        '/script>');
    }
    
    aispeech.loadScriptTime = (new Date).getTime();
    aispeech.host = aispeech.host || "http://sandbox.api.aispeech.com/aispeechapi-js";
    
    aispeech.getCss(aispeech.host + "/aidebug/aidebug.css");
    
    //aispeech.getScript(aispeech.host + "/common/swfobject.js");
    //aispeech.getScript(aispeech.host + "/common/ufo.js");
    //aispeech.getScript(aispeech.host + "/common/AiFlashDetect.js");
    //aispeech.getScript(aispeech.host + "/common/AiStatusCode.js");
    //aispeech.getScript(aispeech.host + "/aidebug/json2.js");
    //aispeech.getScript(aispeech.host + "/aidebug/AiDebug.js");
    //aispeech.getScript(aispeech.host + "/aiplayer/AiPlayer.js");
    //aispeech.getScript(aispeech.host + "/airecorder/SpeechResource.js");
    //aispeech.getScript(aispeech.host + "/airecorder/AiRecorder.js");
    //aispeech.getScript(aispeech.host + "/aitone/AiTone.js");
    aispeech.getScript(aispeech.host + "/min/aispeech-core-min.js");
})();
