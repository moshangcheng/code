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

