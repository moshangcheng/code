// File:	TMD5.cpp
// Date:	3/22/02
// Author:	T.S. Berman
//

//////////////////////////////////////////////////////////////////////////
//																		//
// TMD5 																//
//																		//
// This code implements the MD5 message-digest algorithm.				//
// The algorithm is due to Ron Rivest. This code was					//
// written by Colin Plumb in 1993, no copyright is claimed. 			//
// This code is in the public domain; do with it what you wish. 		//
//																		//
// Equivalent code is available from RSA Data Security, Inc.			//
// This code has been tested against that, and is equivalent,			//
// except that you don't need to include two pages of legalese			//
// with every copy. 													//
//																		//
// To compute the message digest of a chunk of bytes, create an 		//
// TMD5 object, call Update() as needed on buffers full of bytes, and	//
// then call Final(), which will, optinally, fill a supplied 16-byte	//
// array with the  digest.												//
//																		//
//////////////////////////////////////////////////////////////////////////
//#ifndef WIN32

#include "PDCHeader/PDCstring.h"
#include "PDCHeader/PDCerrno.h"

#include "TMD5.h"

//______________________________________________________________________________
MBase::TMD5::TMD5()
{
	// Create TMD5 object. Set bit count to 0 and buffer to mysterious
	// initialization constants.
	
	fBuf[0] = 0x67452301;
	fBuf[1] = 0xefcdab89;
	fBuf[2] = 0x98badcfe;
	fBuf[3] = 0x10325476;
	
	fBits[0] = 0;
	fBits[1] = 0;
	
	memset(fDigest, 0, 16);
	fFinalized = kFALSE;
}

//______________________________________________________________________________
MBase::TMD5::TMD5(const unsigned char *digest)
{
	// Create finalized TMD5 object containing passed in 16 byte digest.
	
	if (digest)
		memcpy(fDigest, digest, 16);
	else {
		memset(fDigest, 0, 16);
		
		/*
		Error("TMD5::TMD5", "digest is 0");
		*/
	}
	fFinalized = kTRUE;
}

//______________________________________________________________________________
MBase::TMD5::TMD5(const TMD5 &md5)
{
	// MD5 copy ctor. Special copy ctor avoids copying unnecessary
	// temp arrays when finalized.
	
	if (!md5.fFinalized) {
		memcpy(fBuf,  md5.fBuf,  4*sizeof(unsigned Int32));
		memcpy(fBits, md5.fBits, 2*sizeof(unsigned Int32));
		memcpy(fIn,   md5.fIn,	 64);
	}
	
	memcpy(fDigest, md5.fDigest, 16);
	fFinalized = md5.fFinalized;
}

//______________________________________________________________________________
MBase::TMD5& MBase::TMD5::operator=(const TMD5& rhs)
{
	// MD5 assignment operator. Special assignment operator avoids
	// copying unnecessary temp arrays when finalized.
	
	if (this != &rhs) {
		if (!rhs.fFinalized) {
			memcpy(fBuf,  rhs.fBuf,  4*sizeof(unsigned Int32));
			memcpy(fBits, rhs.fBits, 2*sizeof(unsigned Int32));
			memcpy(fIn,   rhs.fIn,	 64);
		}
		memcpy(fDigest, rhs.fDigest, 16);
		fFinalized = rhs.fFinalized;
	}
	return *this;
}

