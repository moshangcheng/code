#include <iostream>
using namespace std;

class A {
private:
    A (const A&);
public:
    A (int i);
};

void NeedA(A a) {}

int main() {
    NeedA(3);
    return 0;
}

