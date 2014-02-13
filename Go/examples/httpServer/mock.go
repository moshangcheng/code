package main

import (
    "fmt"
//    "io"
    "net/http"
//    "strings"
    )

func defaultHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("processing default request")
    w.Header().Set("Content-Type", "text/html;charset=utf-8")
    w.Write([]byte(htmlString))
}

func htmlHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("processing HTML request")
    w.Header().Set("Content-Type", "text/html;charset=utf-8")
    w.Write([]byte(htmlString))
}

func jsHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("processing js request")
    w.Header().Set("Content-Type", "application/x-javascript; charset=utf-8")
    w.Write([]byte(jsString))
}

func cssHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("processing css request")
    w.Header().Set("Content-Type", "text/css")
    w.Write([]byte(cssString))
}

func main() {
	//http.Handle("/", http.HandlerFunc(defaultHandler))
	http.Handle("/html", http.HandlerFunc(htmlHandler))
	http.Handle("/js", http.HandlerFunc(jsHandler))
	http.Handle("/css", http.HandlerFunc(cssHandler))
    http.ListenAndServe(":8080", nil)
}

const htmlString = `
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
</head>
<body>
    <div>
        <h1>hello</h1>
    </div>
</body>
</html>
`
const jsString = `
console.log("hello from server");
`

const cssString = `
* { margin: 0px; padding: 0px; }
`
