
import module namespace shu = "http://www.microstrategy.com/xquery/test/shu"
    at "com/microstrategy/www/xquery/test/shu/util.xq";
let $x1 := <a></a>
let $x2 := <b></b>
return shu:push($x1, $x2),
(),shu:test-xquery-script()



(:
import module namespace shu = "http://www.microstrategy.com/xquery/test/shu"
    at "com/microstrategy/www/xquery/test/shu/manipulate-xml.xq";
shu:manipuliate-xml-run()
:)

(:
import module namespace shu = "http://www.microstrategy.com/xquery/test/shu"
    at "com/microstrategy/www/xquery/test/shu/read-and-write.xq";
shu:read-file-run(),
shu:write-file-run()
:)

(:
import module namespace shu = "http://www.microstrategy.com/xquery/test/shu"
    at "com/microstrategy/www/xquery/test/shu/store.xq";
shu:store-document-run()
:)


(:
import module namespace shu = "http://www.microstrategy.com/xquery/test/shu"
    at "com/microstrategy/www/xquery/test/shu/xlst.xq";
shu:xslt-example-run()
:)

(:
import module namespace cqian = "http://www.microstrategy.com/xquery/test/cqian"
    at "com/microstrategy/www/xquery/test/cqian/test.xq";
cqian:test()
:)

(:
import module namespace mstr-zendesk = "http://www.microstrategy.com/xquery/cloudsource/zendesk"
    at "com/microstrategy/www/xquery/cloudsource/zendesk.xq";
mstr-zendesk:get-user-info()
mstr-zendesk:list-all-tickets()
let $tickets := mstr-zendesk:list-all-tickets()
:)









