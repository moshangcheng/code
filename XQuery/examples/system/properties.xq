import module namespace system = "http://www.zorba-xquery.com/modules/system";

for $prop in system:properties()
    return concat("
    ", $prop, ": ", system:property($prop))