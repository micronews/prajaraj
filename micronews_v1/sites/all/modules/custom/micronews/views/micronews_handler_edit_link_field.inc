<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying edit links
 * as fields
 */


class micronews_handler_edit_link_field extends micronews_handler_link_field {
  function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
  }


  function render($values) {
    $type = $values->{$this->aliases['type']};
    
    //Creating a dummy micronews to check access against
    $dummy_micronews = (object) array('type' => $type);
    if (!micronews_access('edit', $dummy_micronews)) {
      return;
    }
    
    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');
    $micronews_id = $values->{$this->aliases['micronews_id']};
    
    return l($text, 'admin/content/micronews/micronews/' . $micronews_id . '/edit');
  }
}
