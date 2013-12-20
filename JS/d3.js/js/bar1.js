var data = [4, 8, 15, 16, 23, 42];

var x = d3.scale.linear()
    .domain([0, d3.max(data)])
    .range([0, 420]);

d3.select("body").append("div")
    .attr("class", "chart");

d3.select(".chart").selectAll("div").data(data).enter().append("div")
    .style("width", function(d) { return x(d) + "px"; })
    .text(function(d) { return d; });

d3.selectAll(".chart div")
    .style({
        "font": "10px sans-seri",
        "background-color": "steelblue",
        "text-align": "right",
        "padding": "3px",
        "margin": "1px",
        "color": "white"
    });


