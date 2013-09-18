#include <node.h>
#include "cppObj.h"

using namespace v8;

CppObj::CppObj() {};
CppObj::~CppObj() {};

void CppObj::Init(Handle<Object> exports) {
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("CppObj"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    // Prototype
    tpl->PrototypeTemplate()->Set(String::NewSymbol("plusOne"),
            FunctionTemplate::New(PlusOne)->GetFunction());

    Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(String::NewSymbol("CppObj"), constructor);
}

Handle<Value> CppObj::New(const Arguments& args) {
    HandleScope scope;

    CppObj* obj = new CppObj();
    obj->counter_ = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
    obj->Wrap(args.This());

    return args.This();
}

Handle<Value> CppObj::PlusOne(const Arguments& args) {
    HandleScope scope;

    CppObj* obj = ObjectWrap::Unwrap<CppObj>(args.This());
    obj->counter_ += 1;

    return scope.Close(Number::New(obj->counter_));
}

