<?php

class views_handler_field_registrations_dates extends views_handler_field_entity {
  function render($values) {
    if ($entity = $this->get_value($values)) {
      $info = pond_get_by_uid($entity->uid, $entity->year);
      return $info['dates_formatted'];
    }
  }
}
