// $Id: README.txt,v 1.3.2.1.2.1 2009/09/14 07:28:54 madsph Exp $

Welcome to Ubercart Views.
--------------------------

The module depends heavily on the popular Views module (http://drupal.org/project/views). For maximum
benifit of this module, you should at least know the basics of that great module

If you're having trouble installing this module, please ensure that your 
tar program is not flattening the directory tree, truncating filenames
or losing files.

Installing Ubercart Views:
--------------------------

Place the content of this directory in sites/all/modules/uc_views

Navigate to administer >> build >> modules. Enable Ubercart Views.

Please note that most of the views included in this module assumes that images are turned on and
configured for products (See administer >> Store administration)

After installation you will have a number of default views which you can enable and modify by navigating to:
http://your-site/admin/build/views

Since this module utilizes database views, you should make sure that your database user has
CREATE VIEW permission. Some users has reported that ALL PRIVILEGES oddly enough doesn't
necessary include CREATE VIEW.

If you lack CREATE VIEW permissions you will get errors like this:
 uc_order_products_qty_vw (nid,order_count,avg_qty,sum_qty,max_qty,min_qty) AS
 SELECT `op`.`nid` AS `nid`, COUNT(`op`.`nid`) AS `order_count`,AVG(`op`.`qty`) AS
 `avg_qty`, SUM(`op`.`qty`) AS `sum_qty`,MAX(`op`.`qty`) AS `max_qty`, MIN(`op`.`qty`) AS
 `min_qty` FROM `uc_order_products` `op` GROUP BY `op`.`nid` ORDER BY `op`.`nid`
 in /var/www/sites/all/modules/uc_views/uc_views.install on line 9.

To explicitly grant CREATE VIEW to your db user on MySQL via phpMyAdmin as root MySQL user,
execute these queries:
 GRANT CREATE VIEW ON yourdbname.* TO 'dbusername'@'localhost'
 (Replace your database and user / host names as appropriate.)
 FLUSH PRIVILEGES

About Ubercart Views
--------------------
This module provides various views on Ubercart data, such as lists of popular products,
users favourite products, 'users who bought the selected product also bought these' and more.
It also describes some of the Ubercart data tables to views, so you can create your own views, based
on these data.

The module will install a number of database views, which is needed for some of the default views
that ships with this module. If that is a problem for you, you should keep theese disabled, and remove
the database views after installation (the sql to remove the views are found in the .install file).

Ubercart Views is developed with the help of Lenio A/S (www.lenio.dk)
