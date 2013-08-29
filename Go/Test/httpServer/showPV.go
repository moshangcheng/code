package main

import (
	"fmt"
	"net/http"
)

type Counter struct {
    n int
}

func (ctr *Counter) ServeHTTP(w http.ResponseWriter, r *http.Request) {
    ctr.n++;
	fmt.Fprintf(w, "counter = %d\n", *ctr)
}

func main() {
    ctr := new(Counter)
	http.Handle("/", ctr)
	http.ListenAndServe(":8080", nil)
}
