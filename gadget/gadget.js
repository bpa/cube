var index;
var rows;

  alert('hi');
  document.body.style.width  = "200px";
  document.body.style.height = "130px";
$(document).ready(function() {
  //document.getElementById('debug').innerHTML = 'Setup';
  $('#debug').innerHTML = 'Setup';
  $('#data').load('cfop.html', function(){
        rows = $('#moves > tbody > tr').length;
	document.write(rows);
        show(1)
    });
});

function show(rowid) {
    index = rowid;
    $('#debug').innerHTML = 'Showing ' + rowid;
    var row = $('#moves > tbody > tr')[rowid];
    var arr = $('td', row);
    $('#setup').innerHTML = arr[4].innerHTML;
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
