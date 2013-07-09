<?php

/**
 * @file admin_entity_list.views_default.inc
 * TODO: Enter file description here.
 */



/**
 * Implements hook_views_default_views().
 */

function admin_entity_list_views_default_views() {

  $eck_types = _admin_entity_list_get_enabled_entity_types();
  $bundles = _admin_entity_list_get_enabled_node_bundles();

  /* if(empty($eck_types)){ */
  /*   return; */
  /* } */


  $views = array();
  foreach($eck_types as $eck_type => $_){
    $view = _admin_entity_list_create_entity_view($eck_type);
    $views[$view->name] = $view;
  }

  foreach($bundles as $bundle => $_){
    $view = _admin_entity_list_create_node_bundle_view($bundle);
    $views[$view->name] = $view;
  }

  // At the end, return array of default views.
  return $views;
}

function _admin_entity_list_create_entity_view($eck_type){
  $human_name = _admin_entity_list_humanize($eck_type);
  $plural_human_name = $human_name."s";
  require(drupal_get_path('module','admin_entity_list').'/admin_entity_list.entity.view');
  return $view;
}

function _admin_entity_list_create_node_bundle_view($bundle){
  // get the raw view export
  $human_name = _admin_entity_list_humanize($bundle);
  $plural_human_name = $human_name."s";
  require(drupal_get_path('module','admin_entity_list').'/admin_entity_list.node_bundle.view');
  // make any bundle specific mods to the view
  $view->name = 'admin_list_entity_'.$bundle;
  $view->human_name = 'Manage Node Bundle: '.$human_name ;
  $handler->display->display_options['title'] = 'Manage Node Bundle: '.$human_name;
  $handler->display->display_options['path'] = 'admin/content/manage-'.$bundle;
  $handler->display->display_options['menu']['title'] = 'Manage '.$plural_human_name;

  return $view;
}