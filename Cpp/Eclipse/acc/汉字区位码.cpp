#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

inline int JN(char c) {
	return c & 255;
}

inline int GB(char c) {
	return (c - 0x8080) & 255;
}

inline int QW(char c) {
	return (c - 0xA0A0) & 255;
}

int main() {
	string s;
	ifstream in("in.txt");
	ofstream out("out.txt");
	out.fill('0');
	out.setf(ios::right);
	while (in >> s) {
		for (int i = 0; i < s.size(); i += 2) {
			out << s.substr(i, 2) << endl;
			out << "机内码 " << hex << setw(2) << JN(s[i]) << setw(2) << JN(s[i
					+ 1]) << "	";
			out << "国标码 " << hex << setw(2) << GB(s[i]) << setw(2) << GB(s[i
					+ 1]) << "	";
			out << "区位码 " << dec << setw(2) << QW(s[i]) << setw(2) << QW(s[i
					+ 1]) << "\n\n\n";
		}
	}
	return 0;
}
