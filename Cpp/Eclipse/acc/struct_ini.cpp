#include <iostream>
using namespace std;

struct cc { char c[5]; int a; };

int main()
{
    cc c1 = {"aaaa", 5}, c2;
    cout << sizeof(cc) << endl;
    cout << c1.c << "," << c1.a << endl;
    memcpy(&c2, &c1, sizeof(cc));
    cout << c2.c << "," << c2.a << endl;
    system("pause");
    return 0;
}
    
    
