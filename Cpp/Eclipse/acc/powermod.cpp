#include <iostream>
using namespace std;

int powmod( long long b, int p, int m )
{
    long long r = 1;
    for( int i = ( 1 << 30 ); i; i >>= 1 )  {
        cout << i << endl;
        r *= r; r %= m;
        if( p & i )     { r *= b; r %= m; }
    }
    return ( int )r;
}

int main()
{
    int p, m;
    long long b;
    while(cin >> b >> p >> m) {
        int x = powmod(b, p, m);
        cout << x << endl;
    }
    return 0;
}
