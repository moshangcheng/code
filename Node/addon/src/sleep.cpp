#include <node.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
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
    sleep(10);
    std::cout << "after sleep\n";
    Local<Number> num = Number::New(args[0]->NumberValue() + args[1]->NumberValue());
    return scope.Close(num);
}

void Init(Handle<Object> exports) {
    exports->Set(String::NewSymbol("add"), FunctionTemplate::New(Add)->GetFunction());
}

NODE_MODULE(sleep, Init)

