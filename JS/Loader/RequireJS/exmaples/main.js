define(function(require, exports, module) {
	console.log("require module: main");

	//asychronus load and initialize
	require(["./mod1"], function(mod1) {
		mod1.hello();
	});

	//preload and initialize
	var mod2 = require("./mod2");
	mod2.hello();

	return {
		hello: function() {
			console.log("hello main");
		}
	};
});

