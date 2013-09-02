package main

import (
    "fmt"
    "io"
    _ "os" //Import for side effect
)

//Interface checks
//a conversion of a *RawMessage to a Marshaler requires that *RawMessage implements Marshaler
//var _ json.Marshaler = (*RawMessage)(nil)

//suppress the warning of unused import io
var _ io.Reader

func main() {
    //suppress the warning of unused variable
    var iv = 3
    _ = iv
    m := make(map[string]int)
    //ignore value in multiple assignment
    _, err := m["a"]
    fmt.Println(err)
}

