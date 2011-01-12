JavaScript Aggregator for Drupal 6
==================================

The JavaScript Aggregator module for Drupal 6 will minify the
aggregated JavaScript file when the Optimize JavaScript option
is enabled in admin/settings/performance. This is done through
the fantastic JSMin library:
http://code.google.com/p/jsmin-php/


Installation
------------

 1) Copy the JavaScript Aggregator module to sites/all/modules.

 2) Enable it in admin/build/modules.

 3) Enable JavaScript Optimization in admin/settings/performance.
 
 4) See that the aggregated JavaScript file now ends with ".jsmin.js",
    and contains minified JavaScript.

 5) Optionally compress the JavaScript even more by enabling GZip
    compression.


Upgrading
---------

The Drupal 5 version of the JavaScript Aggregator module required
the addition of some code to your theme. This is not so in the
Drupal 6 version. In the Drupal 6 version, you just have to enable
the module and you're done. This is due to the use of hook_preprocess_page.

Thank you goes to webchick and her writings of the jQuery Update module
for the idea of using the hook.
