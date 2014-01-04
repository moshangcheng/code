function distanceBetween(p1, p2) {
	return Math.sqrt(Math.pow(p2.x - p1.x, 2) + Math.pow(p2.y - p1.y, 2));
}

function angleBetween(p1, p2) {
	return Math.atan2(p2.x - p1.x, p2.y - p1.y);
}

var el = document.getElementById('c');
var ctx = el.getContext('2d');
ctx.lineJoin  = ctx.lineCap = 'round';

var isDrawing, lastPoint;

el.onmousedown = function(e) {
	isDrawing = true;
	lastPoint = {x: e.clientX, y: e.clientY };
};

el.onmousemove = function(e) {
	if(!isDrawing) return;

	var currentPoint = {x: e.clientX, y: e.clientY};
	var dist = distanceBetween(lastPoint, currentPoint);
	var angle = angleBetween(lastPoint, currentPoint);

	for(var i = 0; i < dist; i+=5) {
		x = lastPoint.x + (Math.sin(angle) * i);
		y = lastPoint.y + (Math.cos(angle) * i);
		var radgrad = ctx.createRadialGradient(x, y, 10, x, y, 20);
		radgrad.addColorStop(0, '#000');
		radgrad.addColorStop(0.5, 'rgba(0, 0, 0, 0.5)');
		radgrad.addColorStop(1, 'rgba(0, 0, 0, 0)');
		ctx.fillStyle = radgrad;
		ctx.fillRect(x-20, y-20, 40, 40);
	}

	lastPoint = currentPoint;
}

el.onmouseup = function() {
	isDrawing = false;
}

