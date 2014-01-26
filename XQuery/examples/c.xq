import module namespace json = 'http://www.zorba-xquery.com/modules/json';
declare copy-namespaces no-preserve, no-inherit;
declare namespace mstr-rest = 'http://www.microstrategy.com/xquery/rest-functions';
declare function mstr-rest:post($uri,$payload,$header) external;
let $header := ('Authorization: Basic {#TOKEN}' )

let $uri := ('https://mstrategy.zendesk.com/api/v2/views.json')
let $payload := ( )
let $jsonresult := mstr-rest:post($uri,$payload,$header)
let $result := json:parse($jsonresult)


return 
