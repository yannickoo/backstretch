(function ($) {
  if ($(window).width() > Drupal.settings.backstretchMinWidth) {
    $.backstretch(Drupal.settings.backstretchURL);
    
    $(document).ready(function () { 
      if (Drupal.settings.backstretchScroller) {
        var height = $(window).height() + parseInt(Drupal.settings.backstretchScrollerAdj);
        if ($('#toolbar').length > 0) { var height = height - $('#toolbar').height(); }
        if (Drupal.settings.backstretchScrollerAdj != 0) {
          $('body').append('<div id="backstretchmargin"></div>');
        }
        $('#backstretchmargin').css('margin-bottom', height);
      }
    });
  }
})(jQuery);
