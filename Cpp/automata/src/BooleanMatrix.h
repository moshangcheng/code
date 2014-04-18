#ifndef __BOOLEAN_MATRIX_H
#define __BOOLEAN_MATRIX_H

#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
#include <exception>

namespace CT
{

class BooleanMatrix
{
public:
	BooleanMatrix(size_t iRowCount, size_t iColumnCount, const bool* ipData = NULL)
		: mpData(NULL)
		, mRowCount(iRowCount)
		, mColumnCount(iColumnCount)
	{
		mpData = new bool[mRowCount * mColumnCount];
		if(ipData != NULL)
		{
			memcpy(mpData, ipData, sizeof(bool) * mRowCount * mColumnCount);
		}
		else
		{
			memset(mpData, 0, sizeof(bool) * mRowCount * mColumnCount);
		}
	}

	BooleanMatrix& operator = (const BooleanMatrix& obj)
	{
		mRowCount = obj.mRowCount;
		mColumnCount = obj.mColumnCount;
		mpData = new bool[mRowCount * mColumnCount];
		if(obj.mpData != NULL)
		{
			memcpy(mpData, obj.mpData, sizeof(bool) * mRowCount * mColumnCount);
		}
		return *this;
	}

	BooleanMatrix(const BooleanMatrix& obj)
	{
		*this = obj;
	}

	bool& operator () (size_t iRow, size_t iColumn)
	{
		return (mpData + iRow * mColumnCount)[iColumn];
	}

	const bool& operator () (size_t iRow, size_t iColumn) const
	{
		return (mpData + iRow * mColumnCount)[iColumn];
	}

	BooleanMatrix operator * (const BooleanMatrix& obj) const
	{
		if(obj.mRowCount != this->mColumnCount)
		{
			throw std::exception("cannot mulitply matrices");
		}

		BooleanMatrix lmResult(this->mRowCount, obj.mColumnCount);

		for(size_t i = 0; i < mRowCount; i++)
		{
			for(size_t j = 0; j < obj.mColumnCount; j++)
			{
				bool& lResut = lmResult(i, j);
				lResut = false;
				for(size_t k = 0; k < mColumnCount; k++)
				{
					lResut |= (*this)(i, k) & obj(k, j);
				}
			}
		}

		return lmResult;
	}

	BooleanMatrix operator | (const BooleanMatrix& obj) const
	{
		if(obj.mRowCount != this->mRowCount || obj.mColumnCount != this->mColumnCount)
		{
			throw std::exception("cannot or matrices");
		}

		BooleanMatrix lmResult(this->mRowCount, obj.mColumnCount);

		for(size_t i = 0; i < mRowCount; i++)
		for(size_t j = 0; i < mColumnCount; i++)
		{
			lmResult(i, j) = (*this)(i, j) | obj(i, j);
		}

		return lmResult;
	}

	BooleanMatrix operator & (const BooleanMatrix& obj) const
	{
		if(obj.mRowCount != this->mRowCount || obj.mColumnCount != this->mColumnCount)
		{
			throw std::exception("cannot and matrices");
		}

		BooleanMatrix lmResult(this->mRowCount, obj.mColumnCount);

		for(size_t i = 0; i < mRowCount; i++)
		for(size_t j = 0; i < mColumnCount; i++)
		{
			lmResult(i, j) = (*this)(i, j) & obj(i, j);
		}

		return lmResult;
	}

	BooleanMatrix operator ! () const
	{
		BooleanMatrix lmResult(this->mRowCount, this->mColumnCount);

		for(size_t i = 0; i < mRowCount; i++)
		for(size_t j = 0; i < mColumnCount; i++)
		{
			lmResult(i, j) = !(*this)(i, j);
		}

		return lmResult;
	}

	bool operator == (const BooleanMatrix& obj) const
	{
		if(obj.mRowCount != this->mRowCount || obj.mColumnCount != this->mColumnCount)
		{
			return false;
		}

		for(size_t i = 0; i < mRowCount; i++)
		for(size_t j = 0; j < mColumnCount; j++)
		{
			if((*this)(i, j) != obj(i, j))
			{
				std::cout << mRowCount << " " << mColumnCount << std::endl;
				std::cout << i << ", " << j << ": " << (*this)(i, j) << " " << obj(i, j) << std::endl;
				std::cout << this->ToSimpleString() << obj.ToSimpleString() << std::endl;
				return false;
			}
		}

		return true;
	}

	bool operator != (const BooleanMatrix& obj) const
	{
		return !(*this == obj);
	}

	size_t GetRowCount() const
	{
		return mRowCount;
	}

	size_t GetColumnCount() const
	{
		return mColumnCount;
	}

	bool Single() const
	{
		size_t sum = 0;
		for(size_t i = 0; i < mRowCount * mColumnCount; i++)
		{
			sum += mpData[i];
		}
		return sum == 1;
	}


	bool AllFalse() const
	{
		for(size_t i = 0; i < mRowCount * mColumnCount; i++)
		{
			if(mpData[i])
			{
				return false;
			}
		}
		return true;
	}
	
	bool AllTrue() const
	{
		for(size_t i = 0; i < mRowCount * mColumnCount; i++)
		{
			if(!mpData[i])
			{
				return false;
			}
		}
		return true;
	}

	BooleanMatrix Transport() const
	{
		BooleanMatrix lmResult(mColumnCount, mRowCount);
		for(size_t i = 0; i < mRowCount; i++)
		for(size_t j = 0; j < mColumnCount; j++)
		{
			lmResult(j, i) = (*this)(i, j);
		}
		return lmResult;
	}

	std::string ToSimpleString() const
	{
		std::string lResultString;
		for(size_t i = 0; i < mRowCount; i++)
		{
			if(i > 0)
			{
				lResultString.append("\n" );
			}

			for(size_t j = 0; j < mColumnCount; j++)
			{
				lResultString.append( (*this)(i, j) ? "1": "0" );
			}
		}
		return lResultString;
	}

	std::string ToString() const
	{
		std::string lResultString;
		for(size_t i = 0; i < mRowCount; i++)
		{
			for(size_t j = 0; j + 1 < mColumnCount; j++)
			{
				lResultString.append( (*this)(i, j) ? "true, ": "false, " );
			}
			lResultString.append( mColumnCount > 0 ? ( (*this)(i, mColumnCount - 1) ? "true\n": "false\n" ): "\n" );
		}
		return lResultString;
	}

	int Value() const
	{
		int sum = 0;
		for(int i = 0; i < mRowCount * mColumnCount; i++)
		{
			sum = 2 * sum + mpData[i];
		}
		return sum;
	}

	~BooleanMatrix()
	{
		if(mpData != NULL)
		{
			delete mpData;
			mpData = NULL;
		}
	}

private:
	size_t mRowCount;
	size_t mColumnCount;
	bool* mpData;
};

}

#endif