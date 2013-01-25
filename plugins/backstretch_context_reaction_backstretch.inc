<?php

/**
 * @file
 * Backstretch reaction class for Context integration.
 */

class backstretch_context_reaction_backstretch extends context_reaction {
  function options_form($context) {
    // Fetching saved values.
    $values = $this->fetch_from_context($context);
    $form = array();

    $form['source'] = array(
      '#type' => 'fieldset',
      '#title' => t('Source'),
    );

    $sources = array(
      'entity' => t('Entity'),
      'path' => t('Path'),
    );

    if (module_exists('media')) {
      $sources['media'] = t('Media');
    }

    $form['source']['type'] = array(
      '#type' => 'select',
      '#title' => t('Type'),
      '#options' => $sources,
      '#default_value' => isset($values['source']) ? $values['source'] : '',
    );

    // Getting all entity types.
    $entities = entity_get_info();
    $entity_types = array();

    // Iterate all entity types and prepare an array with entity type
    // and their label.
    foreach ($entities as $entity => $entity_info) {
      $entity_types[$entity] = $entity_info['label'];
    }

    // Getting all field instances.
    $field_instances = field_info_instances();
    $image_fields = array();

    // Prepare an array with all image fields and their label.
    foreach ($field_instances as $entity_type => $bundles) {
      foreach ($bundles as $bundle_name => $fields) {
        foreach ($fields as $field_name => $field_info) {
          $info = field_info_field($field_name);
          if ($info['type'] != 'image') {
            continue;
          }

          $image_fields[$field_name] = $field_info['label'];
        }
      }
    }

    $form['source']['entity']['entity_type'] = array(
      '#type' => 'select',
      '#title' => t('Entity type'),
      '#options' => $entity_types,
      '#default_value' => isset($values['source']['entity']['entity_type']) ? $values['source']['entity']['entity_type'] : '',
      '#empty_option' => t('Select entity type'),
      '#states' => array(
        'visible' => array(
          ':input[name$="[backstretch][source][type]"]' => array('value' => 'entity'),
        ),
      ),
    );

    $form['source']['entity']['field'] = array(
      '#type' => 'select',
      '#title' => t('Image field'),
      '#options' => $image_fields,
      '#default_value' => isset($values['source']['entity']['field']) ? $values['source']['entity']['field'] : '',
      '#description' => t('Select the image field which holds the image(s). Note that all image fields are listed here.'),
      '#states' => array(
        'visible' => array(
          ':input[name$="[backstretch][source][type]"]' => array('value' => 'entity'),
          ':input[name$="[backstretch][source][entity][entity_type]"]' => array('!value' => ''),
        ),
      ),
    );

    // If entity type and entity id is available, we can display the entity
    // label as description for entity id field.
    if (isset($values['source']['entity']['entity_type']) && isset($values['source']['entity']['id'])) {
      $entity_type = $values['source']['entity']['entity_type'];
      $entity_id = $values['source']['entity']['id'];

      $entity = entity_load($entity_type, array($entity_id));
      $entity = reset($entity);
      $label = entity_label($entity_type, $entity);
      $entity_description = t('Title: %label', array('%label' => $label));
    }

    $form['source']['entity']['id'] = array(
      '#type' => 'textfield',
      '#title' => t('Entity id'),
      '#default_value' => isset($values['source']['entity']['id']) ? $values['source']['entity']['id'] : '',
      '#description' => isset($entity_description) ? $entity_description : '',
      '#states' => array(
        'visible' => array(
          ':input[name$="[backstretch][source][type]"]' => array('value' => 'entity'),
          ':input[name$="[backstretch][source][entity][entity_type]"]' => array('!value' => ''),
        ),
      ),
      '#element_validate' => array('element_validate_integer_positive'),
    );

    $form['source']['path'] = array(
      '#type' => 'textarea',
      '#title' => t('Path'),
      '#default_value' => isset($values['source']['path']) ? $values['source']['path'] : '',
      '#description' => t('Enter one path per line. It can be relative to Drupal root or absolute.'),
      '#states' => array(
        'visible' => array(
          ':input[name$="[backstretch][source][type]"]' => array('value' => 'path'),
        ),
      ),
    );

    // Add a media file selector field if Media module exists.
    if (module_exists('media')) {
      // Currently we can only add one media field.
      $form['source']['media'] = array(
        '#type' => 'media',
        '#title' => t('Media'),
        '#default_value' => isset($values['source']['media']) ? $values['source']['media'] : '',
        '#media_options' => array('types' => array('image')),
        '#description' => t('Select images via the media file selector.'),
        '#states' => array(
          'visible' => array(
            ':input[name$="[backstretch][source][type]"]' => array('value' => 'media'),
          ),
        ),
      );
    }

    $image_styles = image_style_options(FALSE);
    $form['image_style'] = array(
      '#title' => t('Image style'),
      '#type' => 'select',
      '#default_value' => isset($values['image_style']) ? $values['image_style'] : '',
      '#options' => $image_styles,
      '#empty_option' => t('None (original image)'),
      '#description' => t('Image style for the images.'),
    );

    $form['element'] = array(
      '#type' => 'select',
      '#title' => t('Attach to'),
      '#default_value' => isset($values['element']) ? $values['element'] : '',
      '#options' => array(
        'other' => t('Other element'),
      ),
      '#empty_option' => t('Whole page'),
      '#description' => t('Where the Backstretch should be attached to.'),
    );

    $form['element_other'] = array(
      '#type' => 'textfield',
      '#title' => t('Other element'),
      '#default_value' => isset($values['element_other']) ? $values['element_other'] : '',
      '#description' => t('Enter the CSS selector for the element.'),
      '#states' => array(
        'visible' => array(
          ':input[name$="[element]"]' => array('value' => 'other'),
        ),
      ),
    );

    $form['duration'] = array(
      '#type' => 'textfield',
      '#title' => t('Duration'),
      '#default_value' => isset($values['duration']) ? $values['duration'] : 10,
      '#description' => t('Amount of time in between slides.'),
      '#size' => 10,
      '#field_suffix' => 'ms',
      '#element_validate' => array('element_validate_integer_positive'),
    );

    $form['fade'] = array(
      '#type' => 'textfield',
      '#title' => t('Fade'),
      '#default_value' => isset($values['fade']) ? $values['fade'] : 10,
      '#description' => t('Speed of fade transition between slides. Can be an integer or a string like: %slow or %fast.', array('%slow' => 'slow', '%fast' => 'fast')),
      '#size' => 10,
      '#element_validate' => array('backstretch_element_validate_duration'),
    );

    $form['center_x'] = array(
      '#type' => 'checkbox',
      '#title' => t('Horizontal centered'),
      '#default_value' => isset($values['center_x']) ? $values['center_x'] : TRUE,
      '#description' => t('Should we center the image on the X axis?'),
    );

    $form['center_y'] = array(
      '#type' => 'checkbox',
      '#title' => t('Vertically centered'),
      '#default_value' => isset($values['center_y']) ? $values['center_y'] : TRUE,
      '#description' => t('Should we center the image on the Y axis?'),
    );

    return $form;
  }

