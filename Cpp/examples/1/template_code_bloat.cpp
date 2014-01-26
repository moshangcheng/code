#include <iostream>
using namespace std;

template <int n>
class TCBase {
public:
    void print() { cout << n << endl; }
};

template <class T, int n>
class TC {//: public TCBase<n> {
public:
    void nothing() {}
    void print() { cout << n << endl; }
};



int main() {
    cout << "hello world\n";
    TC<int, 3> a1;
    TC<int, 4> a2;
    TC<double, 3> b1;
    TC<double, 4> b2;
    TC<double, 5> b3;
    a1.print();
    a2.print();
    b1.print();
    b2.print();
    b3.print();
    return 0;
}

