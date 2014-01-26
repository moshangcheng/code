#include <stdio.h>

#ifdef WIN32
__declspec(dllexport)
#endif
void lib_hello();
