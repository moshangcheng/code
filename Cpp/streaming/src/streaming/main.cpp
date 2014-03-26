#include <ctime>
#include <iostream>


#include "Adaptor.h"
#include "Connector.h"
#include "LinkedReader.h"
#include "LinkedWriter.h"

using namespace std;
using namespace MDb;
using namespace Streaming;

int main()
{
	const int SIZE = 100 * 1000 * 1000;
	const int RESULT_SIZE = SIZE;
	// basic test
	/*{
		cout << "--- Basic Test\n\n";
		std::string lpStr = "abcdefghijklmn";
		char lResult[14];

		Buffer<char>* lpResultBuffer =
			ReaderFactory::FromArray(lpStr.c_str(), lpStr.length())
			->Pipe(new CharToInt())
			->Pipe(new IntToChar());
	
		size_t lCount = lpResultBuffer->Read(lResult, 14);
		for(size_t i = 0; i < lCount; i++)
		{
			std::cout << lResult[i] << std::endl;
		}

		delete lpResultBuffer;
	}

	// writer test
	{
		cout << "\n\n--- Writer Test\n\n";
		int* src = new int[SIZE];
		int* result = new int[SIZE];
		for(int i = 0; i < SIZE; i++) src[i] = i;

		clock_t start, end;
		start = clock();

		Buffer<int> *lpResultBuffer = WriterFactory::ToArray(result, RESULT_SIZE)->Pipe(new IntFromChar())->Pipe(new CharFromInt());
		size_t lCount = lpResultBuffer->Write(src, SIZE);
		lpResultBuffer->Flush();

		end = clock();
		cout << "\ntime: " << 1.0 * (end -start) / CLK_TCK << "\n";

		for(size_t i = 0; i < RESULT_SIZE; i++)
		{
			if(src[i] != result[i])
			{
				cout << "the " << i << " element not equal: " << src[i] << ", " << result[i] << "\n";
				//break;
			}
		}

		delete lpResultBuffer;
		delete [] src;
	}

	// reader test
	{
		cout << "\n\n--- Reader Test\n\n";
		int* src = new int[SIZE];
		int* result = new int[SIZE];
		for(int i = 0; i < SIZE; i++) src[i] = i;

		clock_t start, end;
		start = clock();

		Buffer<int> *lpResultBuffer =
			ReaderFactory::FromArray(src, SIZE)
			->Pipe(new IntToChar())
			->Pipe(new CharToInt());

		size_t lCount = lpResultBuffer->Read(result, RESULT_SIZE);

		end = clock();
		cout << "\ntime: " << 1.0 * (end -start) / CLK_TCK << "\n";

		// check result
		for(size_t i = 0; i < RESULT_SIZE; i++)
		{
			if(src[i] != result[i])
			{
				cout << "the " << i << " element not equal: " << src[i] << ", " << result[i] << "\n";
				//break;
			}
		}

		delete lpResultBuffer;
		delete [] result;
		delete [] src;
	}*/

	// connector test
	{
		cout << "\n\n--- Simple Connector Test\n\n";
		int* src = new int[SIZE];
		int* result = new int[SIZE];
		for(int i = 0; i < SIZE; i++) src[i] = i;

		clock_t start, end;
		start = clock();

		SimpleConnector<int, char> lConnector(ReaderFactory::FromArray(src, SIZE)
			, WriterFactory::ToArray(result, RESULT_SIZE)->Pipe(new IntFromChar())
			, new IntToChar());
		size_t lCount = lConnector.Run();
		

		end = clock();
		cout << "\ntime: " << 1.0 * (end -start) / CLK_TCK << "\n";

		// check result
		for(size_t i = 0; i < RESULT_SIZE; i++)
		{
			if(src[i] != result[i])
			{
				cout << "the " << i << " element not equal: " << src[i] << ", " << result[i] << "\n";
				//break;
			}
		}

		delete [] src;
		//delete [] result;
	}

	// copyconnector test
	/*{
		cout << "\n\n--- Copy Connector Test\n\n";
		int* src = new int[SIZE];
		int* result = new int[SIZE];
		for(int i = 0; i < SIZE; i++) src[i] = i;

		clock_t start, end;
		start = clock();

		CopyConnector<int> lConnector(
			ReaderFactory::FromArray(src, SIZE)
			, WriterFactory::ToArray(result, SIZE)->Pipe(new IntFromChar())->Pipe(new CharFromInt()));
		size_t lCount = lConnector.Run();
		

		end = clock();
		cout << "\ntime: " << 1.0 * (end -start) / CLK_TCK << "\n";

		// check result
		for(size_t i = 0; i < RESULT_SIZE; i++)
		{
			if(src[i] != result[i])
			{
				cout << "the " << i << " element not equal: " << src[i] << ", " << result[i] << "\n";
				//break;
			}
		}

		delete [] src;
		//delete [] result;
	}

	// multi-thread copyconnector test
	/*{
		cout << "\n\n--- Connector Test\n\n";
		int* src = new int[SIZE];
		int* result = new int[SIZE];
		for(int i = 0; i < SIZE; i++) src[i] = i;

		clock_t start, end;
		start = clock();

		SimpleConnector<int, char> lConnector(ReaderFactory::FromArray(src, SIZE)
			, WriterFactory::ToArray(result, RESULT_SIZE)->Pipe(new IntFromChar())
			, new IntToChar());
		size_t lCount = lConnector.Run();
		

		end = clock();
		cout << "\ntime: " << 1.0 * (end -start) / CLK_TCK << "\n";

		// check result
		for(size_t i = 0; i < RESULT_SIZE; i++)
		{
			if(src[i] != result[i])
			{
				cout << "the " << i << " element not equal: " << src[i] << ", " << result[i] << "\n";
				//break;
			}
		}

		delete [] src;
		//delete [] result;
	}*/

	return 0;
}