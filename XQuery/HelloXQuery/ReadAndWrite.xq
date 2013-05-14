(: XQuery main module :)

import module namespace file = "http://expath.org/ns/file";

variable $local:file-name := fn:resolve-uri("resources/data.xml");
variable $local:my-doc := ();

(: read an XML file from the file system and parse it :)
$local:my-doc := fn:parse-xml(file:read-text(fn:resolve-uri("resources/data.xml")));

(: double the price of each product :)
for $node in $local:my-doc/root/nodes/node
return replace value of node $node with xs:double($node) * 2;

(: write the updated data to a new file :)
file:write("resources/new-data.xml", $local:my-doc, ());

(: return the new data as result of the program :)
$local:my-doc

