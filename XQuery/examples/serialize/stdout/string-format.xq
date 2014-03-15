declare namespace op = "http://www.zorba-xquery.com/options";
declare namespace an = "http://www.zorba-xquery.com/annotations";
declare namespace output = "http://www.w3.org/2010/xslt-xquery-serialization";

"<root>
", for $i in 0 to 1000 return "    <node>" || $i || "</node>
","</root>"
