package main

import (
    "fmt"
    )

func assingAndChange() {
    var x, y string
    x = "abc"
    //y points to x
    y = x
    y = "d"
    fmt.Println(x)
    fmt.Println(y)

}

func main() {
    assingAndChange()
}