//______________________________________________________________________________
void MBase::TMD5::Update(const unsigned char* buf, unsigned Int32 len)
{
	// Update TMD5 object to reflect the concatenation of another buffer full
	// of bytes.
	
	if (fFinalized) {
		//Error("TMD5::Update", "Final() has already been called");
		return;
	}
	
	unsigned Int32  t = 0;
	
	// Update bitcount
	t = fBits[0];
	if ((fBits[0] = t + (len << 3)) < t)
		fBits[1]++; 	   // Carry from low to high
	fBits[1] += len >> 29;
	
	t = (t >> 3) & 0x3f;
	
	// Handle any leading odd-sized chunks
	if (t) {
		unsigned char *p = (unsigned char *) fIn + t;
		
		t = 64 - t;
		if (len < t) {
			memcpy(p, buf, len);
			return;
		}
		memcpy(p, buf, t);
		ByteReverse(fIn, 16);
		Transform(fBuf, (unsigned Int32	*) fIn);
		buf += t;
		len -= t;
	}
	
	// Process data in 64-byte chunks
	while (len >= 64) {
		memcpy(fIn, buf, 64);
		ByteReverse(fIn, 16);
		Transform(fBuf, (unsigned Int32 *) fIn);
		buf += 64;
		len -= 64;
	}
	
	// Handle any remaining bytes of data
	memcpy(fIn, buf, len);
}

//______________________________________________________________________________
void MBase::TMD5::Final(unsigned char digest[16])
{
	// Final wrapup - pad to 64-byte boundary with the bit patterns
	// 1 0* (64-bit count of bits processed, MSB-first).
	// Returns digest.
	
	Final();
	memcpy(digest, fDigest, 16);
}

//______________________________________________________________________________
void MBase::TMD5::Final()
{
	// Final wrapup - pad to 64-byte boundary with the bit patterns
	// 1 0* (64-bit count of bits processed, MSB-first).
	
	if (fFinalized)
		return;
	
	unsigned Int32	count = 0;
	unsigned char	*p;
	
	// Compute number of bytes mod 64
	count = (fBits[0] >> 3) & 0x3F;
	
	// Set the first char of padding to 0x80. This is safe since there is
	// always at least one byte free.
	p = fIn + count;
	*p++ = 0x80;
	
	// Bytes of padding needed to make 64 bytes
	count = 64 - 1 - count;
	
	// Pad out to 56 mod 64
	if (count < 8) {
		// Two lots of padding: pad the first block to 64 bytes
		memset(p, 0, count);
		ByteReverse(fIn, 16);
		Transform(fBuf, (unsigned Int32	*) fIn);
		
		// Now fill the next block with 56 bytes
		memset(fIn, 0, 56);
	} else {
		// Pad block to 56 bytes
		memset(p, 0, count - 8);
	}
	ByteReverse(fIn, 14);
	
	// Append length in bits and transform
	((unsigned Int32 *) fIn)[14] = fBits[0];
	((unsigned Int32 *) fIn)[15] = fBits[1];
	
	Transform(fBuf, (unsigned Int32 *) fIn);
	ByteReverse((unsigned char *) fBuf, 4);
	memcpy(fDigest, fBuf, 16);
	
	fFinalized = kTRUE;
}

//______________________________________________________________________________
void MBase::TMD5::Print() const
{
	// Print digest in ascii hex form.
	
	if (!fFinalized) {
		//Error("TMD5::Print", "Final() has not yet been called");
		return;
	}
	
	for (int i = 0; i < 16; i++)
		printf("%.2hx", (unsigned short)fDigest[i]);
	printf("\n");
}

//______________________________________________________________________________
const char* MBase::TMD5::AsString() const
{
	// Return message digest as string. Returns "" in case Final() has
	// not yet been called. Copy result because it points to a statically
	// allocated string.
	
	if (!fFinalized) {
	/*
	Error("TMD5::AsString", "Final() has not yet been called");
		*/	
		
		return "";
	}
	
	static char s[33];
	
	for (int i = 0; i < 16; i++)
		sprintf((s+2*i), "%.2hx", (unsigned short)fDigest[i]);
	s[32] = 0;
	
	return s;
}

//______________________________________________________________________________
void MBase::TMD5::ByteReverse(unsigned char *buf, unsigned Int32 longs)
{
#ifdef R__BYTESWAP
	UInt_t t;
	do {
		t = (unsigned Int32) ((unsigned Int32) buf[3] << 8 | buf[2]) << 16 |
			((unsigned Int32) buf[1] << 8 | buf[0]);
		*(unsigned Int32 *) buf = t;
		buf += 4;
	} while (--longs);
#endif
}


