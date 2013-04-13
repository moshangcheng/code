#include <iostream>
using namespace std;

int main()
{
    unsigned long long r, n;
    while(cin >> r >> n) 
    if( r == 0) {
        if( n > 0) cout << 2*n << endl;
        else cout << 1 << endl;
    }
    else if( n == 0) cout << 2 << endl;
    else cout << (n+1)*(n+2)/2 << endl;
    return 0;
}
