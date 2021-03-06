<?php

/**
 * @file
 * Providing extra functionality for the micronews UI via views.
 */


/**
 * Implements hook_views_data()
 */
function micronews_views_data_alter(&$data) { 
  $data['micronews']['link_micronews'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a link to the micronews.'),
      'handler' => 'micronews_handler_link_field',
    ),
  );
  $data['micronews']['edit_micronews'] = array(
    'field' => array(
      'title' => t('Edit Link'),
      'help' => t('Provide a link to the edit form for the micronews.'),
      'handler' => 'micronews_handler_edit_link_field',
    ),
  );
  $data['micronews']['delete_micronews'] = array(
    'field' => array(
      'title' => t('Delete Link'),
      'help' => t('Provide a link to delete the micronews.'),
      'handler' => 'micronews_handler_delete_link_field',
    ),
  );
  // This content of this field are decided based on the menu structure that
  // follows micronews/micronews/%micronews_id/op
  $data['micronews']['operations'] = array(
    'field' => array(
      'title' => t('Operations links'),
      'help' => t('Display all operations available for this micronews.'),
      'handler' => 'micronews_handler_micronews_operations_field',
    ),
  );
}


/**
 * Implements hook_views_default_views().
 */
function micronews_views_default_views() {
  $views = array();

  $view = new view;
  $view->name = 'micronews';
  $view->description = 'A list of all micronews';
  $view->tag = 'micronews';
  $view->base_table = 'micronews';
  $view->human_name = 'micronews';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  
  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'micronews';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create any micronews type';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'micronews_id' => 'micronews_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'micronews_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty ';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No micronews have been created yet';
  /* Field: micronews: micronews ID */
  $handler->display->display_options['fields']['micronews_id']['id'] = 'micronews_id';
  $handler->display->display_options['fields']['micronews_id']['table'] = 'micronews';
  $handler->display->display_options['fields']['micronews_id']['field'] = 'micronews_id';
  $handler->display->display_options['fields']['micronews_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['micronews_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['micronews_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['micronews_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['micronews_id']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['micronews_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['micronews_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['micronews_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['micronews_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['micronews_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['micronews_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['micronews_id']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['micronews_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['micronews_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['micronews_id']['empty_zero'] = 0;
  /* Field: micronews: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'micronews';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  /* Field: micronews: Link */
  $handler->display->display_options['fields']['link_micronews']['id'] = 'link_micronews';
  $handler->display->display_options['fields']['link_micronews']['table'] = 'micronews';
  $handler->display->display_options['fields']['link_micronews']['field'] = 'link_micronews';
  $handler->display->display_options['fields']['link_micronews']['label'] = 'View';
  $handler->display->display_options['fields']['link_micronews']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['link_micronews']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['link_micronews']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['link_micronews']['alter']['external'] = 0;
  $handler->display->display_options['fields']['link_micronews']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['link_micronews']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['link_micronews']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['link_micronews']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['link_micronews']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['link_micronews']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['link_micronews']['alter']['html'] = 0;
  $handler->display->display_options['fields']['link_micronews']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['link_micronews']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['link_micronews']['hide_empty'] = 0;
  $handler->display->display_options['fields']['link_micronews']['empty_zero'] = 0;
  /* Field: micronews: Operations links */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'micronews';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['external'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['html'] = 0;
  $handler->display->display_options['fields']['operations']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['operations']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['operations']['hide_empty'] = 0;
  $handler->display->display_options['fields']['operations']['empty_zero'] = 0;
  
  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'micronews_admin_page');
  $handler->display->display_options['path'] = 'admin/content/micronews/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'List';
  $handler->display->display_options['menu']['weight'] = '-10';
  $handler->display->display_options['tab_options']['type'] = 'tab';
  $handler->display->display_options['tab_options']['title'] = 'micronews';
  $handler->display->display_options['tab_options']['description'] = 'Manage micronews';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';
  $translatables['micronews'] = array(
    t('Master'),
    t('micronews'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Empty '),
    t('No micronews have been created yet'),
    t('micronews ID'),
    t('.'),
    t(','),
    t('Name'),
    t('View'),
    t('Operations links'),
    t('Page'),
  );
  $views[] = $view;
  return $views;

}
