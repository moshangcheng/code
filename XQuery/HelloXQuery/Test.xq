(: XQuery main module :)

let $sequence := ('a', 'b', 'c', 'd', 'e', 'f')
 
let $count := count($sequence)

return
<results>
    <count>{$count}</count>
    <items>
    {
        for $item in $sequence
        return
            <item>{$item}</item>
    }
    </items>
</results>