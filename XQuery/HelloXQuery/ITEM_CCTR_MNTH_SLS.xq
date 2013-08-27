import module namespace file = "http://expath.org/ns/file";
import module namespace x = "http://www.zorba-xquery.com/modules/xml";
import schema namespace opt = "http://www.zorba-xquery.com/modules/xml-options";



declare namespace od= 'urn:schemas-microsoft-com:officedata';
let $ancestor := x:parse(file:read-text("resources/ITEM_CCTR_MNTH_SLS.xml"),  
<opt:options>
<opt:parse-external-parsed-entity opt:skip-root-nodes="1"/>
</opt:options>)
(:
return element {"Table"} {
{
for $ancestor0 in $ancestor
return element {"Parent"} {
element {"ab"} {fn:data($ancestor0/TOT_COST)},
element {"dddab"} {fn:data($ancestor0/GROSS_DOLLAR_SALES)}
}
}
}:)
for $ancestor0 in $ancestor return <a>{fn:data($ancestor0/TOT_COST)}</a>
(:
<Table><ColumnHeaders>
<ColumnHeader  name='TOT_COST' type='xs:string' />
</ColumnHeaders>
<Data>{for $ancestor0 in $ancestor
return <Row>
<TOT_COST>{fn:data($ancestor0/TOT_COST)}</TOT_COST>
</Row>}</Data></Table>
:)