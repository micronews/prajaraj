<?php

/**
 * @file
 * Provide views data and handlers for Micro module.
 */

/**
 * Implementation of hook_views_data().
 */
function micro_views_data() {

  // ----------------------------------------------------------------------
  // Micro table

  //Basic table information.
  $data['micro']['table']['group']  = t('Micro');
  $data['micro']['table']['join'] = array(
    'micro_type' => array(
      'left_table' => 'micro',
      'left_field' => 'type',
      'field' => 'type',
      'type' => 'INNER',
    ),
  );

  //Advertise this table as a possible base table.
  $data['micro']['table']['base'] = array(
    'field' => 'mid',
    'title' => t('Micro'),
    'help' => t('Micro items are attacheable to other fieldable entities.'),
    'weight' => 10,
  );

  //Declares the micro id column.
  $data['micro']['mid'] = array(
    'title' => t('Micro ID'),
    'help' => t('The ID of the micro item.'),
    'field' => array(
      'handler' => 'micro_views_handler_field_micro',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['micro']['edit'] = array(
    'title' => t('Edit'),
    'help' => t('Shows a link to edit the micro item to users with permission to see it.'),
    'field' => array(
      'field' => 'mid',
      'handler' => 'micro_views_handler_field_edit',
      'click sortable' => FALSE,
    ),
  );
  $data['micro']['delete'] = array(
    'title' => t('Delete'),
    'help' => t('Shows a link to delete the micro item to users with permission to see it.'),
    'field' => array(
      'field' => 'mid',
      'handler' => 'micro_views_handler_field_delete',
      'click sortable' => FALSE,
    ),
  );

  $data['micro']['path'] = array(
    'field' => array(
      'title' => t('Path'),
      'help' => t('The aliased path to this micro.'),
      'handler' => 'micro_views_handler_field_micro_path',
    ),
  );

  // ----------------------------------------------------------------------
  // Micro type table

  $data['micro_type']['table']['group']  = t('Micro');
  $data['micro_type']['table']['join'] = array(
    'micro' => array(
      'left_field' => 'type',
      'field' => 'machine_name',
      'type' => 'INNER',
    ),
  );

  // Micro type
  $data['micro_type']['machine_name'] = array(
    'title' => t('Type'),
    'help' => t('The type of a micro item.'),
    'field' => array(
      'handler' => 'micro_views_handler_field_micro_type',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'micro_views_handler_filter_micro_type',
    ),
    'argument' => array(
      'handler' => 'micro_views_handler_argument_micro_type',
    ),
  );

  // Entity type
  $data['micro_type']['entity'] = array(
    'title' => t('Entity'),
    'help' => t('The entity the micro item is attached to.'),
    'field' => array(
      'handler' => 'micro_views_handler_field_micro_entity',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'micro_views_handler_filter_micro_entity',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument',
    ),
  );

  return $data;
}

/**
 * A helper function that creates a radio list of available micros.
 *
 * This function is used to select the desired micro when setting up micro
 * relationships and fields.
 */
function micro_views_config_form($form_type, $entity_type, $current_micro) {
  $micro_types = micro_types_from_entity($entity_type);

  $options = array();
  foreach ($micro_types as $type) {
    $options[$type->machine_name] = $type->name;
  }

  $form = array(
    '#type' => $form_type,
    '#title' => t('micro'),
    '#options' => $options,
    '#default_value' => $current_micro,
    '#required' => TRUE,
  );

  return $form;
}


/**
 * Implements hook_views_plugins
 */
function micro_views_plugins() {
  return array(
    'module' => 'views',
    'row' => array(
      'micro' => array(
        'title' => t('Micro'),
        'help' => t('Display the micro with standard micro view.'),
        'handler' => 'micro_plugin_row_micro_view',
        'path' => drupal_get_path('module', 'micro') . '/includes/views',
        'theme' => 'views_view_row_micro',
        'base' => array('micro'),
        'uses options' => TRUE,
        'type' => 'normal',
        'help topic' => 'style-micro',
      ),
    ),
  );
}

/**
 * Template helper for theme_views_view_row_micro
 */
function template_preprocess_views_view_row_micro(&$vars) {
  $options = $vars['options'];

  // Make sure the variables are defined.
  $vars['micro'] = '';
  $vars['comments'] = '';

  if (!empty($vars['row']->{$vars['field_alias']})) {
    $mid = $vars['row']->{$vars['field_alias']};
  }
  if (!is_numeric($mid)) {
    return;
  }

  $row_plugin = $vars['view']->style_plugin->row_plugin;
  $micro = $row_plugin->micros[$mid];

  if (empty($micro)) {
    return;
  }

  $micro->view = $vars['view'];
  // Detect which build module should be used.
  $micro->build_mode = ($options['build_mode'] == 'teaser' || $options['build_mode'] == 'full') ? $options['build_mode'] : 'full';
  $content = micro_view_multiple(array($micro->mid => $micro), $micro->build_mode);
  $content = $content['micro_items'][$micro->mid];
  if (!$options['links']) {
    unset($content['links']);
  }

  /*
   *if (!empty($options['comments']) && user_access('access comments') && $micro->comment) {
   *  $vars['comments'] = drupal_render(comment_micro_page_additions($micro));
   *}
   */

  $vars['micro'] = drupal_render($content);

}

