import module namespace http = "http://www.zorba-xquery.com/modules/http-client";
import module namespace file = "http://expath.org/ns/file";
import module namespace x = "http://www.zorba-xquery.com/modules/xml";
import schema namespace opt = "http://www.zorba-xquery.com/modules/xml-options";



let $xml-frags1 := x:parse(file:read-text(fn:resolve-uri("resources/levels.xml")),  
<opt:options>
<opt:parse-external-parsed-entity/>
</opt:options>)

let $xml-frags2 := x:parse(file:read-text(fn:resolve-uri("resources/levels.xml")),  
<opt:options>
<opt:parse-external-parsed-entity/>
</opt:options>)

(: some calculations based on $xml-frags2 and results :)
let $calc-results := 10

for $x at $i in $xml-frags1 return
{
    if( $calc-results > 8 )
    then    $x
    else    <a></a>
        
}

(:
let $xml-fragments2 := x:parse(file:read-text(fn:resolve-uri("resources/ITEM_CCTR_MNTH_SLS.xml")),  
<opt:options>
<opt:parse-external-parsed-entity opt:skip-root-nodes="1"/>
</opt:options>)
:)


(:
let $ancestor := x:parse(http:get-text("http://chn-bwu/ITEM_CCTR_MNTH_SLS.xml")[2],  
<opt:options>
<opt:parse-external-parsed-entity opt:skip-root-nodes="1"/>
</opt:options>)

return <tabl>
{
for $ancestor0 in $ancestor
return <ab> {fn:data($ancestor0/TOT_COST)} </ab>
}
</tabl>
:)