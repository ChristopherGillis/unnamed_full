<?php

/**
 * Defines one or more datasource inputs.
 *
 * Note: The ids should be valid PHP identifiers of max 32 characters.
 *
 * @return array
 *   An associative array of datasource inputs, keyed by a unique
 *   identifier and containing associative arrays with the following keys:
 *   - name: The datasource input translated name.
 *   - description [optional]: A translated string for description.
 *   - fields: an array of fields
 *   array(
 *     'field1' => t('Name field 1'),
 *     'field2' => array(
 *       'name' => t('Name field 2'),
 *     	 'type' => 'drupal_type', // like Field API, default is string
 *       // datasource supports 1 level of multi valued fields (list) for the input record.
 *       // so type can be a 'list<drupal_type>', in this case getRecord() must provide an array of values.
 *       // You must provide at least 1 udid field to be used as functional key.
 *       // you can provide custom types, but you have to manage the preprocessor callbacks
 *     ),
 *     ...
 *   )
 *   - class: the name of the datasource engine class implementing DatasourceEngineInterface.
 * 
 * @see datasources_inputs_registry()
 * @see DatasourceEngineAbstract::importRecord()
 */
function hook_datasource_inputs() {
  $inputs['example_some_datasource_input'] = array(
    'name' => t('Some Datasource Input'),
    'class' => 'SomeDatasourceEngineClass',
    'fields' => array(
      'field1' => t('Name field 1'),
      'field2' => array(
         'name' => t('Name field 2'),
       	 'type' => 'drupal_type',
       ),
    ),
  );
  $inputs['example_other_datasource_input'] = array(
    /* stuff */
  );

  return $inputs;
}

/**
 * You can define preprocessor callbacks.
 * 
 * Preprocessors callbacks signature is :
 * 
 * function my_callback($original_field_value, $context) returns $processed_value;
 * 
 * $context is an array keyed with :
 *  - source_type
 *  - target_type
 *  - source_field
 *  - target_field
 *  - record
 *  - input
 *  - engine
 * 
 * @param array $callbacks
 */
function hook_datasource_preprocessor_callbacks() {
  return array(
    'processor1' => array(
      'name' => 'Processor 1', // [optional] you can provide a friendly name...
      'callback' => php_callback, // callback for call_user_func()
      'type' => 'return_type', // [optional] a return type
    ),
    'processor2' => php_callback, // You can just put the callback
  );
}