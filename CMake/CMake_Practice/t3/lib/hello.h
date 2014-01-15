#ifndef HELLO_H
#define HELLO_H

#include <stdio.h>
//on Windows, specify exported function
//otherwise, there is no import library generated
#ifdef WIN32
__declspec(dllexport)
#endif
void HelloFunc();

#endif
