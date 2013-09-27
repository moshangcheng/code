import module namespace json = 'http://www.zorba-xquery.com/modules/json';
declare copy-namespaces no-preserve, no-inherit;
declare namespace mstr-rest = 'http://www.microstrategy.com/xquery/rest-functions';
declare function mstr-rest:post($uri,$payload,$header) external;
let $header := ( )

let $uri := ('http://maps.googleapis.com/maps/api/geocode/json?latlng=50,50&amp;sensor=false')

let $payload := ( )
let $jsonresult := mstr-rest:post($uri,$payload,$header)
let $result := json:parse($jsonresult)


return 
<Table><ColumnHeaders>
<ColumnHeader  name='PostalCode' type='xs:string' />
<ColumnHeader  name='streetName' type='xs:string' />
<ColumnHeader  name='streetNum' type='xs:string' />
<ColumnHeader  name='Sub' type='xs:string' />
</ColumnHeaders>
<Data>{for $ancestor0 in $result/pair/item[1]
return <Row>
<PostalCode>{fn:data($ancestor0//pair[@name="short_name" and ../pair[@name="types"]/item="postal_code"])}</PostalCode>
<streetName>{fn:data($ancestor0//pair[@name="short_name" and ../pair[@name="types"]/item="route"])}</streetName>
<streetNum>{fn:data($ancestor0//pair[@name="short_name" and ../pair[@name="types"]/item="street_number"])}</streetNum>
<Sub>{fn:data($ancestor0//pair[@name="short_name" and ../pair[@name="types"]/item="locality"])}</Sub>
</Row>}</Data></Table>
