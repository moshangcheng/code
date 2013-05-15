module namespace shu = 'http://www.microstrategy.com/xquery/test/shu';
 
declare namespace op = "http://www.zorba-xquery.org/options";
declare namespace an = "http://www.zorba-xquery.com/annotations";

import module namespace file = "http://expath.org/ns/file";

declare %an:nondeterministic function shu:ReadFile() as item()+
{ 
    let $local:read-file-name := fn:resolve-uri("read-file.xml")
    let $local:read-file := fn:parse-xml(file:read-text($local:read-file-name))
    return $local:read-file
};

declare %an:nondeterministic function shu:WriteFile() as item()+
{
    let $local:read-file-name := fn:resolve-uri("read-file.xml")
    let $local:read-file := fn:parse-xml(file:read-text($local:read-file-name))
    
    let $local:for-return := for $node in $local:read-file/root/nodes/node
    return replace value of node $node with xs:double($node) * 2
    
    let $local:write-fn-return := file:write("write-file.xml", $local:read-file, ())
    
    return $local:read-file
};