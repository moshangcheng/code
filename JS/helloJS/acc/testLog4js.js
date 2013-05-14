/*
 * Title: 测试log4js
 * Author: moshangchneg
 * Date: 2010.11.27
 */

//建议采用console输出，因为popupLogger有可能被拦截，alertLogger不方便
// log object of priority debug and the popup logger
var log1 = new Log(Log.DEBUG, Log.popupLogger);
// log object of priority warn and the alert logger
var log2 = new Log(Log.WARN, Log.alertLogger);
// log object of priority debug and the console logger (Safari)
// 当开启了firebug，在firebug控制台输出，否则在新窗口中输出，即与popupLogger类似
var log3 = new Log(Log.DEBUG, Log.consoleLogger);
// log object of priority debug and the write logger
var log4  = new Log(Log.DEBUG, Log.writeLogger);

log1.debug('foo1'); // will popup a new window and log 'foo'
log1.warn('bar1'); // will add a new 'bar' message to the popup
log2.debug('foo2'); // will do nothing (Log object's priority threshold is WARN)
log2.warn('bar2'); // will display a javascript alert with the string 'bar'
log3.debug('foo3'); // will log message to Safari console or existing popup
log3.warn('bar3'); // same

log3.info(Log.dumpObject(new Array('apple', 'pear', 'orange', 'banana')));
log4.info("fuck");
