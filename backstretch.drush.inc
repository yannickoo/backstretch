<?php

/**
 * @file
 * Drush integration for the Backstretch module.
 */

/**
 * The URL to Backstretch plugin.
 */
define('BACKSTRETCH_DOWNLOAD_URL', 'https://raw.github.com/srobbin/jquery-backstretch/master/jquery.backstretch.min.js');

/**
 * Implements hook_drush_command().
 */
function backstretch_drush_command() {
  $items = array();

  $items['backstretch-download'] = array(
    'description' => dt('Downloads the Backstretch plugin from GitHub.'),
    'arguments' => array(
      'path' => dt('Optional. A path to the libraries directory. If ommitted the default location will be used (sites/all/libraries).'),
    ),
  );

  return $items;
}

/**
 * Implements drush_MODULE_post_COMMAND().
 */
function drush_backstretch_post_pm_enable() {
  $modules = func_get_args();

  // If our module was enabled we run the download command.
  if (in_array('backstretch_formatter', $modules)) {
    drush_backstretch_formatter_backstretch_download();
  }
}

/**
 * Command callback for 'backstretch-download'.
 */
function drush_backstretch_download() {
  $args = func_get_args();
  if (isset($args[0])) {
    $path = $args[0];
  }
  else {
    $path = 'sites/all/libraries';
  }

  // Building directory name for Backstretch plugin.
  $dirname = str_replace('.min.js', '', basename(BACKSTRETCH_DOWNLOAD_URL));
  $fullpath = $path . '/' . $dirname;

  // Create the path if it does not exist.
  if (!is_dir($fullpath)) {
    // Create path recursively.
    drush_op('mkdir', $fullpath, 0777, TRUE);
    drush_log(dt('Directory @path was created', array('@path' => $fullpath)), 'notice');
  }
  else {
    // Override any existing Backstretch plugin directory.
    drush_log(dt('An existing version of Backstretch was overwritten at @path', array('@path' => $fullpath)), 'warning');
  }

  // Remember curent working directory.
  $olddir = getcwd();

  // Set the directory to the download location.
  chdir($fullpath);

  // Download the Javascript file.
  if (!drush_shell_exec('wget --no-check-certificate ' . BACKSTRETCH_DOWNLOAD_URL)) {
    drush_shell_exec('curl -O ' . BACKSTRETCH_DOWNLOAD_URL);
  }

  // Set working directory back to the previous working directory.
  chdir($olddir);

  if (file_exists($fullpath . '/' . basename(BACKSTRETCH_DOWNLOAD_URL))) {
    drush_log(dt('Backstretch plugin has been downloaded to @path', array('@path' => $fullpath)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to download the Backstretch plugin to @path', array('@path' => $fullpath)), 'error');
  }
}
