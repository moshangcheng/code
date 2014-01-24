//http://blog.golang.org/go-concurrency-patterns-timing-out-and
package main

import (
    "fmt"
    "math/rand"
    "time"
)

var gv1, gv2 int

type Conn struct {
}

func (conn *Conn) DoQuery() int {
    t := rand.Intn(5) + 5
    fmt.Println("wait ", t, " second")
    time.Sleep(time.Second * time.Duration(t))
    return t
}

//The first connection gets respons is selected
//Add default case to not block non-first connections
func Query(conns []Conn) int {
    ch := make(chan int, 1)
    for _, conn := range conns {
        fmt.Println("spawn a new goroutine")
        go func(c Conn) {
            select {
            case ch <- c.DoQuery():
                gv1++
            default:
                gv2++
            }
        }(conn)
    }
    return <-ch
}

func main() {
	rand.Seed(time.Now().Unix())
    conns := make([]Conn, 10, 10)
    fmt.Println(gv1, " ", gv2, "\n", Query(conns))
}
