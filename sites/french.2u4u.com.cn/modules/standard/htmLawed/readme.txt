$Id: readme.txt,v 1.5.2.3.2.1 2009/05/20 03:13:14 patnaik Exp $

htmLawed Drupal 6.x module
==========================

    GPL v3 license
    Copyright Santosh Patnaik, MD, PhD
    Initiated May 2008

About the module
----------------

    The htmLawed Drupal module enables the use of the htmLawed (X)HTML filter/purifier in Drupal. Unlike Drupal's HTML filter, htmLawed allows fine control on the HTML markup (e.g., restricting URLs by protocols and limiting element attributes), balances tags, beautifies HTML code, etc. Unlike filters like HTMLPurifier or HTML Tidy, the single-file htmLawed is much faster, more customizable, uses 10-20x less memory, is 10-20x smaller, works with PHP 4, covers all HTML markup, and does not require an external library or PHP extension.

    The module:

    *   allows CONTENT (node)-TYPE-SPECIFIC htmLawed settings (e.g., allowing a certain HTML tag/element in stories but not in blog-posts)

    *   allows INPUT FORMAT-SPECIFIC htmLawed settings

    *   provides OPTION TO FILTER BEFORE STORAGE in the database (in-built Drupal filters don't do this)

    *   allows DIFFERENT SETTINGS FOR COMMENTS & TEASERS

    *   allows setting DEFAULT VALUES for use with any content-type

    The module does not install or modify (structures of) existing Drupal database tables; all information is stored in the 'variable' table in items named 'htmLawed_format_x' where 'x' refers to numbers identifying various input formats.

    If you enable htmLawed, it is important that you understand the security implications of the settings you use and the limitations of htmLawed.

    The version of htmLawed used by the module would be indicated on the web-page for the 'help' section of the module. Keeping the module up-to-date with the latest htmLawed version is as simple as replacing the htmLawed/htmLawed.php and htmLawed/htmLawed_README.htm files in the htmLawed module folder.


About htmLawed
--------------

    htmLawed is a single-file PHP software that makes input text more secure, and standard- and admin. policy-compliant for use in the body of HTML 4, or XHTML 1 or 1.1 documents. It thus is a customizable HTML/XHTML filter, processor, purifier, sanitizer, beautifier, etc., like HTML Tidy or the Kses, HTMLPurifier, etc., PHP scripts.

    The lawing-in of input text is needed to ensure that HTML code in the text is standard-compliant, does not introduce security vulnerabilities, and does not break a web-page's design/layout. htmLawed tries to do this by, for example, making HTML well-formed with balanced and properly nested tags, neutralizing code that may be used for cross-site scripting (XSS) attacks, and allowing only specified HTML elements/tags and attributes.

    For htmLawed download and forum-based support, visit the htmLawed home page at http://www.bioinformatics.org/phplabware/internal_utilities/htmlawed.


Module installation
-------------------

1.  Move 'htmLawed' folder inside 'modules/' or 'sites/all/modules' (you may have to create the latter sub-folder).

2.  Enable the 'htmLawed filter/purifier' module after browsing to the 'Administer' > 'Site building' > 'Modules' section of your Drupal site.

3.  Browse to the 'Administer' > 'Site configuration' > 'Input formats' section. There you can 'configure' an input format to make it use htmLawed by selecting it in the list of filters available for the input format.

    With htmLawed turned on, you may safely disable Drupal's 'HTML filter'. Depending on the other filters enabled for the input format, you may need to 'rearrange' the filters. Usually, htmLawed would be set to run as the last filter (perhaps second-last, if the 'Line break converter' filter is enabled).

    If a filter that relies on the '<', '>' or '&' character (such as Drupal's 'PHP evaluator') is being used with the input format, then that filter should run before htmLawed. Further, if that filter generates HTML markup, then htmLawed should be configured to permit such markup.

4.  The htmLawed filter is a customizable one. Two values, those of 'Config.' and 'Spec.', dictate the customization. Configuring the htmLawed module thus involves specifying the 'Config.' and 'Spec.' values in the settings form. The htmLawed module permits you to use different 'Config.' and 'Spec.' values for different input formats, content-types, etc.

    To get to the settings form, choose to 'configure' an input format and then choose the 'Configure' link on the ensuing page. A sub-form ('Default') can be used to set the default values to be used for any content-type. Content-type-specific sub-forms allow you to over-ride the default values as well as to choose to use (or disable) htmLawed.

    The 'Config.' form-fields are filled with comma-separated, quoted, key-value pairs; e.g., '"safe"=>1, "elements"=>"a, em, strong"' (these are interpreted as PHP array elements). The 'Spec.' field is optional. The 'Help' field should be filled with information/tips about the filter (such as what tags are allowed) to be displayed to the users. A checkbox is provided in the content-type-specific sub-forms to allow the 'Default' values to be used. If it is unchecked, the content-type-specific values will be used during filtering.

    Filtering is further individualized for 'Body', 'Comment', 'Teaser' and 'Other'. 'Body' refers to the main content (such as a blog-post). 'Comment' refers to a user comment on the main content. 'Teaser' (called 'RSS' in version 1 of the module) refers to the news-feed (RSS) items and teasers generated from the main content. You may have a need for 'Other' (in 'Default') if you use modules like 'Views' to have extra input fields (like 'Header') that are not content (node)-type-specific. Content-type-specific settings for 'Other' are obviously not possible. 

    *   If htmLawed is enabled for 'Teaser', the htmLawed filtering is done at the end of all other filtering, including any prior htmLawed filtering because of 'Body'.

    *   For 'Body' and 'Comment', filtering can also be enabled for 'save', in which case the submitted input is first filtered before being saved in the site database. However, you have to check if this causes conflicts with filters (other than Drupal's 'PHP evaluator') that rely on the '<', '>' or '&' character.

    *   The default settings allow the a, em, strong, cite, code, ol, ul, li, dl, dt and dd HTML tags, and deny the id and style attributes, and any unsafe markup (such as the scriptable HTML attributes). For 'Teaser', the default settings will allow 'br' and 'p' as well.

    *   The default settings are used to pre-fill the htmLawed module form-fields and during the filtering only if the specific settings cannot be found. Emptying a 'Config.' field does not mean that the default settings will be used.

    *   Highly customized filtering can be achieved by appropriately setting 'Config.' and 'Spec.' Refer to htmLawed documentation for more.

5.   For restricting user access to the administration of htmLawed settings, go to the 'Administer' > 'User management' section of your site. Ideally, only the main administrator of the site should have the access.

6.   A Drupal handbook may be available for htmLawed. Check http://drupal.org/search/apachesolr_search/htmLawed?filters=type%3Abook


Notes
-----

1. Check for conflicts with any third-party filter modules in use.

2. You can replace files inside 'htmLawed/htmLawed/' with the latest versions from http://www.bioinformatics.org/phplabware/internal_utilities/htmlawed/index.php.

3. Deleting a content-type will delete the associated htmLawed settings.

4. Deleting an input format will NOT automatically delete the associated htmLawed settings. You'll have to run cron to delete the not-needed htmLawed settings: 'Administer' > 'Reports' > 'Status report' > 'run cron manually'.

5. Disabling htmLawed for an input format will not delete the associated settings.

6. Uninstalling the htmLawed module through 'Administer' > 'Site building' > 'Modules' > 'Uninstall' will delete all htmLawed settings.

7. Disabling the module will not delete any htmLawed setting.

8. The 'save' functionality is turned off by default for all input formats and content-types.

9. When a new content-type is created, the htmLawed-settings to be used with it must be set; otherwise, the default settings will be used.

10. The latest version of Drupal 6 is recommended for use with this module.


Filter workflow
---------------

The schematic below is to give an idea of how filtering works in Drupal. Note that the 'content-type' of a comment is the 'content-type' of the item (such as a blog-post) for which the comment was made.


 STEP 1: Submission
 ------------------------------------
| * Content such as a comment        |
|   or a blog-post is created/edited |
|   and submitted by a user          |
 ------------------------------------


 STEP 2: Storage
 --------------------------------
| * Unfiltered content is stored |   With htmLawed 'save' enabled
| * Teaser is auto-generated     |   content is first htmLawed-filtered
| * Teaser is stored             |   as per content's type
 --------------------------------    
                                     Teaser (like an RSS item) is generated from
                                     the stored content
 STEP 3: Display
 --------------------------------
| * Stored content is retrieved  |   With htmLawed 'show' enabled
|   and filtered before display  |   content is htmLawed-filtered
| * Teaser is filtered for feeds |   as per content's type
 --------------------------------    
                                     Teaser is similarly filtered

                                     Depending on the input format,
                                     filters other than htmLawed
                                     may also process the data