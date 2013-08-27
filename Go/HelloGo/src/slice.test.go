//http://blog.golang.org/go-slices-usage-and-internals
package main

import (
	"fmt"
)

func main() {
	var sliceA = make([]int, 0, 5)
	fmt.Println(sliceA, len(sliceA), cap(sliceA))
	sliceB := append(sliceA, 1)
	fmt.Println(sliceA, len(sliceA), cap(sliceA))
	fmt.Println(sliceB, len(sliceB), cap(sliceB))

	intSlice := make([]int, 10, 100)
	fmt.Println(len(intSlice))
	fmt.Println(cap(intSlice))
	fmt.Println(intSlice)
}
