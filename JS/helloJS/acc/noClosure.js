/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-26 下午04:32:20
 * @include "../log4js.js"
 * @brief 消除闭包的方法
 */
 
var log = new Log(Log.DEBUG, Log.consoleLogger);

// 无意间形成的闭包
var fnArray = [];

(function() {
	for (var i = 0; i < 3; i++) {
		fnArray.push(function() {
					return i;
				});
	}
})();

log.debug("无意形成的闭包，三个函数返回相同的i:");
log.debug(fnArray[0]() + " " + fnArray[1]() + " " + fnArray[2]());

// 最佳解决方案，下建立一个临时对象，在此对象上绑定需返回的函数以及该函数需要访问的变量
// 使用自执行函数。在原函数与被创建函数间添加一个自执行函数
/*一种写法，更容易理解
 * fnArray.push((function() {
					var temp = i;
					return function() {
						return temp;
					}
				})());
 */
fnArray = [];
(function() {
	for (var i = 0; i < 3; i++) {
		(function() {
			var temp = i;
			fnArray.push(function() {
						return temp;
					});
		})();
	}
})();
log.debug("使用自执行函数，三个函数返回不同的i:");
log.debug(fnArray[0]() + " " + fnArray[1]() + " " + fnArray[2]());

// 将i值绑定到调用被创建函数的对象上
fnArray = [];
(function() {
	for (var i = 0; i < 3; i++) {
		fnArray.push({
					i : i,
					fn : function() {
						return this.i;
					}
				});

	}
})();
log.debug("将i值绑定到调用被创建函数的对象上，三个函数返回不同的i:");
log.debug(fnArray[0].fn() + " " + fnArray[1].fn() + " " + fnArray[2].fn());