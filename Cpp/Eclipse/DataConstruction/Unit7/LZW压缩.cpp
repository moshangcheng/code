#include <iostream>
#include <fstream>
using namespace std;
#include "ChainHashTable.h"

class element {
public:
	friend void Compress();
	operator unsigned long() const {
		return key;
	}
	element& operator=(unsigned long y) {
		key = y;
		return *this;
	}
private:
	int code;
	unsigned long key;
};

const int D = 4099, codes = 4096, ByteSize = 8, excess = 4, alpha = 256, mask1 =
		255, mask2 = 15;

int LeftOver, status = 0;

ifstream in("in.txt", ios::binary);
ofstream out("out.txt", ios::binary);

int main() {
	Compress();
	return 0;
}

void Output(unsigned long pcode) {
	unsigned char c, d;
	if (status) {
		d = pcode & mask1;
		c = (LeftOver << excess) | (pcode >> ByteSize);
		out.put(c);
		out.put(d);
		status = 0;
	} else {
		LeftOver = pcode & mask2;
		c = pcode >> excess;
		out.put(c);
		status = 1;
	}
}

void Compress() {
	ChainHashTable<element, unsigned long> h(D);
	element e;
	for (int i = 0; i < alpha; i++) {
		e.key = i;
		e.code = i;
		h.Insert(e);
	}
	int used = alpha;

	unsigned char c;
	c = in.get();
	unsigned long pcode = c;
	if (!in.eof()) {
		do {
			c = in.get();
			if (in.eof())
				break;
			unsigned long k = (pcode << ByteSize) + c;
			if (h.Search(k, e))
				pcode = e.code;
			else {
				Output(pcode);
				if (used < codes) {
					e.code = used++;
					e.key = (pcode << ByteSize) | c;
					h.Insert(e);
				}
				pcode = c;
			}
		} while (1);
		Output(pcode);
		if (status) {
			c = LeftOver << excess;
			out.put(c);
		}
	}
}

