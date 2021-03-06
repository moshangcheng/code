var el = document.getElementById('c');
var ctx = el.getContext('2d');
var isDrawing;

ctx.lineWidth = 10;
// http://www.w3schools.com/tags/ref_canvas.asp
ctx.lineJoin = ctx.lineCap = 'round';
ctx.shadowBlur = 10;
ctx.shadowColor = 'rgb(0, 0, 128)';

el.onmousedown = function(e) {
	isDrawing = true;
	ctx.moveTo(e.clientX, e.clientY);
	console.log("start", e.clientX, e.clientY);
};

//onmousemove is called when mouse moves in any direction
el.onmousemove = function(e) {
	if(isDrawing) {
		ctx.lineTo(e.clientX, e.clientY);
		console.log("drawing", e.clientX, e.clientY);
		//Shadow from current stroke overlaps shadow from previous stroke
		ctx.stroke();
	}
};

el.onmouseup = function() {
	isDrawing = false;
}

el.onmouseout = function() {
	isDrawing = false;
}
