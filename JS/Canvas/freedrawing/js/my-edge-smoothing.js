var el = document.getElementById('c');
var ctx = el.getContext('2d');
var isDrawing;

ctx.lineWidth = 10;
// http://www.w3schools.com/tags/ref_canvas.asp
ctx.lineJoin = ctx.lineCap = 'round';
ctx.shadowBlur = 10;
ctx.shadowColor = 'rgb(0, 0, 128)';

var p1 = {};

el.onmousedown = function(e) {
	isDrawing = true;
	p1.x = e.clientX;
	p1.y = e.clientY;
};

//onmousemove is called when mouse moves in any direction
el.onmousemove = function(e) {
	if(isDrawing) {
		ctx.beginPath();
		ctx.moveTo(p1.x, p1.y);
		ctx.lineTo(e.clientX, e.clientY);
		ctx.stroke();
		p1.x = e.clientX;
		p1.y = e.clientY;
	}
};

el.onmouseup = function() {
	isDrawing = false;
}

el.onmouseout = function() {
	isDrawing = false;
}
