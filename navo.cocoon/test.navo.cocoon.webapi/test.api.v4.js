var navo_cocoon_webservice_url = 'http://127.0.0.1:7901/';

var navo_cocoon_connection_token = '';

$(function () {
    var fpLogin = function () {
        return $.ajax({
            type: 'POST',
            url: navo_cocoon_webservice_url + 'api/v4/login',
            headers:
				{
				    'Content-Type': 'application/json'
				},
            data: JSON.stringify({
                // Application: '',
                // Database: '',
                // EBServer: '',
                user_name: 'Administrator',
                user_password: 'KT1234',
                user_category: 'user',
            }),

            crossDomain: true,

        });
    };
    var fpListOrders = function () {
        return $.ajax({
            type: 'POST',
            url: navo_cocoon_webservice_url + 'api/v4/query/orders?ncct=' + navo_cocoon_connection_token,
            headers:
				{
				    'Content-Type': 'application/json'
				},
            data: JSON.stringify({
                multi_part: false
            }),

            crossDomain: true,
        });
    };
    var fpGetOrder = function () {
        return $.ajax({
            type: 'GET',
            url: navo_cocoon_webservice_url + 'api/v4/document/get/SORS/72?ncct=' + navo_cocoon_connection_token,
            headers:
				{
				    'Content-Type': 'application/json'
				},

            crossDomain: true,
        });
    };

    $('#test_results').append('<div>starting tests</div>');

    fpLogin().done(function (result_) {
        navo_cocoon_connection_token = result_.data;
    })
        .then(fpListOrders, function (error_) { alert(JSON.stringify(error_)); }).then(
        function (results_) {
            $('#test_results').append('<div>' + JSON.stringify(results_) + '</div>');
        }, function (error_) { alert(JSON.stringify(error_)); }).then(function () {
            $('#test_results').append('<div>done tests</div>');
        });


})