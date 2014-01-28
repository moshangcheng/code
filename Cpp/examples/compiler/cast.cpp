#include <iostream>
using namespace std;

class Base {
public:
	int v;
	virtual void print() {
		cout << "base class\n";
	}
};

class A : public Base {
public:
};

class B : public Base {
public:
	int vb;
	void print() {
		cout << "class B\n";
	}
	void print1() {
		cout << vb << endl;
	}
};

int main() {
	Base* lpBase = new Base();
	lpBase->v = 1;

	B* lpB = static_cast<B*>(lpBase);
	lpB->print();
	lpB->print1();

	A* lpA = static_cast<A*>(lpBase);
	lpA->print();

	return 0;
}