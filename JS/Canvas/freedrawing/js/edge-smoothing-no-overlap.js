var el = document.getElementById('c');
var ctx = el.getContext('2d');
var isDrawing;
var points = [];
var paths = [];

ctx.lineWidth = 10;
// http://www.w3schools.com/tags/ref_canvas.asp
ctx.lineJoin = ctx.lineCap = 'round';
ctx.shadowBlur = 10;
ctx.shadowColor = 'rgb(0, 0, 128)';

el.onmousedown = function(e) {
	isDrawing = true;
	points.push({x: e.clientX, y: e.clientY});
};

//onmousemove is called when mouse moves in any direction
el.onmousemove = function(e) {
	if(!isDrawing) return;
	console.log("drawing", e.clientX, e.clientY);
	//This is necessary! We need to redraw all paths every time
	//Otherwise user cannot see these lines when they draw
	ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);
	points.push({x: e.clientX, y: e.clientY});

	ctx.beginPath();
	for(var i = 0; i < paths.length; i++) {
		drawPath(paths[i]);
	}
	drawPath(points);
	ctx.stroke();
};

el.onmouseup = function() {
	isDrawing = false;
	//A new path finished
	paths.push(points);
	points = [];
}

el.onmouseout = function() {
	//isDrawing = false;
	//points.length = 0;
}

function drawPath(path) {
	ctx.moveTo(path[0].x, path[0].y);
	for(var i = 1; i < path.length; i++) {
		ctx.lineTo(path[i].x, path[i].y);
	}
}
