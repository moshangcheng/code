//Value methods can be invoked on pointers and values
//Pointer methods can only be invoked on pointers and addressable values.
//Value functions only accpet values
//Pointer functions only accept pointers
//http://golang.org/doc/effective_go.html#pointers_vs_values
package main

import "fmt"

type MyStruct struct {
	v int
}

func (s MyStruct) PrintValue() {
	fmt.Println("Calling value method, the value is: ", s.v)
}

func (s *MyStruct) SetValue(v int) {
	fmt.Println("Calling pointer method, the old/new value is: ", s.v, "/", v)
	s.v = v
}

func ParamPrintValue(s MyStruct) {
	fmt.Println("Calling value functions", s.v)
}

func ParamSetValue(s *MyStruct, v int) {
	fmt.Println("Calling pointer function, the old/new value is: ", s.v, "/", v)
	s.v = v
}

func main() {
	ps := &MyStruct{3}
	vs := MyStruct{0}
	fmt.Println("value of vs is: ", vs)
	fmt.Println("value of ps is: ", ps)

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
