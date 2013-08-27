// DynamicLibrary.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DynamicLibrary.h"


// This is an example of an exported variable
DYNAMICLIBRARY_API int nDynamicLibrary=0;

// This is an example of an exported function.
DYNAMICLIBRARY_API int fnDynamicLibrary(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see DynamicLibrary.h for the class definition
CDynamicLibrary::CDynamicLibrary()
{
	return;
}
