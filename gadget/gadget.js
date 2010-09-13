var index;
var rows;
var iframe;
var moves;

function show(rowid) {
    index = rowid;
    var row = $('tbody > tr', moves)[rowid];
    var arr = $('td', row);
    document.getElementById('setup').innerHTML = arr[4].innerHTML;
    $('#cube').attr('src', $('img', arr[2]).attr('src'));
}

function setup() {
  document.body.style.height = "130px";
  document.body.style.width  = "200px";
  iframe = document.getElementById('data').contentWindow.document;
  moves = iframe.getElementById('moves');
  rows = $('tbody > tr', moves).length;
  show(1);
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
