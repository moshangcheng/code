import module namespace http-client = "http://expath.org/ns/http-client";  

import schema namespace http = "http://expath.org/ns/http-client";

let $url := "http://10.197.62.102:8080/"

let $req :=
<http:request href="{data($url)}" method="get">
    <http:header name="Accept-Encoding" value="gzip" />
</http:request>
    
let $result := http-client:send-request($req)[2]//body

return $result
