var el = document.getElementById('c');
var ctx = el.getContext('2d');
var isDrawing;

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
		ctx.stroke();
	}
};

el.onmouseup = function() {
	isDrawing = false;
}

