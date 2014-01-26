#include <iostream>
using namespace std;


template<class T>
class Outer {
public:
    class Inner {
    public:
        int v;
        Inner(int iv): v(iv) {}
    }
};

int main() {
    Outer<int>::Inner inner(3);
    std::cout << inner.v << std::endl;
    return 0;
}
