#include <node.h>
#include "cppObj.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
    CppObj::Init(exports);
}

NODE_MODULE(cppObj, InitAll)
