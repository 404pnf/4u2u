// $Id: swftools_onepixelout.js,v 1.1.2.7 2010/04/07 21:33:36 stuartgreenfield Exp $

/**
 * Ensure swftools namespace is established.
 */
var swftools = swftools || {};

/**
 * Callback from OnePixelOut to stop all players when a player is stopped. 
 */
function ap_stopAll(playerID) {
  swftools.onepixelout.closeAll(playerID);
}

/**
 * Define OnePixelOut functions here.
 */
swftools.onepixelout = function() {
  var instances = [];
  return {
    pushInstance: function(playerID) {
      instances.push(playerID);
    },
    closeAll: function(playerID) {
      for(var i = 0; i < instances.length; i++) {
        player = swftools.getObject('swf-' + instances[i]);
        if(instances[i] != playerID) {
          player.SetVariable('closePlayer', 1);
        }
        else {
          player.SetVariable('closePlayer', 0);
        }
      }
    },
  }
}();

Drupal.behaviors.swftools_onepixelout = function (context) {
  $('.swftools-onepixelout:not(.swftools-onepixelout-processed)', context).addClass('swftools-onepixelout-processed').each(function () {
    swftools.onepixelout.pushInstance($(this).attr('id').substring(13));
  });
}
