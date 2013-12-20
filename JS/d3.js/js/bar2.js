d3.select("body").append("svg")
    .attr("class", "chart");


var width = 420,
    barHeight = 20;

var x = d3.scale.linear()
    .range([0, width]);

var chart = d3.select(".chart")
    .attr("width", width);

d3.tsv("js/bar2.tsv", type, function(error, data) {
  x.domain([0, d3.max(data, function(d) { return d.value; })]);

  chart.attr("height", barHeight * data.length);

  var bar = chart.selectAll("g")
      .data(data)
    .enter().append("g")
      .attr("transform", function(d, i) { return "translate(0," + i * barHeight + ")"; });

  bar.append("rect")
      .attr("width", function(d) { return x(d.value); })
      .attr("height", barHeight - 1);

  bar.append("text")
      .attr("x", function(d) { return x(d.value) - 3; })
      .attr("y", barHeight / 2)
      .attr("dy", ".35em")
      .text(function(d) { return d.value; });
    
  d3.selectAll(".chart rect")
    .style({
        "fill": "steelblue"
    });
    

  d3.selectAll(".chart text")
    .style({
        "fill": "white",
        "font": "10px sans-serif",
        "text-anchor": "end"
    });
});

function type(d) {
  d.value = +d.value; // coerce to number
  return d;
}

