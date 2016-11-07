(function ($) {

  Drupal.behaviors.pond_regos = {
    attach: function (context, settings) {

      var placeSearch;
      var autocomplete = {};

      var contexts = [
        'edit',
        'edit-user',
        'edit-new-church',
        'edit-new-referee-church'
      ];

      var lookupFieldID = 'address-lookup-field';

      var fieldNames = {};
      fieldNames['subpremise'] = 'field-address-street-number';
      fieldNames['street_number'] = 'field-address-street-number';//Concatenated below
      fieldNames['route'] = 'field-address-street-name';
      fieldNames['locality'] = 'field-address-suburb';
      fieldNames['administrative_area_level_1'] = 'field-address-state';
      fieldNames['postal_code'] = 'field-address-postcode';
      fieldNames['country'] = 'field-address-country';

      var groupClass = 'gaddress_group';

      $('.' + groupClass + ' input').attr('readonly', 'readonly');
      $('.' + groupClass).addClass('disabled');

      var changeAddress = function(place, thiscontext) {
        var contextClass = (thiscontext == 'edit') ? '.'+groupClass : '#'+thiscontext+' .'+groupClass;
        $(contextClass + ' input').removeAttr('readonly').val('');//Reset each input, ready to be filled.
        $(contextClass).removeClass('disabled');
        for (var j = 0; j < place.address_components.length; j++) {
          component_type = place.address_components[j].types[0];
          switch(component_type){
            case 'subpremise'://We are going to concatenate, but subpremise always comes first
              $('#'+thiscontext+'-'+fieldNames[component_type]+' input').val(place.address_components[j]['long_name'] + '/');
              break;
            case 'street_number':
              $('#'+thiscontext+'-'+fieldNames[component_type]+' input').val( function( index, value ) { 
                return value + place.address_components[j]['long_name']; 
              });
              break;
            case 'route':
            case 'locality':
            case 'administrative_area_level_1':
            case 'postal_code':
            case 'country':
              $('#'+thiscontext+'-'+fieldNames[component_type]+' input').val(place.address_components[j]['long_name']);
              break;
          }
        }
      };

      for (var i = 0; i < contexts.length; i++) {
        theid = contexts[i]+'-'+lookupFieldID;
        if(document.getElementById(theid)){
          autocomplete[i] = new google.maps.places.Autocomplete(document.getElementById(theid), { types: [ 'geocode' ] });
          autocomplete[i].context = contexts[i];
          google.maps.event.addListener(autocomplete[i], 'place_changed', function(){
            var place = this.getPlace();
            changeAddress(place, this.context);
          });
          /*
          $('#'+theid, context).focus(function () {
            //Set bounds to current location.
            if (navigator.geolocation) {
              navigator.geolocation.getCurrentPosition(function(position, i) {
                var geolocation = new google.maps.LatLng(position.coords.latitude,position.coords.longitude);
                console.log(i);//Why is this Undefined?
                console.log(autocomplete);
                console.log(autocomplete[i]);
                autocomplete[i].setBounds(new google.maps.LatLngBounds(geolocation, geolocation));
              });
            }
          });
          */
        }
      }
      
      

      
    }
  };

})(jQuery);