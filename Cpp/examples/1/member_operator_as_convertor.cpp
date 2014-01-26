#include <iostream>
using namespace std;

template<class T>
class TC {
};

template<class T>
class A {
    public:
        typedef T type;
            operator A const& () {
                        return A();
                            }
};

int main() {
        A<int> a;
            a.operator A const& ();
                return 0;
}

