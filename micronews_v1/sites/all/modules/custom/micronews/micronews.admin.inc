<?php

/**
 * @file
 * micronews editing UI.
 *
 * We make very little use of the EntityAPI interface for this - preferring instead to use
 * views. That offers more flexibility to change a UI that will, more often than not,
 * be end-user facing.
 */

/**
 * UI controller.
 */
class micronewsUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults. Main reason for doing this is that
   * parent class hook_menu() is optimized for entity type administration.
   */
  public function hook_menu() {
    
    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    $items[$this->path] = array(
      'title' => 'Micronews',
      'description' => 'Add edit and update Micronews.',
      'page callback' => 'system_admin_menu_block_page',
      'access arguments' => array('access administration pages'),
      
      'file path' => drupal_get_path('module', 'system'),
      'file' => 'system.admin.inc',
    );
    
    // Change the overview menu type for the list of micronews.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;
    
    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add a Micronews',
      'description' => 'Add a new Micronews',
      'page callback'  => 'micronews_add_page',
      'access callback'  => 'micronews_access',
      'access arguments' => array('edit'),

      'type' => MENU_NORMAL_ITEM,
      'weight' => 20,
      'file' => 'micronews.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])

    );
    
    // Add menu items to add each different type of entity.
    foreach (micronews_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => 'Add ' . $type->label,
        'page callback' => 'micronews_form_wrapper',
        'page arguments' => array(micronews_create(array('type' => $type->type))),
        'access callback' => 'micronews_access',
        'access arguments' => array('edit', 'edit ' . $type->type),
        'file' => 'micronews.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module'])
      );
    }

    // Loading and editing micronews entities
    $items[$this->path . '/micronews/' . $wildcard] = array(
      'page callback' => 'micronews_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'micronews_access',
      'access arguments' => array('edit', $id_count + 1),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'micronews.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    $items[$this->path . '/micronews/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );
    
    $items[$this->path . '/micronews/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'micronews_delete_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'micronews_access',
      'access arguments' => array('edit', $id_count + 1),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'micronews.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    
    // Menu item for viewing micronews
    $items['micronews/' . $wildcard] = array(
      //'title' => 'Title',
      'title callback' => 'micronews_page_title',
      'title arguments' => array(1),
      'page callback' => 'micronews_page_view',
      'page arguments' => array(1),
      'access callback' => 'micronews_access',
      'access arguments' => array('view', 1),
      'type' => MENU_CALLBACK,
    );
    return $items;
  }
  
  
  /**
   * Create the markup for the add micronews Entities page within the class
   * so it can easily be extended/overriden.
   */ 
  public function addPage() {
    $item = menu_get_item();
    $content = system_admin_menu_block($item);

    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }    
        
    return theme('micronews_add_list', array('content' => $content));
  }
  
}


/**
 * Form callback wrapper: create or edit a micronews.
 *
 * @param $micronews
 *   The micronews object being edited by this form.
 *
 * @see micronews_edit_form()
 */
function micronews_form_wrapper($micronews) {
  // Add the breadcrumb for the form's location.
  micronews_set_breadcrumb();
  return drupal_get_form('micronews_edit_form', $micronews);
}


/**
 * Form callback wrapper: delete a micronews.
 *
 * @param $micronews
 *   The micronews object being edited by this form.
 *
 * @see micronews_edit_form()
 */
function micronews_delete_form_wrapper($micronews) {
  // Add the breadcrumb for the form's location.
  //micronews_set_breadcrumb();
  return drupal_get_form('micronews_delete_form', $micronews);
}


/**
 * Form callback: create or edit a micronews.
 *
 * @param $micronews
 *   The micronews object to edit or for a create form an empty micronews object
 *     with only a micronews type defined.
 */
function micronews_edit_form($form, &$form_state, $micronews) {
  // Add the default field elements.
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => isset($micronews->name) ? $micronews->name : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );
  
  $form['data']['#tree'] = TRUE;


  // Add the field related form elements.
  $form_state['micronews'] = $micronews;
  field_attach_form('micronews', $micronews, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Micronews'),
    '#submit' => $submit + array('micronews_edit_form_submit'),
  );
  
  if (!empty($micronews->name)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete Micronews'),
      '#suffix' => l(t('Cancel'), 'admin/content/micronews'),
      '#submit' => $submit + array('micronews_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'micronews_edit_form_validate';
  return $form;
}


/**
 * Form API validate callback for the micronews form
 */
function micronews_edit_form_validate(&$form, &$form_state) {
  $micronews = $form_state['micronews'];
  
  // Notify field widgets to validate their data.
  field_attach_form_validate('micronews', $micronews, $form, $form_state);
}


/**
 * Form API submit callback for the micronews form.
 * 
 * @todo remove hard-coded link
 */
function micronews_edit_form_submit(&$form, &$form_state) {
  
  $micronews = entity_ui_controller('micronews')->entityFormSubmitBuildEntity($form, $form_state);
  // Save the micronews and go back to the list of micronews
  
  // Add in created and changed times.
  if ($micronews->is_new = isset($micronews->is_new) ? $micronews->is_new : 0){
    $micronews->created = time();
  }

  $micronews->changed = time();
  
  $micronews->save();
  $form_state['redirect'] = 'admin/content/micronews';
}

/**
 * Form API submit callback for the delete button.
 * 
 * @todo Remove hard-coded path
 */
function micronews_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/micronews/micronews/' . $form_state['micronews']->micronews_id . '/delete';
}


/**
 * Form callback: confirmation form for deleting a micronews.
 *
 * @param $micronews
 *   The micronews to delete
 *
 * @see confirm_form()
 */
function micronews_delete_form($form, &$form_state, $micronews) {
  $form_state['micronews'] = $micronews;

  $form['#submit'][] = 'micronews_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete Micronews %name?', array('%name' => $micronews->name)),
    'admin/content/micronews/micronews',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );
  
  return $form;
}

/**
 * Submit callback for micronews_delete_form
 */
function micronews_delete_form_submit($form, &$form_state) {
  $micronews = $form_state['micronews'];

  micronews_delete($micronews);

  drupal_set_message(t('The Micronews %name has been deleted.', array('%name' => $micronews->name)));
  watchdog('micronews', 'Deleted Micronews %name.', array('%name' => $micronews->name));

  $form_state['redirect'] = 'admin/content/micronews';
}



/**
 * Page to add micronews Entities.
 *
 * @todo Pass this through a proper theme function
 */
function micronews_add_page() {
  $controller = entity_ui_controller('micronews');
  return $controller->addPage();
}


/**
 * Displays the list of available micronews types for micronews creation.
 *
 * @ingroup themeable
 */
function theme_micronews_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<dl class="micronews-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer micronews types')) {
      $output = '<p>' . t('Micronews Entities cannot be added because you have not created any micronews types yet. Go to the <a href="@create-micronews-type">micronews type creation page</a> to add a new micronews type.', array('@create-micronews-type' => url('admin/structure/micronews_types/add'))) . '</p>';
    }
    else {
      $output = '<p>' . t('No Micronews types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}





/**
 * Sets the breadcrumb for administrative micronews pages.
 */
function micronews_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('Micronews'), 'admin/content/micronews'),
  );

  drupal_set_breadcrumb($breadcrumb);
}



