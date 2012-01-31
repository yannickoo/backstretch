<?php

/**
 * Page callback for admin/appearance/backstretch.
 */
function backstretch_admin_settings() {
  $form = array();
  $form['backstretch_image_url'] = array(
    '#title' => t('Image URL'),
    '#description' => t('URL of picture to display as backstretched background. Leave blank for none.'),
    '#type' => 'textfield',
    '#default_value' => variable_get('backstretch_image_url', ''),
  );
  return system_settings_form($form);
}
