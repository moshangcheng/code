#ifndef __ADAPTOR_H__
#define __ADAPTOR_H__

#include "consumer.h"
#include "buffer.h"

template<class I, class O>
struct Adaptor
{
	virtual size_t operator()(Consumer<I>* ipReader, Consumer<O>* opWriter, size_t iExpectedCount = 1) = 0;
};

template<class I, class O>
struct SimpleAdaptor: public Adaptor<I, O>
{
	size_t operator()(Consumer<I>* ipReader, Consumer<O>* opWriter, size_t iExpectedCount = 1)
	{
		if(ipReader == NULL || opWriter == NULL || iExpectedCount == 0)
		{
			return 0;
		}

		I* lpSrc = NULL;
		size_t lCount = ipReader->Get(&lpSrc, 10000);
		I* lpEnd = lpSrc + lCount;

		for(I* lpLineStart = lpSrc; lpLineStart < lpEnd; )
		{
			I* lpLineEnd = this->InputPause(lpLineStart, lpEnd);
			if(lpLineEnd)
			{
				
			}
		}
	}
};

#endif