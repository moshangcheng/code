var canvas = document.getElementById("c");
var ctx = canvas.getContext('2d');
var radgrad = ctx.createRadialGradient(canvas.width/2, canvas.height/2, 10, canvas.width/2, canvas.height/2, 50);
radgrad.addColorStop(0, '#000');
radgrad.addColorStop(0.5, 'rgba(0, 0, 0, 0.5)');
radgrad.addColorStop(1, 'rgba(0, 0, 0, 0)');
ctx.fillStyle = radgrad;

ctx.fillRect(canvas.width/2-20, canvas.height/2-20, 100, 100);
