#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const char* gpStr = "AbcdefghijAbcdefghijAbcdefghijAbcdefghij";

int main()
{
	stringstream ss;
	for(int i = 0; i < 100; i++)
	{
		ss << gpStr;
	}

	string str;
	char c1, c2;
	ss >> c1 >> c2;
	cout << c1 << " " << c2 << endl;

	return 0;
}