// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DYNAMICLIBRARY_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DYNAMICLIBRARY_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DYNAMICLIBRARY_EXPORTS
#define DYNAMICLIBRARY_API __declspec(dllexport)
#else
#define DYNAMICLIBRARY_API __declspec(dllimport)
#endif

// This class is exported from the DynamicLibrary.dll
template <class T>
class DYNAMICLIBRARY_API CDynamicLibrary {
public:
	T v;
	CDynamicLibrary(void);
	void print() {}
};

extern DYNAMICLIBRARY_API int nDynamicLibrary;

DYNAMICLIBRARY_API int fnDynamicLibrary(void);
