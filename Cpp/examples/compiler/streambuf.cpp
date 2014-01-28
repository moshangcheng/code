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

	/*std::stringstream ss1, ss2;
	ss1.std::ios::rdbuf(ss2.rdbuf());
	ss1 << "ss1\n";
	std::string str;
	char c1, c2;
	ss1 >> c1;
	ss2 >> c2;
	cout << ss2.str();*/
	return 0;
}
