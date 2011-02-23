// $Id: swftools_wijering4.js,v 1.1.2.4 2010/03/29 22:07:14 stuartgreenfield Exp $

/**
 * Ensure swftools namespace is established.
 */
var swftools = swftools || {};

/**
 * Callback from LongTail player when an instance is initialized. 
 */
function playerReady(player) {
  swftools.wijering4.pushInstance(player.id);
  player = swftools.getObject(player.id);
  player.addModelListener('STATE','swftools.wijering4.stateTracker');
};

/**
* Define LongTail player functions here.
*/
swftools.wijering4 = function() {
  var instances = [];
  var activePlayer = null;
  return {
    pushInstance: function(playerID) {
      instances.push(playerID);
    },
    stateTracker: function(player) {
      // States are: IDLE, BUFFERING, PLAYING, PAUSED, COMPLETED
      if (player.newstate == 'PAUSED' || player.newstate == 'COMPLETED') {
        activePlayer = null;
      }
      // Pause other players when another one starts
      if (player.newstate == 'PLAYING') {
        if (activePlayer && player.id != activePlayer) {
          swftools.wijering4.pause(activePlayer);
        }
        activePlayer = player.id;
      }
    },
    play: function(playerID) {
      swftools.getObject(playerID).sendEvent('PLAY', 'true');
    },
    pause: function(playerID) {
      swftools.getObject(playerID).sendEvent('PLAY', 'false');
    },
    stop: function(playerID) {
      swftools.getObject(playerID).sendEvent('STOP');
    },
    mute: function(playerID) {
      swftools.getObject(playerID).sendEvent('MUTE', 'true');
    },
    unmute: function(playerID) {
      swftools.getObject(playerID).sendEvent('MUTE');
    }
  }
}();

Drupal.behaviors.swftools_wijering4 = function (context) {
  $('[class^=wijering4-accessible]:not(.swftools-wijering4-processed)', context).addClass('swftools-wijering4-processed').each(function () {
    $(this).click(function(){
      var classes = $(this).attr('class');
      var classes = classes.split(' ');
      var parts = classes[0].split('-');
      var idStarts = 22 + parts[2].length;
      var action = "swftools.wijering4." + parts[2] + "('" + classes[0].substring(idStarts) + "')";
      eval(action);
      return false;
    });
  });
}
