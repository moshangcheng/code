package main

import (
    "fmt"
    "sync"
)

var l sync.Mutex

func main() {
    l.Lock()
    go func() {
        fmt.Print("hello")
        l.Unlock()
    }()
    l.Lock()
    fmt.Println(" world")
}

