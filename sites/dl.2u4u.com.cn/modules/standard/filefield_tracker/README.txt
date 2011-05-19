; $Id: README.txt,v 1.2 2010/05/28 11:29:08 xeniox Exp $

Description
-----------
The filefield_tracker module allows you to track the download of private filefields.
This module depends on the Filefield module and requires the private download method to be set.

Features
---------
* Provides new CCK field formatter that lists filefield files with a trackable link
* Provides global reporting for privileged users on downloaded files (filename - node - user - download time)
* Provides per node reporting tab for privileged  users on downloaded files belonging to that node (filename - user - download time)
* Exclude roles from tracking

Installation
------------
1) Place the module folder in your sites/all/modules folder
2) Activate the module via admin/build/modules
3) Set the permissions at admin/user/permissions
4a) Go to Administer > Site configuration > Filefield download tracker
4b) Specify for which content types you wish to enable the tracking tab for privileged users.
    By default the tab will appear on all content types that have a filefield.
5) For each filefield you wish to track downloads on:
   * Go to Administer > Content types.
   * Click 'edit' per content type that has filefields that should have download tracking
   * Select the tab 'Manage fields'
   * Search for your filefields, and select 'Filefield download tracking link' as formatter for teaser and / or full node display

Note that only filefields with this formatter will have download tracking enabled.
Alternatively you could use the function filefield_tracker_create_url($fid, $nid, $filename) to construct a trackable URL in your own module or theme

Hooks
-----
When a new tracking record is stored into the database, hook_filefield_tracker($entry) is invoked.

Author
------
Sven Decabooter (http://drupal.org/user/35369) of Pure Sign (http://www.puresign.be)
The author can be contacted for paid customizations of this module as well as Drupal consulting and development.