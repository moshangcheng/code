#include <iostream>
using namespace std;

template <int n>
class TCBase {
public:
	void print() { cout << 3 << endl; }
};

template <class T, int n>
class TC: public TCBase<n> {
public:
	void nothing() {}
};



int main() {
	cout << "hello world\n";
	TC<int, 3> a1;
	TC<int, 4> a2;
	TC<int, 5> a3;
	TC<double, 3> b1;
	TC<double, 4> b2;
	TC<double, 5> b3;
	TC<char, 3> c1;
	TC<char, 4> c2;
	TC<char, 5> c3;
	a1.print();
	a2.print();
	a3.print();
	b1.print();
	b2.print();
	b3.print();
	c1.print();
	c2.print();
	c3.print();
	return 0;
}