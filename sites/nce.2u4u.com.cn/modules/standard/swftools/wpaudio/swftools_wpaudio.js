// $Id: swftools_wpaudio.js,v 1.1.2.11 2010/04/07 21:33:36 stuartgreenfield Exp $

/**
 * WordPress audio player functions exist in the AudioPlayer namespace.
 */    
var AudioPlayer = function () {
  var instances = [];
  var activePlayerID;
  var currentVolume = -1;
  return {
    syncVolumes: function (playerID, volume) {
      currentVolume = volume;
      for (var i = 0; i < instances.length; i++) {
        if (instances[i] != playerID) {
          swftools.getObject(instances[i]).setVolume(currentVolume);
        }
      }
    },
    activate: function (playerID, info) {
      if (activePlayerID && activePlayerID != playerID) {
        swftools.getObject(activePlayerID).close();
      }
      activePlayerID = playerID;
    },
    close: function (playerID) {
      swftools.getObject(playerID).close();
      if (playerID == activePlayerID) {
        activePlayerID = null;
      }
    },
    open: function (playerID, index) {
      swftools.getObject(playerID).open(index == undefined ? 0 : index-1);
    },
    pushInstance: function (playerID) {
      instances.push(playerID);
    },
  }
}();

Drupal.behaviors.swftools_wpaudio = function (context) {
  $('.swftools-wpaudio:not(.swftools-wpaudio-processed)', context).addClass('swftools-wpaudio-processed').each(function () {
    AudioPlayer.pushInstance($(this).attr('id').substring(9));
  });
  $('[class^=wpaudio-accessible]:not(.swftools-wpaudio-processed)', context).addClass('swftools-wpaudio-processed').each(function () {
    $(this).click(function(){
      var classes = $(this).attr('class');
      var classes = classes.split(' ');
      var parts = classes[0].split('-');
      var idStarts = 20 + parts[2].length;
      var action = "AudioPlayer." + parts[2] + "('" + classes[0].substring(idStarts) + "')";
      eval(action);
      return false;
    });
  });
};
