function getRandomInt(min, max) {
	return Math.floor(Math.random() * (max - min + 1)) + min;
}

var el = document.getElementById('c');
var ctx = el.getContext('2d');
ctx.lineJoin = ctx.lineCap = 'round';
ctx.fillStyle = 'red';

var isDrawing, points = [], radius = 15;

el.onmousedown = function(e) {
	isDrawing = true;
	points.push({
		x: e.clientX,
		y: e.clientY
	});
}

el.onmousemove = function(e) {
	if(!isDrawing) return;

	ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);

	points.push({
		x: e.clientX,
		y: e.clientY
	});

	for(var i = 1; i < points.length; i++) {
		ctx.beginPath();
		ctx.arc(points[i].x, points[i].y, radius, false, Math.PI * 2, false);
		ctx.fill();
		ctx.stroke();
	}
}

el.onmouseup = function() {
	isDrawing = false;
	points.length = 0;
}

