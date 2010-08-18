package {
	import flash.events.EventDispatcher;
	import flash.display.MovieClip;
	import flash.utils.Dictionary;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.net.URLLoader;
	import flash.net.URLRequest;
	import flash.display.Graphics;
	public class GameEngine extends EventDispatcher {
		public static  var GAME_START:String="GAME_START";
		public static  var GAME_SUCCESS:String="GAME_SUCCESS";
		public static  var GAME_OVER:String="GAME_OVER";
		public static  var GAME_LIST_DATA_SUCCESS:String="GAME_LIST_DATA_SUCCESS";
		public static  var GAME_LIST_DATA_FAIL:String="GAME_LIST_DATA_FAIL";
		public var _gameDatas:Dictionary=new Dictionary();
		private var _eventListeners:Dictionary=new Dictionary();
		public static  var _ins:GameEngine=new GameEngine();

		private var _gamePane:MovieClip=null;

		private var _wordsResHash:Dictionary=new Dictionary();

		public var _gameLevels:int=8;
		private var _currentLevel:int=1;

		private var _urlLoader:URLLoader=null;

		private var _tiles:Array=null;

		private var _preObject:MoveObject=null;
		
		private var _tileWidth:Number=0;
		private var _tileHeight:Number=0;
		private var _positionX:Number=0;
		private var _positionY:Number=0;
		
		//Score
		public var _score:Number=0;
		public var _count:int=0;
		public var _totalTime:Number=0;
		
		public var _lineCount:int=0;
		
		private var tiles:Array=null;
		
		public function GameEngine() {
			_wordsResHash["level_"+1]={count:12,x:4,y:6,res:"cet6.xml",time:180000,perScore:20,data:null};
			_wordsResHash["level_"+2]={count:16,x:4,y:8,res:"cet6.xml",time:180000,perScore:20,data:null};
			_wordsResHash["level_"+3]={count:20,x:5,y:8,res:"cet6.xml",time:180000,perScore:20,data:null};
			_wordsResHash["level_"+4]={count:24,x:6,y:8,res:"cet6.xml",time:180000,perScore:20,data:null};
			_wordsResHash["level_"+5]={count:28,x:7,y:8,res:"cet6.xml",time:180000,perScore:20,data:null};
			_wordsResHash["level_"+6]={count:32,x:8,y:8,res:"cet6.xml",time:180000,perScore:20,data:null};
			_wordsResHash["level_"+7]={count:36,x:8,y:9,res:"cet6.xml",time:180000,perScore:20,data:null};
			_wordsResHash["level_"+8]={count:40,x:8,y:10,res:"cet6.xml",time:180000,perScore:20,data:null};

			_urlLoader=new URLLoader();
			_urlLoader.addEventListener(Event.COMPLETE,onWordsLoaded);

		}
		public function listUserGameDatas():void {
			this.dispatchEvent(new Event(GAME_LIST_DATA_SUCCESS));
		}
		public function rePlan():void{
			
			if(_tiles!=null){
				var tmp:Array=new Array();
				var jj:int=0;
				for(jj=0;jj<_tiles.length;jj++){
					var ii:int=0;
					var t:Array=_tiles[jj];
					for(ii=0;ii<t.length;ii++){
						
							var obj:Object=_gamePane.getChildByName("n"+jj+"_"+ii);
							if(obj!=null){
								tmp.push(obj);
							}
					}
				}
				//重排tmp
				var i:int=tmp.length/2;
				for(var j:int=0;j<i;j++){
					var xindex:int=tmp[j]._xindex;
					var yindex:int=tmp[j]._yindex;
					var tx:Number=tmp[j].x;
					var ty:Number=tmp[j].y;
					tmp[j]._xindex=tmp[j+i]._xindex;
					tmp[j]._yindex=tmp[j+i]._yindex;
					tmp[j].x=tmp[j+i].x;
					tmp[j].y=tmp[j+i].y;
					tmp[j+i]._xindex=xindex;
					tmp[j+i]._yindex=yindex;
					tmp[j+i].x=tx;
					tmp[j+i].y=ty;
				}
			}
		}
		private function fillTiles(tiles:Array,idx:int,v:Boolean,fh:Dictionary,words:Array):void{
			var widx:int=_windex;
			var levelData:Object=_wordsResHash["level_"+_currentLevel];
			trace(v+":"+idx);
			if(!v){
				if(fh["h"+idx]!=null){
					return;
				}
				fh["h"+idx]={};
				var tmpArr:Array=tiles[idx];
				var tmpArr2:Array=[];
				var lastIdx:int=0;
				for(var i:int=0;i<levelData.x;i++){
					if(tmpArr[i].push==false){
						tmpArr2.push(tmpArr[i]);
						lastIdx=i;
					}
				}
				
				var hasLeft:Boolean=false;
				if(tmpArr2.length%2!=0){
					tmpArr2.splice(tmpArr2.length-1,1);
					hasLeft=true;
				}
				for (var m:int=0; m<tmpArr2.length/2; m++) {
					tmpArr2[m*2].push=true;
					tmpArr2[m*2].word={label:words[0].@eng,index:widx};
					tmpArr2[m*2+1].push=true;
					tmpArr2[m*2+1].word={label:words[0].@zh,index:widx};
					words.splice(0,1);
					_windex++;
					widx++;
				}
				//把单词打散填充进去
				//重新排一下
				var tmpArr3:Array=tmpArr2;
				/*
				for(i=0;i<levelData.x;i++){
					if(tmpArr[i].push==true){
						tmpArr3.push(tmpArr[i]);
					}
				}
				*/
				for(i=0;i<tmpArr3.length;i++){
					if(tmpArr3.length<2){
						break;
					}
					var tmp:Object=tmpArr3[0];
					tmpArr3.splice(0,1);
					var tmpN:int=Math.random()*tmpArr3.length;
					var tmpW:Object=tmp.word;
					tmp.word=tmpArr3[tmpN].word;
					tmpArr3[tmpN].word=tmpW;
					tmpArr3.splice(tmpN,1);
				}
				if(hasLeft){
					fillTiles(tiles,lastIdx,true,fh,words);
				}else{
					for (var yy:int=0; yy<levelData.y; yy++) {
						for(var xx:int=0;xx<levelData.x;xx++){
							if(tiles[yy][xx].push==false){
								if(fh["v"+xx]==null){
									fillTiles(tiles,xx,true,fh,words);
								}else if(fh["h"+yy]==null){
									fillTiles(tiles,yy,false,fh,words);
								}
							}
						}
					}
				}
				
			}else{
				if(fh["v"+idx]!=null){
					return;
				}
				fh["v"+idx]={};
				
				var tmpArr0:Array=[];
				for(var h:int=0;h<levelData.y;h++){
					tmpArr0.push(tiles[h][idx]);
				}
				var tmpArr02:Array=[];
				var lastIdx0:int=0;
				for(var i0:int=0;i0<levelData.y;i0++){
					if(tmpArr0[i0].push==false){
						tmpArr02.push(tmpArr0[i0]);
						lastIdx0=i0;
					}
				}
				var hasLeft0:Boolean=false;
				if(tmpArr02.length%2!=0){
					tmpArr02.splice(tmpArr02.length-1,1);
					hasLeft0=true;
				}
				
				for (var m0:int=0; m0<tmpArr02.length/2; m0++) {
					tmpArr02[m0*2].push=true;
					tmpArr02[m0*2].word={label:words[0].@eng,index:widx};
					tmpArr02[m0*2+1].push=true;
					tmpArr02[m0*2+1].word={label:words[0].@zh,index:widx};
					words.splice(0,1);
					_windex++;
					widx++;
				}
				
				//把单词打散填充进去
				//把单词打散填充进去
				//重新排一下
				var tmpArr03:Array=tmpArr02;
				/*
				for(i0=0;i0<levelData.y;i0++){
					if(tmpArr0[i0].push==true){
						tmpArr03.push(tmpArr0[i0]);
					}
				}
				*/
				for(i0=0;i0<tmpArr03.length;i0++){
					if(tmpArr03.length<2){
						break;
					}
					var tmp0:Object=tmpArr03[0];
					tmpArr03.splice(0,1);
					var tmpN0:int=Math.random()*tmpArr03.length;
					var tmpW0:Object=tmp0.word;
					tmp0.word=tmpArr03[tmpN0].word;
					tmpArr03[tmpN0].word=tmpW0;
					tmpArr03.splice(tmpN0,1);
				}
				if(hasLeft0){
					fillTiles(tiles,lastIdx0,false,fh,words);
				}else{
					for (var yy0:int=0; yy0<levelData.y; yy0++) {
						for(var xx0:int=0;xx0<levelData.x;xx0++){
							if(tiles[yy0][xx0].push==false){
								if(fh["h"+yy0]==null){
									fillTiles(tiles,yy0,false,fh,words);
								}else if(fh["v"+xx0]==null){
									fillTiles(tiles,xx0,true,fh,words);
								}
							}
						}
					}
				}
			}
		}
		
		private var _windex:int=0;
		public function setGamePane(pane:MovieClip):void {
			_gamePane=pane;
			_windex=0;
			//初始化游戏界面
			var levelData:Object=_wordsResHash["level_"+_currentLevel];
			var words:XMLList=levelData.data;
			var step:int=words.length()/levelData.count;
			var tmp:Array=new Array();
			for (var i:int=0; i<levelData.count; i++) {
				var idx:int=i*step+Math.random()*levelData.count;
				tmp.push(words[idx]);
			}
			tiles=new Array();
			//根据游戏的横、竖坐标生成一个布局块
			for (var yy:int=0; yy<levelData.y; yy++) {
				var tmpArr22:Array=[];
				for(var xx:int=0;xx<levelData.x;xx++){
					tmpArr22.push({push:false});
				}
				tiles.push(tmpArr22);
			}
			//进行方块的布局
			var r:int=Math.random()*2;
			if(r==0){
				fillTiles(tiles,0,false,new Dictionary(),tmp);
			}else{
				fillTiles(tiles,levelData.y-1,false,new Dictionary(),tmp);
			}
			
			//在界面上绘制生成的块

			var ii:int=0;
			var jj:int=0;
			var mm:int=0;
			_tiles=new Array();
			var tmpObj:MoveObject=new MoveObject();
			var initx:Number=(_gamePane.width-tmpObj.width*levelData.x)/2;
			var inity:Number=(_gamePane.height-tmpObj.height*levelData.y)/2;
			
			_positionX=initx;
			_positionY=inity;
			
			_tileWidth=tmpObj.width;
			_tileHeight=tmpObj.height;
			_gamePane._linePane_mc.graphics.clear();
			//画网格

			var graph:Graphics=_gamePane._gridPane_mc.graphics;
			graph.clear();
			graph.lineStyle(1, 0x888888,0.4);
			graph.moveTo(initx,inity);
			graph.lineTo(initx+tmpObj.width*levelData.x,inity);
			graph.moveTo(initx,inity);
			graph.lineTo(initx,inity+tmpObj.height*levelData.y);
			var tmpArr:Array=[];
			_tiles.push(tmpArr);
			tmpArr.push(0);
			for (jj=0; jj<levelData.x; jj++) {
				tmpArr.push(0);
			}
			tmpArr.push(0);
			for (ii=0; ii<levelData.y; ii++) {
				tmpArr=[];
				_tiles.push(tmpArr);
				tmpArr.push(0);
				for (jj=0; jj<levelData.x; jj++) {
					var obj:MoveObject=new MoveObject();
					obj.setData(tiles[ii][jj].word.label,tiles[ii][jj].word.index,jj+1,ii+1);
					tmpArr.push(1);
					obj.x=initx+jj*obj.width;
					obj.y=inity+ii*obj.height;
					obj.name="n"+ii+"_"+jj;
					graph.moveTo(obj.x,obj.y+obj.height);
					graph.lineTo(obj.x+obj.width,obj.y+obj.height);
					graph.lineTo(obj.x+obj.width,obj.y);
					obj.addEventListener(MouseEvent.CLICK,checkLink);
					_gamePane.addChild(obj);
					mm++;
				}
				tmpArr.push(0);
			}
			tmpArr=[];
			_tiles.push(tmpArr);
			tmpArr.push(0);
			for (jj=0; jj<levelData.x; jj++) {
				tmpArr.push(0);
			}
			tmpArr.push(0);

		}
		private function checkLink(e:MouseEvent):void {
			var t:MoveObject=MoveObject(e.currentTarget);
			t.setSelect(true);
			if (_preObject==null) {
				_preObject=t;
				return;
			}
			if (_preObject._data!=t._data) {
				_preObject.setSelect(false);
				_preObject=t;
				t.setSelect(true);
				return;
			}
			if (_preObject!=t) {
				//计算连线和销毁条件
				aryCrossPath=[];
				trace("cross test");
				if (testCrossAbleXY(_preObject,t)) {
					_tiles[_preObject._yindex][_preObject._xindex]=0;
					_tiles[t._yindex][t._xindex]=0;
					_preObject.destroy();
					t.destroy();
					_preObject=null;
					//加分
					countScore();
					if(aryCrossPath.length>0){
						trace("path len:"+aryCrossPath.length);
						_lineCount=12;
						var g:Graphics=_gamePane._linePane_mc.graphics;
						g.clear();
						g.lineStyle(1,0xFF0000);
						g.moveTo(_positionX+(aryCrossPath[0][0]*_tileWidth)-(_tileWidth/2),_positionY+(aryCrossPath[0][1]*_tileHeight)-(_tileHeight/2));
						for(var i:int=1;i<aryCrossPath.length;i++){
							g.lineTo(_positionX+(aryCrossPath[i][0]*_tileWidth)-(_tileWidth/2),_positionY+(aryCrossPath[i][1]*_tileHeight)-(_tileHeight/2));
						}
					}
				} else {
					//扣分
					_score=_score-5;
					if(_score<0){
						_score=0;
					}
					_preObject.setSelect(false);
					_preObject=t;
					
				}
			}
		}
		//同一列方向(X相同时)的直接连通检测
		function testCrossAbleX(disX:uint, firstObjDisY:uint, secondObjDisY:uint):Boolean {
			var maxY = Math.max(firstObjDisY,secondObjDisY);
			var minY = Math.min(firstObjDisY,secondObjDisY);
			if ((maxY - minY)>1) {
				for (var i:uint = minY+1; i< maxY; i++) {
					if (_tiles[i][disX]==1) {
						return false;
					}
				}
			}
			return true;
		}
		function testCrossAbleY(disY:uint, firstObjDisX:uint, secondObjDisX:uint):Boolean {
			var maxX = Math.max(firstObjDisX,secondObjDisX);
			var minX = Math.min(firstObjDisX,secondObjDisX);
			if ((maxX - minX)>1) {
				for (var i:uint = minX+1; i< maxX; i++) {
					if (_tiles[disY][i]==1) {
						return false;
					}
				}
			}
			return true;
		}
		var aryCrossPath:Array=[];
		function testCrossAbleXY(firstObj:MoveObject, secondObj:MoveObject):Boolean {
			var aryFlag1:Boolean = false;
			var aryFlag2:Boolean = false;
			var levelData:Object=_wordsResHash["level_"+_currentLevel];
			var WIDTHNUM:int=levelData.x+2;
			var HEIGHTNUM:int=levelData.y+2;
			if ((firstObj._xindex == secondObj._xindex && testCrossAbleX(firstObj._xindex,firstObj._yindex,secondObj._yindex)) || (firstObj._yindex == secondObj._yindex && testCrossAbleY(firstObj._yindex,firstObj._xindex,secondObj._xindex))) {
				var aryP1:Array = [firstObj._xindex,firstObj._yindex];
				var aryP2:Array = [secondObj._xindex,secondObj._yindex];
				aryCrossPath.push(aryP1);
				aryCrossPath.push(aryP2);
				return true;
			} else {
				for (var i:uint = 0; i<HEIGHTNUM; i++) {
					var flagH1:Boolean;
					var flagH2:Boolean;
					var flagH3:Boolean;
					if (_tiles[i][firstObj._xindex]==0) {
						flagH1 = testCrossAbleX(firstObj._xindex,i,firstObj._yindex);
						if (i == secondObj._yindex) {
							flagH2 = testCrossAbleY(i,firstObj._xindex,secondObj._xindex);
						} else {
							flagH2 = (_tiles[i][secondObj._xindex]==0) && testCrossAbleY(i,firstObj._xindex,secondObj._xindex);
						}
						flagH3 = testCrossAbleX(secondObj._xindex,i,secondObj._yindex);
						aryFlag1 = aryFlag1 || (flagH1 && flagH2 && flagH3);
						if (aryFlag1) {
							var aryPx1:Array = [firstObj._xindex,firstObj._yindex];
							var aryPx2:Array = [firstObj._xindex,i];
							var aryPx3:Array = [secondObj._xindex,i];
							var aryPx4:Array = [secondObj._xindex,secondObj._yindex];
							aryCrossPath.push(aryPx1);
							aryCrossPath.push(aryPx2);
							aryCrossPath.push(aryPx3);
							aryCrossPath.push(aryPx4);
							return true;
						}
					}
				}
				for (var j:uint = 0; j<WIDTHNUM; j++) {
					var flagW1:Boolean;
					var flagW2:Boolean;
					var flagW3:Boolean;
					if (_tiles[firstObj._yindex][j]==0) {
						flagW1 = testCrossAbleY(firstObj._yindex,j,firstObj._xindex);
						if (j == secondObj._xindex) {
							flagW2 = testCrossAbleX(j,firstObj._yindex,secondObj._yindex);
						} else {
							flagW2 = (_tiles[secondObj._yindex][j]==0) && testCrossAbleX(j,firstObj._yindex,secondObj._yindex);
						}
						flagW3 = testCrossAbleY(secondObj._yindex,j,secondObj._xindex);
						aryFlag2 = aryFlag2 || (flagW1 && flagW2 && flagW3);
						if (aryFlag2) {
							var aryPy1:Array = [firstObj._xindex,firstObj._yindex];
							var aryPy2:Array = [j,firstObj._yindex];
							var aryPy3:Array = [j,secondObj._yindex];
							var aryPy4:Array = [secondObj._xindex,secondObj._yindex];
							aryCrossPath.push(aryPy1);
							aryCrossPath.push(aryPy2);
							aryCrossPath.push(aryPy3);
							aryCrossPath.push(aryPy4);
							return true;
						}
					}
				}
			}
			aryCrossPath= [];
			return false;
		}
		private function countScore():void {
			var levelData:Object=_wordsResHash["level_"+_currentLevel];
			_score=_score+levelData.perScore;
			_count++;
		}
		public function pauseGame():void {
		}
		public function resumeGame():void {
		}
		public function addTime():void {
		}
		public function getHelpMsg():String {
			return "";
		}
		public function getCurrentMaxTime():Number{
			var levelData:Object=_wordsResHash["level_"+_currentLevel];
			return levelData.time;
		}
		public function getCurrentMaxCount():Number{
			var levelData:Object=_wordsResHash["level_"+_currentLevel];
			return levelData.count;
		}
		public function getCurrentLevel():int {
			return _currentLevel;
		}
		public function setCurrentLevel(cl:int):void {
			_currentLevel=cl;
		}
		public function startGame():void {
			if (_wordsResHash["level_"+_currentLevel].data!=null) {
				this.dispatchEvent(new Event(GAME_START));
				return;
			}
			//导入游戏单词
			var req:URLRequest=new URLRequest(_wordsResHash["level_"+_currentLevel].res);
			_urlLoader.load(req);

		}
		private function onWordsLoaded(e:Event):void {
			trace("load words successful");
			var xml:XML=new XML(_urlLoader.data);
			var res:String=_wordsResHash["level_"+_currentLevel].res;
			for (var i=1; i<=_gameLevels; i++) {
				if (_wordsResHash["level_"+i].res==res) {
					_wordsResHash["level_"+i].data=xml.word;
				}
			}
			this.dispatchEvent(new Event(GAME_START));
		}
		override public function addEventListener(type:String, listener:Function, useCapture:Boolean = false, priority:int = 0, useWeakReference:Boolean = false):void {
			if (this.hasEventListener(type)) {
				this.removeEventListener(type,_eventListeners[type]);
			}
			super.addEventListener(type,listener,useCapture,priority,useWeakReference);
			_eventListeners[type]=listener;
		}
	}
}