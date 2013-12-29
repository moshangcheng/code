var c = {
	"widht": 960,
	"height": 500,
	"interval": 4,
	"splitNum": 4,
	"id": 1,
	"end": true
};

var nodes = [{"id": 0,	"x": 200,	"y": 200,	"r": 30,	"vx": 0,	"vy": 0}];

var svg = d3.select("body").append("svg")
	.attr("width", c.width).attr("height", c.height);

d3.timer(function() {
	var sBubbles = svg.selectAll("g").data(nodes, function(d) {	return d.id; });
	
	//add bubble
	sBubbles.enter().append("g").attr("class", "bubble").append("circle");
	
	//remove bubble
	sBubbles.exit().remove();
	
	//select all bubbles
	var bubbles = d3.selectAll(".bubble circle");

	bubbles.attr("r", function(d, i){
			return d.r;
		})
		.attr("fill", "red")
		.attr("transform", function(d, i) {
			return "translate(" + d.x + ", " + d.y + ")";
		});

	bubbles.on("click", function(d, i) {
		console.log("bubble " + i + " clicked");
		d3.select(this).select("circle")
			.transition()
			.attr("r", 0);
			
		d3.select(this).transition()//create a transition
		.duration(250)
		.style("fill-opacity", 0)
		.each("end", function() {
			var removedBubble = nodes.splice(i, 1);
			addChildBubbles(removedBubble[0]);
		});
	});
});


function addChildBubbles(bubble) {

	var tlChild = {}, trChild = {}, blChild = {}, brChild = {};

	$.extend(tlChild, bubble);
	tlChild.id = c.id++;
	tlChild.r = bubble.r / 2;
	tlChild.x -= tlChild.r;
	tlChild.y -= tlChild.r;


	$.extend(trChild, tlChild);
	trChild.id = c.id++;
	trChild.x += 2 * trChild.r;

	$.extend(blChild, tlChild);
	blChild.id = c.id++;
	blChild.y += 2 * blChild.r;

	$.extend(brChild, blChild);
	brChild.id = c.id++;
	brChild.x += 2 * brChild.r;

	nodes.push(tlChild);
	nodes.push(trChild);
	nodes.push(blChild);
	nodes.push(brChild);
}
