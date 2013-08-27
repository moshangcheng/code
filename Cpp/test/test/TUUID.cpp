// File:	TUUID.cpp
// Date:	3/22/02
// Author:	T.S. Berman
//
// Copyright (C) 2002 MicroStrategy Incorporated
// All rights reserved
// 
// This file defines a class to be used on the UNIX Platforms to generate
// a GUID.	The code is extensively based on an implementation done for an
// open source system known as root.  Therefore some copyright protection is
// afforded by the following:
//
// Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.
//
// The original code has been extensively modified to integrate with our
// system, remove conditional windows compilation, and to remove dependencies
// on the bulk of the original root code

//#include "../../../Defines/BasicTypes.h"
//#include "Base/Base/System.h"
//////////////////////////////////////////////////////////////////////////
//																		//
// TUUID																//
//																		//
// This class defines a UUID (Universally Unique IDentifier), also		//
// known as GUIDs (Globally Unique IDentifier). A UUID is 128 bits		//
// long, and if generated according to this algorithm, is either		//
// guaranteed to be different from all other UUIDs/GUIDs generated		//
// until 3400 A.D. or extremely likely to be different. UUIDs were		//
// originally used in the Network Computing System (NCS) and			//
// later in the Open Software Foundation's (OSF) Distributed Computing	//
// Environment (DCE).													//
//																		//
// Structure of universal unique IDs (UUIDs).							//
//																		//
// Depending on the network data representation, the multi- 			//
// octet unsigned integer fields are subject to byte swapping			//
// when communicated between dissimilar endian machines.				//
//																		//
// +-----------------------------------+								//
// |	 low 32 bits of time		   |  0-3	.fTimeLow				//
// +-------------------------------+----								//
// |	 mid 16 bits of time	   |	  4-5	.fTimeMid				//
// +-------+-----------------------+									//
// | vers. |   hi 12 bits of time  |	  6-7	.fTimeHiAndVersion		//
// +-------+-------+---------------+									//
// |Res | clkSeqHi |					  8 	.fClockSeqHiAndReserved //
// +---------------+													//
// |   clkSeqLow   |					  9 	.fClockSeqLow			//
// +---------------+------------------+ 								//
// |			node ID 			  |   10-15 .fNode					//
// +----------------------------------+ 								//
//																		//
// The adjusted time stamp is split into three fields, and the			//
// clockSeq is split into two fields.									//
//																		//
// The timestamp is a 60-bit value. For UUID version 1, this			//
// is represented by Coordinated Universal Time (UTC/GMT) as			//
// a count of 100-nanosecond intervals since 00:00:00.00,				//
// 15 October 1582 (the date of Gregorian reform to the 				//
// Christian calendar). 												//
//																		//
// The version number is multiplexed in the 4 most significant			//
// bits of the 'fTimeHiAndVersion' field. There are two defined 		//
// versions:															//
//				 MSB <---												//
// Version		4-Bit Code		Description 							//
// ------------------------------------------------------------ 		//
// |  1 		  0 0 0 1	  DCE version, as specified herein. 		//
// |  2 		  0 0 1 0	  DCE Security version, with				//
// |						  embedded POSIX UIDs.						//
// |  3 		  0 0 1 1	  node id is a random value 				//
// ------------------------------------------------------------ 		//
//																		//
// Clock Sequence														//
//																		//
// The clock sequence value must be changed whenever:					//
//																		//
//	  The UUID generator detects that the local value of UTC			//
//	  has gone backward; this may be due to re-syncing of the system	//
//	  clock.															//
//																		//
// While a node is operational, the UUID service always saves			//
// the last UTC used to create a UUID. Each time a new UUID 			//
// is created, the current UTC is compared to the saved value			//
// and if either the current value is less or the saved value			//
// was lost, then the clock sequence is incremented modulo				//
// 16,384, thus avoiding production of duplicted UUIDs. 				//
//																		//
// The clock sequence must be initialized to a random number			//
// to minimize the correlation across system. This provides 			//
// maximum protection against node identifiers that may move			//
// or switch from system to system rapidly. 							//
//																		//
// Clock Adjustment 													//
//																		//
// UUIDs may be created at a rate greater than the system clock 		//
// resolution. Therefore, the system must also maintain an				//
// adjustment value to be added to the lower-order bits of the			//
// time. Logically, each time the system clock ticks, the				//
// adjustment value is cleared. Every time a UUID is generated, 		//
// the current adjustment value is read and incremented, and			//
// then added to the UTC time field of the UUID.						//
//																		//
// Clock Overrun														//
//																		//
// The 100-nanosecond granularity of time should prove sufficient		//
// even for bursts of UUID production in the next generation of 		//
// high-performance multiprocessors. If a system overruns the			//
// clock adjustment by requesting too many UUIDs within a single		//
// system clock tick, the UUID generator will stall until the			//
// system clock catches up. 											//
//																		//
//////////////////////////////////////////////////////////////////////////
//

