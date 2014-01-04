var el = document.getElementById('c');
var ctx = el.getContext('2d');

ctx.lineWidth = 10;
ctx.lineJoin = ctx.lineCap = 'butt';
ctx.strokeStyle = 'purple';

var isDrawing;

var p1, p2;

el.onmousedown = function(e) {
	isDrawing = true;
	p1 = {
		x: e.clientX,
		y: e.clientY
	};
}

el.onmousemove = function(e) {
	if(!isDrawing) return;

	p2 = {
		x: e.clientX,
		y: e.clientY
	};

	ctx.beginPath();
	ctx.moveTo(p1.x - 5, p1.y - 5);
	ctx.lineTo(p2.x - 5, p2.y - 5);
	ctx.stroke();

	ctx.beginPath();
	ctx.moveTo(p1.x, p1.y);
	ctx.lineTo(p2.x, p2.y);
	ctx.stroke();

	p1 = p2;
}

el.onmouseup = function() {
	isDrawing = false;
}

