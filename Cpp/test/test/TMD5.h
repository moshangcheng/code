// File:	TMD5.h
// Date:	3/22/02
// Author:	T.S. Berman
//
// Copyright (C) 2002 MicroStrategy Incorporated
// All rights reserved
//

#ifndef MBase_TMD5_h
#define MBase_TMD5_h

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TMD5                                                                 //
//                                                                      //
// This code implements the MD5 message-digest algorithm.               //
// The algorithm is due to Ron Rivest. This code was                    //
// written by Colin Plumb in 1993, no copyright is claimed.             //
// This code is in the public domain; do with it what you wish.         //
//                                                                      //
// Equivalent code is available from RSA Data Security, Inc.            //
// This code has been tested against that, and is equivalent,           //
// except that you don't need to include two pages of legalese          //
// with every copy.                                                     //
//                                                                      //
// To compute the message digest of a chunk of bytes, create an         //
// TMD5 object, call Update() as needed on buffers full of bytes, and   //
// then call Final(), which will, optionally, fill a supplied 16-byte   //
// array with the digest.                                               //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "PDCHeader/PDCstdio.h"
#include "UUIDTypes.h"
#include "../../../Defines/BasicTypes.h"

namespace MBase
{
	// forward declaration
	class TMD5;
	bool  operator==(const TMD5 &m1, const TMD5 &m2);


	class TMD5
	{

	friend bool operator==(const TMD5 &m1, const TMD5 &m2);

	private:
	   unsigned Int32    fBuf[4];     //!temp buffer
	   unsigned Int32    fBits[2];    //!temp buffer
	   unsigned char    fIn[64];     //!temp buffer
	   unsigned char    fDigest[16]; //message digest
	   bool             fFinalized;  //true if message digest has been finalized

	   void Transform(unsigned Int32 buf[4], const unsigned Int32 in[16]);
	   void ByteReverse(unsigned char *buf, unsigned Int32 longs);

	public:
	   TMD5();
	   TMD5(const unsigned char *digest);
	   TMD5(const TMD5 &md5);
	   TMD5 &operator=(const TMD5 &rhs);

	   void        Update(const unsigned char *buf, unsigned Int32  len);
	   void        Final();
	   void        Final(unsigned char digest[16]);
	   void        Print() const;
	   const char *AsString() const;
	};
}

#endif // MBase_TMD5_h
