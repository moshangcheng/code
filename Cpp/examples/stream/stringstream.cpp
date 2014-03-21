#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/*
 * stringstream has hidden ios::rdbuf()
 * to change its internal buffer, use obj.ios::rdbuf()
 * see zorba source code: src/util/icu_streambuf.h
 * http://stackoverflow.com/questions/5289774/is-it-ever-moral-to-override-a-nonvirtual-function
 */
int main()
{
	std::stringstream ss1, ss2;
	ss1.std::ios::rdbuf(ss2.rdbuf());
	ss1 << "ss1\n";
	std::string str;
	char c1, c2;
	ss1 >> c1;
	ss2 >> c2;
	cout << ss2.str();
	return 0;
}
