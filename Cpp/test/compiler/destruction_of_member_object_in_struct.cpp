#include <iostream>
using namespace std;

class A {
public:
	A() {
		cout << "construct class A" << endl;
	}
	~A() {
		cout << "destruct class A" << endl;
	}
};

struct B {
	int v;
	A a;
};

int main() {
	B* lpB = new B();
	delete lpB;
	return 0;
}