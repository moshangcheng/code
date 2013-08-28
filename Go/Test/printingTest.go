package main

import "fmt"
import "os"

type T struct {
    a int
    b float64
    c string
}

type Nothing struct {
    v1, v2, v3 int
}

func (o Nothing) String() string {
    return fmt.Sprintf("nothing")
}


func main() {
    //The following lines produce the same output
    fmt.Printf("Hello %d\n", 23)
    fmt.Fprint(os.Stdout, "Hello ", 23, "\n")
    fmt.Println("Hello", 23)
    fmt.Println(fmt.Sprint("Hello ", 23))
    fmt.Println()

    //Print fixed width number
    fmt.Printf("%7.4f\n", 1234.56789)
    fmt.Println()

    //Print struct
    t := &T{ 7, -2.35, "abc\tdef" }
    fmt.Printf("%v\n", t)
    fmt.Printf("%+v\n", t)
    fmt.Printf("%#v\n", t)
    fmt.Println()

    //Use %q to integer
    intArray := [...]int{1, 2, 3}
    fmt.Printf("%T\n%+q\n%+q\n", intArray, "abc", intArray)
    fmt.Println()

    //Print with customized String() method
    nth1 := Nothing{1, 2, 3}
    fmt.Println(nth1)
}
