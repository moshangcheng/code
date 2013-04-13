#include <iostream>
#include <math.h>
using namespace std;
#include "HashTable.h"

const int Maxrand = 1000000;

class element {
public:
	element(int d = 0, long k = 0) :
		data(d), key(k) {
	}
	operator long() const {
		return key;
	}
	friend ostream& operator<<(ostream&, const element&);
	element& operator=(long y) {
		key = y;
		return *this;
	}
private:
	int data;
	long key;
};

ostream& operator<<(ostream& out, const element& t) {
	out << t.data << "-" << t.key << "  ";
	return out;
}

int main() {
	HashTable<element, int> H(11);
	for (int i = 0; i < 10; i++) {
		element Ele(i, i * 11 + i / 3);
		cout << Ele << endl;
		H.Insert(Ele);
	}
	element Ele;
	H.Delete(22, Ele);
	cout << endl << Ele << endl << endl;
	H.Output();
	system("pause");
	return 0;
}