#ifndef WIN32

#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#include "TUUID.h"
#include "TMD5.h"

char MBase::TUUID::gsNodeName[] = \
		{'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', \
		 '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', \
		 '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', \
		 '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
#ifdef __hpux
		 };
#else
		 , \
		 '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', \
		 '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', \
		 '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', \
		 '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', \
		 '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', \
		 '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', \
		 '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', \
		 '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', \
		 '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', \
		 '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', \
		 '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', \
		 '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',};
#endif

unsigned char MBase::TUUID::gsfNode[6] = {'\0', '\0', '\0', '\0', '\0', '\0'};

bool MBase::TUUID::gsHasIP = false;

//______________________________________________________________________________
MBase::TUUID::TUUID()
{
	// Create a UUID.
	
	static uuid_time_t		 time_last;
	static unsigned short	 clockseq;
	
	GetCurrentTime(&time_last);
	clockseq = (unsigned short) randomINT(65536);
	
	
	uuid_time_t timestamp;
	
	// get current time
	GetCurrentTime(&timestamp);
	
	// if clock went backward change clockseq
	if (CmpTime(&timestamp, &time_last) == -1) {
		clockseq = (clockseq + 1) & 0x3FFF;
		if (clockseq == 0) clockseq++;
	}
	
	Format(clockseq, timestamp);
		
	time_last = timestamp;
}

//______________________________________________________________________________
int MBase::TUUID::CmpTime(uuid_time_t *t1, uuid_time_t *t2)
{
	// Compare two time values.
	
	if (t1->high < t2->high) return -1;
	if (t1->high > t2->high) return 1;
	if (t1->low  < t2->low)  return -1;
	if (t1->low  > t2->low)  return 1;
	return 0;
}

//______________________________________________________________________________
void MBase::TUUID::SetFromString(const char *uuid)
{
	// Set this UUID to the value specified in uuid ((which must be in
	// TUUID::AsString() format).
	
	// Format is tttttttt-tttt-cccc-cccc-nnnnnnnnnnnn.
	int    timeLo = 0;
	int 	timeMid = 0;
	int 	timeHiAndVersion = 0;
	int 	clockSeqHiAndRes = 0;
	int 	clockSeqLo = 0;
	int 	node[6];
	
	sscanf(uuid, "%8x-%4x-%4x-%2x%2x-%2x%2x%2x%2x%2x%2x",
		&timeLo,
		&timeMid,
		&timeHiAndVersion,
		&clockSeqHiAndRes,
		&clockSeqLo,
		&node[0], &node[1], &node[2], &node[3], &node[4], &node[5]);
	
	// Note that we're going through this agony because scanf is
	// defined to know only to scan into "int"s or "long"s.
	fTimeLow			   = (unsigned int) timeLo;
	fTimeMid			   = (unsigned short) timeMid;
	fTimeHiAndVersion	   = (unsigned short) timeHiAndVersion;
	fClockSeqHiAndReserved = (unsigned char) clockSeqHiAndRes;
	fClockSeqLow		   = (unsigned char) clockSeqLo;
	fNode[0]			   = (unsigned char) node[0];
	fNode[1]			   = (unsigned char) node[1];
	fNode[2]			   = (unsigned char) node[2];
	fNode[3]			   = (unsigned char) node[3];
	fNode[4]			   = (unsigned char) node[4];
	fNode[5]			   = (unsigned char) node[5];
}

