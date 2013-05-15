#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <list>

class TrieNode
{
public:
	char* mpBuffer;
	size_t mSize;
	std::list<std::pair<char, TrieNode*> > mpChildren;

	TrieNode()
	{
		mpBuffer = NULL;
		mSize = 0;
	}

	~TrieNode()
	{
		if(mSize > 0)
		{
			delete [] mpBuffer;
		}
		mSize = 0;

		if(!mpChildren.empty())
		{
			for(std::list<std::pair<char, TrieNode*> >::iterator cnt = mpChildren.begin(); cnt != mpChildren.end(); cnt++)
			{
				delete cnt->second;
			}
		}
	}

	const char* Find(size_t iKeyCurrent, const char* ipKey, size_t iKeyLength)
	{
		if(iKeyCurrent == iKeyLength)
		{
			return mpBuffer;
		}
		else
		{
			if(mpChildren.empty())
			{	
				return NULL;
			}
			
			char lCurrentKey = *(ipKey + iKeyCurrent);

			std::list<std::pair<char, TrieNode*> >::iterator cnt = mpChildren.begin();
			while(cnt != mpChildren.end())
			{
				if(cnt->first == lCurrentKey)
				{
					break;
				}
				cnt++;
			}

			if(cnt == mpChildren.end())
			{
				return NULL;
			}

			return cnt->second->Find(iKeyCurrent + 1, ipKey, iKeyLength);
		}
	}

	void Insert(size_t iKeyCurrent, const char* ipKey, size_t iKeyLength, const char* ipValue, size_t iValueLength)
	{
		if(iKeyCurrent == iKeyLength)
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
			char lCurrentKey = *(ipKey + iKeyCurrent);

			std::list<std::pair<char, TrieNode*> >::iterator cnt = mpChildren.begin();
			while(cnt != mpChildren.end())
			{
				if(cnt->first == lCurrentKey)
				{
					break;
				}
				cnt++;
			}
			
			TrieNode* lpTrieNode;
			if(cnt == mpChildren.end())
			{
				lpTrieNode = new TrieNode();
				mpChildren.push_back(std::pair<char, TrieNode*>(lCurrentKey, lpTrieNode));
			}
			else
			{
				lpTrieNode = cnt->second;
			}

			return lpTrieNode->Insert(iKeyCurrent + 1, ipKey, iKeyLength, ipValue, iValueLength);
		}
	}
};

int main()
{
	TrieNode* lpRoot = new TrieNode();

	bool lFlag = true;
	char lpKey[21];
	for(int i = 0; i < 100000; i++)
	{
		for(int j = 0; j < 20; j++)
		{
			lpKey[j] = (i * rand()  + j * rand() + rand()) % 26 + 'a';
		}
		lpKey[20] = '\0';

		lpRoot->Insert(0, lpKey, 20, (char*)&i, sizeof(int));
		const char* lAns = lpRoot->Find(0, lpKey, 20);
		//printf("%d %d\n", i, *(int*)lAns);
		lFlag &= (i == *(int*)lAns);
	}
	printf("The result is: %s\n", lFlag ? "Success" : "Fail");
	delete lpRoot;
	return 0;
}