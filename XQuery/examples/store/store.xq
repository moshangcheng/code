import module namespace doc = "http://www.zorba-xquery.com/modules/store/dynamic/documents";
import module namespace f = "http://expath.org/ns/file";
 
declare namespace op = "http://www.zorba-xquery.org/options";
declare namespace an = "http://www.zorba-xquery.com/annotations";

declare %an:sequential function local:run() as item()+
{
    variable $doc := document { <root> { fn:parse-xml(f:read-text(fn:resolve-uri("books.xml"))) } </root> };
    doc:put("books.xml", $doc);
    variable $doc1 := doc:document("books.xml");
    $doc1
};

local:run()