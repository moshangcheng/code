#include <iostream>
#include <string>
using namespace std;

void replace(string & strBig, const string & strsrc, const string &strdst) {
	string::size_type pos = 0;
	string::size_type srclen = strsrc.size();
	string::size_type dstlen = strdst.size();
	while ((pos = strBig.find(strsrc, pos)) != string::npos) {
		strBig.replace(pos, srclen, strdst);
		pos += dstlen;
	}
}

int main() {
	string a, b, s;
	while (getline(cin, a)) {
		getline(cin, b);
		while (getline(cin, s, '\n')) {
			replace(s, a, b);
			cout << s << endl;
		}
	}
	return 0;
}

