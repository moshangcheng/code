#include <iostream>
#include <fstream>
using namespace std;

int main() {
	string a("111111111111111111111111111111111111111111111111111111111111111111");
	for(int i = 0; i < 1000000; i++) {
		ofstream out("output.txt", ofstream::app);
		out << a << endl;
		out.close();
	}
	return 0;
}

