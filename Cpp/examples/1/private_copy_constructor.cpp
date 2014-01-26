#include <iostream>
using namespace std;

class B {
public:
};

class A {
public:
    A(const B& b) {}
    operator B() { return B(); }
    operator B() const { return B(); }
private:
    A(const A& a) {}
    A() {}
};

class C {
public:
    C(A a) {}
};

void NeedA(A a) {}


int main() {
    B b;
    A a(b);
    C c(B(a));
    NeedA(b);
    return 0;
}

