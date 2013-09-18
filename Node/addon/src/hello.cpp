#include <node.h>
#include <v8.h>

using namespace v8;

//Every native function called by JS should be similar to it
Handle<Value> Method(const Arguments& args) {
  HandleScope scope;
  return scope.Close(String::New("world"));
}

//Module initialization function
void init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("hello"),
      FunctionTemplate::New(Method)->GetFunction());
}

NODE_MODULE(hello, init)
