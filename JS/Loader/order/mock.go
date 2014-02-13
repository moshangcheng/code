// This program is used to test HTML resource load order
package main

import (
    "fmt"
    "net/http"
    "time"
    "strconv"
    )

func discontinuousStream(w http.ResponseWriter, t1 int, s1 string, t2 int, s2 string) {
    fmt.Println("delay is ", t1,  ", pause is ", t2)

    time.Sleep(time.Duration(t1) * time.Second)
    w.Write([]byte(s1))

    //flush stream to make browser parse transfered content
    w.(http.Flusher).Flush()

    time.Sleep(time.Duration(t2) * time.Second)
    w.Write([]byte(s2))
}

func htmlHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("processing HTML request")
    w.Header().Set("Content-Type", "text/html;charset=utf-8")
    r.ParseForm()
    delay, _ := strconv.Atoi(r.FormValue("delay"))
    pause, _ := strconv.Atoi(r.FormValue("pause"))
    discontinuousStream(w, delay, htmlString1, pause, htmlString2)
}

func jsHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("processing js request")
    w.Header().Set("Content-Type", "application/x-javascript; charset=utf-8")
    r.ParseForm()
    delay, _ := strconv.Atoi(r.FormValue("delay"))
    pause, _ := strconv.Atoi(r.FormValue("pause"))
    discontinuousStream(w, delay, jsString1, pause, jsString2)
}

func cssHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("processing css request")
    w.Header().Set("Content-Type", "text/css")
    r.ParseForm()
    delay, _ := strconv.Atoi(r.FormValue("delay"))
    pause, _ := strconv.Atoi(r.FormValue("pause"))
    discontinuousStream(w, delay, cssString1, pause, cssString2)
}

func main() {
	http.Handle("/html", http.HandlerFunc(htmlHandler))
	http.Handle("/js", http.HandlerFunc(jsHandler))
	http.Handle("/css", http.HandlerFunc(cssHandler))
	http.Handle("/image/", http.StripPrefix("/image/", http.FileServer(http.Dir("./image"))))
    http.ListenAndServe(":8080", nil)
}

const htmlString1 = `
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <link rel="stylesheet" href="css?delay=2&pause=3">
    <script type="text/javascript" src="js?delay=1&pause=1"></script>
</head>
`

const htmlString2 =`
<body>
    <link rel="stylesheet" href="css?delay=0&pause=0" onload="console.log('first css loaded')" >
    <script type="text/javascript" src="js?delay=2&pause=1" onload="console.log('first script loaded')"></script>
    <img src="image/chart.png">
</body>
</html>
`
const jsString1 = `
console.log("hello");
for(var i = 0; i < 10000; i++) { console.log("i") }
`

const jsString2 = `
console.log("world");
`
const cssString1 = `
* { padding: 0px; }
`

const cssString2 = `
* { margin: 0px; }
`
