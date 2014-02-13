(:
http://www.zorba.io/blog/60027975996/xml-streaming-with-xquery
:)

import module namespace file = "http://expath.org/ns/file";
import module namespace p = "http://www.zorba-xquery.com/modules/xml";

import schema namespace opt = "http://www.zorba-xquery.com/modules/xml-options";

declare namespace w = "http://www.mediawiki.org/xml/export-0.6/";

let $raw-data as xs:string := file:read-text("enwikibooks-20120520-pages-meta-history.xml")
let $pages := p:parse($raw-data, <opt:options>
                                   <opt:parse-external-parsed-entity opt:skip-root-nodes="1"/>
                                 </opt:options>)
for $page in $pages
where starts-with($page/w:title, "XQuery")
let $title          := $page/w:title/text()
let $creation-date  := min($page/w:revision/w:timestamp/xs:dateTime(.))
return
<page title="{$title}" date="{$creation-date}" />