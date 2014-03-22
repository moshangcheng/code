#include <iostream>

#include "adaptor.h"

using namespace std;

int main()
{
	const int SIZE = 10000;
	const int EACH = 1000;

	int v[SIZE];
	for(int i = 0; i < SIZE; i++)
	{
		v[i] = i;
	}

	Buffer<int> lBuffer(SIZE);
	Consumer<int> *lpBufferReader = lBuffer.GetReader();
	Consumer<int> *lpBufferWriter = lBuffer.GerWriter();
	
	cout << lpBufferReader->Size() << " " << lpBufferWriter->Size() << endl;

	// get write buffer
	{
		int *lpWriter = NULL;
		int lCount = lpBufferWriter->Get(&lpWriter, EACH);
		for(int i = 0; i < lCount; i++)
		{
			lpWriter[i] = v[i];
		}
		lpBufferWriter->UnGet(3);
	}

	// get read buffer
	{
		int *lpReader = NULL;
		int lCount = lpBufferReader->Get(&lpReader, EACH);
		for(int i = 0; i < lCount; i++)
		{
			cout << lpReader[i] << " ";
		}
		cout << endl;
	}

	cout << lpBufferReader->Size() << " " << lpBufferWriter->Size() << endl;

	delete lpBufferReader;
	delete lpBufferWriter;

	return 0;
}