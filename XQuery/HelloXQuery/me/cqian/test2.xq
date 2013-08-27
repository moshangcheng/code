(: XQuery main module :)

import module namespace expath-http = "http://expath.org/ns/http-client";

let $url := "https://appstest.microstrategy.com/TechSupportWebAPI/API/Case/CreateNewCase"
let $req :=
<request href="{data($url)}" method="post">
    <header name="Authorization" value=" Basic YmVlYmU6cWlhbmNvbmcx" />
    <header name="Connection" value="Close" />
    <body media-type="text/plain">
        trigger_actions=1
    </body>
</request>

let $result := expath-http:send-request($req)