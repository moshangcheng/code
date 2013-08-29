package myPkg

import "fmt"

var v2 = -2
var V2 = 2

func init() {
    fmt.Println("hello f2", v1, v2, V1, V2)
}

//Function has the same name can only appeare once in a package, except for init()
/*func run() {
    fmt.Println("this f2.run()")
}*/

