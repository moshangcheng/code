#include <node.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
  #include <Winbase.h>
#else
  #include <unistd.h>
#endif
#include <iostream>

using namespace v8;

Handle<Value> Add(const Arguments& args) {
    HandleScope scope;

    if (args.Length() < 2) {
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }

    if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
        ThrowException(Exception::TypeError(String::New("Wrong arguments")));
        return scope.Close(Undefined());
    }

    std::cout << "before sleep\n";
#ifdef WIN32
    Slee(10000);
#else
    sleep(10);
#endif
    std::cout << "after sleep\n";
    Local<Number> num = Number::New(args[0]->NumberValue() + args[1]->NumberValue());
    return scope.Close(num);
}

void Init(Handle<Object> exports) {
    exports->Set(String::NewSymbol("add"), FunctionTemplate::New(Add)->GetFunction());
}

NODE_MODULE(sleep, Init)

