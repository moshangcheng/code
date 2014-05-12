variable $x := 1;

variable $array := ();

while($x < 10) {
    $array := ($array, <v>{$x}</v>);
    $x := $x + 1;
}
<Table>
<ColumnHeaders>
<ColumnHeader name="v" type="xsd:integer"></ColumnHeader>
</ColumnHeaders>
<Data>
{
for $v in $array
return $v
}
</Data>
</Table>