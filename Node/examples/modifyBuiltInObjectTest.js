(function() {
    Array.prototype.print = function() { console.log(3); }
    var arrayObj = [];
    arrayObj.print();
    [].print();
})()

var arrayObj2 = [];
arrayObj2.print();
[].print();

