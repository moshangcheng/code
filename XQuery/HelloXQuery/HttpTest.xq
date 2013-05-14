(: XQuery main module :)

import module namespace http="http://www.zorba-xquery.com/modules/http-client";
declare namespace xhtml="http://www.w3.org/1999/xhtml";

http:get-node( "http://www.w3.org" )[2]//xhtml:body