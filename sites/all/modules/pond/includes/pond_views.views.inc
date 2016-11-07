<?php


/**
 * Implements hook_views_data_alter().
 */
function pond_views_views_data_alter(&$data) {
  $entity_tables = array(
    'eck_registrations' => 'Registration',
    'eck_worker' => 'Worker',
    'eck_international_application' => 'International Application',
    'eck_reference' => 'Reference',
    'eck_assessment' => 'Assessment',
    );
  foreach($entity_tables as $source_table => $source_label){
    foreach($entity_tables as $target_table => $target_label){
      if($target_table != $source_table){
        //Link every table to every other table but not to itself.
        $label = t('Linked '.$target_label);
        $data[$source_table][$target_table] = array(
          'title' => $label,
          'help' => $label,
          'relationship' => array(
            'label' => $label,
            'handler' => 'views_handler_relationship',
            'base' => $target_table,
            'base field' => 'uid',
            'relationship field' => 'uid',
            'extra' => $source_table.'.year = '.$target_table.'_'.$source_table.'.year',
          ),
        );
      }
    }
  }


  $data['views_entity_registrations']['base'] = array(
    'field' => array(
      'title' => t('Base Name'),
      'help' => t('Full name followed by gender and age.'),
      'handler' => 'views_handler_field_registrations_base',
    ),
  );
  $data['views_entity_registrations']['building'] = array(
    'field' => array(
      'title' => t('Assigned Buildings'),
      'help' => t('The hotels this person has been assigned to.'),
      'handler' => 'views_handler_field_registrations_building',
    ),
  );
  $data['views_entity_registrations']['church'] = array(
    'field' => array(
      'title' => t('Church'),
      'help' => t('The church this person is currently attending.'),
      'handler' => 'views_handler_field_registrations_church',
    ),
  );
  $data['views_entity_registrations']['dates'] = array(
    'field' => array(
      'title' => t('Dates'),
      'help' => t('The dates this person has applied for (seperated by a "|").'),
      'handler' => 'views_handler_field_registrations_dates',
    ),
  );
  $data['views_entity_registrations']['leader'] = array(
    'field' => array(
      'title' => t('Team Leader'),
      'help' => t('The assigned team leader.'),
      'handler' => 'views_handler_field_registrations_leader',
    ),
  );
  $data['views_entity_registrations']['location'] = array(
    'field' => array(
      'title' => t('Location'),
      'help' => t('The location applied for.'),
      'handler' => 'views_handler_field_registrations_location',
    ),
  );
  $data['views_entity_registrations']['nation'] = array(
    'field' => array(
      'title' => t('Nation'),
      'help' => t('The nation of the location this user has applied for.'),
      'handler' => 'views_handler_field_registrations_nation',
    ),
  );
  $data['views_entity_registrations']['owing'] = array(
    'field' => array(
      'title' => t('Amount Owing'),
      'help' => t('The amount outstanding for this user and this year.'),
      'handler' => 'views_handler_field_registrations_owing',
    ),
  );
  $data['views_entity_registrations']['referee'] = array(
    'field' => array(
      'title' => t('Referee'),
      'help' => t('The referee listed by this applicant.'),
      'handler' => 'views_handler_field_registrations_referee',
    ),
  );
  $data['views_entity_registrations']['role'] = array(
    'field' => array(
      'title' => t('Role'),
      'help' => t('The role applied for.'),
      'handler' => 'views_handler_field_registrations_role',
    ),
  );
  $data['views_entity_registrations']['status'] = array(
    'field' => array(
      'title' => t('Status'),
      'help' => t('The current status of this application.'),
      'handler' => 'views_handler_field_registrations_status',
    ),
  );
  $data['views_entity_registrations']['zone'] = array(
    'field' => array(
      'title' => t('Zone'),
      'help' => t('The zone this person has been assigned to.'),
      'handler' => 'views_handler_field_registrations_zone',
    ),
  );
}


