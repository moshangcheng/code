package main

import "fmt"

type Stringer interface {
    String() string
}


func main() {
    //type assertion
    {
        v := "abc"
        value := interface{}(v)
        str, ok := value.(string)
        fmt.Println(str, ok)
    }

    //type switch
    {
        v := "abc"
        value := interface{}(v)
        switch str := value.(type) {
        case string:
            fmt.Println("string", str)
        case Stringer:
            fmt.Println("Stringer", str.String())
        default:
            fmt.Println("default", str)
        }
    }
}

