declare namespace op = "http://www.zorba-xquery.com/options";
declare namespace an = "http://www.zorba-xquery.com/annotations";
declare namespace output = "http://www.w3.org/2010/xslt-xquery-serialization";

import module namespace f = "http://expath.org/ns/file";

let $params :=
  <output:serialization-parameters>
    <output:omit-xml-declaration value="yes"/>
    <output:indent value="yes" />
  </output:serialization-parameters>

let $out-file := fn:resolve-uri("data.xml")

let $result :=
<root>
{
    for $i in 0 to 5000000
    return  <node>{$i}</node>
}
</root>

return f:write($out-file, $result, $params)
