/*
Hot Keys
"S": split,		83
"D": destory,	68
"T": hit		84
*/

var c = {
	"box": {
		"width": 800,
		"height": 600
	},
	"status": {
		"counter": 0, //bubble ordinal
		"paused": false,
		"action": 0, //nothing
		"modified": true
	},
	"physics": {
		"dampingRatio": 0.005,
		"gravity": 0.25,
		"collision": {
			//collision with bubble
			"lost1": 0.01,
			//collision with border
			"lost2": 0.1
		},
		"padding": 3,
		"speed": {
			"max": 100,
			"min": 1
		}
	},
	"keys": {
	},
	"actions": {
		"nothing": 0,
		"destroy": 1,
		"split": 2,
		"tap": 3
	},
	"bubble": {

	},
	"end": true
};



var m = (function(){

	var gen = function(v) {
		this.x = v.x;
		this.y = v.y;
	};

	var t = {
		"vector": {
			"length": function(){
				return Math.sqrt(this.x * this.x + this.y * this.y);
			},

			"e": function() {
				return this.scale(1.0 / this.length());
			},

			"dotm": function(v) {
				return this.x * v.x + this.y * v.y;
			},

			"plus": function(v) {
				this.x += v.x;
				this.y += v.y;
				return this;
			},

			"minus": function(v) {
				if(v != undefined) {
					this.x -= v.x;
					this.y -= v.y;
				} else {
					this.scale(-1);
				}
				return this;
			},
			
			"copy": function() {
				return new gen(this);
			},

			"scale": function(s) {
				this.x *= s;
				this.y *= s;
				return this;
			},

			"data": function() {
				return {
					"x": this.x,
					"y": this.y
				}
			}
		}
	};

	gen.prototype = t.vector;

	return function(v) {
		return new gen(v);
	};
})();

var nodes = [
	{"id": 0,	"r": 100,	"p": {"x": c.box.width/2,	"y": c.box.height * 1.0 / 4},	"v": {"x": 0,	"y": 0},	"a": {"x": 0,	"y": 0}}
];

$("body").on("keydown", function(e){
		console.log("key " + e.keyCode + " pressed");
		c.keys[e.keyCode] = true;
		switch(e.keyCode) {
		case 68:
			c.status.paused = true;
			c.status.action = c.actions.destroy;
			break;
		case 83:
			c.status.paused = true;
			c.status.action = c.actions.split;
			break;
		case 84:
			c.status.paused = false;
			c.status.action = c.actions.tap;
			tapFloor();
			break;
		}
	});

$("body").on("keyup", function(e){
	console.log("key " + e.keyCode + " popped up");
	c.keys[e.keyCode] = false;
});

$("body").on("click", function(e){
	console.log("body clicked, continue move");
	c.status.paused = false;
});

var svg = d3.select("#game-box").append("svg")
	.attr("width", c.box.width).attr("height", c.box.height);

var color = d3.scale.category20c();

d3.timer(function() {
	if(c.status.modified) {
		//get d3 selections
		var sBubbles = svg.selectAll("g").data(nodes, function(d) { return d.id;} );
	
		//add new bubbles
		sBubbles.enter().append("g").attr("class", "bubble")
			.attr("transform",  function(d, i) {
				return "translate(" + d.p.x + ", " + d.p.y + ")";
			}).append("circle").attr("r", function(d, i){
				return d.r;
			})
			.attr("fill", function(d, i){
				return color(i);
			});
		
		//remove bubbles
		sBubbles.exit().remove();
		c.status.modified = false;

		//set event listener for all bubbles
		svg.selectAll(".bubble").on("click", function(d, i) {
			console.log("bubble clicked, current action is " + c.status.action);
			//first, consider "Split"
			if(c.status.action == c.actions.split) {
				c.status.action = 0;
				//animation
				d3.select(this).select("circle")
					.transition()
					.attr("r", 0);
					
				d3.select(this).transition()//create a transition
				.duration(250)
				.style("fill-opacity", 0)
				.each("end", function() {
					//remove clicked bubble
					var removedBubble = nodes.splice(i, 1);
					addChildBubbles(removedBubble[0]);
					c.status.modified = true;
				});
			}
			//then, consider "D"
			else if(c.status.action == c.actions.destroy) {
				c.status.action = 0;
				d3.select(this).select("circle")
					.transition()
					.attr("r", 0);
					
				d3.select(this).transition()//create a transition
				.duration(250)
				.style("fill-opacity", 0)
				.remove()
				.each("end", function() {
					//remove clicked bubble
					var removedBubble = nodes.splice(i, 1);
					c.status.modified = true;
				});
			}
		});
	}

	//"Pause" is pressed
	if(c.status.paused == true) {
		return;
	}

	//update position
	svg.selectAll(".bubble").attr("transform", function(d, i) {
		d.p.y += d.v.y;
		d.p.x += d.v.x;
		return "translate(" + d.p.x + ", " + d.p.y + ")";
	});

	for(var i = 0; i < nodes.length; i++) {
		var v = nodes[i].v;
		var a = nodes[i].a;

		//update speed
		v.y += a.y;
		v.x += a.x;

		//update accelerated speed
		a.x = -v.x * c.physics.dampingRatio;
		a.y = -v.y * c.physics.dampingRatio;
		a.y += c.physics.gravity;

		//console.log("p: (" + nodes[i].p.x + ", " + nodes[i].p.y + ")");
		//console.log("v: (" + v.x + ", " + v.y + ")");
		//console.log("a: (" + a.x + ", " + a.y + ")");
		//console.log("##############################")
	}

	//collision detection
	for(var i = 0; i < nodes.length; i++) {
		var node = nodes[i];
		for(var j = i+1; j < nodes.length; j++) {
			collision(i, j);
		}
		//check collision with border
		if(node.p.x < node.r) {
			node.v.x = (1 - c.physics.collision.lost2) * Math.abs(node.v.x);
		} else if(node.p.x + node.r > c.box.width) {
			node.v.x = -1 * (1 - c.physics.collision.lost2) * Math.abs(node.v.x);
		}
		if(node.p.y < node.r) {
			node.v.y = (1 - c.physics.collision.lost2) * Math.abs(node.v.y);
		} else if(node.p.y + node.r + c.physics.padding > c.box.height) {
			//reverse move direction
			node.v.y = -1 * (1 - c.physics.collision.lost2) * Math.abs(node.v.y);
			//set postion, necessary
			node.p.y = c.box.height - node.r;
			//set accelerated speed
			node.a.y = 0; // -= c.physics.gravity;

			//console.log("v: (" + v.x + ", " + v.y + ")");
			//console.log("a: (" + a.x + ", " + a.y + ")");
			//console.log("##############################")
		}
	}
});


