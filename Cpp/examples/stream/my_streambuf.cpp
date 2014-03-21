#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

class MyStreamBuf : public stringbuf
{
public:
	int_type underflow()
	{
		cout << "MyStreamBuf underflow" << std::endl;
		return stringbuf::underflow();
	}

	streamsize xsgetn(char_type* _Ptr, streamsize _Count)
	{
		std::cout << "MyStreamBuf xsgetn" << std::endl;
		return stringbuf::xsgetn(_Ptr, _Count);
	}


	int_type uflow()
	{
		std::cout << "MyStreamBuf uflow" << std::endl;
		return stringbuf::uflow();
	}
};


int main(int argc, const char * argv[])
{
	MyStreamBuf buf;
	std::iostream stream(&buf);

	stream << "abcde";

	char lBuf[100] = {'\0'};
	cout << stream.get();
	stream.read(lBuf, 100);
	std::cout<< lBuf << std::endl;

	return 0;
}
