(function ($) {
  if ($(window).width() > Drupal.settings.backstretchMinWidth) {
    $.backstretch(Drupal.settings.backstretchURL);
    
    $(document).ready(function () { 
      //var height = $(window).height() - 153;
      var height = $(window).height() + parseInt(Drupal.settings.backstretchMarginAdj);
      if($('#toolbar').length > 0) { var height = height - $('#toolbar').height(); }
      $(Drupal.settings.backstretchSelector).css('margin-bottom', height);
    });
  }
})(jQuery);
