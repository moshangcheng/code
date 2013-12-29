d3.select("body").selectAll("div")
    .data([4, 8, 15, 16, 23, 42])
  .enter().append("div")
    .text(function(d) { return d; });

d3.selectAll("div").on("click", function(d, i) { 
	console.log(i);
});

//set key function
var div = d3.select("body").selectAll("div")
    .data([1, 2, 4, 8, 16, 32], function(d) { return d; });

div.enter().append("div")
    .text(function(d) { return d; });

div.exit().remove();

d3.selectAll("div").on("click", function(d, i) { 
	console.log(i);
});

/*
d3.selectAll("div").on("click", function(d, i) {
	d3.select(this).transition().remove()
	.each("end", function(){
		d3.selectAll("div").attr("index", function(d, i) { 
			console.log(i);
		});
	});
});*/
