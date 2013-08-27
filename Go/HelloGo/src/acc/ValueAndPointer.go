//Value methods can be invoked on pointers and values
//Pointer methods can only be invoked on pointers.
//Value functions only accpet values
//Pointer functions only accept pointers
//http://golang.org/doc/effective_go.html#pointers_vs_values
package main

import "fmt"

type MyStruct struct {
    v int
}

func (s MyStruct) PrintValue() {
    fmt.Println(s.v)
}

func (s *MyStruct) SetValue(v int) {
    s.v = v
}

func ParamPrintValue(s MyStruct) {
    fmt.Println(s.v)
}

func ParamSetValue(s *MyStruct, v int) {
    s.v = v
}

func main() {
    ps := &MyStruct{3}
    vs := MyStruct{0}
    fmt.Println(vs, ps)

    //If vs is addressable and &vs's method set contains SetValue()
    //vs.SetValue() is shorthand for (&vs).SetValue()
    //http://golang.org/ref/spec#Calls
    //http://stackoverflow.com/questions/7438323/method-requires-pointer-receiver-in-go-programming-language
    vs.SetValue(4)
    ps.SetValue(5)

    vs.PrintValue()
    ps.PrintValue()

    //ParamSetValue(vs, 0)
    ParamSetValue(ps, 3)

    ParamPrintValue(vs)
    //ParamPrintValue(ps)
}

