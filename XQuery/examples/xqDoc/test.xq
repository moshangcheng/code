(:
http://www.zorba.io/blog/60028475838/xqdoc-support-in-zorba
:)

import module namespace http  = "http://expath.org/ns/http-client";
import module namespace xqdoc = "http://www.zorba-xquery.com/modules/xqdoc";
import module namespace f = "http://expath.org/ns/file";
import module namespace html-stylesheet = "http://www.zorba-xquery.com/modules/xqdoc/html" at "html.xq";


let $module-uri := "http://www.xqueryfunctions.com/xq/functx-1.0-doc-2007-01.xq"
let $module     := http:send-request(<http:request href="{$module-uri}" method="get" />)[2]
let $xqdoc      := xqdoc:xqdoc-content($module)
return {
    variable $doc-html := html-stylesheet:convert($xqdoc);
    f:write(fn:resolve-uri("./doc.html"), $doc-html , ());
    "done"
    }
