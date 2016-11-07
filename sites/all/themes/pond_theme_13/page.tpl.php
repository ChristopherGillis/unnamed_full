
<div id="branding" class="clearfix">
  <div class="squeeze">
    <?php echo l('Home', 'home', array('attributes' => array('id' => 'logo-rf'))); ?>
<?php 
    $header = render($page['header']);
    print ($header)?$header:'<div class="region-header"></div>';
?>
    <div id="logo-pond"></div>
    
<?php 
  if (isset($main_menu)) {
    print theme('links__system_main_menu', array(
      'links' => $main_menu,
      'attributes' => array(
        'id' => 'top-nav',
        'class' => array('links', 'inline', 'main-menu'),
      )
    ));
  }
?>
    </div>
  </div>

  <div id="page">
    <div class="squeeze">

      <div id="content" class="clearfix">
        <div class="element-invisible"><a id="main-content"></a></div>

        <div class="clearfix">
          <?php print render($title_prefix); ?>
          <?php if ($title): ?>
            <h1 class="page-title"><?php print $title; ?></h1>
          <?php endif; ?>
          <?php print render($title_suffix); ?>
        </div>

        <?php print render($primary_local_tasks); ?>
        
        <?php if ($secondary_local_tasks): ?>
          <div class="tabs-secondary clearfix"><ul class="tabs secondary"><?php print render($secondary_local_tasks); ?></ul></div>
        <?php endif; ?>

        <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>

        <?php if ($messages): ?>
          <div id="console" class="clearfix"><?php print $messages; ?></div>
        <?php endif; ?>
        <?php if ($page['help']): ?>
          <div id="help">
            <?php print render($page['help']); ?>
          </div>
        <?php endif; ?>

        <?php print render($page['content']); ?>
      </div>

      <div id="footer">
        <?php print $feed_icons; ?>
      </div>
    </div>
  </div>
