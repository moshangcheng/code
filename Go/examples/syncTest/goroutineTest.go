package main

import "fmt"

func main() {
	c := make(chan int)
	go func() {
		fmt.Print("hello ")
		close(c)
	}()
	<-c
	fmt.Println("world")
}
