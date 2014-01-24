package main

import (
	_ "./myPkg"
	"fmt"
)

var a = getV()

func init() {
	fmt.Println("hello main")
}

func getV() int {
    fmt.Println("main var init")
    return 3
}

func main() {
	//fmt.Println(m.V1, m.V2)
}
