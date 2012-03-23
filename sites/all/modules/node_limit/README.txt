node_limit Module

This module allows administrators to limit the number of nodes that users may create.  This limitation may be done on a per-role or per-user basis.

INSTALLATION:

- Put the module in your drupal modules directory and enable it in admin/build/module.
- Only users with the "administer node limits" permissions will be able to edit node limits.
- The administration page is at admin/user/node_limit

DETAILS:

- Node limits do not apply to user 1.
- If a user belongs to roles A and B, which have limits of 3 and 4 (respectively), the user will have a node limit of 4.
- Individual user node limits override role node limits

FUTURE PLANS:

- Allow for time-based node limits (a limit for a certain time period, or a limit that expires on a certain date or after a certain interval)
- Integration with other modules that segregate content, such as Organic Groups

HOOKS FOR SUBMODULES:
- hook_node_limit_element($lid = 0):
  return an array with a single key-value pair.  The key must be the name of the submodule, and the value is an element in form api.
  see node_limit_user for an implementation.
  You may set the value '#custom_render' => true if your element requires a custom rendering
  The $lid parameter is given if the user is editing (as opposed to adding) a node limit.  The implementor should fill in a #default_value for the element
  
- hook_node_limit_render_element(&$element):
  called if the element returned from hook_node_limit_element has '#custom_render' => true
  should return a string of rendered html
  
- hook_node_limit_element_validate($element):
  called when the user attempts to add or edit a Node Limit.  The implementor of the hook has the opportunity to validate the value the user entered.
  
- hook_node_limit_element_submit($lid, $applies, $element):
  called when the user adds or edits a Node Limit (and has passed validation).  The implementor of the hook has the opportunity to save the user-entered value based on the passed Node Limit id.  $applies == true iff the limit uses this limitation.  Otherwise the submodule should delete the limitation from its table.
  
- hook_node_limit_load($lid):
  Called when node_limit loads a limit from the database.  The implementor should return an array with a single key-value pair.  The key must be the name of the submodule, and the value is an array containing 
  