for $prod in doc("../resources/catalog.xml")/catalog/product
where $prod/@dept = "ACC"
order by $prod/name
return $prod/name