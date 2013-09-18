{
  "targets": [
    {
      "target_name": "sleep",
      "sources": ["src/sleep.cpp"],
      "dependencies": [ ],
      "conditions": [["OS==\"win\"", { }], ["OS==\"mac\"", { "libraries": ["-lobjc"] }]]
    },
    {
      "target_name": "hello",
      "sources": ["src/hello.cpp"],
      "dependencies": [ ],
      "conditions": [["OS==\"win\"", { }], ["OS==\"mac\"", { "libraries": ["-lobjc"] }]]
    },
    {
      "target_name": "args",
      "sources": ["src/args.cpp"],
      "dependencies": [ ],
      "conditions": [["OS==\"win\"", { }], ["OS==\"mac\"", { "libraries": ["-lobjc"] }]]
    },
    {
      "target_name": "callbacks",
      "sources": ["src/callbacks.cpp"],
      "dependencies": [ ],
      "conditions": [["OS==\"win\"", { }], ["OS==\"mac\"", { "libraries": ["-lobjc"] }]]
    },
    {
      "target_name": "objs",
      "sources": ["src/objs.cpp"],
      "dependencies": [ ],
      "conditions": [["OS==\"win\"", { }], ["OS==\"mac\"", { "libraries": ["-lobjc"] }]]
    },
    {
      "target_name": "funcs",
      "sources": ["src/funcs.cpp"],
      "dependencies": [ ],
      "conditions": [["OS==\"win\"", { }], ["OS==\"mac\"", { "libraries": ["-lobjc"] }]]
    }
  ]
}
