﻿/** * Copyright 2008 - TMTDigital LLC * * Author:   Travis Tidwell (www.travistidwell.com) * Version:  1.0 * Date:     June 9th, 2008 * * Description:  Functionality for the menu section of the Dash Player. * **/package com.tmtdigital.dash.display.ads{   import com.tmtdigital.dash.display.ads.Ad;   import flash.display.*;   public class TextAd extends Ad   {      public function TextAd( _skin:MovieClip )      {         super( _skin );      }      public override function setSkin(_skin:MovieClip)      {         super.setSkin(_skin);         type = "text";           title = skin.title;         body = skin.body;         addLink( title );         addLink( body );      }      public override function onAdLoad( _ad:Object )      {         super.onAdLoad( _ad );                  if( title && title.txt ) {            title.txt.text = ad.title;         }                  if( body && body.txt ) {            body.txt.text = ad.body;         }      }      public override function onHideShow( state:Boolean )      {         if ( rootSkin && (rootSkin.hideShowTextAd is Function) ) {            rootSkin.hideShowTextAd( state );         }            }      public var title:MovieClip;      public var body:MovieClip;   }}