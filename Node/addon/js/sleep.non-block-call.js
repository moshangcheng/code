var sleep = require("../build/Debug/sleep");

console.log("before call setTimeout");
setTimeout(function() { console.log( 'This should be eight:', sleep.add(3,5)); }, 10);
console.log('after call setTimeout');

