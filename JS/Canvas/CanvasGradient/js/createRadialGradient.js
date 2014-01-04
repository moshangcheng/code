/*
http://www.whatwg.org/specs/web-apps/current-work/multipage/the-canvas-element.html#dom-context-2d-createradialgradient
*/

var circles = [
	{"x": 100, "y": 200, "r": 100}
	, {"x": 300, "y": 300, "r": 50}
];

var c1 = circles[0];
var c2 = circles[1];

var canvas = document.getElementById("c");
if (canvas.getContext('2d')) {
	// Create the initial canvas and start the gradient.
	ctx = canvas.getContext('2d');
	ctx.clearRect(0, 0, 600, 600);
	gradient = ctx.createRadialGradient(c1.x, c1.y, c1.r, c2.x, c2.y, c2.r);
	ctx.fillStyle = getColors(gradient);
	ctx.fillRect(0, 0, 600, 600);
	/*canvas.onmousemove = function (event) {
		var width = window.innerWidth,
		height = window.innerHeight,
		x = event.clientX,
		y = event.clientY,
		rx = 600 * x / width,
		ry = 600 * y / height;

		gradient = ctx.createRadialGradient(rx, ry, 0, rx, ry, 300);
		ctx.fillStyle = getColors(gradient);            // Use the gradient for the fill style.
		ctx.fillStyle = gradient;
		ctx.fillRect(0, 0, 600, 600);
	};*/
	drawLine(ctx, c1.x, c1.y, c1.r);
	drawLine(ctx, c2.x, c2.y, c2.r);
}

function getColors(gradient)  // Get the colors. Because they are used twice, get them when they are needed.
{
	gradient.addColorStop("0", "black");
	//gradient.addColorStop(".25", "blue");
	//gradient.addColorStop(".50", "green");
	//gradient.addColorStop(".75", "yellow");
	gradient.addColorStop("1.0", "red");
	return (gradient);
}


function drawLine(ctx, x, y, r)
{
	ctx.beginPath();
	ctx.arc(x, y, r, 0, 2 * Math.PI, false);
	//ctx.fillStyle = 'green';
	//ctx.fill();
	ctx.lineWidth = 3;
	ctx.strokeStyle = '#003300';
	ctx.stroke();
}
