variable $x := 1;

variable $array := ();

while($x < 10) {
    $array := ($array, <data>{$x}</data>);
    $x := $x + 1;
}

$array