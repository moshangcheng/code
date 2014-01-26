define(function(require, exports, module) {
	console.log("require module: mod1");

	return {
		hello: function() {
			console.log("hello mod1");
		}
	};
});

