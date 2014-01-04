var el = document.getElementById('c');
var ctx = el.getContext('2d');

ctx.lineWidth = 3;
ctx.lineJoin = ctx.lineCap = 'round';

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

	ctx.globalAlpha = 1;

	for(var i = -4; i < 6; i += 2) {
		ctx.beginPath();
		ctx.globalAlpha = -0.1 * i + 0.5;
		ctx.moveTo(p1.x + i, p1.y + i);
		ctx.lineTo(p2.x + i, p2.y + i);
		ctx.stroke();
	}

	p1 = p2;
}

el.onmouseup = function() {
	isDrawing = false;
}

