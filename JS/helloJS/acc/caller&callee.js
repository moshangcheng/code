/*
 * Title: caller&callee Author: moshangchneg Date: 2010.12.23 Description:
 */

var log = new Log(Log.DEBUG, Log.consoleLogger);

/**
 * 演示arguments的用法,如何获取实参数和形数数
 */
log.debug("如何获取形参数量和实参数量：");
function argTest(a, b, c, d) {
	// 获取被传递参数的数值
	log.debug("实参数目为:" + arguments.length);
	// 获取期望参数的数值
	log.debug("形数数目为:" + argTest.length);
}

argTest(1, 2);

/**
 * arguments不是数组(Array类)
 */
log.debug("***************************");
log.debug("aguments不是一个Array对象：");
Array.prototype.selfvalue = 1;
function testAguments() {
	log.debug("arguments.selfvalue=" + arguments.selfvalue);
}

log.debug("Array.sefvalue=" + new Array().selfvalue);// 打印 "Array.sefvalue=1"
testAguments();// 打印 "arguments.selfvalue=undefined"

/**
 * 演示函数的caller属性. 说明:(当前函数).caller:返回一个对函数的引用，该函数调用了当前函数
 */
log.debug("***************************");
log.debug("函数的caller属性");
function callerDemo() {
	if (callerDemo.caller) {
		log.debug(callerDemo.caller.toString());
	} else {
		log.debug("caller is undefined");
	}
}

function handleCaller() {
	callerDemo();
}

callerDemo(); // 打印 "this is a top function"
var oFuncTest = {};
oFuncTest.fn = callerDemo;
oFuncTest.fn();
handleCaller("参数1", "参数2"); // 打印 "参数1"

/**
 * 演示函数的callee属性. 说明:arguments.callee:初始值就是正被执行的 Function 对象,用于匿名函数
 */
log.debug("***************************");
log.debug("arguments的callee属性");

function calleeDemo() {
	log.debug(arguments.callee);
}

calleeDemo(); // 打印 calleeDemo 整个函数体
(function(arg0, arg1) {
	log.debug("形参数目为:" + arguments.callee.length)
})();// 打印 "形数数目为:2"

