package myPkg 

import "fmt"

var v1 = -1
var V1 = 1

func init() {
    fmt.Println("hello f1", v1, v2, V1, V2)
}

func init() {
    fmt.Println("hello f1, too", v1, v2, V1, V2)
}

func run() {
    fmt.Println("this f1.run()")
}


