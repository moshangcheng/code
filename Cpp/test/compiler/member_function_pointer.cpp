#include <iostream>
using namespace std;

class A {
public:
	void fa() {
		cout << "hello function a\n";
	}

	void fb() {
		cout << "hello function b\n";
	}
};

typedef void (A::*AVoidF)();

int main() {
	A a;
	AVoidF f1 = &A::fa;
	(a.*f1)();
	f1 = &A::fb;
	(a.*f1)();
	return 0;
}