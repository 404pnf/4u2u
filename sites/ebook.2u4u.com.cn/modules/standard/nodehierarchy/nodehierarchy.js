// $Id: nodehierarchy.js,v 1.4.2.2 2009/02/15 05:43:05 ronan Exp $

Drupal.nodehierarchy = {
  callbackURL : "",  
  autoAttach  : function( ctxt ) {
    
  ctxt = ctxt || document;
  
  // expand/collapse links

  // links that are already expanded just need the slide animation
  $(".nodehierarchy_outline li.expanded", ctxt).each(Drupal.nodehierarchy.addExpandCollapse);

  // add the ajax call to the collapsed links
  $(".nodehierarchy_outline li.collapsed", ctxt).each(
     function() {     
      var li    = this;
      var nid   = li.getAttribute("id").replace(/nodehierarchy_child\-/, "");
      var url   = '';
      url += Drupal.nodehierarchy.callbackURL +"/"+ nid +"/getchildren";
      url += url.indexOf('?') >-1 ? "&" : "?";
      url += Drupal.nodehierarchy.destination;

      $("a.expand_widget", this)
        .click(function (e) {
            $(li).addClass("loading");
            $.ajax({
                type:     'GET',
                url:      url,
                success:  function (data) {
                  $('div.children', li).append(data);
                  $(li)
                    .removeClass('loading')
                    .removeClass('collapsed')
                    .addClass('expanded')
                    .unbind('click')
                    .each(Drupal.nodehierarchy.addExpandCollapse)
                    .find( "div.children" )
                       .hide()
                       .slideToggle('fast');
                  Drupal.nodehierarchy.autoAttach(li);
                },
                error:    function (xmlhttp) {
                  $(li)
                    .removeClass('loading')
                    .addClass('collapsed');
                  alert('An HTTP error '+ xmlhttp.status +' occured.\n' + url);
                }
              });
            return false;
          }
        );
    });
    
    var x = $('a.nodehierarchy_action_up');
    $('a.nodehierarchy_action_up', ctxt).click(function(e) {
      var item = $(this).parent().parent().parent();
      var prev = $(item).prev();
      if( prev.length ) {
        return Drupal.nodehierarchy.moveUpDown( 
            item, 
            prev,
            'up' 
          );
      } else if ( $(item).is( '.first' ) ) {
        return false;
      } else {
        return true;
      }
    });

    $('a.nodehierarchy_action_down', ctxt).click(function() {
      var item = $(this).parent().parent().parent();
      var next = $(item).next();
      if( next.length ) {
        return Drupal.nodehierarchy.moveUpDown( 
            item, 
            next,
            'down' 
          );
      } else if ( $(item).is( '.last' ) ) {
        return false;
      } else {
        return true;
      }
    });

  },
  
  moveUpDown : function( item, swap, dir ) {
    var nid   = item.attr("id").replace(/nodehierarchy_child\-/, "");
    var url   = Drupal.nodehierarchy.callbackURL + "/"+ nid +"/"+dir;
    
    if (item.attr('id') != swap.attr('id')) {      
      // move item
      if( dir == 'down' ) {
        swap.after(item);
      } else {
        swap.before(item);      
      }
      Drupal.nodehierarchy.fixFirstLastClass( item, swap );
      $.ajax({ type: 'GET', url: url });
    }
    return false;
  },
  
  fixFirstLastClass : function( item, swap ) {
    if( item.is(".first") ) {
      item.removeClass("first");
      swap.addClass("first");
    } else if( swap.is(".first") ) {
      swap.removeClass("first");
      item.addClass("first");
    }
    if( item.is(".last") ) {
      item.removeClass("last");
      swap.addClass("last");
    } else if( swap.is(".last") ) {
      swap.removeClass("last");
      item.addClass("last");
    }
  },
  
  addExpandCollapse : function () {
    var li    = this;
    
    $("a.expand_widget", this)
      .unbind('click')
      .click(function (e) {
        // Only toggle if this is the element that was clicked.
        // Otherwise, a parent li element might be toggled too.
        $(this.parentNode.parentNode)
          .toggleClass('collapsed')
          .toggleClass('expanded')
          .find('div.children')
            .slideToggle('fast');
       return false;
      });
  }
}


// Global Killswitch
if (Drupal.jsEnabled) {
  $(document).ready(function() { Drupal.nodehierarchy.autoAttach( document ) } );
}
