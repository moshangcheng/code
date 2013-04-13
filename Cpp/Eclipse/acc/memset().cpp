#include <iostream>
using namespace std;

struct pix { char c; int a, b;};

int main()
{    
    int b[10];
    cout << sizeof(b) << endl;
    memset(b, 10, sizeof(b));
    for(int i = 0; i < 5; i++) cout << hex << b[i] <<" ";
    cout << endl << endl;
    
    int c[5][5];
    cout << sizeof(c) << endl;
    memset(c, 10, sizeof(c));
    for(int i = 0;i < 5; i++) {
        for(int j = 0;j < 5; j++) cout << hex << c[i][j] <<" ";
        cout << endl;
    }
    cout << endl;
    
    pix a[5];
    cout << dec << sizeof(a) << " " << sizeof(a[0]) << endl;
    memset(a, '0', sizeof(a));
    for(int i = 0; i < 5;i++) 
    cout << a[i].a << " " << a[i].b << " " << a[i].c <<endl;
    cout << endl;
    
    int size;
    cin >> size;
    int* s = new int[size];
    cout << sizeof(s) << endl;
    memset(s, 0, sizeof(s)*size);
    for(int i = 0; i < size; i++) cout << s[i] << ' ';
    cout << endl;
    
    system("pause");
}
