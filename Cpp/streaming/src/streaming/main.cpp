#include <ctime>
#include <iostream>
using namespace std;


#include "Adaptor.h"
#include "Connector.h"
#include "LinkedReader.h"
#include "LinkedWriter.h"

int main()
{
	// basic test
	{
		std::string lpStr = "abcdefghijklmn";
		char lResult[14];

		Buffer<char>* lpResultBuffer = ReaderFactory::FromArray(lpStr.c_str(), lpStr.length())->Pipe(new CharToInt())->Pipe(new IntToChar());
	
		size_t lCount = lpResultBuffer->Read(lResult, 14);
		for(size_t i = 0; i < lCount; i++)
		{
			std::cout << lResult[i] << std::endl;
		}

		delete lpResultBuffer;
	}

	// reader test
	{
		const int SIZE = 10 * 1000 * 1000;
		int* src = new int[SIZE];
		for(int i = 0; i < SIZE; i++) src[i] = i;

		clock_t start, end;
		start = clock();

		Buffer<int> *lpResultBuffer = ReaderFactory::FromArray(src, SIZE)->Pipe(new IntToChar())->Pipe(new CharToInt());

		int* result = NULL;
		size_t lCount = lpResultBuffer->Get(&result, SIZE);

		end = clock();
		cout << "\ntime: " << 1.0 * (end -start) / CLK_TCK << "\n";

		// check result
		for(size_t i = 0; i < SIZE; i++)
		{
			if(src[i] != result[i])
			{
				cout << "the " << i << " element not equal\n";
				break;
			}
		}

		delete lpResultBuffer;
		delete [] src;
	}

	// writer test
	{
		
	}

	// connector test
	{
		const int SIZE = 10 * 1000 * 1000;
		int* src = new int[SIZE];
		int* result = new int[10];
		for(int i = 0; i < SIZE; i++) src[i] = i;

		clock_t start, end;
		start = clock();

		Buffer<char> *lpInputBuffer = ReaderFactory::FromArray(src, SIZE)->Pipe(new IntToChar());
		Buffer<char> *lpOutputBuffer = WriterFactory::ToArray<int>(result, 10)->Pipe(new IntFromChar());
		SimpleConnector<char> lConnector(lpInputBuffer, lpOutputBuffer, 512);
		size_t lCount = lConnector.Run();
		

		end = clock();
		cout << "\ntime: " << 1.0 * (end -start) / CLK_TCK << "\n";

		// check result
		for(size_t i = 0; i < SIZE; i++)
		{
			if(src[i] != result[i])
			{
				cout << "the " << i << " element not equal\n";
				break;
			}
		}

		delete lpInputBuffer;
		delete lpOutputBuffer;

		delete [] src;
		//delete [] result;
	}

	return 0;
}