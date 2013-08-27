#include <iostream>
using namespace std;

class A {
private:
	void privateFunc() {}
protected:
	void protectedFunc() {}
public:
	void publicFunc(A& a) {
		a.privateFunc();
		a.protectedFunc();
		//a.publicFunc();
	}
};

int main() {
	A a1;
	A a2;
	a2.publicFunc(a1);
	return 0;
}