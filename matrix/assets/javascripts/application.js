/**
 * RKAG Open Source organization
 * GitHub Page project presentation
 *
 * \author Sven Marc Gehring
 * \date 2015-03-10
 */


/**
 * Global page init function
 *
 * Scroll to the top of the page on transition
 * Initialize highlight.js for every code bloack
 * Add click listener to images for new-tab view
 */
window._pageInit = function() {
    $('html, body').animate({ scrollTop: 0 }, 0);

    $('pre code').each(function(i, block) {
        hljs.highlightBlock(block);
    });

    $('#content img').click(function(){
        window.open($(this).attr('src'));
    });

    $('#cryear').text("" + (new Date()).getFullYear());
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
    this.route('software-introduction');
    this.route('software-examples');
    this.route('software-documentation');

    this.route('weiteres-expansion');
	
    this.route('assembly-placement');
    this.route('assembly-housing')
    this.route('assembly-bootloaderfuses');
    this.route('assembly-ftdi');
    this.route('assembly-test');
});


/**
 * Controller for examples page
 *
 * This will be used to display the selected 
 * example after clicking an entry.
 */
App.SoftwareExamplesController = Ember.Controller.extend({
    actions: {
        se: function(example){
            var self = this;
            Ember.$.get('examples/'+example+'.c', function(payload){
                Ember.$('#exc').text(payload);
                hljs.highlightBlock(document.getElementById('exc'));
            });
        }
    }    
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