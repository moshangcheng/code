/**
 * @title: Collections of RegExp in JavaScript
 * @author moshangcheng
 * @version 1.0
 * @date 2010.11.14
 * @include "log4js.js"
 * @description 演示使用firebug的命令行，判断字符串是否符合某一种模式，使用test方法
 */
var log = new Log(Log.DEBUG, Log.consoleLogger);

// 不包含 ".mht" 和 ".html" 的正则表达式。
// 注意，'.' 必须在预搜索表达式之后。否则，".mht" 就会满足匹配。

var notContainsStrs = /^((?!(\.mht|\.html)).)*$/g;

log.debug('不包含 ".mht" 和 ".html" 的正则表达式');
log.debug('(".mht").match(/^((?!(\.mht|\.html)).)*$/g):'
		+ (".mht").match(notContainsStrs)// null
		+ '\n("a.mht").match(/^((?!(\.mht|\.html)).)*$/g):'
		+ ("a.mht").match(notContainsStrs) // null
		+ '\n(".mhta").match(/^((?!(\.mht|\.html)).)*$/g)):'
		+ (".mhta").match(notContainsStrs));// null

// 不以 ".mht" 和 ".html" 结尾的正则表达式。
var notEndsWithStrs = /^((?!(\.mht$|\.html$)).)*$/g;
log.debug('不以 ".mht" 和 ".html" 结尾的正则表达式');
log.debug('(".mht").match(/^((?!(\.mht$|\.html$)).)*$/g):'
		+ (".mht").match(notEndsWithStrs)// null
		+ '\n("a.mht").match(/^((?!(\.mht$|\.html$)).)*$/g):'
		+ ("a.mht").match(notEndsWithStrs) // null
		+ '\n(".mhta").match(/^((?!(\.mht$|\.html$)).)*$/g):'
		+ (".mhta").match(notEndsWithStrs));// .mhta

// 不以 "file" 和 "http" 开头的正则表达式。注意，javascript 未实现反向预查。
// var startsWithStrs = /^(?!(^file|^http)).*$/g; 两者效果相同
var notStartsWithStrs = /^(?!(file|http)).*$/g;
log.debug('不以 "file" 和 "http" 开头的正则表达式');
log.debug('("file").match(/^(?!(file|http)).*$/g):'
		+ ("file").match(notStartsWithStrs)// null
		+ '\n("filea").match(/^(?!(file|http)).*$/g):'
		+ ("filea").match(notStartsWithStrs) // null
		+ '\n("afile").match(/^(?!(file|http)).*$/g):'
		+ ("afile").match(notStartsWithStrs));// afile

//包含.mht和.html的正则表达式 
var containsStrs = /^.*(\.mht|\.html).*$/;
log.debug(('.mht').match(containsStrs));

//以.mht和.html结尾的正则表达式 
var endsWithStrs = /^.*([.]mht|[.]html)$/;
log.debug(('.mht').match(endsWithStrs));

//包含title属性的<a></a>标签
var containsTitle = /<a(?=\s).*?\stitle=('|").+?\1(>|\s+.*?>).*?<\/a>/;

// email地址有效性验证,由数字、下划线、'.'组成
var emailPattern = /^\w+(\.\w+)*@\w+(\.\w+)+$/g;

// 浮点数有效性验证
var floatPattern = /^(-?\d+)(\.\d+)?$/g;

// 整数，可以包含前导0
var intPattern = /^-?\d+$/g;

// 整数，不包含前导0
var intPatternNoPreZero = /^(0|-?[1-9]\d*)$/g;

// url
var urlPattern = /^[a-zA-z]+:\/\/\w+(-\w+)*(\.\w+(-\w+)*)*(:\d+)?(\?\S*)?$/g;
