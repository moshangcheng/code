//There's an important way in which embedding differs from subclassing.
//When we embed a type, the methods of that type become methods of the outer type
//, but when they are invoked the receiver of the method is the inner type, not the outer one.
package main

import "fmt"

type I1 interface {
	F1()
}

func NeedF1(i1 I1) {
	i1.F1()
}

type I2 interface {
	F2()
}

func NeedF2(i2 I2) {
	i2.F2()
}

type I interface {
	I1
	I2
}

type S1 struct {
	v, v1 int
}

func (o S1) F1() {
	fmt.Println(o.v1)
}

type S2 struct {
	v, v2 int
}

func (o S2) F2() {
	fmt.Println(o.v2)
}

type S struct {
	S1
	S2
}

func main() {
	s1 := S1{1, 1}
	i1 := I1(&s1)
	NeedF1(i1)

	s2 := S2{2, 2}
	i2 := I2(&s2)
	NeedF2(i2)

	s := S{s1, s2}
	i := I(&s)
	//interface I satisfy NeedF1() and NeedF2()
	NeedF1(i)
	NeedF2(i)

	//struct S satisfy F1() and F2()
	s.F1()
	s.F2()

	//visit embedded struct
	fmt.Println(s.v1, " ", s.S1, " ", s.S1.v)
	fmt.Println(s.v2, " ", s.S2, " ", s.S2.v)
}
