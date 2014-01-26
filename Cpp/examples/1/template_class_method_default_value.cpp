#include <iostream>
#include "template.hpp"

class A;


class C {
public:
    TemplateClass<A> lTA;
    C()
    {
       lTA.Run(); 
    }
    TemplateClass<A> get() {
        return lTA;
    }
};


class A {
public:
    void Run() {
        std::cout << "hello\n";
    }
};


int main() {
    C c;
    return 0;
}
