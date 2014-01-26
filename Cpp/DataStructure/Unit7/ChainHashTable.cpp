#include <iostream>
#include <math.h>
using namespace std;
#include "ChainHashTable.h"

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
private:
	int data;
	long key;
};

ostream& operator<<(ostream& out, const element& t) {
	out << t.data << "-" << t.key;
	return out;
}
int main() {
	ChainHashTable<element, long> L;
	for (int i = 0; i < 100; i++) {
		element Ele(rand() % Maxrand, i);
		L.Insert(Ele);
	}
	cout << L;
	element Ele;
	if (L.Search(34, Ele))
		cout << Ele << endl;
	L.Delete(2, Ele);
	cout << Ele << endl;
	system("pause");
	return 0;
}
