#include <iostream>

#include "adaptor.h"

using namespace std;


// In the ideal situation,
// Reader doesn't know its upstreams
//		IntReader r;
//		r.From(IntFromString).From(StringArray).From(File)
//		r.Read(data)
// Writer doesn't know its downstreams
//		IntWriter w;
//		w.To(IntToString).To(StringArray).To(File)
//		w.Write(data)

// But C++'s static type system doesn't allow this to be implemented
// Analysis
// In this form, the reader we use to read data is the first reader, and its upstreams are not cared.
// As as we see, it's also the first node constructed, all its upstreams are constructed after it.
// But in order to cascade buffers, Reader must has a member pointed to its upstream.
// Notice that the data type of upstream is not necessarily the same the current stream.
// Then LinkedReader shoulde be a template class which has two template parameters
// one is used to denote its type, and the other one is used to denote its upstream type
// So to consturct a Reader, we must know its type and its upstream type
// Then this is a paradox! We don't know its upstream type

// To solve this problem, we must construct its upstream first
// So we should write code as follows:
// IntReader r = FileReader.Pipe(ToStringArray).Pipe(StringToInt)

// Analogously, for Writer, we must construct its downstream first
// IntWriter w = FileWriter.Pipe(FromStringArray).Pipe(StringFromInt)

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
	Consumer<int> *lpBufferWriter = lBuffer.GetWriter();
	
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