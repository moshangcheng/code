package main

import "fmt"

func main() {
    //declare array and initialize arrary by default
    var a [4]int
    fmt.Printf("%#v\n", a)
    fmt.Printf("%T\n", a)
    fmt.Println()

    //initialize array
    b := [4]int{1, 2, 3, 4}
    fmt.Printf("%#v\n", b)
    fmt.Printf("%T\n", b)
    fmt.Println()

    //declare slice and it's not initialized
    var nilSlice []int
    fmt.Printf("%#v\n", nilSlice)
    fmt.Printf("%T\n", nilSlice)
    fmt.Println(nilSlice, len(nilSlice), cap(nilSlice), nil == nilSlice)  //print [] 0 0 true
    fmt.Println()

    //declare and initialize slice
    c := []int{1, 2, 3}
    fmt.Printf("%#v\n", c)
    fmt.Printf("%T\n", c)
    fmt.Println(c, len(c), cap(c), nil == c)
}

