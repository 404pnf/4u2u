// $Id: swftools.js,v 1.1.2.5 2010/03/31 22:23:37 stuartgreenfield Exp $

/**
 * Ensure swftools namespace is established.
 */
var swftools = swftools || {};

/**
 * Returns a DOM object that points to the flash content with the supplied id. 
 */
swftools.getObject = function(objectID) {
  
  // Get the base object
  swftoolsObject = document.getElementById(objectID);
  
  // See if we can get the object like this (IE/Chrome)
  if (typeof swftoolsObject == 'object') {
    return swftoolsObject;
  }
  // See if we can get the object like this (FF with swfobject embedding)
  if (typeof swftoolsObject.attributes.type != 'undefined' && swftoolsObject.attributes.type.value == 'application/x-shockwave-flash') {
    return swftoolsObject;
  }
  // Otherwise try this (FF with direct embedding)
  return swftoolsObject.getElementsByTagName('object')[0];
}

