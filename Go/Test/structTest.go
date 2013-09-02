package main

import "fmt"

type ST struct {
	v1, v2 int
}

func main() {
	//declare a ST and initlaize a ST by default
	var s1 ST
	fmt.Println(s1)

	//declare and initialize a ST
	s := ST{1, 2}
	fmt.Println(s)

	//declare and initialize a ST in another way
	s2 := ST{v1: 1, v2: 2}
	fmt.Println(s2)
}
