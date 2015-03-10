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
        window.location.open($(this).attr('src'));
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
 * This is a bit of a hacky approach as of now.
 */
App.SoftwareDocumentationView = Ember.View.extend({ didInsertElement: window._pageInit });
App.SoftwareExamplesView = Ember.View.extend({ didInsertElement: window._pageInit });
