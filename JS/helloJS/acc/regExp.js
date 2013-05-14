/**
 * @title The RegExp in JavaScript
 * @author moshangcheng
 * @include "../log4js.js"
 * @date: 2010.11.27
 */

var log = new Log(Log.DEBUG, Log.consoleLogger);

// 由于“g”为全文查找，当第一个“test”匹配结束时，全局对象RegExp的lastIndex已经不是-1，
// 而下一次的全局查找是从当前的lastIndex处开始的
log.debug("");
var reg = /^\d+(?:\.\d)?$/g;
log.debug(reg.test(2.2));
log.debug(reg.test(2.5));

// 当第二次查找时由于是全局查找，则从上次的lastIndex处开始，显然其结果为false，并导致lastIndex归零，结果第三次全局查找的结果为true。
// 因此在使用g全局查找时，应该考虑当前RegExp对象所保存的状态
var reg = /^\d+(?:\.\d)?$/g;
log.debug(reg.test(2.2));
log.debug(reg.lastIndex);
log.debug(reg.test(2.4));
log.debug(reg.lastIndex);
log.debug(reg.test(2.6));

// 重新创建当前正则表达式的RegExp对象
var reg = /^\d+(?:\.\d)?$/g;
log.debug(reg.test(2.2));
reg = /^\d+(?:\.\d)?$/g;
log.debug(reg.test(2.4));

// 重置lastIndex
var reg = /^\d+(?:\.\d)?$/g;
log.debug(reg.test(2.2));
reg.lastIndex = 0;
log.debug(reg.test(2.3));
