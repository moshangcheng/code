package main

import (
    "fmt"
    "math/rand"
    "time"
)

type OC struct {
    name string
}

func (o OC) Open() {
    fmt.Println("Open", o.name)
}

func (o OC) Close() {
    fmt.Println("Close", o.name)
}

func main() {
    rand.Seed(time.Now().Unix())

    a := OC{ name: "a"}
    a.Open()
    defer a.Close()

    if rand.Int31() < 10000 {
        return
    }

    //b.Close() is called at the end of main()
    //For local variable, its life time is decided by GC
    {
        b := OC{ name: "b" }
        b.Open()
        defer b.Close()
    }

    //c.Close() is called at the end of anonymous function
    //There is clousure
    c := OC{"c"}
    c.Open()
    func() {
        defer c.Close()
    }()

    fmt.Println("over")
}
