function getRandomInt(min, max) {
	return function() {
		return Math.floor(Math.random() * (max - min + 1)) + min;
	};
}

var el = document.getElementById('c');
var ctx = el.getContext('2d');
ctx.lineJoin = ctx.lineCap = 'round';
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

	var randGen = getRandomInt(0, 2);
	ctx.beginPath();
	ctx.moveTo(p1.x - randGen(), p1.y - randGen());
	ctx.lineTo(p2.x - randGen(), p2.y - randGen());
	ctx.stroke();

	ctx.beginPath();
	ctx.moveTo(p1.x, p1.y);
	ctx.lineTo(p2.x, p2.y);
	ctx.stroke();

	ctx.beginPath();
	ctx.moveTo(p1.x + randGen(), p1.y + randGen());
	ctx.lineTo(p2.x + randGen(), p2.y + randGen());
	ctx.stroke();

	p1 = p2;
}

el.onmouseup = function() {
	isDrawing = false;
}

