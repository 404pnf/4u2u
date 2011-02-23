// $Id: swftools_soundmanager2.js,v 1.1.2.2 2010/04/09 22:20:06 stuartgreenfield Exp $

Drupal.behaviors.swftools_soundmanager2 = function (context) {
  if (typeof soundManager != 'undefined') {

    soundManager.url = Drupal.settings['swftools_soundmanager2']['soundManager.url'];
    soundManager.debugMode = Drupal.settings['swftools_soundmanager2']['soundManager.debugMode'];
    soundManager.flashVersion = Drupal.settings['swftools_soundmanager2']['soundManager.flashVersion']=='8'?8:9;
    soundManager.useFlashBlock = Drupal.settings['swftools_soundmanager2']['soundManager.useFlashBlock'];
    soundManager.useFastPolling = Drupal.settings['swftools_soundmanager2']['soundManager.useFastPolling'];
    soundManager.useHighPerformance = Drupal.settings['swftools_soundmanager2']['soundManager.useHighPerformance'];
    
    threeSixtyPlayer.config.imageRoot = Drupal.settings['swftools_soundmanager2']['threeSixtyPlayer.config.imageRoot'];
    
    if (typeof Drupal.settings['swftools_soundmanager2']['useVisualisation'] != 'undefined') {
      
      threeSixtyPlayer.config.showHMSTime = Drupal.settings['swftools_soundmanager2']['threeSixtyPlayer.config.showHMSTime'];
      threeSixtyPlayer.config.useWaveformData = Drupal.settings['swftools_soundmanager2']['threeSixtyPlayer.config.useWaveformData'];
      threeSixtyPlayer.config.useEQData = Drupal.settings['swftools_soundmanager2']['threeSixtyPlayer.config.useEQData'];
      threeSixtyPlayer.config.scaleFont = (navigator.userAgent.match(/msie/i)?false:true);

      soundManager.flash9Options.useWaveformData = Drupal.settings['swftools_soundmanager2']['soundManager.flash9Options.useWaveformData'];
      soundManager.flash9Options.useEQData = Drupal.settings['swftools_soundmanager2']['soundManager.flash9Options.useEQData'];
      soundManager.flash9Options.usePeakData = Drupal.settings['swftools_soundmanager2']['soundManager.flash9Options.usePeakData'];
      
    }
  
  };
};
