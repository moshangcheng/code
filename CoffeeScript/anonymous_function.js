// Generated by CoffeeScript 1.6.3
(function() {
  var obj;

  (function() {
    return console.log("I'm anonymous function");
  })();

  (function() {
    return console.log("I'm anonymous function2");
  })();

  obj = {
    "str": "abc"
  };

  (function() {
    console.log("hello");
    return console.log("my value is " + this.str);
  }).call(obj);

}).call(this);
