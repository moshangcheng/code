package main

import "fmt"

type I1 interface {
    F1()
}

type I2 interface {
    F2()
}

type I interface {
    I1
    I2
}

func main() {
    fmt.Println("hello")
}
