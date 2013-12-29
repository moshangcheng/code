var canvas = document.getElementById("c");
if (canvas.getContext('2d')) {
	// Create the initial canvas and start the gradient.
	ctx = canvas.getContext('2d');
	ctx.clearRect(0, 0, 600, 600);
	gradient = ctx.createRadialGradient(300, 300, 150, 300, 150, 200);
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
}

function getColors(gradient)  // Get the colors. Because they are used twice, get them when they are needed.
{
	gradient.addColorStop("0", "magenta");
	gradient.addColorStop(".25", "blue");
	gradient.addColorStop(".50", "green");
	gradient.addColorStop(".75", "yellow");
	gradient.addColorStop("1.0", "red");
	return (gradient);
}
