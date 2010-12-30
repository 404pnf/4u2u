//
// Add multi-select toggling for file type checkboxes
//
/*
  DIV.tree-branch
    DIV.tree-content
      LABEL.file-item
        checkbox.tree-leaf
      LABEL.image-item
        checkbox.tree-item
      
*/

/** 
 * Add some checkboxes which, if clicked will toggle on or off all matching file type selectors
 */

if (Drupal.jsEnabled) {
  $(document).ready(function() {
    // Add new UI boxes
    var types = {'html-item':'Page', 'image-item':'Image', 'resource-item':'Resource', 'document-item':'Document'};
    for(type in types){
      $('#import-html-selectors').append("<label class='"+ type +"'><input type='checkbox' value='"+ type +"' />"+ types[type] +"</label>");
    }
    $('#import-html-selectors input').change(
      function(e){
        var checked = $(this).attr("checked");
        $('#import-html-process-form label.'+ $(this).val() + " input" ).attr("checked", checked ? 1 : 0);
        
    })
  })   // ready func
}      // JS OK
