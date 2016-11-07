
(function($){
$(document).ready(function(){
  $('.payments').hide();
  $('.payments_trigger').click(function() { 
    $(this).closest('.control_links').siblings('.payments').slideToggle(); 
    return false; 
  });
});
})(jQuery);