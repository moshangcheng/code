(: XQuery main module :)


(:
import module namespace mstr-zendesk = "http://www.microstrategy.com/xquery/cloudsource/zendesk"
    at "com/microstrategy/www/xquery/cloudsource/zendesk.xq";

mstr-zendesk:get-user-info()
mstr-zendesk:list-all-tickets()
let $tickets := mstr-zendesk:list-all-tickets()
:)

(:
import module namespace cqian = "http://www.microstrategy.com/xquery/test/cqian"
    at "com/microstrategy/www/xquery/test/cqian/test.xq";
cqian:test()
:)

(:
import module namespace shu = "http://www.microstrategy.com/xquery/test/shu"
    at "com/microstrategy/www/xquery/test/shu/ReadAndWrite.xq";

let $local:read-file-name := fn:resolve-uri("read-file.xml")
let $local:read-file := fn:parse-xml(file:read-text($local:read-file-name))

return $local:read-file
:)

import module namespace doc = "http://www.zorba-xquery.com/modules/store/dynamic/documents";
import module namespace f = "http://expath.org/ns/file";

let $doc := document { <root> { fn:parse-xml(f:read-text("resources/books.xml")) } </root> }
return doc:put("meat_poultry.xml", $doc);

let $doc1 := doc:document("meat_poultry.xml")
let $first-row := $doc1/root/row[1]
for $row in $doc1/root/row[position() > 1]
for $column at $y in $row/column
return rename node $column as $first-row/column[$y];












