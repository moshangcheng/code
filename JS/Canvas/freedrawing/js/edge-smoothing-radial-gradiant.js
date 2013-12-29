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
		var radgrad = ctx.createRadialGradient(e.clientX, e.clientY, 10, e.clientX, e.clientY, 20);
		radgrad.addColorStop(0, '#000');
		radgrad.addColorStop(0.5, 'rgba(0, 0, 0, 0.5)');
		radgrad.addColorStop(1, 'rgba(0, 0, 0, 0)');
		ctx.fillStyle = radgrad;

		ctx.fillRect(e.clientX-20, e.clientY-20, 40, 40);
		console.log("drawing", e.clientX, e.clientY);
	}
};

el.onmouseup = function() {
	isDrawing = false;
}

el.onmouseout = function() {
	isDrawing = false;
}
