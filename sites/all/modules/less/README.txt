// $Id: README.txt,v 1.1.2.4 2010/12/09 03:22:13 coreym29 Exp $

LESS CSS Preprocessor

Files in lessphp/ are from the library at http://leafo.net/lessphp/

The LICENSE file in lessphp/ applies only to files within lessphp/


DIRECTIONS:

Can be invoked by either "drupal_add_css('filename.css.less')" or in the .info
file of your theme as "stylesheets[all][] = filename.css.less"

I highly suggest that you name your files as "somefilename.css.less", as .css
portion of the filename is critical to some internal Drupal code.


RTL Compatibility:

As long as you name your files like "filename.css.less" Drupal should
automatically detect and use "filename-rtl.css.less" if the file is present.


INCLUDES:

Files can be included using the standard @import syntax
(http://www.w3.org/TR/CSS2/cascade.html#at-import).
Each file that is included in such a manner will inserted into the including
document and then the including document will be parsed.