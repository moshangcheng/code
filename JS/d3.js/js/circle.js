var svg = d3.select("body").append("svg")
    .selectAll("circle")
    .data([23, 48, 28]).enter().append("circle")
    .attr("cx", function(d, i) { return 100 * (i+1); })
    .attr("cy", 100)
    .attr("r", function(d, i) { return d; })
    .style({
        "fill": "none",
        "stroke": "black",
        "stroke-width": 1.25
    });
