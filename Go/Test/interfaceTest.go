//an interface value is like a box in which you can store any value that has the necessary methods
package main

import "fmt"

type I interface {
    Print()
}

type S struct {
    v int
}

func (s S) Print() {
    fmt.Println(s.v)
}

func (s *S) Set(iv int) {
    s.v = iv
}

func main() {
    var s = S{1}

    i1 := I(s)
    i2 := I(&s)

    i1.Print()
    i2.Print()

    s.Set(2)

    i1.Print()
    i2.Print()
}

