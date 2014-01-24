package main

import "fmt"

func main() {
    var structArray = []struct {
            v1 string
            v2 int
    }{
        {"a", 1},
        {"b", 2},
        {"c", 3},
    }
    fmt.Println(structArray)

    var structObj1 = struct { v1 string; v2 int } {"d", 3}
    fmt.Println(structObj1)
}
