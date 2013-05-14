/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-9上午05:18:32
 * @include "../log4js.js"
 * @description
 */
window.onload = function() {
	var log = new Log(Log.DEBUG, Log.consoleLogger);
	/**
	 * @author moshangcheng
	 * @date 2011-3-9上午05:20:38
	 * @constructor
	 * @description A "constructor" function for creating MyObject1.
	 */
	function MyObject1(formalParameter) {
		/*
		 * Give the constructed object a property called - testNumber - and
		 * assign it the value passed to the constructor as its first argument:-
		 */
		this.testNumber = formalParameter;
	}

	/*
	 * A "constructor" function for creating objects of a - MyObject2 - type:-
	 */
	function MyObject2(formalParameter) {
		/*
		 * Give the constructed object a property called - testString - and
		 * assign it the value passed to the constructor as its first argument:-
		 */
		this.testString = formalParameter;
	}

	/*
	 * The next operation replaces the default prototype associated with all
	 * MyObject2 instances with an instance of MyObject1, passing the argument -
	 * 8 - to the MyObject1 constructor so that its - testNumber - property will
	 * be set to that value:-
	 */
	MyObject2.prototype = new MyObject1(8);

	/*
	 * Finally, create an instance of - MyObject2 - and assign a reference to
	 * that object to the variable - objectRef - passing a string as the first
	 * argument for the constructor:-
	 */
	var objectRef = new MyObject2("String_Value");
	var oTest = new MyObject1(89);

	/*
	 * MyObject1是oTest的构造函数， 也是 MyObject1.prototype的构造函数
	 */
	log.debug(MyObject1 == oTest.constructor);
	log.debug(MyObject1.prototype.constructor == MyObject1);

	/*
	 * MyObject2不是 objectRef的构造函数， 但MyObject1是objectRef的构造函数
	 * MyObject2.prototype的构造函数是 MyObject1 instanceof 运算符在原型链中的结果
	 */
	log.debug(MyObject1 == objectRef.constructor);
	log.debug(objectRef instanceof MyObject2);
	log.debug(objectRef instanceof MyObject1);
	log.debug(objectRef instanceof Object);
	log.debug(MyObject2.prototype.constructor == MyObject1);
	log.debug(MyObject2.prototype.constructor.prototype.constructor);

};
