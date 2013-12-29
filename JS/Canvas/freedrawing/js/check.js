try {
    // Try to grab the standard context. If it fails, fallback to experimental.
	var c1 = document.getElementById("threed");
    threed = c1.getContext("webgl") || canvas.getContext("experimental-webgl");
	console.log(threed);

	var c2 = document.getElementById("twod");
	twod = c2.getContext("2d");
	console.log(twod);
}
catch(e) {}
