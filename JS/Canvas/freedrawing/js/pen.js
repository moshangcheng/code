function getRandomInt(min, max) {
	return Math.floor(Math.random() * (max - min + 1)) + min;
}

var el = document.getElementById('c');
var ctx = el.getContext('2d');
ctx.lineJoin = ctx.lineCap = 'round';

var isDrawing, points = [];

var p1, p2;

el.onmousedown = function(e) {
	isDrawing = true;
	points.push({
		x: e.clientX,
		y: e.clientY,
		width: getRandomInt(3, 5)
	});
}

el.onmousemove = function(e) {
	if(!isDrawing) return;

	ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);

	points.push({
		x: e.clientX,
		y: e.clientY,
		width: getRandomInt(3, 5)
	});

	for(var i = 1; i < points.length; i++) {
		ctx.beginPath();
		ctx.moveTo(points[i-1].x, points[i-1].y);
		ctx.moveTo(points[i-1].x, points[i-1].y);
		ctx.lineWidth = points[i].width;
		ctx.lineTo(points[i].x, points[i].y);
		ctx.stroke();
	}
	ctx.beginPath();
	ctx.moveTo(p1.x, p1.y);
	ctx.lineWidth = p2.width;
	ctx.lineTo(p2.x, p2.y);
	ctx.stroke();
	p1 = p2;
}

el.onmouseup = function() {
	isDrawing = false;
	points.length = 0;
}

