(: 
It seems that Zorba Windows build has a bug
It keeps conumsing memory when executing this script
On Linux, it's OK. 
:)

declare namespace op = "http://www.zorba-xquery.com/options";
declare namespace an = "http://www.zorba-xquery.com/annotations";
declare namespace output = "http://www.w3.org/2010/xslt-xquery-serialization";

import module namespace f = "http://expath.org/ns/file";

let $params :=
  <output:serialization-parameters>
    <output:omit-xml-declaration value="yes"/>
    <output:method value="text" />
  </output:serialization-parameters>

let $out-file := fn:resolve-uri("data.xml")

return {
    f:write($out-file, "<root>
", $params);
    
    for $i in 0 to 1000
    return {
        f:append($out-file, "   <node>" || $i || "</node>
", $params);
    }
    
    f:append($out-file, "</root>", $params)
}
