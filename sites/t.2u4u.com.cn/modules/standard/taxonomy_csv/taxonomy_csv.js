// $Id: taxonomy_csv.js,v 1.1.2.10 2009/12/10 13:05:57 danielkm Exp $

if (Drupal.jsEnabled) {
  (function ($) {

    /**
    * Allows to hide unchosen sub-options and to show chosen sub-options.
    *
    * @todo To factorize.
    */
    $(document).ready(function() {
      // Import options.
      $('#edit-import').addClass('filtered');
      // Source choice.
      // Add/remove class to show/hide it.
      $('#edit-source-choice').change(function(){
        var methods = new Array('text', 'path', 'url');
        for(var m in methods) {
          $('#edit-import').removeClass(methods[m]);
        }
        $('#edit-import').addClass(this.value)
          .animate({opacity:.5}, 1)
          .animate({opacity:1}, 1)
      });
      // Update current display.
      $('#edit-source-choice').trigger('change');

      // Import/Export CSV format options.
      $('#edit-csv-format').addClass('filtered');
      // Export delimiter.
      // Add/remove class to show/hide it.
      $('#delimiter').change(function(){
        var methods = new Array('comma', 'semicolon', 'tabulation', 'space', 'currency_sign', 'custom_delimiter');
        for(var m in methods) {
          $('#edit-csv-format').removeClass(methods[m]);
        }
        $('#edit-csv-format').addClass(this.value)
          .animate({opacity:.5}, 1)
          .animate({opacity:1}, 1)
      });
      // Update current display.
      $('#delimiter').trigger('change');

      // Import/Export CSV enclosure.
      // Add/remove class to show/hide it.
      $('#enclosure').change(function(){
        var methods = new Array('none', 'quotation', 'custom_enclosure');
        for(var m in methods) {
          $('#edit-csv-format').removeClass(methods[m]);
        }
        $('#edit-csv-format').addClass(this.value)
          .animate({opacity:.5}, 1)
          .animate({opacity:1}, 1)
      });
      // Update current display.
      $('#enclosure').trigger('change');

      // Destination choice.
      $('#edit-destination').addClass('filtered');
      // Add/remove class to show/hide it.
      $('#edit-vocabulary-target').change(function(){
        var methods = new Array('autocreate', 'duplicate', 'existing');
        for(var m in methods) {
          $('#edit-destination').removeClass(methods[m]);
        }
        $('#edit-destination').addClass(this.value)
          .animate({opacity:.5}, 1)
          .animate({opacity:1}, 1)
      });
      // Update current display.
      $('#edit-vocabulary-target').trigger('change');

      // Import options (general, description and specific).
      // Hide all items defined with the css class filtered.
      var methods_import = new Array('#edit-existing-items-update-wrapper', '#edit-existing-items-update-merge-wrapper', '#edit-existing-items-update-replace-wrapper', '#edit-existing-items-ignore-wrapper', '#edit-existing-items-ignore-create-wrapper', '#edit-existing-items-ignore-all-wrapper', '#description_alone_terms', '#description_fields_links', '#description_flat', '#description_tree_structure', '#description_polyhierarchy', '#description_parents', '#description_children', '#description_relations', '#description_fields', '#description_descriptions', '#description_weights', '#description_synonyms', '#description_taxonomy_manager', '#help_alone_terms', '#help_fields_links', '#help_flat', '#help_tree_structure', '#help_polyhierarchy', '#help_parents', '#help_children', '#help_relations', '#help_fields', '#help_descriptions', '#help_weights', '#help_synonyms', '#help_taxonomy_manager', '#edit-fields-links', '#edit-relations');
      for(var m in methods_import) {
        $(methods_import[m]).addClass('filtered');
      }
      // Existing terms.
      // Add/remove class to show/hide it.
      $('#edit-import-format').change(function(){
        var methods_import_format = new Array('alone_terms', 'fields_links', 'flat', 'tree_structure', 'polyhierarchy', 'parents', 'children', 'relations', 'fields', 'descriptions', 'weights', 'synonyms', 'taxonomy_manager');
        // Remove all added classes in order to return to base.
        for(var m in methods_import) {
          for(var n in methods_import_format) {
            $(methods_import[m]).removeClass(methods_import_format[n]);
          }
        }
        // Add current class to show it with css.
        for(var m in methods_import) {
          $(methods_import[m]).addClass(this.value)
            .animate({opacity:.5}, 1)
            .animate({opacity:1}, 1)
        }
      });
      // Update current display.
      $('#edit-import-format').trigger('change');

      // Export options (specific)
      // Hide all items defined with the css class filtered.
      var methods_export = new Array('#edit-fields-links');
      for(var m in methods_export) {
        $(methods_export[m]).addClass('filtered');
      }
      // Add/remove class to show/hide it.
      $('#edit-export-format').change(function(){
        var methods_export_format = new Array('alone_terms', 'fields_links', 'flat', 'tree_structure', 'polyhierarchy', 'parents', 'children', 'relations', 'fields', 'descriptions', 'weights', 'synonyms', 'taxonomy_manager');
        // Remove all added classes in order to return to base.
        for(var m in methods_export) {
          for(var n in methods_export_format) {
            $(methods_export[m]).removeClass(methods_export_format[n]);
          }
        }
        // Add current class to show it with css.
        for(var m in methods_export) {
          $(methods_export[m]).addClass(this.value)
            .animate({opacity:.5}, 1)
            .animate({opacity:1}, 1)
        }
      });
      // Update current display.
      $('#edit-export-format').trigger('change');

      // Advanced options.
      // Result display.
      // Add/remove class to show/hide it.
      $('#edit-disable-internal-cache').change(function(){
        if (this.checked) {
          $('#result_display_options').addClass('filtered');
          $('#result_display_cache').removeClass('filtered');
        }
        else {
          $('#result_display_options').removeClass('filtered');
          $('#result_display_cache').addClass('filtered');
        }
      });
      // Update current display.
      $('#edit-disable-internal-cache').trigger('change');

      // Vocabulary hierarchy.
      // Add/remove class to show/hide it.
      $('#edit-disable-hierarchy-check').change(function(){
        if (this.checked) {
          $('#hierarchy_level').removeClass('filtered');
        }
        else {
          $('#hierarchy_level').addClass('filtered');
        }
      });
      // Update current display.
      $('#edit-disable-hierarchy-check').trigger('change');

      // Result level.
      // Add/remove class to show/hide it.
      $('#edit-result-level-none').change(function(){
        if (this.checked) {
          $('#result_type').addClass('filtered');
        }
      });
      $('#edit-result-level-warnings').change(function(){
        if (this.checked) {
          $('#result_type').removeClass('filtered');
        }
      });
      $('#edit-result-level-notices').change(function(){
        if (this.checked) {
          $('#result_type').removeClass('filtered');
        }
      });
      $('#edit-result-level-infos').change(function(){
        if (this.checked) {
          $('#result_type').removeClass('filtered');
        }
      });
      // Update current display.
      $('#edit-result-level-none').trigger('change');
      $('#edit-result-level-warnings').trigger('change');
      $('#edit-result-level-notices').trigger('change');
      $('#edit-result-level-infos').trigger('change');
    });

  })(jQuery);
}
