module namespace  zendesk = 'http://www.microstrategy.com/xquery/cloudsource/zendesk';

import module namespace expath-http-client = "http://expath.org/ns/http-client";
import module namespace json = "http://www.zorba-xquery.com/modules/converters/json";
import module namespace base64 = "http://www.zorba-xquery.com/modules/converters/base64";

declare default element namespace "http://expath.org/ns/http-client";
declare namespace op = "http://www.zorba-xquery.org/options";
declare namespace an = "http://www.zorba-xquery.com/annotations";

declare %an:sequential function zendesk:execute(
    $req as element(expath-http-client:request)) as xs:string
{
    let $result := expath-http-client:send-request($req)
    let $jsonResult := base64:decode($result[2])
    return $jsonResult
};

declare %an:sequential function zendesk:get-user-info() as xs:string
{
    let $uri := "https://moshangcheng.zendesk.com/api/v2/users/me.json"
    
    let $req :=
    <request href="{data($uri)}" method="get">
        <header name="Content-Type" value="application/json" />
        <header name="Authorization" value=" Basic bW9zaGFuZ2NoZW5nQGdtYWlsLmNvbS90b2tlbjpndnZaTzRadkRwdXZyRW13NTVISzVyVHRPUnIyT0YxMmtwSUlxbUhP" />
    </request>
    
   return zendesk:execute($req)
};

declare %an:sequential function zendesk:list-all-tickets() as xs:string
{
    let $uri := "https://moshangcheng.zendesk.com/api/v2/tickets.json"
    
    let $req :=
    <request href="{data($uri)}" method="get">
        <header name="Content-Type" value="application/json" />
        <header name="Authorization" value=" Basic bW9zaGFuZ2NoZW5nQGdtYWlsLmNvbS90b2tlbjpndnZaTzRadkRwdXZyRW13NTVISzVyVHRPUnIyT0YxMmtwSUlxbUhP" />
    </request>
    
   return zendesk:execute($req)
};

declare %an:sequential function zendesk:get-tickets-last-n-days($n as xs:integer) as xs:string
{
    let $lNDaysBeforeToday := fn:current-date() - xs:dayTimeDuration(string-join(('P', xs:string($n), 'D'), ''))
    let $lDateString := fn:substring(xs:string($lNDaysBeforeToday), 0, 11)
    let $queryString := fn:concat("query=type:ticket+created>", $lDateString)
    let $uri := fn:concat("https://moshangcheng.zendesk.com/api/v2/search.json?", fn:iri-to-uri($queryString))
    
    let $req :=
    <request href="{data($uri)}" method="get">
        <header name="Content-Type" value="application/json" />
        <header name="Authorization" value=" Basic bW9zaGFuZ2NoZW5nQGdtYWlsLmNvbS90b2tlbjpndnZaTzRadkRwdXZyRW13NTVISzVyVHRPUnIyT0YxMmtwSUlxbUhP" />
    </request>
    
   return zendesk:execute($req)
};

declare %an:sequential function zendesk:get-tickets-with-comments() as xs:string
{
    let $queryString := "query=type:ticket+commenter:*"
    let $uri := fn:concat("https://moshangcheng.zendesk.com/api/v2/search.json?", fn:iri-to-uri($queryString))
    
    let $req :=
    <request href="{data($uri)}" method="get">
        <header name="Content-Type" value="application/json" />
        <header name="Authorization" value=" Basic bW9zaGFuZ2NoZW5nQGdtYWlsLmNvbS90b2tlbjpndnZaTzRadkRwdXZyRW13NTVISzVyVHRPUnIyT0YxMmtwSUlxbUhP" />
    </request>
    
   return zendesk:execute($req)
};
