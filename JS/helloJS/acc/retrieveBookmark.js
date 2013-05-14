/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-5-6 下午09:57:27
 * @include "log4js.js"
 * @brief 提取CSDN网摘上的书签，生成通用格式的书签文件
 */
 //从csdn网摘网页提取书签信息
var csdnTable = $$("table tr td");
var bookmarkList = [];
for(var i = 5; i < csdnTable.length; i += 6)	{
	var temp = {};
	temp.title = csdnTable[i-3].firstChild.innerText;
	temp.href = csdnTable[i-3].firstChild.href;
	temp.tagsName = csdnTable[i-2].innerText;
	bookmarkList.push(temp);
}

//生成通用的书签文件，从console中拷贝在本地保存，注意本地文件的编码格式
var bookmarkStr = '<!DOCTYPE NETSCAPE-Bookmark-file-1>';
bookmarkStr += '\n<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=GBK">';
bookmarkStr += '\n<TITLE>Bookmarks</TITLE>';
bookmarkStr += '\n<H1>Bookmarks</H1>';
bookmarkStr += '\n<DL><p>';
for(var i = 0; i < bookmarkList.length; i++)	{
	var tempStr = '\n<DT><A HREF="' + bookmarkList[i].href + '" TAGS="' + bookmarkList[i].tagsName + '">';
	tempStr += bookmarkList[i].title + '</A>';
	bookmarkStr += tempStr;
}
bookmarkStr += '\n</DL><p>';
console.log(bookmarkStr);