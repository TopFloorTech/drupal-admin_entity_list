<?php

function admin_entity_list_admin(){
  $form = array();
  $eck_types = array();
  foreach(entity_get_info() as $type_name => $type){
    if(isset($type['module']) && $type['module'] == 'eck'){
      $eck_types[$type_name] = $type_name;
    }
  }
  $node_info = node_entity_info();
  $node_bundles = array();
  foreach($node_info['node']['bundles'] as $bundle_slug => $bundle_label){
    $node_bundles[$bundle_slug] = $bundle_slug;
  }

  $form['admin_entity_list_enabled_entities'] = array(
    '#type' => 'checkboxes',
    '#options' => $eck_types,
    '#default_value' => variable_get('admin_entity_list_enabled_entities',array()),
    '#title' => t('Entity Types')
  );

  $form['admin_entity_list_enabled_node_bundles'] = array(
    '#type' => 'checkboxes',
    '#options' => $node_bundles,
    '#default_value' => variable_get('admin_entity_list_enabled_node_bundles',array()),
    '#title' => t('Node Bundles')
  );

  $form['#submit'][] = 'admin_entity_list_form_submit';

  return system_settings_form($form);


}

function admin_entity_list_form_submit($form,$form_state){
  // TODO: figure out a way to clear cache properly
  menu_rebuild();
}
