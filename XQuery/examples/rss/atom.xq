(:
http://www.zorba.io/blog/60028351254/atom-processing
:)

import module namespace http = "http://expath.org/ns/http-client";
import module namespace ft = "http://www.zorba-xquery.com/modules/full-text";

declare namespace atom = "http://www.w3.org/2005/Atom";
declare namespace an = "http://www.zorba-xquery.com/annotations";

declare %an:sequential function local:create-tinyurl($url as xs:string) as xs:string
{
  let $url-encoded := encode-for-uri($url)
  let $result := http:send-request(
    <http:request href="http://tinyurl.com/api-create.php?url={$url-encoded}" 
                  method="get" />
  )
  return $result[2]
};

let $feed := http:send-request(
      <http:request href="http://feed.cnblogs.com/blog/u/66591/rss" method="get" />
)[2]

return $feed//atom:entry[position() le 3]//atom:id