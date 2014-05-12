let $response := fn:doc("file:///C:/Users/shu/Desktop/Cognos/Data.xml")//*:dataTable[1]
return
<Table>
    <ColumnHeaders>
    {
        for $column in $response/*:row[1]/child::*
        return <ColumnHeader name="{fn:local-name($column)}" type="xsd:string"/>
    }
    </ColumnHeaders>
    <Data>
    {
        for $row in $response/*:row
        return
        <Row>
        {
            for $col in $row/child::*
            return element {fn:local-name($col)} {fn:string($col)}
        }
        </Row>
    }
    </Data>
</Table>
