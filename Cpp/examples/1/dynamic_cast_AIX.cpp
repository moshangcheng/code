#include <iostream>

class Base {
    virtual void VFunc() {
    }
};

class Child : public Base {
};

int main() {
    Child* a = new Child();
    Base* b = a;
    Child* c = dynamic_cast<Child*>(b);
    //if not built with -qrtti, the value of c would 0
    std::cout << c << std::endl;
    Base* pB = new Base();
    Child* pC = dynamic_cast<Child*>(pB);
    std::cout << pC << std::endl;
    return 0;
}

