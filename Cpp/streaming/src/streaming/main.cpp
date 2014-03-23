#include <ctime>
#include <iostream>
using namespace std;


#include "Adaptor.h"
#include "LinkedReader.h"

int main()
{
	{
		clock_t start, end;
		start = clock();

		const int SIZE = 10 * 1000 * 1000;
		int* src = new int[SIZE];
		for(int i = 0; i < SIZE; i++) src[i] = i;

		BufferReader<int> *lpResultBuffer = (new LinkedReader<int, int>(src, SIZE))->Pipe(new IntToChar())->Pipe(new CharToInt());

		int* result = NULL;
		size_t lCount = lpResultBuffer->Get(&result, SIZE);

	

		end = clock();
		cout << "\ntime: " << 1.0 * (end -start) / CLK_TCK << "\n";

		for(size_t i = 0; i < SIZE; i++)
		{
			if(src[i] != result[i])
			{
				cout << "the " << i << " element not equal\n";
				//break;
			}
		}

		delete lpResultBuffer;
		delete [] src;
	}

	{
		std::string lpStr = "abcdefghijklmn";
		char lResult[14];

		BufferReader<char>* lpResultBuffer =  (new LinkedReader<char, char>(lpStr.c_str(), lpStr.length()))->Pipe(new CharToInt())->Pipe(new IntToChar());
	
		size_t lCount = lpResultBuffer->Read(lResult, 14);
		for(size_t i = 0; i < lCount; i++)
		{
			std::cout << lResult[i] << std::endl;
		}
	}
	return 0;
}