#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int a[1000], b[1000], p[1000];
    a[0] = 2;   b[0] = 3;     p[0] = 1;
    int i = 0, j = 0, num = 1, x;
    while(num < 20) {
        x = a[i] < b[j] ? a[i] : b[j];
        if( x == a[i]) i++;
        if( x == b[j]) j++;
        a[num] = 2*x;
        b[num] = 3*x;
        p[num++] = x;
    }
    for(int k = 0; k < 20; k++) cout << p[k] << endl;
    system("pause");
    return 0;
}
        
    
