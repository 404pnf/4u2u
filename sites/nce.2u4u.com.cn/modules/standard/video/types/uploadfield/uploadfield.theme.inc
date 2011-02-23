<?php
//$Id: uploadfield.theme.inc,v 1.1.2.1 2010/04/27 15:34:46 iLLin Exp $
/**
 * 
 * @file
 * Theme functions for the videoftp module.
 */

/**
 * FormAPI theme function. Theme the output of an video upload field.
 */
function theme_uploadfield_widget($element) {
  return theme('form_element', $element, $element['#children']);
}

function theme_uploadfield_widget_item($element) {
  return theme('filefield_widget_item', $element);
}