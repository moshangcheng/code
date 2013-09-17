{
  "targets": [
    {
      "target_name": "sleep",
      "sources": ["src/sleep.cpp"],
      "dependencies": [ ],
      "conditions": [["OS==\"win\"", { }], ["OS==\"mac\"", { "libraries": ["-lobjc"] }]]
    }
    , {
      "target_name": "hello",
      "sources": ["src/hello.cpp"],
      "dependencies": [ ],
      "conditions": [["OS==\"win\"", { }], ["OS==\"mac\"", { "libraries": ["-lobjc"] }]]
    }
  ]
}
