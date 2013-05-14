(: XQuery main module :)

(: curl -k -u moshangcheng@gmail.com/token:gvvZO4ZvDpuvrEmw55HK5rTtORr2OF12kpIIqmHO
   https://moshangcheng.zendesk.com/api/v2/search.json?query="type:user"
:)


import module namespace expath-http = "http://expath.org/ns/http-client";
import module namespace base64 = "http://www.zorba-xquery.com/modules/converters/base64";

declare default element namespace "http://expath.org/ns/http-client";
declare namespace op = "http://www.zorba-xquery.org/options";


let $l90DaysBeforeToday := fn:current-date() - xs:dayTimeDuration('P90D')
let $lDateString := fn:substring(xs:string($l90DaysBeforeToday), 0, 10)
let $queryString := fn:concat("query=type:ticket+created>", $lDateString)
let $uri := fn:concat("https://moshangcheng.zendesk.com/api/v2/search.json?", fn:iri-to-uri($queryString))

return
<request xmlns="http://expath.org/ns/http-client" href="{data($uri)}" method="get">
    <header name="Content-Type" value="application/json" />
    <header name="Authorization" value="Basic bW9zaGFuZ2NoZW5nQGdtYWlsLmNvbS90b2tlbjpndnZaTzRadkRwdXZyRW13NTVISzVyVHRPUnIyT0YxMmtwSUlxbUhP" />
</request>

(:
let $result := expath-http:send-request($req, $uri)

let $jsonResult := base64:decode($result[2])

return json:parse($jsonResult)
:)