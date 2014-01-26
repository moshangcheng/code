// File:	UUIDTypes.h
// Date:	3/22/02
// Author:	T.S. Berman
//
// Copyright (C) 2002 MicroStrategy Incorporated
// All rights reserved
//
// Types to be used by all UUID Classes and Supporting Utilities
//
//
#ifndef MBase_UUIDTypes_h
#define MBase_UUIDTypes_h

#define R__LONGLONG
#define R__LL(long) _NAME2_(long,LL)

namespace MBase
{
	typedef void         (*VoidFuncPtr_t)();  //pointer to void function


	const bool  kTRUE   = 1;
	const bool  kFALSE  = 0;

#ifdef R__LONGLONG  // should go into Rtypes.h
#ifdef R__B64
	typedef long               Long64_t;    //Signed long integer 8 bytes
	typedef unsigned long      ULong64_t;   //Unsigned long integer 8 bytes
#else
	typedef long long          Long64_t;    //Signed long integer 8 bytes
	typedef unsigned long long ULong64_t;   //Unsigned long integer 8 bytes
#endif // R__B64
#endif // R__LONGLONG
}

#endif // MBase_UUIDTypes_h
