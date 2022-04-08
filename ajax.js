$('#submit_btn').click(function(e) {
    e.preventDefault();
    alert("gfh"+$('#start_date').val()+$('#end_date').val());
    $('#res').post(
        'act.php',
        {
            trip-start: $('#start_date').val(),
            trip-end: $('#end_date').val(),
			vals1: $('#vals1').val(),
			vals2: $('#vals2').val(),
			vals3: $('#vals3').val(),
        },
        function() {
            alert("completed");
            $(this).fadeIn("slow"); // Or $('#cont').fadeIn("slow");
        }
    );
});