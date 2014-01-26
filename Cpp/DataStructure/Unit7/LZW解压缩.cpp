#include <iostream>
#include <fstream>
using namespace std;

class element {
private:
	friend void Decompress();
	friend void Output(int);
private:
	int prefix;
	unsigned char suffix;
};

const int codes = 4096, ByteSize = 8, excess = 4, alpha = 256, mask = 15;

unsigned char s[codes];
int size, LeftOver, status = 0;
element ht[codes];
ifstream in("out.txt", ios::binary);
ofstream out("despress.txt", ios::binary);

int main() {
	Decompress();
	return 0;
}

void Output(int code) {
	size = -1;
	while (code >= alpha) {
		s[++size] = ht[code].suffix;
		code = ht[code].prefix;
	}
	s[++size] = code;
	for (int i = size; i > -1; i--)
		out.put(s[i]);
}

bool GetCode(int& code) {
	unsigned char c, d;
	c = in.get();
	if (in.eof())
		return false;
	if (status)
		code = (LeftOver << ByteSize) | c;
	else {
		d = in.get();
		code = (c << excess) | (d >> excess);
		LeftOver = d & mask;
	}
	status = 1 - status;
	return true;
}

void Decompress() {
	int used = alpha;
	int pcode, ccode;
	if (GetCode(pcode)) {
		s[0] = pcode;
		out << s[0];
		size = 0;
		while (GetCode(ccode)) {
			if (ccode < used) {
				Output(ccode);
				if (used < codes) {
					ht[used].prefix = pcode;
					ht[used++].suffix = s[size];
				}
			} else {
				ht[used].prefix = pcode;
				ht[used++].suffix = s[size];
				Output(ccode);
			}
			pcode = ccode;
		}
	}
}