//______________________________________________________________________________
MBase::TUUID::TUUID(const char *uuid)
{
	// Initialize a TUUID with uuid (which must be in TUUID::AsString() format).
	
	fTimeLow			   = 0;
	fTimeMid			   = 0;
	fTimeHiAndVersion	   = 0;
	fClockSeqHiAndReserved = 0;
	fClockSeqLow		   = 0;
	fNode[0]			   = 0;
	
	/*
	if (!uuid || !*uuid)
	Error("TUUID", "null string not allowed");
	*/
	
	SetFromString(uuid);
}

//______________________________________________________________________________
void MBase::TUUID::Format(unsigned short clockseq, uuid_time_t ts)
{
	// Make a UUID from timestamp, clockseq and node id.
	
	fTimeLow = ts.low;
	fTimeMid = (unsigned short)(ts.high & 0xFFFF);
	fTimeHiAndVersion = (unsigned short)((ts.high >> 16) & 0x0FFF);
	fTimeHiAndVersion |= (1 << 12);
	fClockSeqLow = clockseq & 0xFF;
	fClockSeqHiAndReserved = (clockseq & 0x3F00) >> 8;
	fClockSeqHiAndReserved |= 0x80;
	GetNodeIdentifier();
}

//______________________________________________________________________________
void MBase::TUUID::GetCurrentTime(uuid_time_t *timestamp)
{
	// Get current time as 60 bit 100ns ticks since whenever.
	// Compensate for the fact that real clock resolution is less
	// than 100ns.
	
	const unsigned short uuids_per_tick = 1024;
	
	static uuid_time_t time_last;
	static unsigned short	 uuids_this_tick;
	static bool 	 init = kFALSE;
	
	if (!init) {
		GetSystemTime(&time_last);
		uuids_this_tick = uuids_per_tick;
		init = kTRUE;
	}
	
	uuid_time_t time_now;
	
	while (1) {
		GetSystemTime(&time_now);
		
		// if clock reading changed since last UUID generated
		if (CmpTime(&time_last, &time_now))  {
			// reset count of uuid's generated with this clock reading
			uuids_this_tick = 0;
			break;
		}
		if (uuids_this_tick < uuids_per_tick) {
			uuids_this_tick++;
			break;
		}
		// going too fast for our clock; spin
	}
	
	time_last = time_now;
	
	if (uuids_this_tick != 0) {
		if (time_now.low & 0x80000000) {
			time_now.low += uuids_this_tick;
			if (!(time_now.low & 0x80000000))
				time_now.high++;
		} else
			time_now.low += uuids_this_tick;
	}
	
	timestamp->high = time_now.high;
	timestamp->low	= time_now.low;
}

