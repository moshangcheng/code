#include <iostream>
using namespace std;

bool isp[1000002];
int semi[1000002];

int main() {
    int x, y, n;
    memset(isp, true, sizeof(isp));
    isp[1] = false;
    for( x = 1; x <= 1001; x += 4 ) if( isp[x] )
        for( y = x*x; y <= 1000001; y += 4*x )
            isp[y] = false;
    for( x = 1; x <= 1001; x += 4 ) if( isp[x] )
        for( y = x; x*y <= 1000001; y += 4 ) if( isp[y] )
            semi[x*y] = 1;
    for( x = 5; x <= 1000001; x ++ ) semi[x] += semi[x-1];
    while( cin >> n && n ) cout << n << ' ' << semi[n] << endl;
    return 0;
}
