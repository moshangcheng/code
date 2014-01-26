CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)

PROJECT(EXPORTS C)

SET(CMAKE_VERBOSE_MAKEFILE ON)
SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")

FILE(WRITE ${CMAKE_BINARY_DIR}/main.c
"
#ifdef WIN32
	#include <Windows.h>
#else
	#include <dlfcn.h>
#endif
#include <stdio.h>
void internal(void){printf(\"internal()\\n\");}
int main(void)
{
    void *p=dlopen(\"./libplugin.so\",RTLD_NOW);
    void (*f)(void)=dlsym(p,\"external\");
    f();
}\n")

ADD_EXECUTABLE(main main.c)
TARGET_LINK_LIBRARIES(main dl)

SET_TARGET_PROPERTIES(main PROPERTIES
    ENABLE_EXPORTS TRUE)

FILE(WRITE ${CMAKE_BINARY_DIR}/plugin.c
"void external(void){internal();}\n")

ADD_LIBRARY(plugin MODULE plugin.c)
TARGET_LINK_LIBRARIES(plugin main)
