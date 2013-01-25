CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation


INTRODUCTION
------------

Current Maintainers:
  Yannick Leyendecker (http://drupal.org/user/531118)
  Matt Tucker (http://drupal.org/user/153963)

This module provides a field formatter for jQuery Backstretch [1].
A simple jQuery plugin that allows you to add a dynamically-resized,
slideshow-capable background image to any page or element.

INSTALLATION
------------

1. Install the module the drupal way [2]

2. Install the jQuery Update (>7.x-2.2) module [3]

3. Put the jquery.backstretch.min.js [4] in
   sites/all/libraries/jquery.backstretch/ directory or just run
   "drush backstretch-download" if you have Drush installed. The Drush command
   runs automatically if you enable this module via Drush.

4. Select "Backstretch" as field formatter or create a new Context and select
   "Backstretch" as reaction.

[1] http://srobbin.com/jquery-plugins/backstretch
[2] http://drupal.org/documentation/install/modules-themes/modules-7
[3] http://drupal.org/project/jquery_update
[4] http://git.io/h6PMuw
