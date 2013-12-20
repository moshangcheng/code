var graph = new Springy.Graph();

graphJSON = {
  "nodes": ["mark", "higgs", "other", "etc"],
  "edges": [
    ["mark", "higgs"],
    ["mark", "etc"],
    ["mark", "other"]
  ]
};

graph.loadJSON(graphJSON);

var layout = new Springy.Layout.ForceDirected(graph, 400.0, 400.0, 0.5);

var renderer = new Springy.Renderer(layout,
  function clear() {
    // code to clear screen
    console.log("clear");
  },
  function drawEdge(edge, p1, p2) {
    // draw an edge
    console.log("draw edge " + "(" + edge.source.id + ", " + edge.target.id + ") at (" + p1.x + ", " + p1.y + ") (" + p2.x + ", " + p2.y + ")");
  },
  function drawNode(node, p) {
    // draw a node
    console.log("draw node " + node.id + " at " + p.x + ", " + p.y);
  }
);

renderer.start();

//$('<canvas id="container" />').appendTo('body').springy({ graph: graph });
