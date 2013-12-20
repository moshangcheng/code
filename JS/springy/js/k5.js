var graph = new Springy.Graph();

graphJSON = {
  "nodes": ["N1", "N2", "N3", "N4", "N5"],
  "edges": [
    ["N1", "N2"],
    ["N1", "N3"],
    ["N1", "N4"],
    ["N1", "N5"],
    ["N2", "N3"],
    ["N2", "N4"],
    ["N2", "N5"],
    ["N3", "N4"],
    ["N3", "N5"],
    ["N4", "N5"],
  ]
};

graph.loadJSON(graphJSON);

$('<canvas id="container" />').appendTo('body').springy({ graph: graph });
