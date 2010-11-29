/* $Id: README.txt,v 1.1 2006/10/13 14:34:50 dman Exp $ */

Import HTML

@author - Dan Morrison <http://coders.co.nz>

About
-----------------------------
For full details, see the import_html_help.htm

Upgrade: Oct 2006
-----------------------------
Significant changes were made to the file exclusion regular expression
process. The original defaults should work as well as they ever did,
but the new default config is:

 ^_
 /_
 CVS
 ^\.
 /\.
 
- this prevents files found INSIDE skipped directories from turning up.
