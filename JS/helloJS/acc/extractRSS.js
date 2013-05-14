/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-11-3 下午06:53:29
 * @include "log4js.js"
 * @brief 提取RSS Live Links的RSS源
 */
 
var log = new Log(Log.DEBUG, Log.consoleLogger);
 
var rssArray = [{
			"url" : "http://blog.sina.com.cn/rss/twocold.xml",
			"name" : "韩寒",
			"group" : "资讯",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://blog.jjgod.org/feed/",
			"name" : "jjgod",
			"group" : "Web",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://feed.feedsky.com/bingo929",
			"name" : "彬Go",
			"group" : "Web",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://kinvix.kdv.cn/blog/?feed=rss2",
			"name" : "i在云端",
			"group" : "Web",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://feeds.feedsky.com/csdn.net/gengv",
			"name" : "GengV",
			"group" : "Web",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://feed.feedsky.com/cssrain",
			"name" : "CssRain",
			"group" : "Web",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://www.qianduan.net/feed",
			"name" : "前端观察",
			"group" : "Web",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://mrthink.net/feed/",
			"name" : "Mr.Think",
			"group" : "Web",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://lifesinger.wordpress.com/feed/",
			"name" : "岁月如歌",
			"group" : "Web",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://www.cn-cuckoo.com/feed",
			"name" : "为之漫笔",
			"group" : "重要",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://feeds.feedburner.com/dancewithnet",
			"name" : "随网之舞",
			"group" : "Web",
			"faviconURL" : "http://dancewithnet.com/favicon.ico",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://tianpeng.72pines.com/feed/",
			"name" : "数学日记",
			"group" : "其它",
			"faviconURL" : "http://tianpeng.72pines.com/wp-content/themes/iblog2/favicon.ico",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://ued.sohu.com/feed",
			"name" : "搜狐UED",
			"group" : "Web",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://blog.csdn.net/dojotoolkit/rss/list",
			"name" : "Dojo博客",
			"group" : "Web",
			"faviconURL" : "http://blog.csdn.net/favicon.ico",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://feed.feedsky.com/wsdued",
			"name" : "腾讯WSD",
			"group" : "Web",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://codingdao.com/wp/feed/",
			"name" : "Coding 道",
			"group" : "其它",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://typeof.net/feed/rss/",
			"name" : "typeof.net",
			"group" : "重要",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://cnodejs.org/blog/?feed=rss2",
			"name" : "CNode社区",
			"group" : "阿里巴巴",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://www.aqee.net/feed/",
			"name" : "外刊IT评论",
			"group" : "其它",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://fed.renren.com/?feed=rss2",
			"name" : "人人网FED",
			"group" : "Web",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://ued.ctrip.com/blog/?feed=rss2",
			"name" : "携程UED菁华",
			"group" : "Web",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://cdc.tencent.com/?feed=rss2",
			"name" : "Tencent CDC",
			"group" : "Web",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://ued.alimama.com/feed/",
			"name" : "阿里妈妈UED",
			"group" : "阿里巴巴",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://www.sndaued.com/blog/?feed=rss2",
			"name" : "盛大游戏UED",
			"group" : "Web",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://isd.tencent.com/?feed=rss2",
			"name" : "ISD Webteam",
			"group" : "Web",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://www.baiduux.com/blog/feed/",
			"name" : "百度泛用户体验",
			"group" : "Web",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://ued.alipay.com/wd/feed/atom/",
			"name" : "支付宝前端开发",
			"group" : "阿里巴巴",
			"faviconURL" : "http://ued.alipay.com/wd/favicon.ico",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://zhedahht.blog.163.com/rss/",
			"name" : "何海涛面试宝典",
			"group" : "重要",
			"faviconURL" : "http://zhedahht.blog.163.com/favicon.ico",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://www.cnblogs.com/LeftNotEasy/rss",
			"name" : "leftnoteasy的博客",
			"group" : "其它",
			"faviconURL" : "http://www.cnblogs.com/favicon.ico",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://robbin.javaeye.com/rss",
			"name" : "robbin的自言自语",
			"group" : "其它",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://www.cnblogs.com/anderslly/rss",
			"name" : "一个程序员的自省",
			"group" : "其它",
			"faviconURL" : "http://www.cnblogs.com/favicon.ico",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://www.ruanyifeng.com/blog/atom.xml",
			"name" : "阮一峰的个人网站",
			"group" : "重要",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://qa.taobao.com/?feed=rss2",
			"name" : "Taobao QA Team",
			"group" : "阿里巴巴",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://www.aliued.com/feed/",
			"name" : "Alibaba.com UED",
			"group" : "阿里巴巴",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://hax.iteye.com/rss",
			"name" : "hax的技术部落格",
			"group" : "Web",
			"faviconURL" : "http://hax.iteye.com/images/favicon.ico",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://feeds.feedsky.com/csdn.net/v_JULY_v",
			"name" : "结构之法 算法之道",
			"group" : "重要",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://ued.taobao.com/blog/feed/",
			"name" : "Taobao UED Team",
			"group" : "阿里巴巴",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://coolshell.cn/feed",
			"name" : "酷壳 – CoolShell.cn",
			"group" : "其它",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://diaorui.net/?feed=rss2",
			"name" : "Dora Blog RSS Feed",
			"group" : "其它",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://www.cc98.org/rss.asp",
			"name" : "CC98.org - 热门话题",
			"group" : "资讯",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://feed.feedsky.com/taobaodba",
			"name" : "淘宝数据库技术团队",
			"group" : "阿里巴巴",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://www.searchtb.com/feed",
			"name" : "搜索技术博客－淘宝",
			"group" : "阿里巴巴",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://buaawhl.iteye.com/rss",
			"name" : "buaawhl的iteye博客",
			"group" : "重要",
			"faviconURL" : "http://buaawhl.iteye.com/images/favicon.ico",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://www.oschina.net/news/rss",
			"name" : "开源中国 - 最新新闻",
			"group" : "资讯",
			"faviconURL" : "http://www.oschina.net/img/favicon.ico",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://feed.planabc.net/",
			"name" : "PlanABC – 怿飞’s Blog",
			"group" : "Web",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://rdc.taobao.com/blog/cs/?feed=rss2",
			"name" : "淘宝核心系统团队博客",
			"group" : "重要",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://uedc.163.com/rss",
			"name" : "网易用户体验设计中心",
			"group" : "Web",
			"faviconURL" : "http://uedc.163.com/favicon.ico",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://blog.zhaojie.me/rss",
			"name" : "老赵点滴 - 追求编程之美",
			"group" : "重要",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://rdc.taobao.com/team/jm/feed",
			"name" : "淘宝JAVA中间件团队博客",
			"group" : "阿里巴巴",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://www.aliued.cn/feed",
			"name" : "阿里巴巴（中文站）UED",
			"group" : "阿里巴巴",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://www.pushiming.com/blog/feed/",
			"name" : "他的博客-行于前端的程序员",
			"group" : "其它",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://www.tbdata.org/feed",
			"name" : "淘宝数据平台与产品部官方博客",
			"group" : "阿里巴巴",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://www.cvchina.info/feed/",
			"name" : "增强视觉 | 计算机视觉 增强现实",
			"group" : "重要",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}, {
			"url" : "http://www.infoq.com/cn/rss/rss.action?token=LptadlW9tthhy0rqUeiJ31ZrtW2ygJVn",
			"name" : "sany的 InfoQ 个性化 RSS Feed",
			"group" : "资讯",
			"refreshTime" : "TTL",
			"networkTimeout" : "0",
			"changesUnseen" : false,
			"useBookmarkFolder" : false
		}];
var output = "\n";
for(var i = 0; i < rssArray.length; i++) {
	output += rssArray[i].name + " " + rssArray[i].url + '\n';
}
log.info(output);
