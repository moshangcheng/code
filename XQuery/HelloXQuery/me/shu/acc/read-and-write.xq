module namespace shu = 'http://shu.me/acc';
 
declare namespace op = "http://www.zorba-xquery.org/options";
declare namespace an = "http://www.zorba-xquery.com/annotations";

import module namespace f = "http://expath.org/ns/file";

declare %an:nondeterministic function shu:read-file-run() as item()+
{ 
    let $file-name := fn:resolve-uri("read-file.xml")
    let $file := fn:parse-xml(f:read-text($file-name))
    return $file
};

(: XQuery Update doesn't have side effect :)
(: So we use XQuery Script Extension and add ";" to generate side effect :)
declare %an:nondeterministic %an:sequential function shu:write-file-run() as item()+
{
    variable $file-name := fn:resolve-uri("read-file.xml");
    variable $file := fn:parse-xml(f:read-text($file-name));
    
    for $node in $file/root/nodes/node
    return replace value of node $node with xs:double($node) * 2;
    
    f:write("read-file.xml", $file, ());
    $file
};