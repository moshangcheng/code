var cppObj = require('../build/Debug/cppObj');

var obj = new cppObj.CppObj(10);
console.log( obj.plusOne() ); // 11
console.log( obj.plusOne() ); // 12
console.log( obj.plusOne() ); // 13
