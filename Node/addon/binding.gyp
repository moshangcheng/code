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
    },
    {
      "target_name": "cppObj",
      "sources": ["src/cppObj/cppObj.cpp", "src/cppObj/addon.cpp"],
      "dependencies": [ ],
      "conditions": [["OS==\"win\"", { }], ["OS==\"mac\"", { "libraries": ["-lobjc"] }]]
    },
    {
      "target_name": "objFactory",
      "sources": ["src/objFactory/myobject.cpp", "src/objFactory/addon.cpp"],
      "dependencies": [ ],
      "conditions": [["OS==\"win\"", { }], ["OS==\"mac\"", { "libraries": ["-lobjc"] }]]
    },
    {
      "target_name": "unwrapping",
      "sources": ["src/unwrapping/myobject.cpp", "src/unwrapping/addon.cpp"],
      "dependencies": [ ],
      "conditions": [["OS==\"win\"", { }], ["OS==\"mac\"", { "libraries": ["-lobjc"] }]]
    }
  ]
}
