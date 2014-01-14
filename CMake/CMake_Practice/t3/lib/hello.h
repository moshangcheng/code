#ifndef HELLO_H
#define HELLO_H

#include <stdio.h>
//on Windows, specify exported function
//otherwise, there is no import library generated
__declspec(dllexport) void HelloFunc();

#endif
