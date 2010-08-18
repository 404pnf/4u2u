// $Id: views_slideshow.js,v 1.1.2.2.2.11 2009/09/29 20:48:36 redndahead Exp $

/**
 *  @file
 *  A simple jQuery ThumbnailHover Div Slideshow Rotator.
 */

/**
 *  This will set our initial behavior, by starting up each individual slideshow.
 */
Drupal.behaviors.viewsSlideshowThumbnailHover = function (context) {
  $('.views_slideshow_thumbnailhover_main:not(.viewsSlideshowThumbnailHover-processed)', context).addClass('viewsSlideshowThumbnailHover-processed').each(function() {
    var fullId = '#' + $(this).attr('id');
    var settings = Drupal.settings.viewsSlideshowThumbnailHover[fullId];
    settings.targetId = '#' + $(fullId + " :first").attr('id');
    settings.opts = {
      speed:settings.speed,
      timeout:parseInt(settings.timeout),
      delay:parseInt(settings.delay),
      sync:settings.sync==1,
      random:settings.random==1,
      pause:settings.pause==1,
      pager:(settings.pager_event == 'hoverIntent') ? null : '#views_slideshow_breakout_teasers_' + settings.id,
      pagerAnchorBuilder:(settings.pager_event == 'hoverIntent') ? null : function(idx, slide) { 
        return '#views_slideshow_thumbnailhover_div_breakout_teaser_' + settings.id + '_' + idx; 
      },
      after:function(curr, next, opts) {
        // Used for Image Counter.
        if (settings.image_count) {
          $('#views_slideshow_thumbnailhover_image_count_' + settings.id + ' span.num').html(opts.currSlide + 1);
          $('#views_slideshow_thumbnailhover_image_count_' + settings.id + ' span.total').html(opts.slideCount);
        }
      },
      before:(settings.pager_event == 'hoverIntent') ? function(current,next) {
        var currId = (currId=$(current).attr('id')).substring(currId.lastIndexOf('_')+1)
        var nextId = (nextId=$(next).attr('id')).substring(nextId.lastIndexOf('_')+1)
        $('#views_slideshow_thumbnailhover_div_breakout_teaser_' + settings.id + '_' + currId).removeClass('activeSlide');
        $('#views_slideshow_thumbnailhover_div_breakout_teaser_' + settings.id + '_' + nextId).addClass('activeSlide');
      } : null,
      pagerEvent: (settings.pager_event == 'hoverIntent') ? null : settings.pager_event,
      prev:(settings.controls > 0)?'#views_slideshow_thumbnailhover_prev_' + settings.id:null,
      next:(settings.controls > 0)?'#views_slideshow_thumbnailhover_next_' + settings.id:null,
      cleartype:(settings.ie.cleartype),
      cleartypeNoBg:(settings.ie.cleartypenobg)
    };
    
    if (settings.effect == 'none') {
      settings.opts.speed = 1;
    }
    else {
      settings.opts.fx = settings.effect;
    }
    
    /**
     * Add additional settings.
     */
    var advanced = settings.advanced.split("\n");
    for (i=0; i<advanced.length; i++) {
      var prop = '';
      var value = '';
      var property = advanced[i].split(":");
      for (j=0; j<property.length; j++) {
        if (j == 0) {
          prop = property[j];
        }
        else if (j == 1) {
          value = property[j];
        }
        else {
          value += ":" + property[j];
        }
      }
      settings.opts[prop] = value;
    }

    $(settings.targetId).cycle(settings.opts);
    
    // Show image count for people who have js enabled.
    $('#views_slideshow_thumbnailhover_image_count_' + settings.id).show();
    
    if (settings.pager_event == 'hoverIntent') {
      $('#views_slideshow_thumbnailhover_breakout_teasers_' + settings.id + ' .views_slideshow_thumbnailhover_div_breakout_teaser').each(function(i,obj) {
        $(obj).hoverIntent(
          function() {
            $('.views_slideshow_thumbnailhover_div_breakout_teaser').removeClass('activeSlide');
            var id = $(this).attr('id');
            id = parseInt(id.substring(id.lastIndexOf('_')+1));
            $(settings.targetId).cycle(id);
            $('#views_slideshow_thumbnailhover_div_breakout_teaser_' + settings.id + '_' + id).addClass('activeSlide');
            $(settings.targetId).cycle('stop');
          },
          function() {
            var id = $(this).attr('id');
            settings.opts.startingSlide = parseInt(id.substring(id.lastIndexOf('_')+1));
            $(settings.targetId).cycle(settings.opts);
          }
        );
      });
    }
   
    if (settings.controls > 0) {
      // Show controls for people who have js enabled browsers.
      $('#views_slideshow_thumbnailhover_controls_' + settings.id).show();
      
      $('#views_slideshow_thumbnailhover_playpause_' + settings.id).click(function(e) {
        if (settings.paused) {
          $(settings.targetId).cycle('resume');
          $('#views_slideshow_thumbnailhover_playpause_' + settings.id).addClass('views_slideshow_thumbnailhover_pause').removeClass('views_slideshow_thumbnailhover_play').text('Pause');
          settings.paused = false;
        }
        else {
          $(settings.targetId).cycle('pause');
          $('#views_slideshow_thumbnailhover_playpause_' + settings.id).addClass('views_slideshow_thumbnailhover_play').removeClass('views_slideshow_thumbnailhover_pause').text('Resume');
          settings.paused = true;
        }
        e.preventDefault();
      });
    }
  });
}