//______________________________________________________________________________
void MBase::TUUID::GetSystemTime(uuid_time_t *timestamp)
{
	// Get system time with 100ns precision. Time is since Oct 15, 1582.
	
	struct timeval tp;
	gettimeofday(&tp, 0);
	
#ifdef R__LONGLONG
	// Offset between UUID formatted times and Unix formatted times.
	// UUID UTC base time is October 15, 1582.
	// Unix base time is January 1, 1970.
	const unsigned Int64 lMicrosecondsSince1970Jan1 = tp.tv_sec * 1000000 + tp.tv_usec;
	
	const unsigned Int64 uuid_time = (lMicrosecondsSince1970Jan1 * 10) + INT64(0x01B21DD213814000);
	
	timestamp->high = (unsigned Int32) (uuid_time >> 32);
	timestamp->low	= (unsigned Int32) (uuid_time & 0xFFFFFFFF);
#else
	timestamp->high = tp.tv_sec;
	timestamp->low	= tp.tv_usec * 10;
#endif
}
//______________________________________________________________________________
void MBase::TUUID::GetNodeIdentifier()
{
	// Get node identifier. Try first to get network address, if no
	// network interface try random info based on some machine parameters.
	
	// Get the host address information if it can be found
	// Otherwise simply generate random info and return it
	
	// for all Unix platforms
	int error_num = 0;
	if (MBase::TUUID::gsNodeName[0] == '\0'){
		// there could be race condition here, but it should not matter
		gethostname(MBase::TUUID::gsNodeName, MAXHOSTNAMELEN);
		char * services = NULL;
		struct addrinfo hints, *res;
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		Int32 ret = getaddrinfo(MBase::TUUID::gsNodeName, services, &hints, &res);
		if (ret == NULL && res->ai_family == AF_INET) {
			memcpy(MBase::TUUID::gsfNode, (res->ai_addr->sa_data+2), 4);
			//printf("===%d.%d.%d.%d====\n", gsfNode[0], gsfNode[1], gsfNode[2], gsfNode[3]);
			freeaddrinfo(res);
			MBase::TUUID::gsHasIP = true;
			memcpy(fNode, MBase::TUUID::gsfNode, 4);
		}
		else {
			// error on getting node ip address
			printf("%s\n", gai_strerror(ret));
			unsigned char seed[16];
			GetRandomInfo(seed);
			seed[0] |= 0x80;
			memcpy(fNode, seed, sizeof(fNode));

			fTimeHiAndVersion |= (3 << 12);    // version == 3: random node info
		}
	}
	Int32 lProcessID=  MBase::GetCurrentProcessID();
	Int32 lThreadID=  MBase::GetCurrentThreadID();
	fNode[2] = (unsigned char) (fNode[2] + (unsigned char)(lThreadID>>24));
	fNode[3] = (unsigned char) (fNode[3] + (unsigned char)(lThreadID>>16));
	fNode[4] = (unsigned char) (0xbe + (unsigned char)(lThreadID>>8));
	fNode[5] = (unsigned char) (0xef + (unsigned char)lThreadID);
	//printf("===%d.%d.%d.%d.%d.%d====\n", fNode[0], fNode[1], fNode[2], fNode[3], fNode[4], fNode[5]);
}

//______________________________________________________________________________
void MBase::TUUID::GetRandomInfo(unsigned char	seed[16])
{
	// Get random info based on some machine parameters.
	struct randomness {
		struct timeval	 t;
		char			 hostname[257];
	};
	
	randomness r;
	gettimeofday(&r.t, 0);
	//gethostname(r.hostname, 256);
	int error_num = 0;
	if (MBase::TUUID::gsNodeName[0] == '\0'){
		// there could be race condition here, but it should not be matter
		gethostname(MBase::TUUID::gsNodeName, MAXHOSTNAMELEN);
		memcpy(r.hostname, MBase::TUUID::gsNodeName, MAXHOSTNAMELEN);
		r.hostname[MAXHOSTNAMELEN] = '\0';
#if defined(_AIX) || defined(linux)
		// doing nothing
#else	// for HP-UX and Solaris
		struct hostent* hp = getipnodebyname(MBase::TUUID::gsNodeName, AF_INET,AI_DEFAULT, &error_num);
//printf("\t\tcall GetRandomInfo");
		if (!hp){
			memcpy(MBase::TUUID::gsfNode, *(hp->h_addr_list), 4);
			freehostent(hp);
			MBase::TUUID::gsHasIP = true;
//printf("\t%ld", hp);
		}
//printf("\n");
#endif
	}
	else{
		memcpy(r.hostname, MBase::TUUID::gsNodeName, MAXHOSTNAMELEN);
		r.hostname[MAXHOSTNAMELEN] = '\0';
	}
	TMD5 md5;
	md5.Update((unsigned char *)&r, sizeof(randomness));
	md5.Final(seed);
}

//______________________________________________________________________________
void MBase::TUUID::Print() const
{
	// Print UUID.
	
	printf("%s\n", AsString());
}

//______________________________________________________________________________
const char* MBase::TUUID::AsString() const
{
	// Return UUID as string. Copy string immediately since it will be reused.
	
	static char uuid[40];
	
	sprintf(uuid, "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		fTimeLow, fTimeMid, fTimeHiAndVersion, fClockSeqHiAndReserved,
		fClockSeqLow, fNode[0], fNode[1], fNode[2], fNode[3], fNode[4],
		fNode[5]);
	
	return uuid;
}

