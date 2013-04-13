#include <iostream>
#include <math.h>
using namespace std;
#include "SkipList.h"

const int Maxrand = 1000000;
const int Large = 100000000;

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
	out << t.data << "-" << t.key << endl;
	return out;
}

int main() {
	SkipList<element, long> L(100000000);//初始化一个很大的key值
	for (int i = 0; i < 10; i++) {
		element Ele(rand() % Maxrand, i);
		L.Insert(Ele);
	}
	cout << L << endl;
	element x;
	L.Delete(2, x);
	cout << x << " " << L << endl;
	system("pause");
	return 0;
}
