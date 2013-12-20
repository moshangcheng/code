var graph = new Springy.Graph();

var r = 20;

graphJSON = {
  "nodes": ["1", "2", "3", "4", "5", "6"],
  "edges": [
    ["1", "4"],
    ["1", "5"],
    ["1", "6"],
    ["2", "4"],
    ["2", "5"],
    ["2", "6"],
    ["3", "4"],
    ["3", "5"],
    ["3", "6"]
  ]
};

var nodes = {};

graph.loadJSON(graphJSON);

var layout = new Springy.Layout.ForceDirected(graph, 400.0, 400.0, 0.5);

var renderer = new Springy.Renderer(layout,
  function clear() {
    // code to clear screen
    //console.log("clear");
  },
  function drawEdge(edge, p1, p2) {
    // draw an edge
    //console.log("draw edge " + "(" + edge.source.id + ", " + edge.target.id + ") at (" + p1.x + ", " + p1.y + ") (" + p2.x + ", " + p2.y + ")");
  },
  function drawNode(node, p) {
    // draw a node
    //console.log("draw node " + node.id + " at " + p.x + ", " + p.y);
    nodes[node.id] = {
      "id": node.id,
      "x": p.x,
      "y": p.y
    };
  }
);

renderer.start(function() {
  var nodesArray = [];
  for(var i in nodes) {
    nodesArray.push({"id": i, "x": 80 * nodes[i].x + 400, "y": 80 * nodes[i].y + 400});
  }
  var svg = d3.select("body").append("svg").attr("width", "800px").attr("height", "800px");
  svg.selectAll("circle")
    .data(nodesArray).enter().append("circle")
    .attr("cx", function(d, i) {
        return d.x;
    })
    .attr("cy", function(d, i) {
        return d.y;
    })
    .attr("r", r)
    .style({
        "fill": "none",
        "stroke": "#808080",
        "stroke-width": 1.25
    });

  svg.selectAll("text").data(nodesArray).enter().append("text")
    .attr("x", function(d) { return d.x; })
    .attr("y", function(d) { return d.y; })
    .text(function(d) { 
        return d.id; }
    )
    .attr("font-family", "sans-serif")
    .attr("font-size", "15px")
    .attr("fill", "black")
    .attr("dy", "0.35em");
  for(var e in graphJSON.edges) {
    var startNode = nodes[graphJSON.edges[e][0]];
    startX = startNode.x * 80 + 400;
    startY = startNode.y * 80 + 400;
    var endNode = nodes[graphJSON.edges[e][1]];
    endX = endNode.x * 80 + 400;
    endY = endNode.y * 80 + 400;
    var startBBox = [
        {"x": startX + r, "y": startY},
        {"x": startX, "y": startY + r},
        {"x": startX - r, "y": startY},
        {"x": startX, "y": startY - r}
     ];

     var endBBox = [
        {"x": endX + r, "y": endY},
        {"x": endX, "y": endY + r},
        {"x": endX - r, "y": endY},
        {"x": endX, "y": endY - r}
      ];

    //find the shortest edge
    var minDist = 1000000, startMin, endMin;
    for(var i = 0; i < 4; i++)
    for(var j = 0; j < 4; j++) {
        var dist = Math.sqrt(Math.pow(startBBox[i].x - endBBox[j].x, 2.0) + Math.pow(startBBox[i].y - endBBox[j].y, 2.0));
        if(dist < minDist) {
            minDist = dist;
            startMin = i;
            endMin = j;
        }
    }

    //calculate the control points of spline curve
    var edgePath = [];
    var x1 = Math.floor(startBBox[startMin].x+0.5), y1 = Math.floor(startBBox[startMin].y+0.5);
    var x4 = Math.floor(endBBox[endMin].x+0.5), y4 = Math.floor(endBBox[endMin].y+0.5);
    dx = Math.max(Math.abs(x1 - x4) / 2, 10);
    dy = Math.max(Math.abs(y1 - y4) / 2, 10);
    var x2 = Math.floor([x1 + dx, x1, x1-dx, x1][startMin]+0.5), y2 = Math.floor([y1, y1+dy, y1, y1-dy][startMin]+0.5);
    var x3 = Math.floor([x4 + dx, x4, x4-dx, x4][endMin]+0.5), y3 = Math.floor([y4, y4+dy, y4, y4-dy][endMin]+0.5);

    var controlPoints = [{"x": x1, "y": y1}, {"x": x2, "y": y2}, {"x": x3, "y": y3}, {"x": x4, "y": y4}];
    //var edgeLine = d3.svg.line().x(function(d, i) { return d.x; }).y(function(d, i){ return d.y;}).interpolate("cardinal-open")(controlPoints);
    //var edgeLine = d3.svg.line().x(function(d, i) { return d.x; }).y(function(d, i){ return d.y;}).interpolate("cardinal-open")(controlPoints);
    var pathString = "M" + x1 + "," + y1 + "C" + [x2, y2, x3, y3, x4, y4].join(",");
    d3.select("svg").append("path").attr("fill", "none").attr("stroke", "#cc333f").attr("d", pathString);
  }
});
