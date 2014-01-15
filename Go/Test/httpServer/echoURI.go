package main

import (
	"fmt"
	"net/http"
)

// Default Request Handler
func defaultHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "<h1>Hello %s!</h1>", r.URL.Path[1:])
}

func main() {
	fmt.Print("hello")
    //The difference between http.HandleFunc() and http.Handle() is
    //the first one accepts function and the second one accepts struct instance
    //We can use http.HanlderFunc() to construct a struct from function
	http.HandleFunc("/", defaultHandler)
	http.ListenAndServe(":8080", nil)
}
