package main

import (
    "compress/gzip"
    "io"
    "net/http"
    "strings"
    )

type gzipResponseWriter struct {
    io.Writer
    http.ResponseWriter
}

func (w gzipResponseWriter) Write(b []byte) (int, error) {
    return w.Writer.Write(b)
}

/*
func gzipHandler(w http.ResponseWriter, r *http.Request) {
    w.Header().Set("Content-Type", "text/html")
    if !strings.Contains(r.Header.Get("Accept-Encoding"), "gzip") {
        w.Write([]byte(htmlText))
    } else {
        gzipWriter := gzip.NewWriter(w) 
        w.Header().Set("Content-Encoding", "gzip")
        w.Write([]byte(htmlText))
    }
}
*/

func makeGzipHandler(fn http.HandlerFunc) http.HandlerFunc {
    return func(w http.ResponseWriter, r *http.Request) {
        if !strings.Contains(r.Header.Get("Accept-Encoding"), "gzip") {
            fn(w, r)
            return
        }
        w.Header().Set("Content-Encoding", "gzip")
        gz := gzip.NewWriter(w)
        defer gz.Close()
        gzr := gzipResponseWriter{Writer: gz, ResponseWriter: w}
        fn(gzr, r)
    }
}

func handler(w http.ResponseWriter, r *http.Request) {
    w.Header().Set("Content-Type", "text/html")
    w.Write([]byte(htmlText))
}

func main() {
    http.ListenAndServe(":8080", makeGzipHandler(handler))
}

const htmlText = `
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