//______________________________________________________________________________
unsigned short MBase::TUUID::Hash() const
{
	// Compute 16-bit hash value of the UUID.
	
	short	 c0 = 0, c1 = 0, x, y;
	char	*c = (char *) &fTimeLow;
	
	// For speed lets unroll the following loop:
	//	 for (i = 0; i < 16; i++) {
	//		c0 += *c++;
	//		c1 += c0;
	//	 }
	
	c0 += *c++; c1 += c0;
	c0 += *c++; c1 += c0;
	c0 += *c++; c1 += c0;
	c0 += *c++; c1 += c0;
	
	c0 += *c++; c1 += c0;
	c0 += *c++; c1 += c0;
	c0 += *c++; c1 += c0;
	c0 += *c++; c1 += c0;
	
	c0 += *c++; c1 += c0;
	c0 += *c++; c1 += c0;
	c0 += *c++; c1 += c0;
	c0 += *c++; c1 += c0;
	
	c0 += *c++; c1 += c0;
	c0 += *c++; c1 += c0;
	c0 += *c++; c1 += c0;
	c0 += *c++; c1 += c0;
	
	//	Calculate the value for "First octet" of the hash
	x = -c1 % 255;
	if (x < 0)
		x += 255;
	
	// Calculate the value for "second octet" of the hash
	y = (c1 - c0) % 255;
	if (y < 0)
		y += 255;
	
	return (unsigned short)((y << 8) + x);
}

//______________________________________________________________________________
int MBase::TUUID::Compare(const TUUID &u) const
{
	// Compare two UUIDs "lexically" and return
	//	  -1   this is lexically before u
	//	   0   this is equal to u
	//	   1   this is lexically after u
	
#define CHECK(f1, f2) if (f1 != f2) return f1 < f2 ? -1 : 1;
	CHECK(fTimeLow, u.fTimeLow)
		CHECK(fTimeMid, u.fTimeMid)
		CHECK(fTimeHiAndVersion, u.fTimeHiAndVersion)
		CHECK(fClockSeqHiAndReserved, u.fClockSeqHiAndReserved)
		CHECK(fClockSeqLow, u.fClockSeqLow)
		for (int i = 0; i < 6; i++) {
			if (fNode[i] < u.fNode[i])
				return -1;
			if (fNode[i] > u.fNode[i])
				return 1;
		}
		return 0;
}

//______________________________________________________________________________
unsigned int MBase::TUUID::GetHostAddress() const
{
	// Get address of host encoded in UUID. If host id is not an ethernet
	// address, but random info, then the returned inetaddress is not valid.
	
	if ((fTimeHiAndVersion >> 12) == 1)
	{
		unsigned int  addr = 0;
		memcpy(&addr, fNode, 4);
		return addr;
	}
	return (unsigned int)0;
}

//______________________________________________________________________________
void MBase::TUUID::GetUUID(unsigned char uuid[16]) const
{
	// Return uuid in specified buffer (16 byte = 128 bits).
	
	memcpy(uuid, &fTimeLow, 16);
}

//______________________________________________________________________________
void MBase::TUUID::SetUUID(const char *uuid)
{
	// Set this UUID to the value specified in uuid ((which must be in
	// TUUID::AsString() format).
	
	/*
	if (!uuid || !*uuid)
	Error("SetUUID", "null string not allowed");
	*/
	
	SetFromString(uuid);
}
//______________________________________________________________________________
unsigned int MBase::TUUID::randomINT(unsigned int imax)
{
	// returns a random integer on [ 0, imax-1]
	
	unsigned int ui = 0;
	ui = (unsigned int)(imax*random());
	return ui;
}

//_______________________________________________________________________________
// uuid represent a uuid in 16 bit format
MBase::TUUID::TUUID(void *uuid)
{
	memcpy(&fTimeLow, uuid, 16);
}

#endif // WIN32
