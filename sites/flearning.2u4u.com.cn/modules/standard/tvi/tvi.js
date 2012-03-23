
Drupal.behaviors.tvi_initialize = function(context) {
	
	//--------------------------------------------------------------------------
	// Properties

	var current_display = $('#tvi-display-selector').val();

	//--------------------------------------------------------------------------
	// Handlers
	
	var set_active_option = function() {
		$('#tvi-display-selector').val(current_display);
	}
	
	//--------------------------------------------------------------------------
	
	var view_change_handler = function() {
		var view_name = $('#tvi-view-selector').val();
		
		if (!view_name) {
			view_name = $('#tvi-view-selector option:first').val();
			$('#tvi-view-selector').val(view_id);
		}		
		// Load new view displays.
		$('#tvi-display-selector').load(
			'/tvi/js/display_options?view_name=' + view_name, 
			'', set_active_option
		);
	}
	
	//--------------------------------------------------------------------------
	// Start	
	
	// Javascript is enabled.
	$('.javascript-warning').hide();
	
	// Reload displays when views are changed.
	$('#tvi-view-selector').change(view_change_handler);
	view_change_handler();
}