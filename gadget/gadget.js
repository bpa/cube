var index;
var rows;
var data;
var moves;
var current_row;

function toggleFlyout() {
	System.Gadget.Flyout.show = !System.Gadget.Flyout.show;
}

function on_flyout_show() {
	flyout = System.Gadget.Flyout.document;
	flyout.getElementById('solution').innerHTML = current_row[5].innerHTML;
}

function init() {
    window.detachEvent("onload", init);
	document.body.style.height = "130px";
	document.body.style.width  = "130px";

	System.Gadget.Flyout.onShow = on_flyout_show;
	System.Gadget.Flyout.file = "flyout.html";

	//document.getElementById('setup').onClick = toggleFlyout();
	data = document.getElementById('data').contentWindow.document;
	moves = data.getElementById('moves');
	rows = $('tbody > tr', moves).length;
	show(1);
}

function show(rowid) {
	index = rowid;
	var row = $('tbody > tr', moves)[rowid];
	current_row = $('td', row);
	document.getElementById('setup').innerHTML = current_row[4].innerHTML;
	$('#cube').attr('src', $('img', current_row[2]).attr('src'));
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

window.attachEvent("onload", init)
