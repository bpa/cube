var index;
var rows;

$(document).ready(function() {
  $('#data').load('cfop.html', function(){
        rows = $('#moves > tbody > tr').length;
        show(1)
    });
});

function show(rowid) {
    index = rowid;
    var row = $('#moves > tbody > tr')[rowid];
    var arr = $('td', row);
    $('#setup').text(arr[4].innerHTML);
    $('#cube').attr('src', $('img', arr[2]).attr('src'));
}

function showNext() {
    index++;
    if (index >= rows) index = 1;
    show(index);
}

function showPrev() {
    if (index <= 1) index = rows;
    index--;
    show(index);
}
