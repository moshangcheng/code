#include <iostream>
using namespace std;

class Base {
private:
	int vb;
public:
	virtual void print() {
		cout << "Base \n";
	}
};

class Derived1: public Base {
private:
	int vd;
public:
	virtual void print() {
		cout << "Derived1 \n";
	}
};

class Derived2: public Base {
private:
	int vd;
public:
	virtual void print() {
		cout << "Derived2 \n";
	}
};

int main() {
	Derived1** lppD;
	Base** lppB;
	lppB[0] = new Derived2[3];
	lppB[0] = new Derived1[3];
	return 0;
}