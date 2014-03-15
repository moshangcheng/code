declare namespace op = "http://www.zorba-xquery.com/options";
declare namespace an = "http://www.zorba-xquery.com/annotations";

import module namespace f = "http://expath.org/ns/file";

let $node :=
<node>
    <name>Lion</name>
    <description>Dota Hero</description>
    <type>Intelligence</type>
    <attack-range>600</attack-range>
    <mana>unknow</mana>
    <agilty>unknow</agilty>
    <strength>unknow</strength>
    <intelligence>unknown</intelligence>
</node>

for $i in 0 to 1000000
return f:append(fn:resolve-uri("./large-file.xml"), $node, ())