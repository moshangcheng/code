<root>
    <entity name='"'>"</entity>
    <entity name='&apos;'>'</entity>
    <entity name="lower than">&lt;</entity>
    <entity name="greater than">&gt;</entity>
    <entity name="double quote">&amp;</entity>
</root>
(:
let $x := '{"a": 1}'
let $y := "&quot;s""s"
let $z := ''''
return <a>{($x, $y, $z)}</a>
:)
(:
import module namespace http-client = "http://expath.org/ns/http-client";  

import schema namespace http = "http://expath.org/ns/http-client";

let $result1 := http-client:send-request(validate{
<http:request href="http://www.w3school.com.cn/xquery/books.xml" method="GET" />
})[2]

let $result2 := http-client:send-request(validate{
<http:request href="http://www.w3schools.com/xquery/books.xml" method="GET" />
})[2]

let $price1 := $result1//price
let $price2 := $result2//price
let $price-item-count := fn:count($price1)

return
<Table>
<ColumnHeaders>
    <ColumnHeader name="price1" type="xsd:string"/>
    <ColumnHeader name="price2" type="xsd:string"/>
</ColumnHeaders>
<Data>
{
for $x in (1 to $price-item-count)
return <Row>
            <price1>{data($price1[$x])}</price1>
            <price2>{data($price2[$x])}</price2>
       </Row>
}
</Data>
</Table>
:)
(:
for $x in 1 to 3
return {
    variable $y := $x * $x;
    $y
}
:)

(:
import module namespace http-client = "http://expath.org/ns/http-client";  

import schema namespace http = "http://expath.org/ns/http-client";

let $result := http-client:send-request(validate{
<http:request href="http://www.w3school.com.cn/xquery/books.xml" method="GET" />
})[2]

return $result
:)

(:
import module namespace http-client = "http://expath.org/ns/http-client";  

import schema namespace http = "http://expath.org/ns/http-client";

let $result1 := http-client:send-request(validate{
<http:request href="http://www.w3school.com.cn/xquery/books.xml" method="GET" />
})[2]

let $result2 := http-client:send-request(validate{
<http:request href="http://www.w3schools.com/xquery/books.xml" method="GET" />
})[2]

let $price1 := $result1//price
let $price2 := $result2//price
let $price-item-count := fn:count($price1)

return
<Table>
<ColumnHeaders>
    <ColumnHeader name="price1" type="xsd:string"/>
    <ColumnHeader name="price2" type="xsd:string"/>
</ColumnHeaders>
<Data>
{
for $x in (1 to $price-item-count)
return <Row>
            <price1>{data($price1[$x])}</price1>
            <price2>{data($price2[$x])}</price2>
       </Row>
}
</Data>
</Table>
:)
(:
variable $x := 1;

variable $array := ();

while($x < 10) {
    $array := ($array, <data>{$x}</data>);
    $x := $x + 1;
}

$array
:)

(:
import module namespace expath-http-client = "http://expath.org/ns/http-client";
import module namespace json = "http://www.zorba-xquery.com/modules/json";
import module namespace base64 = "http://www.zorba-xquery.com/modules/base64";

declare default element namespace "http://expath.org/ns/http-client";
declare namespace op = "http://www.zorba-xquery.org/options";
declare namespace an = "http://www.zorba-xquery.com/annotations";

let $uri := "https://moshangcheng.zendesk.com/api/v2/users/me.json"
    
let $req :=
<request href="{data($uri)}" method="get">
    <header name="Content-Type" value="application/json" />
    <header name="Authorization" value=" Basic bW9zaGFuZ2NoZW5nQGdtYWlsLmNvbS90b2tlbjpndnZaTzRadkRwdXZyRW13NTVISzVyVHRPUnIyT0YxMmtwSUlxbUhP" />
</request>

let $result := expath-http-client:send-request($req)
let $jsonResult := base64:decode($result[2])
return $jsonResult
:)

(:
import module namespace shu = "http://www.microstrategy.com/xquery/test/shu"
    at "com/microstrategy/www/xquery/test/shu/util.xq";
shu:test-fn-trace()
:)

(:
declare namespace op = "http://www.zorba-xquery.org/options";
declare namespace an = "http://www.zorba-xquery.com/annotations";

import module namespace f = "http://expath.org/ns/file";

doc("resources/books.xml")
, f:read-binary("resources/books.xml")
, fn:parse-xml(f:read-text("resources/books.xml"))
:)


(:
import module namespace shu = "http://www.microstrategy.com/xquery/test/shu"
    at "com/microstrategy/www/xquery/test/shu/util.xq";
let $x1 := <a></a>
let $x2 := <b></b>
return shu:push($x1, $x2),
(),shu:test-xquery-script()
:)


(:
import module namespace shu = "http://www.microstrategy.com/xquery/test/shu"
    at "com/microstrategy/www/xquery/test/shu/manipulate-xml.xq";
shu:manipuliate-xml-run()
:)

(:
import module namespace shu = "http://www.microstrategy.com/xquery/test/shu"
    at "com/microstrategy/www/xquery/test/shu/read-and-write.xq";
shu:read-file-run(),
shu:write-file-run()
:)

(:
import module namespace shu = "http://www.microstrategy.com/xquery/test/shu"
    at "com/microstrategy/www/xquery/test/shu/store.xq";
shu:store-document-run()
:)


(:
import module namespace shu = "http://www.microstrategy.com/xquery/test/shu"
    at "com/microstrategy/www/xquery/test/shu/xlst.xq";
shu:xslt-example-run()
:)

(:
import module namespace cqian = "http://www.microstrategy.com/xquery/test/cqian"
    at "com/microstrategy/www/xquery/test/cqian/test.xq";
cqian:test()
:)

(:
import module namespace mstr-zendesk = "http://www.microstrategy.com/xquery/cloudsource/zendesk"
    at "com/microstrategy/www/xquery/cloudsource/zendesk.xq";
mstr-zendesk:get-user-info()
mstr-zendesk:list-all-tickets()
let $tickets := mstr-zendesk:list-all-tickets()
:)








