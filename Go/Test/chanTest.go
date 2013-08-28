package main

import "fmt"

func main() {
    ch1 := make(chan int)
    fmt.Println(cap(ch1), len(ch1), nil == ch1) //print 0 0 false
    //ch2 <- 3.4 //compile error

    ch3 := make(chan int, 1)
    fmt.Println(cap(ch3), len(ch3)) //print 1 0 
    ch3 <- 3
    fmt.Println(cap(ch3), len(ch3)) //print 1 1
    //_ = ch3 <- 5
} 
