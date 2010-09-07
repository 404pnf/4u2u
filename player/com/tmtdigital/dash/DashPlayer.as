﻿/** * DashPlayer.as - See class description for information. * * Author - Travis Tidwell ( travist@tmtdigital.com ) * License - General Public License ( GPL version 3 ) * * This program is free software; you can redistribute it and/or modify * it under the terms of the GNU General Public License as published by * the Free Software Foundation; either version 3 of the License, or * (at your option) any later version. *  * This program is distributed in the hope that it will be useful, * but WITHOUT ANY WARRANTY; without even the implied warranty of * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the * GNU General Public License for more details. *  * You should have received a copy of the GNU General Public License * along with this program. If not, see http://www.gnu.org/licenses/ **/package com.tmtdigital.dash{	import com.tmtdigital.dash.display.Dash;	import com.tmtdigital.dash.display.PreLoader;   import com.tmtdigital.dash.display.Fields;   import com.tmtdigital.dash.display.node.NodeBase;   import com.tmtdigital.dash.display.Playlist;   import com.tmtdigital.dash.display.media.MediaPlayer;   import com.tmtdigital.dash.display.node.Node;   import com.tmtdigital.dash.utils.Utils;   import com.tmtdigital.dash.utils.Resizer;   import com.tmtdigital.dash.utils.LayoutManager;   import com.tmtdigital.dash.net.Gateway;   import com.tmtdigital.dash.net.Service;   import com.tmtdigital.dash.config.Params;   import flash.display.*;   import flash.events.*;   import flash.ui.*;   import flash.system.*;   import flash.net.*;   import flash.utils.*;   import flash.geom.*;   import fl.transitions.*;   import fl.transitions.easing.*;   /**    *  The DashPlayer class is used as the entry point for the Dash Media Player.    *  It works by triggering when this player has been added to the screen.  Once    *  this occurs, it then triggers a load process which loads all components within    *  the player.    *  <h5>Usage:</h5>    *  <div style="margin-left:20px;">    *  <code>    *    var dashPlayer:DashPlayer = new DashPlayer();<br/>    *    addChild( dashPlayer );<br/>    *  </code>    *  </div></p>    */   public class DashPlayer extends MovieClip   {		private static const dashWebsite:String = "http://www.tmtdigital.com/project/dash_player";				      // Check the mouse state every 1/3 second.      private static const mouseTimerInterval:uint = 300;      // The load parameters.      private static const LOAD_PARAMS:String = "loadParams";		private static const LOAD_PRELOADER:String = "loadPreLoader";      private static const LOAD_SKIN:String = "loadSkin";      private static const LOAD_THEME:String = "loadTheme";      private static const LOAD_SERVICE:String = "loadService";      private static const SHOW_PLAYER:String = "showPlayer";      private static const LOAD_GATEWAY:String = "loadGateway";      private static const LOAD_CONTENT:String = "loadContent";				/**		 * Constructor for the Dash Media Player.  This simply adds an 		 * event handler to trigger when the player has been added to the page.		 */      public function DashPlayer()      {         super();		 Security.allowDomain("static.plymedia.com");         Security.allowDomain("content.plymedia.com");            addEventListener( Event.ADDED_TO_STAGE, onAdded );      }      // Called when the player has been added to the stage.      private function onAdded( event:Event )      {         loadPlayer( stage );      }				/**		 * Called when the player has been added to the state.  This function triggers		 * the load process for the Dash media player.  Its purpose is it set up the timers		 * as well as set up the stage scale mode, alignment, and resize handler.  When it		 * is done doing this it triggers the <strong>loadProcess</strong> function.		 *		 * @see loadProcess		 * @param playerStage - This is the stage that this player is loaded onto.  The reason		 * this needs to be passed into this function is because the DashPlayer class acts as		 * a singleton, and therefore, needs to retain the stage instance as a static member variable.		 */		      public static function loadPlayer( playerStage:Stage )       {         // Store the stage instance.         _stage = playerStage;                  // Set up the mouse timer.  This is used to keep track of the mouse position during full screen mode.         mouseTimer = new Timer(mouseTimerInterval);         mouseTimer.addEventListener( TimerEvent.TIMER, onMouseTimer );         mouseTimer.stop();         // Initialize the load state.  Loading the parameters is the first thing this player does.         loadState = LOAD_PARAMS;         // Setup the stage.         _stage.scaleMode = StageScaleMode.NO_SCALE;         _stage.align = StageAlign.TOP_LEFT;         _stage.addEventListener(Event.RESIZE, resizeHandler);			                  // Begin the load process.         loadProcess();      }		/**		 * The load process state machine for the Dash Media Player.  This function keeps track		 * of each load state, and then processes the next load process when the previous one completes.		 */      public static function loadProcess()      {         if (! loaded) {            switch ( loadState ) {                           // Load the parameters.               case LOAD_PARAMS :                  loadState = LOAD_PRELOADER;                  Params.loadParams( _stage.root.loaderInfo, loadProcess );                  break;               // Load the pre-loader.					case LOAD_PRELOADER:						loadState = LOAD_SERVICE;						preLoader = new PreLoader( _stage, loadProcess );						break;											// Load the service.               case LOAD_SERVICE :                  loadState = LOAD_SKIN;                  Service.connect( loadProcess );                  break;               // Load the skin.               case LOAD_SKIN :                  loadState = LOAD_THEME;                  loadDash();                  break;               // Load the theme.               case LOAD_THEME :                  loadState = SHOW_PLAYER;                  LayoutManager.loadTheme( loadProcess );                  break;               // Show the player.               case SHOW_PLAYER:                  loadState = LOAD_GATEWAY;                  showPlayer();                  break;               // Load the gateway.               case LOAD_GATEWAY :                  loadState = LOAD_CONTENT;                  Gateway.loadGateway( loadProcess );                  break;               // Load the content.               case LOAD_CONTENT :                  dash.loadContent();                  loaded = true;                  break;            }         }      }		/**		 * The resize handler for the Dash Media Player.  This method gets called whenever the player is 		 * resized.  It then triggers the Resizer component to resize all the elements provided within		 * the <strong>getLayoutInfo</strong> function within the <strong>skin.as</strong> file.  It also		 * keeps track of the fullscreen state of the player, where it performs certain setup and teardown		 * for the full screen state.		 *		 * @see setupFullScreen		 * @param event - This is the resize event passed to this function from Flash when the player is resized.		 */      public static function resizeHandler(event:Event):void      {         // We only want to resize if the player is visible.         if (playerVisible) {                     // Store the full screen mode.            fullScreenMode = (_stage.displayState == StageDisplayState.FULL_SCREEN);            // Store the stage width and height.            stageWidth = _stage.stageWidth;            stageHeight = _stage.stageHeight;            // Resize our layout.            Resizer.resizeLayout( "dash", (stageWidth - oldScreenWidth), (stageHeight - oldScreenHeight) );            // If the full screen mode state changes, then we need to setup the full screen to handle            // the new full screen mode state change.            if ( !prevFullScreen && fullScreenMode ) {               prevFullScreen = fullScreenMode;               setupFullScreen( true );            }            else if ( prevFullScreen && !fullScreenMode ) {               prevFullScreen = fullScreenMode;               setupFullScreen( false );            }            // Store our old screen width and height to calculate the change at a later time...            oldScreenWidth = stageWidth;            oldScreenHeight = stageHeight;         }      }		/**		 * Used to setup or teardown the full screen mode for the Dash Media Player.  It does this by first hooking		 * into the skin to determine what skin specific functionality would like to be performed during the setup		 * or teardown of the full screen mode.  It then keeps track of the mouseTimer which is used to periodically		 * tell the player where the mouse is pointing on the player.  This is used in full screen mode to show/hide		 * the playlist of the player.		 *		 * @param full - Indicates if we are going into full screen ( true ) or out of full screen ( false ).		 */      public static function setupFullScreen( full:Boolean ):void      {         // If their skin implemented the onFullScreen function, then allow the skin to hook into this funcionality.         if ( skin && (skin.onFullScreen is Function) ) {            skin.onFullScreen( full );         }                  if (full) {            // If we are in full screen mode, then we need to start the mouse timer to start tracking the mouse movements.            mouseCount = 0;            lastMouse = new Point(_stage.mouseX,_stage.mouseY);            mouseTimer.start();         }         else {            // We are out of full screen mode... stop tracking the mouse movements.            mouseTimer.stop();         }      }		/**		 * Used to toggle the player to go into full screen or out of full screen.		 *		 * @param on - Boolean to indicate if you would like to take the player in full screen ( true ), or out		 * of full screen.		 */      public static function toggleFullScreen(on:Boolean):void      {         // Set the stage display state.         _stage.displayState = on ? StageDisplayState.FULL_SCREEN : StageDisplayState.NORMAL;      }		private static function validate( passed:Boolean )		{			if (passed) {				if (Params.flashVars.showdash) {					showDashLogo();				}				else if( dash ) {					dash.loadLogo();				}				_valid = true;			} else {				showDashLogo();			}		}				private static function showDashLogo()		{			var dashLogo:DashLogo = new DashLogo();			dashLogo.buttonMode = true;			dashLogo.mouseChildren = false;			dashLogo.addEventListener( MouseEvent.MOUSE_UP, gotoDashWebsite );			_stage.addChildAt( dashLogo, _stage.numChildren );			if ( dash.node && dash.node.fields ) {				dash.node.fields.setLogoPos(true, dashLogo);			}		}		private static function gotoDashWebsite(event:Object = null)		{			navigateToURL(new URLRequest(dashWebsite), '_blank');		}				public static function get valid():Boolean		{			return _valid;		}		/**		 * Set the skin of the Dash media player.		 *		 * @param skinName - The name of the skin that you would like the player to load and use.		 */      public static function setSkin( _skinName:String )      {         if (_skinName) {            skinName = _skinName;            loaded = false;            loadState = LOAD_SKIN;            loadProcess();         }      }		/**		 * Maximizes the Dash Media Player... ie, hide or show the playlist.		 *		 * @param on - Boolean to indicate if you would like to maximize ( true ) or minimize ( false )		 * the Dash Media Player.  When you maximize the player, it will end up hiding the playlist.  If you		 * minimize the player it will show the playlist.		 *		 * @param tween - Boolean to indicate if you would like to tween the playlist hide/show movement.		 */      public static function setMaximize( on:Boolean, tween:Boolean = true )      {         Params.flashVars.showplaylist = !on;                  if( dash ) {            dash.maximize( on, tween );         }      }		/**		 * Loads a node in the given player area.		 *		 * @param node - A variable used to tell the player which node to load.  This variable can either be a 		 * number, which would indicate the Node ID of the node you would like to load or it can be an object, which		 * would be the node data in object form ( which would skip the load ).		 */      public static function loadNode( _node:* )      {         if( dash ) {            dash.loadNode( _node );         }			      }		/**		 * Used to trigger the auto-hide feature.  The auto-hide feature will maximize the player once it has		 * been embedded within a page where the width or height is smaller than a specified value.  This is used to simplify		 * the embed process where the user would most likely not want to see the playlist when the player is embedded using		 * a small size.  These parameters (<strong>autoHideY</strong> and <strong>autoHideX</strong> ) can be set within the 		 * <strong>getLayoutInfo</strong> function within the <strong>skin.as</strong> file.  		 */      public static function setAutoHide()      {         if (! fullScreenMode && Params.flashVars.autohide) {            if (Params.flashVars.showinfo) {               if (_stage.stageHeight <= LayoutManager.autoHideY) {                  Params.flashVars.showinfo = false;               }            }            if (Params.showPlaylist) {               if (_stage.stageWidth <= LayoutManager.autoHideX) {                  Params.flashVars.showplaylist = false;               }            }         }      }		/**		 * Returns the media player object.  This is used to access the currently playing media within the player.		 *		 * @return MediaPlayer - The media player object.		 */      public static function get media():MediaPlayer      {         return dash ? dash.media : null;      }		/**		 * Returns the currently loaded skin.  		 *		 * @return MovieClip - The skin object.		 */      public static function get skin() : MovieClip      {         return dash ? dash.skin : null;      }      // Called every given interval.  This function is used to check the mouse location in full screen to see if we need      // to hide or show the playlist.      private static function onMouseTimer( e:TimerEvent ):void      {         // Only do this if we are in full screen mode.         if (fullScreenMode) {                     // If the mouse has moved...            if ( (_stage.mouseX != lastMouse.x) || (_stage.mouseY != lastMouse.y) ) {               lastMouse.x = _stage.mouseX;               lastMouse.y = _stage.mouseY;               // Hook into the skin to perform the functionality of the mouse movement.               if ( skin && (skin.onFullScreenMove is Function) ) {                  skin.onFullScreenMove( _stage.mouseX, _stage.mouseY );               }               mouseCount = 0;            }            else {               // If the mouse has not moved for ~ 3 seconds.               if ( (++mouseCount == 9) && skin && (skin.onFullScreenHide is Function) ) {                  skin.onFullScreenHide();               }            }         }      }      // Loads the dash display object.      private static function loadDash()      {         if( dash && dash.skin ) {            _stage.removeChild( dash.skin );            dash.loadNewSkin( skinName );         }         else {            skinName = Params.flashVars.skin;            dash = new Dash( skinName, loadProcess, preLoader.onProgress );         }      }      // Shows the player.      private static function showPlayer()      {         playerVisible = true;                resizeHandler( null );         if( dash.skin ) {            _stage.addChild( dash.skin );            preLoader.visible = false;         }         //dash.loadLogo();          validate( /*LicenseManager.validateLicense( Params.license )*/true );         loadProcess();           }			  // Returns the stage.	  public static function getStage() : Stage	  {         return _stage;      }      /**       * The Dash Player display object.       */      public static var dash:Dash;            /**       * Boolean to keep track if the player is maximized or not.       */            public static var maximized:Boolean = false;            /**       * The name of the skin that is loaded.       */             public static var skinName:String = null;            /**       * The preloader display object.       */             public static var preLoader:PreLoader;      /**       * Boolean to keep track of the current full screen mode.       */       public static var fullScreenMode:Boolean = false;            /**       * Boolean to keep track of the previous full screen mode.  This is used to keep us       * from constantly changing full screen states.  Because of this variable, we can trigger       * the full screen state change when the variable fullScreenMode and this variable are different.       */             public static var prevFullScreen:Boolean = false;            /**       * The width of the stage       */             public static var stageWidth:Number;            /**       * The height of the stage       */             public static var stageHeight:Number;            /**       * The previous width of the stage.       */             public static var oldScreenWidth:Number;            /**       * The previous height of the stage.       */             public static var oldScreenHeight:Number;      // Private variables...      private static var playerVisible:Boolean = false;      private static var loaded:Boolean = false;      private static var loadState:String;      private static var mouseCount:uint = 0;      private static var mouseTimer:Timer;      private static var lastMouse:Point;      private static var _stage:Stage;      private static var _valid:Boolean = false;		   }}