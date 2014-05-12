for $d in distinct-values(doc("../resources/order.xml")//item/@dept)
let $items := doc("../resources/order.xml")//item[@dept = $d]
order by $d
return <department name="{$d}" totQuantity="{sum($items/@quantity)}"/>