  function execute() {
    foreach ($this->get_contexts() as $context) {
      if (!empty($context->reactions[$this->plugin])) {
        // We need an unique id for every Backstretch.
        static $id = 1;
        // Getting context settings.
        $settings = $context->reactions[$this->plugin];
        // Store the source stuff here.
        $source = $settings['source']['type'];

        // We store the default values from Backstretch formatter here.
        $formatters = backstretch_field_formatter_info();
        $default = $formatters['backstretch']['settings'];

        // We need the js variable name.
        $options_info = backstretch_formatter_options();
        // Here we store all options later.
        $options = array();

        foreach ($settings as $name => $value) {
          if (array_key_exists($name, $options_info)) {
            $option = $options_info[$name];
            $js = isset($option['js']) ? $option['js'] : '';

            // We need some special handling with the element settings.
            if ($name == 'element' || ($name == 'element_other' && $settings['element'] == '')) {
              continue;
            }

            // We only put the setting into $options when it is
            // not the default value.
            if ($value != $default[$name] && $js) {
              $options[$js] = $value;
            }
          }
        }

        // We need special handling for every source type.
        switch ($source) {
          case 'entity':
            // We store the entity info.
            $entity_type = $settings['source']['entity']['entity_type'];
            $field = $settings['source']['entity']['field'];
            $entity_id = $settings['source']['entity']['id'];

            $entity = entity_load($entity_type, array($entity_id));
            // Because entity_load needs an array for the ids so we have to
            // get the first array item.
            $entity = reset($entity);
            // Getting the field items.
            $items = field_get_items($entity_type, $entity, $field);

            // Iterate all items and store the absolute url to it.
            foreach ($items as &$item) {
              $uri = $item['uri'];
              // Get url to image styled image if a image style was set.
              if ($settings['image_style']) {
                $url = image_style_url($settings['image_style'], $uri);
              }
              // Otherwise just get the url.
              else {
                $url = file_create_url($uri);
              }
              $options['items'][] = $url;
            }
            break;

          case 'path':
            // Just storing the path info.
            $paths = $settings['source']['path'];
            // We need an array for processing the paths.
            $paths = explode("\n", $paths);

            foreach ($paths as $key => $path) {
              $path = trim($path);
              // Just build an url for the path.
              $paths[$key] = url($path);
              // If an image style was set we try to image style the image.
              if ($settings['image_style']) {
                $uri = file_build_uri(drupal_basename($path));
                $paths[$key] = image_style_url($settings['image_style'], $uri);
              }
            }

            $options['items'] = $paths;
            break;

          case 'media':
            // Getting the selected media.
            $media = $settings['source']['media'];

            // Currently we can only add one media field.
            $fid = $media['fid'];

            $file = file_load($fid);
            $uri = $file->uri;
            // Get url to image styled image if a image style was set.
            if ($settings['image_style']) {
              $url = image_style_url($settings['image_style'], $uri);
            }
            // Otherwise just get the url.
            else {
              $url = file_create_url($uri);
            }
            $options['items'][] = $url;

            break;
        }

        // Prepare a renderable array.
        $element = array(
          '#theme' => 'backstretch',
          '#id' => 'backstretch-' . $id,
          '#options' => $options,
        );

        // Increasing the id.
        $id++;

        // Return the rendered element.
        return drupal_render($element);
      }
    }
  }
}