// The four core functions - F1 is optimized somewhat
// #define F1(x, y, z) (x & y | ~x & z)
#define F1(x, y, z) (z ^ (x & (y ^ z)))
#define F2(x, y, z) F1(z, x, y)
#define F3(x, y, z) (x ^ y ^ z)
#define F4(x, y, z) (y ^ (x | ~z))

// This is the central step in the MD5 algorithm
#define MD5STEP(f, w, x, y, z, data, s) \
( w += f(x, y, z) + data,  w = w<<s | w>>(32-s),  w += x )

//______________________________________________________________________________
void MBase::TMD5::Transform(unsigned Int32 buf[4], const unsigned Int32 in[16])
{
	// The core of the MD5 algorithm, this alters an existing MD5 hash to
	// reflect the addition of 16 longwords of new data. Update() blocks
	// the data and converts bytes into longwords for this routine.
	
	register unsigned Int32 a = 0,  b = 0 ,	c = 0 ,  d = 0 ;
	
	a = buf[0];
	b = buf[1];
	c = buf[2];
	d = buf[3];
	
	MD5STEP(F1, a, b, c, d, in[0] + 0xd76aa478, 7);
	MD5STEP(F1, d, a, b, c, in[1] + 0xe8c7b756, 12);
	MD5STEP(F1, c, d, a, b, in[2] + 0x242070db, 17);
	MD5STEP(F1, b, c, d, a, in[3] + 0xc1bdceee, 22);
	MD5STEP(F1, a, b, c, d, in[4] + 0xf57c0faf, 7);
	MD5STEP(F1, d, a, b, c, in[5] + 0x4787c62a, 12);
	MD5STEP(F1, c, d, a, b, in[6] + 0xa8304613, 17);
	MD5STEP(F1, b, c, d, a, in[7] + 0xfd469501, 22);
	MD5STEP(F1, a, b, c, d, in[8] + 0x698098d8, 7);
	MD5STEP(F1, d, a, b, c, in[9] + 0x8b44f7af, 12);
	MD5STEP(F1, c, d, a, b, in[10] + 0xffff5bb1, 17);
	MD5STEP(F1, b, c, d, a, in[11] + 0x895cd7be, 22);
	MD5STEP(F1, a, b, c, d, in[12] + 0x6b901122, 7);
	MD5STEP(F1, d, a, b, c, in[13] + 0xfd987193, 12);
	MD5STEP(F1, c, d, a, b, in[14] + 0xa679438e, 17);
	MD5STEP(F1, b, c, d, a, in[15] + 0x49b40821, 22);
	
	MD5STEP(F2, a, b, c, d, in[1] + 0xf61e2562, 5);
	MD5STEP(F2, d, a, b, c, in[6] + 0xc040b340, 9);
	MD5STEP(F2, c, d, a, b, in[11] + 0x265e5a51, 14);
	MD5STEP(F2, b, c, d, a, in[0] + 0xe9b6c7aa, 20);
	MD5STEP(F2, a, b, c, d, in[5] + 0xd62f105d, 5);
	MD5STEP(F2, d, a, b, c, in[10] + 0x02441453, 9);
	MD5STEP(F2, c, d, a, b, in[15] + 0xd8a1e681, 14);
	MD5STEP(F2, b, c, d, a, in[4] + 0xe7d3fbc8, 20);
	MD5STEP(F2, a, b, c, d, in[9] + 0x21e1cde6, 5);
	MD5STEP(F2, d, a, b, c, in[14] + 0xc33707d6, 9);
	MD5STEP(F2, c, d, a, b, in[3] + 0xf4d50d87, 14);
	MD5STEP(F2, b, c, d, a, in[8] + 0x455a14ed, 20);
	MD5STEP(F2, a, b, c, d, in[13] + 0xa9e3e905, 5);
	MD5STEP(F2, d, a, b, c, in[2] + 0xfcefa3f8, 9);
	MD5STEP(F2, c, d, a, b, in[7] + 0x676f02d9, 14);
	MD5STEP(F2, b, c, d, a, in[12] + 0x8d2a4c8a, 20);
	
	MD5STEP(F3, a, b, c, d, in[5] + 0xfffa3942, 4);
	MD5STEP(F3, d, a, b, c, in[8] + 0x8771f681, 11);
	MD5STEP(F3, c, d, a, b, in[11] + 0x6d9d6122, 16);
	MD5STEP(F3, b, c, d, a, in[14] + 0xfde5380c, 23);
	MD5STEP(F3, a, b, c, d, in[1] + 0xa4beea44, 4);
	MD5STEP(F3, d, a, b, c, in[4] + 0x4bdecfa9, 11);
	MD5STEP(F3, c, d, a, b, in[7] + 0xf6bb4b60, 16);
	MD5STEP(F3, b, c, d, a, in[10] + 0xbebfbc70, 23);
	MD5STEP(F3, a, b, c, d, in[13] + 0x289b7ec6, 4);
	MD5STEP(F3, d, a, b, c, in[0] + 0xeaa127fa, 11);
	MD5STEP(F3, c, d, a, b, in[3] + 0xd4ef3085, 16);
	MD5STEP(F3, b, c, d, a, in[6] + 0x04881d05, 23);
	MD5STEP(F3, a, b, c, d, in[9] + 0xd9d4d039, 4);
	MD5STEP(F3, d, a, b, c, in[12] + 0xe6db99e5, 11);
	MD5STEP(F3, c, d, a, b, in[15] + 0x1fa27cf8, 16);
	MD5STEP(F3, b, c, d, a, in[2] + 0xc4ac5665, 23);
	
	MD5STEP(F4, a, b, c, d, in[0] + 0xf4292244, 6);
	MD5STEP(F4, d, a, b, c, in[7] + 0x432aff97, 10);
	MD5STEP(F4, c, d, a, b, in[14] + 0xab9423a7, 15);
	MD5STEP(F4, b, c, d, a, in[5] + 0xfc93a039, 21);
	MD5STEP(F4, a, b, c, d, in[12] + 0x655b59c3, 6);
	MD5STEP(F4, d, a, b, c, in[3] + 0x8f0ccc92, 10);
	MD5STEP(F4, c, d, a, b, in[10] + 0xffeff47d, 15);
	MD5STEP(F4, b, c, d, a, in[1] + 0x85845dd1, 21);
	MD5STEP(F4, a, b, c, d, in[8] + 0x6fa87e4f, 6);
	MD5STEP(F4, d, a, b, c, in[15] + 0xfe2ce6e0, 10);
	MD5STEP(F4, c, d, a, b, in[6] + 0xa3014314, 15);
	MD5STEP(F4, b, c, d, a, in[13] + 0x4e0811a1, 21);
	MD5STEP(F4, a, b, c, d, in[4] + 0xf7537e82, 6);
	MD5STEP(F4, d, a, b, c, in[11] + 0xbd3af235, 10);
	MD5STEP(F4, c, d, a, b, in[2] + 0x2ad7d2bb, 15);
	MD5STEP(F4, b, c, d, a, in[9] + 0xeb86d391, 21);
	
	buf[0] += a;
	buf[1] += b;
	buf[2] += c;
	buf[3] += d;
}

//______________________________________________________________________________
bool MBase::operator==(const MBase::TMD5& m1, const MBase::TMD5& m2)
{
	// Compare two message digests for equality.
	
	// Make sure both are finalized.
	if (!m1.fFinalized || !m2.fFinalized) {
		
	/*
	if (!m1.fFinalized)
	Error("TMD5::operator==(const TMD5&, const TMD5&)", "arg1.Final() not yet called");
	if (!m2.fFinalized)
	Error("TMD5::operator==(const TMD5&, const TMD5&)", "arg2.Final() not yet called");
		*/ 
		
		return kFALSE;
	}
	
	for (int i = 0; i < 16; i++)
		if (m1.fDigest[i] != m2.fDigest[i])
			return kFALSE;
		
		return kTRUE;
}


//#endif // WIN32
