var sleep = require("../build/Debug/sleep");

console.log("before call native function")
console.log("This should be eight:", sleep.add(3,5));
console.log("After call native function")
