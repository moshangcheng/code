//http://stackoverflow.com/questions/4278430/convert-string-to-integer-type-in-go
package main

import (
    "flag"
    "os"
    "fmt"
    "strconv"
    )

func main() {
    flag.Parse()
    s := flag.Arg(0)
    i, err := strconv.Atoi(s)
    if err != nil {
        fmt.Println(err)
        os.Exit(2)
    }
    fmt.Println(s, i)
}

