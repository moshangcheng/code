package main

import "fmt"

var v1 int
var v2 int = 2
var v3 = 3
var v4, v5 = 4, 5.0

func init() {
	fmt.Println("call init()")
	fmt.Println(v1, v2, v3, v4, v5)
}

func main() {
}
