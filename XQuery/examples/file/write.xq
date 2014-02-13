declare namespace op = "http://www.zorba-xquery.com/options";
declare namespace an = "http://www.zorba-xquery.com/annotations";

import module namespace f = "http://expath.org/ns/file";
import module namespace system = "http://www.zorba-xquery.com/modules/system";

declare %an:nondeterministic function local:read-file() as item()+
{
    let $file-name := fn:resolve-uri("input.xml")
    let $file := fn:parse-xml(f:read-text($file-name))
    return $file
};

(: XQuery Update doesn't have side effect :)
(: So we use XQuery Script Extension and add ";" to generate side effect :)
declare %an:sequential %an:nondeterministic function local:write-file() as item()+
{
    variable $file-name := fn:resolve-uri("input.xml");
    variable $file := fn:parse-xml(f:read-text($file-name));

    for $node in $file/root/nodes/node
    return replace value of node $node with xs:double($node) * 2;

    fn:trace($file, "value of file: ");
    f:write(fn:resolve-uri("./output.xml"), $file, ());
    $file
};

local:write-file()
