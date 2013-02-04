<?php

/**
 * This field handler aggregates operations that can be done on a micronews
 * under a single field providing a more flexible way to present them in a view
 */
class micronews_handler_micronews_operations_field extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['micronews_id'] = 'micronews_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {

    $links = menu_contextual_links('micronews', 'admin/content/micronews/micronews', array($this->get_value($values, 'micronews_id')));
    
    if (!empty($links)) {
      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
