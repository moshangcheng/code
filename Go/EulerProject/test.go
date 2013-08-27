package main

import "fmt"
//import "os"
import "flag"
import "reflect"
import "github.com/moshangcheng/code/Go/EulerProject/solutions"

type Run interface {
    Run() int
}

var typeMap = map[int]reflect.Type {
    0: reflect.TypeOf(solutions.P1{}),
    1: reflect.TypeOf(solutions.P2{}),
}

func main() {
    var pid = flag.Int("problem", 1, "the problem id")
    flag.Parse()
    p := reflect.ValueOf(reflect.New(typeMap[*pid]))
    fmt.Println(p) 
}
