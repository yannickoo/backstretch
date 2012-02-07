<?php

/**
 * Page callback for admin/appearance/backstretch.
 */
function backstretch_admin_settings() {
  $form = array();
  $form['backstretch_image_url'] = array(
    '#title' => t('Image URL'),
    '#description' => t('URL of picture to display as backstretched background (begin with / if local to drupal). Leave blank for none.'),
    '#type' => 'textfield',
    '#default_value' => variable_get('backstretch_image_url', ''),
  );
  $form['backstretch_min_width'] = array(
    '#title' => t('Minimum width'),
    '#description' => t('Window width (in px) must be greater than this value in order for backstretch to apply. This allows you to prevent large images from being loaded on to small devices.'),
    '#type' => 'textfield',
    '#default_value' => variable_get('backstretch_min_width', 0),
  );
  $form['backstretch_margin_selector'] = array(
    '#title' => t('Margin selector'),
    '#description' => t('If a CSS selector is provided, a margin equal to the window height will be added. This selector should ideally be at the bottom of the DOM to allow the user to scroll down to view the full photo.'),
    '#type' => 'textfield',
    '#default_value' => variable_get('backstretch_margin_selector', ''),
  );
  $form['backstretch_margin_adjustment'] = array(
    '#title' => t('Margin adjustment'),
    '#description' => t('Add or subtract a px amount from the margin added to the selector listed above.'),
    '#type' => 'textfield',
    '#default_value' => variable_get('backstretch_margin_adjustment', 0),
  );
  return system_settings_form($form);
}
