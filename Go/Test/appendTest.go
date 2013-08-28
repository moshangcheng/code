package main

import "fmt"

func main() {
    x := []int{1, 2, 3}
    y := []int{4, 5, 6}
    //x = append(x, y) //compile error
    x = append(x, y...)
    fmt.Println(x)
}

