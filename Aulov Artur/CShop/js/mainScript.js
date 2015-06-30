// JavaScript source code
var angle = 0;

$(function () {
    $(".content").css("height", $(".mainContent").height() - $(".footer").height());
    
    //if ($(".pic").height() < $(".pic").width()) {
    //    $(".pic").css("height", "100%");
    //}
    //else {
    //    $(".pic").css("widht", "100%");
    //}

    $(".delete").click(function () {
        $(this).parent().detach();
    });

    $("#add").click(function () {
        angle += 360;
        $("#add > img").css("-webkit-transform", "rotate(" + angle +"deg)");
        $("#add > img").css("-moz-transform", "rotate(" + angle + "deg)");
        $("#add > img").css("-o-transform", "rotate(" + angle + "deg)");
        $("#add > img").css("-ms-transform", "rotate(" + angle + "deg)");
        $("#add > img").css("transform", "rotate(" + angle + "deg)");
        $("#form").slideToggle();
    });
});

