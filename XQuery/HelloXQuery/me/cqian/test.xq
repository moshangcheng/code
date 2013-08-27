module namespace cqian = 'http://www.microstrategy.com/xquery/test/cqian';

import module namespace expath-http = "http://expath.org/ns/http-client";

declare default element namespace "http://expath.org/ns/http-client";
declare namespace op = "http://www.zorba-xquery.org/options";
declare namespace an = "http://www.zorba-xquery.com/annotations";

declare %an:sequential function cqian:test() as item()+
{
    let $url := "http://chn-cqian:8089/servicesNS/beebe/search/saved/searches/Category/dispatch"
    let $req :=
    <request href="{data($url)}" method="post">
        <header name="Authorization" value=" Basic YmVlYmU6cWlhbmNvbmcx" />
        <header name="Connection" value="Close" />
        <body media-type="text/plain">
            trigger_actions=1
        </body>
    </request>
    
    let $result := expath-http:send-request($req)
    
    let $queryString := fn:data($result[2]//*:sid)
    
    let $queryString2 := "?output_mode=xml&amp;count=5"
    
    let $uri := "http://chn-cqian:8089/servicesNS/beebe/search/search/jobs/"
    let $url2 := fn:concat($uri, $queryString,'/results',$queryString2)
    
    let $req2 :=
    <request href="{data($url2)}" method="get">
        <header name="Connection" value=" Keep-Alive" />
        <header name="Pragma:" value=" no-cache" />
        <header name="Authorization" value=" Basic YmVlYmU6cWlhbmNvbmcx" />
    </request>
    
    let $number_seq := (
        for $number in 1 to 200
            let $num := $number * 2
            order by $num
            return $num
        )
    
    let $result2 := expath-http:send-request($req2)
    return $result2
};

(:

MSTR-style xquery

declare namespace mstr-rest = "http://www.microstrategy.com/xquery/rest-functions";

declare function mstr-rest:post($uri, $payload, $header) external;

let $uri :=
('https://chn-cqian:8089/services/saved/searches')


let $lRHeader := ('Authorization: Basic YWRtaW46cWlhbmNvbmcx')
let $lHContectType := ('Content-Type: application/json')
let $lHAccept := ('Accept: application/json, text/javascript, */*; q=0.01')
let $lHeaders := ($lRHeader, $lHContectType, $lHAccept)
let $lPayload := ()
let $result := mstr-rest:post($uri , $lPayload, $lHeaders )


return
<Table>
    <ColumnHeaders>
        <ColumnHeader name="name" type="xsd:string" />
    </ColumnHeaders>
    <Data>
        {
        for $customer in $result//*:name
        return
        <Row>
            <name>
                {$customer}
            </name>
        </Row>
        }
    </Data>
</Table>
:)