function addChildBubbles(bubble) {

	var tlChild = $.extend(true, {}, bubble);
	tlChild.id = ++c.status.counter;
	tlChild.r = tlChild.r / 2;
	tlChild.p.x -= tlChild.r;
	tlChild.p.y -= tlChild.r;
	tlChild.v.x += c.physics.speed.max * (Math.random() - 0.5);
	tlChild.v.y += c.physics.speed.max * (Math.random() - 0.5);


	var trChild = $.extend(true, {}, bubble);
	trChild.id = ++c.status.counter;
	trChild.r = trChild.r / 2;
	trChild.p.x += trChild.r;
	trChild.p.y -= trChild.r;
	trChild.v.x += c.physics.speed.max * (Math.random() - 0.5);
	trChild.v.y += c.physics.speed.max * (Math.random() - 0.5);

	var blChild = $.extend(true, {}, bubble);
	blChild.id = ++c.status.counter;
	blChild.r = blChild.r / 2;
	blChild.p.x -= blChild.r;
	blChild.p.y += blChild.r;
	blChild.v.x += c.physics.speed.max * (Math.random() - 0.5);
	blChild.v.y += c.physics.speed.max * (Math.random() - 0.5);

	var brChild = $.extend(true, {}, bubble);
	brChild.id = ++c.status.counter;
	brChild.r = brChild.r / 2;
	brChild.p.x += brChild.r;
	brChild.p.y += brChild.r;
	brChild.v.x += c.physics.speed.max * (Math.random() - 0.5);
	brChild.v.y += c.physics.speed.max * (Math.random() - 0.5);

	nodes.push(tlChild);
	nodes.push(trChild);
	nodes.push(blChild);
	nodes.push(brChild);
}

function tapFloor() {
	for(var i = 0; i < nodes.length; i++) {
		var node = nodes[i];
		//detect bubble on the floor
		if(node.p.y + node.r + c.physics.padding > c.box.height) {
			node.v.y = c.physics.speed.max * (Math.random() + 1) / 2;
			node.v.x += c.physics.speed.max * Math.random() / 4;
		}
	}
}

function collision(i, j) {
	var n1 = nodes[i];
	var n2 = nodes[j];
	var d = m(n1.p).minus(n2.p);
	var dist = d.length();
	if (dist < n1.r + n2.r) {
		var dv = m(n1.v).minus(n2.v);
		if(d.dotm(dv) < 0) {
			//simply swap speed
			var ed = d.e();
			var ev1 = ed.copy().scale(ed.dotm(n1.v));
			var ev2 = ed.copy().scale(ed.dotm(n2.v));

			//console.log("before swap speed:");
			//console.log("the d " +  d.length() + "is: " + d.x + ", " + d.y + ")");
			//console.log("the dv is: " + dv.x + ", " + dv.y + ")");
			//console.log("before swap speed: (" + n1.v.x + ", " + n1.v.y + " ) (" + n2.v.x + ", " + n2.v.y + ")");
			//console.log("the dv * d is: " + d.dotm(m(n1.v).minus(n2.v)));

			n1.v = ev2.copy().scale(1 - c.physics.collision.lost1)//collision energy lost
				.plus(n1.v).minus(ev1).data();
			n2.v = ev1.copy().scale(1 - c.physics.collision.lost1)//collision energy lost
				.plus(n2.v).minus(ev2).data();
			
			dv = m(n1.v).minus(n2.v);
			//console.log("after swap speed:");
			//console.log("the d " +  d.length() + "is: " + d.x + ", " + d.y + ")");
			//console.log("the dv is: " + dv.x + ", " + dv.y + ")");
			//console.log("after swap speed: (" + n1.v.x + ", " + n1.v.y + " ) (" + n2.v.x + ", " + n2.v.y + ")");
			//console.log("the dv * d is: " + d.dotm(m(n1.v).minus(n2.v)));
			//console.log("###############################################################");
		}
	}
}
