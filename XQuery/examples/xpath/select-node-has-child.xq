let $c :=
<root>
    <node>2</node>
    <node>
        <a>1</a>
    </node>
    <node>
        <b>2</b>
    </node>
    <node>
        <c>3</c>
    </node>
</root>

return $c/node[a | b] | $c/node[c]
