package main

import "fmt"

//declare a function accepts variable length parameters
//The type of v is []interface{}, a slice
func f1(v ...interface{}) {
    fmt.Printf("%#v\n", v)
}


//declare a function accepts variable length integers as parameters
func f2(d int, v ...int) {
    if d == 0 {
        fmt.Printf("%#v\n", v)
        //Go doesn't support covariant
        //http://stackoverflow.com/questions/3839335/any-sensible-solution-to-the-lack-of-array-slice-covariance-in-go
        //f1(v...)
        return
    }
    f2(d-1, v...) //expand v so f2() treats it as variable lenght arguments
}


func main() {
    //invoke f1()
    f1(1, 2, 3.2, "abc")

    f2(0, 1, 2, 3)
    //f2(1, 1, 2, 'a') //compile error

    //intArray := [...]int{1, 2, 3, 4}
    //f2(1, intArray) //cannot use int array as arguments of function f2()

    intSlice := []int{1, 2, 3, 4}
    //f2(1, intSlice) //cannot use int slice as arguments of function f2()
    f2(1, intSlice...)
}

