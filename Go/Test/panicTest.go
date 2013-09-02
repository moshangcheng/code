package main

import "fmt"

//read only chan
func server(workChan <-chan *int) {
    for work := range workChan {
        safelyDo(work)
    }
}

func safelyDo(work *int) {
    defer func() {
        if err := recover(); err != nil {
            fmt.Println("work failed:", err)
        }
    }()
    fmt.Println(*work)
    panic(*work)
}

func main() {
    c := make(chan *int)
    var a = 3
    go server(c)
    c <- &a
}

