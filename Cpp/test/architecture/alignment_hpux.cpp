#include <iostream>
using namespace std;

struct ArrayStruct {
//    union {
    char data[9];
//    long long dummy;
//    };
};

struct Test {
    bool a;
    ArrayStruct  b;
    int c;
};

int main() {
    ArrayStruct a[10];
    Test b;
    ArrayStruct* a1 = &b.b;
    a1->data[0]
    //printf ("%p\n", &b.b);
    //printf ("%p\n", &b.c);
    //printf("%p\n", &a[1]);

    //*reinterpret_cast<int *>(p) = 1;

    //printf("%d, %p\n", *p, p);

};
