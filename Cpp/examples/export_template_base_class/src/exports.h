#pragma once

#ifdef LIBRARY_EXPORTS
	#define	LIBRARY_EXPORT_EXIM	_declspec(dllexport)
#else
	#define	LIBRARY_EXPORT_EXIM	_declspec(dllimport)
#endif

#ifdef DERIVED_EXPORTS
	#define	DERIVED_EXPORT_EXIM	_declspec(dllexport)
#else
	#define	DERIVED_EXPORT_EXIM	_declspec(dllimport)
#endif