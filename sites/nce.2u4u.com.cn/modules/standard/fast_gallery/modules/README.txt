/* $Id:  */

-------------
-- SUMMARY --
-------------
This gives you the option to have a public API with different formats. So you
can use a REST interface to have your images anywhere else.

Easy, Fast, Reliable.

For a full description of the module, visit the project page:
  http://drupal.org/project/fast_gallery

To submit bug reports and feature suggestions, or to track changes:
  http://drupal.org/project/issues/fast_gallery


-------------------
-- How to use it --
-------------------

This is how you use the REST interface:

http://localhost/htdocs/drupal/fast_gallery_api/get?type=html&path=test&gallery=sites/default/files

Use the following GET keys:

- type -
  html
  xml
  json
How should the data be delivered

- path -
The path of the gallery. You can read this from the webinterface. So this is the
actual path of that you are browsing through. If you want to display the top folder
you would just type in the path alias

- gallery -
This is the path to the actual gallery.