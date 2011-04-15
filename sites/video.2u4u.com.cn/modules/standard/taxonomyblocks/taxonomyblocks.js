// $Id: taxonomyblocks.js,v 1.2 2010/05/05 08:36:35 aaronhawkins Exp $
$(document).ready(function(){
  var vocab_over = function() {
    var link_width = $(this).children('.vocab_edit_link').width() + 15;
    
    $(this).children('.vocab_edit_link').css('margin-left','-'+link_width+'px');
    $(this).children('.vocab_edit_link').fadeIn();
  }
  var vocab_out = function() {
    $(this).children('.vocab_edit_link').fadeOut();
  }
  $('.block-taxonomyblocks h3').hover(vocab_over, vocab_out);
});