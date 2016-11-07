<?php

/**
 * Override theme_user_list()
 * Returns HTML for a list of users.
 *
 * @param $variables
 *   An associative array containing:
 *   - users: An array with user objects. Should contain at least the name and
 *     uid.
 *   - title: (optional) Title to pass on to theme_item_list().
 *
 * @ingroup themeable
 */
function pond_theme_13_user_list($variables) {
  $users = $variables['users'];
  $title = $variables['title'];
  $items = array();

  if (!empty($users)) {
    foreach ($users as $user) {
    	$info = pond_get_by_uid($user->uid);
      $items[] = l($info['full_name'], 'dash/manage_user/'.$user->uid);
    }
  }
  return theme('item_list', array('items' => $items, 'title' => $title));
}