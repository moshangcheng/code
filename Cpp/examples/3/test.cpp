#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>

const int UNIT = 8;
const int CHILDREN_COUNT = 1 << UNIT;

class TrieNode
{
public:
	char* mpBuffer;
	size_t mSize;
	TrieNode** mpChildren;

	TrieNode()
	{
		mpBuffer = NULL;
		mSize = 0;
		mpChildren = NULL;
	}

	~TrieNode()
	{
		if(mSize > 0)
		{
			delete [] mpBuffer;
		}
		mSize = 0;

		if(mpChildren != NULL)
		{
			for(size_t i = 0; i < CHILDREN_COUNT; i++)
			{
				if(mpChildren[i] != NULL)
				{
					delete mpChildren[i];
				}
			}
			delete [] mpChildren;
		}
	}

	const char* Find(size_t iKeyCurrent, const char* ipKey, size_t iKeyLength)
	{
		if(iKeyCurrent == (iKeyLength * 8 / UNIT - 1))
		{
			return mpBuffer;
		}
		else
		{
			if(mpChildren == NULL)
			{	
				return NULL;
			}

			unsigned int lA = iKeyCurrent * UNIT / 8;
			unsigned int lB = iKeyCurrent * UNIT % 8;
		
			unsigned int lCurrentKey = ((unsigned int)(*(ipKey + lA)) >> lB) & ((1 << UNIT) - 1);

			_ASSERT(lCurrentKey < CHILDREN_COUNT);
			
			if(mpChildren[lCurrentKey] == NULL)
			{
				return NULL;
			}

			return mpChildren[lCurrentKey]->Find(iKeyCurrent + 1, ipKey, iKeyLength);
		}
	}

	void Insert(size_t iKeyCurrent, const char* ipKey, size_t iKeyLength, const char* ipValue, size_t iValueLength)
	{
		if(iKeyCurrent == (iKeyLength * 8 / UNIT - 1))
		{
			if(mpBuffer == NULL)
			{
				mpBuffer = new char[iValueLength];
				memcpy(mpBuffer, ipValue, iValueLength);
				mSize = iValueLength;
			}
		}
		else
		{
			if(mpChildren == NULL)
			{
				mpChildren = new TrieNode*[CHILDREN_COUNT];
				memset(mpChildren, 0, sizeof(TrieNode*) * CHILDREN_COUNT);
			}

			unsigned int lA = iKeyCurrent * UNIT / 8;
			unsigned int lB = iKeyCurrent * UNIT % 8;
		
			unsigned int lCurrentKey = ((unsigned int)(*(ipKey + lA)) >> lB) & ((1 << UNIT) - 1);

			_ASSERT(lCurrentKey < CHILDREN_COUNT);

			if(mpChildren[lCurrentKey] == NULL)
			{
				mpChildren[lCurrentKey] = new TrieNode();
			}

			mpChildren[lCurrentKey]->Insert(iKeyCurrent + 1, ipKey, iKeyLength, ipValue, iValueLength);
		}
	}
};

struct StringCompare
{
	bool operator() (const std::string& a, const std::string& b) const
	{
		return a.compare(b) < 0;
	}
};

int main()
{
	TrieNode* lpRoot = new TrieNode();
	std::map<std::string, int, StringCompare> lSTDMap;

	bool lFlag = true;
	char lpKey[21];
	for(int i = 0; i < 10000; i++)
	{
		for(int j = 0; j < 20; j++)
		{
			lpKey[j] = (i * rand()  + j * rand() + rand()) % 26 + 'a';
		}
		lpKey[20] = '\0';

		lpRoot->Insert(0, lpKey, 20, (char*)&i, sizeof(int));
		const char* lAns = lpRoot->Find(0, lpKey, 20);
		lFlag &= (i == *(int*)lAns);
		//lSTDMap[lpKey] = i;
		//printf("%d %d\n", i, lSTDMap[lKeyString]);
		//lFlag &= (i == lSTDMap[lpKey]);
	}
	printf("The result is: %s\n", lFlag ? "Success" : "Fail");
	delete lpRoot;
	return 0;
}