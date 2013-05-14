/*
 * Title: The Array in JavaScript
 * Author: moshangchneg
 * Date: 2010.11.27
 */

var log = new Log(Log.DEBUG, Log.consoleLogger);

var a = [3, 5, 2];

//数组元素中，下标最大的被认为是数组的长度，未初始化的元素为空值
a[4] = 4;


//遍历数组的另外一种方式是使用for...in循环。
//对于数组中没有初始化的元素，不会遍历
//注意，如果有人向Array.prototype添加新的属性，通过这样的循环它们也同样会被遍历
log.debug("改变原型前采用for...in形式输出");
for (var i in a) {
  log.debug(a[i]);
}

log.debug("改变原型后采用for...in形式输出");
Array.prototype.sorry = "i'm sorry"
for (var i in a) {
  log.debug(a[i]);
}

//splice方法
log.debug("调用splice方法");
log.debug("splice方法返回的是被删除的数组：\n" + Log.dumpObject(a.splice(0, 1)));
log.debug(Log.dumpObject(a));

//slice方法
log.debug("调用slice方法");
log.debug("默认参数调用slice方法: \n" + Log.dumpObject(a.slice()));
log.debug("负参数调用slice方法A: \n" + Log.dumpObject(a.slice(0, -1)));
log.debug("负参数调用slice方法B: \n" + Log.dumpObject(a.slice(-1, 2)));

//sort方法
log.debug("调用sort方法");
log.debug(Log.dumpObject(a.sort()));
