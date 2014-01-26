#include <iostream>
using namespace std;

class Base {
private:
    int vb;
    int va;
public:
    virtual void print() {
        cout << "Base \n";
    }
};

class Derived: public Base {
private:
    int vd;
public:
    virtual void print() {
        cout << "Derived \n";
    }
};

int main() {
    cout << sizeof(int) << endl;
    cout << sizeof(Base) << endl;
    cout << sizeof(Derived) << endl;
    return 0;
}

