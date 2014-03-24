#ifndef __BUFFER_H
#define __BUFFER_H

#include <iostream>

/* why not std::basic_stringbuf
   - too complicated
   - does't have APIs for non-copy read/write
   - for C++11, we have std::move
*/


// read and write are dual operations
// read is operation of occupied space
// write is operation of not occupied space


template<typename T>
class Buffer
{
public:

	// constructor for read/write buffer
	// to reduce initial response time, intial capacity is small
	Buffer(size_t iMaxBufferSize = SIZE_MAX)
		: mpData(NULL)
		, mpCurrent(NULL)
		, mpEnd(NULL)
		, mCapacity(10)
		, mMaxCapacity(iMaxBufferSize)
		, mVersion(0)
		, mTotalGetCount(0)
		, mTotalPutCount(0)
	{
		mpData = new T[mCapacity];
		mpCurrent = mpEnd = mpData;

		std::cout << "Read/Write buffer constructor\n";
	}

	// constructor for write buffer
	Buffer(T* ipArray, size_t n)
		: mpData(NULL)
		, mpCurrent(NULL)
		, mpEnd(NULL)
		, mCapacity(n)
		, mMaxCapacity(n)
		, mVersion(0)
		, mTotalGetCount(0)
		, mTotalPutCount(0)
	{
		if(ipArray != NULL && mCapacity > 0)
		{
			mpData = ipArray;
			// set status
			mpCurrent = mpEnd = mpData;
		}
		else
		{
			mCapacity = mMaxCapacity = 0;
		}

		std::cout << "Write buffer constructor\n";
	}

	// constructor for read buffer
	Buffer(const T* ipArray, size_t n)
		: mpData(NULL)
		, mpCurrent(NULL)
		, mpEnd(NULL)
		, mCapacity(n)
		, mMaxCapacity(n)
		, mVersion(0)
		, mTotalGetCount(0)
		, mTotalPutCount(0)
	{
		if(ipArray != NULL && mCapacity > 0)
		{
			mpData = new T[mCapacity];

			// set status
			mpCurrent = mpEnd = mpData;

			// copy data
			mpEnd = mpData + n;
			for(T *lpDest = mpData; lpDest < mpEnd;)
			{
				*(lpDest++) = *(ipArray++);
			}
		}
		else
		{
			mCapacity = mMaxCapacity = 0;
		}

		std::cout << "Read buffer constructor\n";
	}

	const T* Current() const
	{
		return mpCurrent;
	}

	const T* End() const
	{
		return mpEnd;
	}

	size_t Capacity() const
	{
		return mCapacity;
	}

	size_t Size() const
	{
		return mpEnd - mpCurrent;
	}

	size_t FreeSpaceSize()
	{
		if(mpEnd == mpCurrent)
		{
			mpCurrent = mpEnd = mpData;
			mVersion++;
		}
		return mpData + mCapacity - mpEnd;
	}

	size_t GetTotalGetCount() const
	{
		return mTotalGetCount;
	}

	size_t GetTotalPutCount() const
	{
		return mTotalPutCount;
	}

	// do nothing
	virtual bool Flush()
	{
		return false;
	}

	// Get data from buffer
	virtual size_t Get(T** p, size_t n = 1)
	{
		if(n == 0)
		{
			*p = NULL;
			return 0;
		}

		*p = mpCurrent;
		size_t lCount = n < Size() ? n: Size();
		mpCurrent += lCount;
		mTotalGetCount += lCount;
		return lCount;
	}

	virtual size_t Read(T* p, size_t n = 1)
	{
		if(p == NULL || n == 0)
		{
			return 0;
		}

		size_t lCount = Size() < n ? Size(): n;

		for(const T* lpEnd = mpCurrent + lCount; mpCurrent < lpEnd;)
		{
			*(p++) = *(mpCurrent++);
		}
		mTotalGetCount += lCount;
		return lCount;
	}

	// Get the pointer to free space which will be filled by caller
	virtual size_t Put(T** p, size_t n = 1)
	{
		if(n == 0)
		{
			*p = NULL;
			return NULL;
		}

		// try to allocate memory
		More(n);
		size_t lCount = n < FreeSpaceSize() ? n: FreeSpaceSize();
		*p = mpEnd;
		mpEnd += lCount;
		mTotalPutCount += lCount;
		return lCount;
	}

	virtual size_t Write(T* p, size_t n = 1)
	{
		if(p == NULL || n == 0)
		{
			return 0;
		}

		size_t lCount = FreeSpaceSize() < n ? FreeSpaceSize(): n;

		for(const T* lpNewEnd = mpEnd + lCount; mpEnd < lpNewEnd;)
		{
			*(mpEnd++) = *(p++);
		}
		mTotalPutCount += lCount;
		return lCount;
	}

	// Go backward
	virtual bool UnGet(size_t n = 1)
	{
		if(n > mpCurrent - mpData)
		{
			return false;
		}
		mpCurrent -= n;
		mTotalGetCount -= n;
		return true;
	}

	// Go backward
	virtual bool UnPut(size_t n = 1)
	{
		if(n > Size())
		{
			return false;
		}
		mpEnd -= n;
		mTotalPutCount -= n;
		return true;
	}

	// used to check validity of pointer returned by Get()/Put()
	// when objects in buffer are rearranged, version number is incremented
	size_t Version() const
	{
		return mVersion;
	}


	// require memory to save more n elements
	void More(size_t n = 0)
	{
		if(mpEnd + n <= mpData + mCapacity)
		{
			return;
		}
		
		T* lpNewBuffer = mpData;

		// check buffer capacity
		size_t lExpectedCapacity = n + Size();
		if(lExpectedCapacity > mCapacity && (mMaxCapacity == 0 || mCapacity < mMaxCapacity))
		{
			std::cout << "--- reallocate buffer " <<  this << " , old buffer size is: " << mCapacity << "\n";
			
			// reallocate memory, use the strategy which is used in string::append and strstreambuf
			mCapacity = (mCapacity / 2 > lExpectedCapacity / 3) ? mCapacity * 3 / 2: lExpectedCapacity;

			if(mMaxCapacity > 0 && mCapacity > mMaxCapacity)
			{
				// reach the max capacity
				mCapacity = mMaxCapacity;
			}

			std::cout << "--- reallocate buffer " <<  this << " , new buffer size is: " << mCapacity << "\n\n";
			lpNewBuffer = new T[mCapacity];
		}

		if(lpNewBuffer != mpCurrent)
		{
			// update version number
			mVersion++;

			// copy
			for(T *i = mpCurrent, *j = lpNewBuffer; i < mpEnd;)
			{
				*(j++) = *(i++);
			}

			// if memory is newly allocated, delete old memory
			if(lpNewBuffer != mpData)
			{
				delete [] mpData;
				mpData = lpNewBuffer;
			}

			//set status
			mpEnd = mpData + (mpEnd - mpCurrent);
			mpCurrent = mpData;
		}
	}

	virtual ~Buffer()
	{
		std::cout << "Buffer destructor, version number is: " << mVersion << " \n";

		if(mCapacity > 0 && mpData != NULL)
		{
			delete [] mpData;
			mCapacity = 0;
			mpData = mpCurrent = mpEnd = NULL;
		} 
	}

private:

	T* mpData;
	T* mpCurrent;
	T* mpEnd;

	size_t mCapacity;
	size_t mMaxCapacity;
	size_t mVersion;

	size_t mTotalGetCount;
	size_t mTotalPutCount;

	Buffer(const Buffer<T>& irBuffer) {}
};

#endif