var objs = require('../build/Debug/objs');

var obj1 = objs('hello');
var obj2 = objs('world');
console.log(obj1.msg+' '+obj2.msg); // 'hello world'
