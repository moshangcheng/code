var graph = new Springy.Graph();

graphJSON = {
  "nodes": ["N1", "N2", "N3", "N4", "N5", "N6"],
  "edges": [
    ["N1", "N4"],
    ["N1", "N5"],
    ["N1", "N6"],
    ["N2", "N4"],
    ["N2", "N5"],
    ["N2", "N6"],
    ["N3", "N4"],
    ["N3", "N5"],
    ["N3", "N6"],
  ]
};

graph.loadJSON(graphJSON);

$('<canvas id="container" />').appendTo('body').springy({ graph: graph });
