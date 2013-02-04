<?php

/**
 * @file
 * micronews type editing UI.
 */

/**
 * UI controller.
 */
class micronewsTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
		$items[$this->path]['description'] = 'Manage micronews entity types, including adding
		and removing fields and the display of fields.';
    return $items;
  }
}

/**
 * Generates the micronews type editing form.
 */
function micronews_type_form($form, &$form_state, $micronews_type, $op = 'edit') {

  if ($op == 'clone') {
    $micronews_type->label .= ' (cloned)';
    $micronews_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $micronews_type->label,
    '#description' => t('The human-readable name of this micronews type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($micronews_type->type) ? $micronews_type->type : '',
    '#maxlength' => 32,
//    '#disabled' => $micronews_type->isLocked() && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'micronews_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this micronews type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['data']['#tree'] = TRUE;


  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save micronews type'),
    '#weight' => 40,
  );

  //Locking not supported yet
  /*if (!$micronews_type->isLocked() && $op != 'add') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete micronews type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('micronews_type_form_submit_delete')
    );
  }*/
  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function micronews_type_form_submit(&$form, &$form_state) {
  $micronews_type = entity_ui_form_submit_build_entity($form, $form_state);
  $micronews_type->save();
  $form_state['redirect'] = 'admin/structure/micronews_types';
}

/**
 * Form API submit callback for the delete button.
 */
function micronews_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/micronews_types/manage/' . $form_state['micronews_type']->type . '/delete';
}
