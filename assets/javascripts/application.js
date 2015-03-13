/**
 * RKAG Open Source organization
 * GitHub Page project presentation
 *
 * \author Sven Marc Gehring
 * \date 2015-03-10
 */


/**
 * Global page init function
 */
window._pageInit = function() {
    $('pre code').each(function(i, block) {
        hljs.highlightBlock(block);
    });

    $('img').click(function(){
        window.open($(this).attr('src'));
    });
}


/**
 * Ember application for site
 */
var App = Ember.Application.create();


/** 
 * Application router
 *
 * We're only using top level routes, since this will be
 * hosten on GitHub pages and since we cannot load in
 * templates dynamically, nested routes would be a pain to load.
 */
App.Router.map(function() {

    this.route('resources');

    this.route('hardware-case');
    this.route('hardware-print');
    this.route('hardware-partlist');
    this.route('hardware-documentation');

    this.route('software-installation');
    this.route('software-examples');
    this.route('software-documentation');

});


/**
 * Initialize highlight.js in ember views
 *
 * This will run the global page init function after
 * rendering an ember page view.
 */
Ember.View.reopen({
    didInsertElement: function() {
        this._super();
        window._pageInit();
    }
});


/**
 * Warning message for unfinished pages
 *
 * This is wrapped in a handlebars helper so we can 
 * add it as easy as possible to the pages.
 */
Ember.Handlebars.helper('not-finished', function(value, options) {
  return new Ember.Handlebars.SafeString('<div class="alert alert-danger"> <strong>Hinweis:</strong> Diese Seite ist ein Entwurf. Dieser Teil der Dokumentation wird im Verlauf der weiteren Entwicklung dieses  Projektes erweiter. Er dient im Moment lediglich als Platzhalter um grundlegende Informationen zur Verfügung zu stellen und ist keineswegs vollständig!</div>');
});