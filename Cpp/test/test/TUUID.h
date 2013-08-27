// File:	TUUID.h
// Date:	3/22/02
// Author:	T.S. Berman
//
// Copyright (C) 2002 MicroStrategy Incorporated
// All rights reserved
// 
// This file defines a class to be used on the UNIX Platforms to generate
// a GUID.  The code is extensively based on an implementation done for an
// open source system known as root.  Therefore some copyright protection is
// afforded by the following:
//
// Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.
//
// The original code has been extensively modified to integrate with our
// system, remove conditional windows compilation, and to remove dependencies
// on the bulk of the original root code

#ifndef MBase_TUUID_h
#define MBase_TUUID_h

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TUUID                                                                //
//                                                                      //
// This class defines a UUID (Universally Unique IDentifier), also      //
// known as GUIDs (Globally Unique IDentifier). A UUID is 128 bits      //
// long, and if generated according to this algorithm, is either        //
// guaranteed to be different from all other UUIDs/GUIDs generated      //
// until 3400 A.D. or extremely likely to be different. UUIDs were      //
// originally used in the Network Computing System (NCS) and            //
// later in the Open Software Foundation's (OSF) Distributed Computing  //
// Environment (DCE).                                                   //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "UUIDTypes.h"

#if defined(__hpux)
#include <sys/param.h>		// for gethostname, the value of MAXHOSTNAMELEN : 64 on HPUX.
#endif

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 256
#endif 

namespace MBase
{
	class TUUID
	{

	private:
	   unsigned int     fTimeLow;                // 60 bit time, lower 32 bits
	   unsigned short   fTimeMid;               // middle 16 time bits
	   unsigned short   fTimeHiAndVersion;      // high 12 time bits + 4 UUID version bits
	   unsigned char    fClockSeqHiAndReserved; // high 6 clock bits + 2 bits reserved
	   unsigned char    fClockSeqLow;           // low 8 clock bits
	   unsigned char    fNode[6];               // 6 node id bytes

	   static char gsNodeName[MAXHOSTNAMELEN];	// Cache the host name to reduce call to gethostname
	   static unsigned char gsfNode[6];			// Cache the ip address
	   static bool gsHasIP;						// Indicator of whether get the IP address or not

	   struct uuid_time_t
	   {
		  unsigned int high;
		  unsigned int low;
	   };

	   int  CmpTime(uuid_time_t *t1, uuid_time_t *t2);
	   void Format(unsigned short clockseq, uuid_time_t ts);
	   void GetNodeIdentifier();
	   void GetCurrentTime(uuid_time_t *timestamp);
	   void GetSystemTime(uuid_time_t *timestamp);
	   void GetRandomInfo(unsigned char seed[16]);
	   void SetFromString(const char *uuid_str);
	   unsigned int  randomINT(unsigned int imax);

	public:
	   TUUID();
	   TUUID(const char *uuid_str); // from uuid string representation
	   TUUID(void *uuid); // from a uuid in 16 bits format

	   const char*       AsString() const;
	   int               Compare(const TUUID &u) const;
	   unsigned short    Hash() const;
	   void              Print() const;
	   unsigned int      GetHostAddress() const;
	   void              GetUUID(unsigned char  uuid[16]) const;
	   void              SetUUID(const char* uuid_str);
	};


	inline bool operator==(const TUUID& u1, const TUUID& u2)
	{
		return (!u1.Compare(u2)) ? kTRUE : kFALSE;
	}

	inline bool  operator!=(const TUUID& u1, const TUUID& u2)
	{
		return !(u1 == u2);
	}
}

#endif // MBase_TUUID_h
