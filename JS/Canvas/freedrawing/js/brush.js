var img = new Image(30, 30);
img.src = 'http://www.tricedesigns.com/wp-content/uploads/2012/01/brush2.png';

function distanceBetween(p1, p2) {
	return Math.sqrt(Math.pow(p2.x - p1.x, 2) + Math.pow(p2.y - p1.y, 2));
}

function angleBetween(p1, p2) {
	return Math.atan2(p2.x - p1.x, p2.y - p1.y);
}

var el = document.getElementById('c');
var ctx = el.getContext('2d');
ctx.lineJoin = ctx.lineCap = 'round';

var isDrawing, lastPoint;

el.onmousedown = function(e) {
	isDrawing = true;
	lastPoint = { x: e.clientX, y: e.clientY };
}

el.onmousemove = function(e) {
	if(!isDrawing) return;

	var currentPoint = { x: e.clientX, y: e.clientY };
	var dist = distanceBetween(lastPoint, currentPoint);
	var angle = angleBetween(lastPoint, currentPoint);

	for(var i = 0; i < dist; i++) {
		x = lastPoint.x + (Math.sin(angle) * i) - 25;
		y = lastPoint.y + (Math.cos(angle) * i) - 25;
		ctx.drawImage(img, x, y);
	}

	lastPoint = currentPoint;
}

el.onmouseup = function() {
	isDrawing = false;
}

		
