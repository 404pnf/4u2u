<?php
// $Id: swftools_imagerotator.admin.inc,v 1.1.2.6 2010/04/04 23:36:21 stuartgreenfield Exp $

function swftools_imagerotator_admin_form() {

  // Retrieve default or saved settings
  $saved_settings = _swftools_imagerotator_settings();

  // Retrieve options needed to populate select elements
  $options = _swftools_imagerotator_options();
  
  // See if colorpicker 2 is loaded
  $colorfield = function_exists('colorpicker_2_or_later') ? 'colorpicker_textfield' : 'textfield';
  
  // Initialise array to hold form
  $form = array();

  $form['swftools_imagerotator']['basic'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Basic'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['swftools_imagerotator']['basic']['height'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['basic']['height'],
    '#size' => 8,
    '#maxlength' => 5,
    '#title' => t('Height'),
    '#description' => t('Leave blank for default. (<em>height</em>)'),
  );
  
  $form['swftools_imagerotator']['basic']['width'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['basic']['width'],
    '#size' => 8,
    '#maxlength' => 5,
    '#title' => t('Width'),
    '#description' => t('Leave blank for default. (<em>width</em>)'),
  );
  
  $form['swftools_imagerotator']['color'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Color'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['swftools_imagerotator']['color']['backcolor'] = array(
    '#type' => $colorfield,
    '#default_value' => $saved_settings['color']['backcolor'],
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Background color'),
    '#description' => t('Enter a hex value eg. for white enter <b>#FFFFFF</b>. (<em>backcolor</em>)'),
  );
  
  $form['swftools_imagerotator']['color']['frontcolor'] = array(
    '#type' => $colorfield,
    '#default_value' => $saved_settings['color']['frontcolor'],
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Text color'),
    '#description' => t('Enter a hex value eg. for white enter <b>#FFFFFF</b>. (<em>frontcolor</em>)'),
  );
  
  $form['swftools_imagerotator']['color']['lightcolor'] = array(
    '#type' => $colorfield,
    '#default_value' => $saved_settings['color']['lightcolor'],
    '#size' => 8,
    '#maxlength' => 7,
    '#title' => t('Rollover color'),
    '#description' => t('Enter a hex value eg. for white enter <b>#FFFFFF</b>. (<em>lightcolor</em>)'),
  );
  
  $form['swftools_imagerotator']['appearance'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Appearance'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['swftools_imagerotator']['appearance']['logo'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['appearance']['logo'],
    '#title' => t('Logo URL'),
    '#description' => t('Full url to logo for a watermark, use PNG files for best results. (<em>logo</em>)'),
  );
  
  $form['swftools_imagerotator']['appearance']['overstretch'] = array(
    '#type' => 'select',
    '#default_value' => $saved_settings['appearance']['overstretch'],
    '#title' => t('Overstretch'),
    '#options' => $options['overstretch'],
    '#description' => t('Defines how to stretch images to fit the display. (<em>overstretch</em>)'),
  );
  
  $form['swftools_imagerotator']['appearance']['showicons'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['appearance']['showicons'],
    '#title' => t('Show icons'),
    '#description' => t('Show status icons in display. (<em>showicons</em>)'),
  );
  
  $form['swftools_imagerotator']['appearance']['shownavigation'] = array(
    '#type' => 'select',
    '#default_value' => $saved_settings['appearance']['shownavigation'],
    '#options' => $options['bool'],
    '#title' => t('Show navigation'),
    '#description' => t('If false then all navigation controls are hidden. (<em>shownavigation</em>)'),
  );
  
  $form['swftools_imagerotator']['appearance']['transition'] = array(
    '#type' => 'select',
    '#default_value' => $saved_settings['appearance']['transition'],
    '#options' => $options['transition'],
    '#title' => t('Transition effect'),
    '#description' => t('The way the photos change from one to another. (<em>transition</em>)'),
  );
  
  $form['swftools_imagerotator']['playback'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Playback'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['swftools_imagerotator']['playback']['rotatetime'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['playback']['rotatetime'],
    '#size' => 5,
    '#maxlength' => 3,
    '#title' => t('Rotate time'),
    '#description' => t('Number of seconds between image rotations. (<em>rotatetime</em>)'),
  );
  
  $form['swftools_imagerotator']['playback']['shuffle'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['playback']['shuffle'],
    '#title' => t('Shuffle'),
    '#description' => t('Shuffle media randomly. (<em>shuffle</em>)'),
  );
  
  $form['swftools_imagerotator']['interaction'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Interaction'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['swftools_imagerotator']['interaction']['enablejs'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['interaction']['enablejs'],
    '#title' => t('Enable JavaScript'),
    '#description' => t('Enable JavaScript interaction with the flash player. (<em>enablejs</em>)'),
  );
  
  $form['swftools_imagerotator']['interaction']['link'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved_settings['interaction']['link'],
    '#title' => t('Link URL'),
    '#description' => t('Web address linked to logo watermark. (<em>link</em>)'),
  );
  
  $form['swftools_imagerotator']['interaction']['linkfromdisplay'] = array(
    '#type' => 'select',
    '#options' => $options['bool'],
    '#default_value' => $saved_settings['interaction']['linkfromdisplay'],
    '#title' => t('Link from display'),
    '#description' => t('Link "Link URL" but with the whole display as the click area. (<em>linkfromdisplay</em>)'),
  );
  
  $form['swftools_imagerotator']['interaction']['linktarget'] = array(
    '#type' => 'select',
    '#default_value' => $saved_settings['interaction']['linktarget'],
    '#options' => $options['linktarget'],
    '#title' => t('Link target'),
    '#description' => t('Target of "Link URL". (<em>linktarget</em>)'),
  );

  // Initialise tree for these settings
  $form['swftools_imagerotator']['#tree'] = TRUE;

  // Add custom form handler to flush cache upon submit
  $form['#submit'][] = 'swftools_admin_settings_submit';
  
  // Return finished form
  return system_settings_form($form);

}


/**
 * flashvar and param option arrays. These are used for options settings in the
 * configuration screen.
 */
function _swftools_imagerotator_options() {
  $options['overstretch'] = array('default' => 'default', 'false' => 'false', 'true' => 'true', 'fit' => 'fit', 'none' => 'none', );
  $options['repeat'] = array('default' => 'default', 'false' => 'false', 'true' => 'true', 'list' => 'list', );
  $options['linktarget'] = array('default' => 'default', '_self' => '_self', '_blank' => '_blank', );
  $options['transition'] = array('default' => 'default', 'fade' => 'fade', 'bgfade' => 'bgfade', 'blocks' => 'blocks', 'bubbles' => 'bubbles', 'circles' => 'circles', 'flash' => 'flash', 'fluids' => 'fluids', 'lines' => 'lines', 'slowfade' => 'slowfade', 'random' => 'random', );
  $options['bool'] = array('default' => 'default', 'true' => 'true', 'false' => 'false');
  return $options;
}
