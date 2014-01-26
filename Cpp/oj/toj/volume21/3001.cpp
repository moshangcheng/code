#include <iostream>
#include <cmath>
using namespace std;

typedef long long ll;
ll exGCD(ll a, ll b, ll &x, ll &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll r = exGCD(b, a % b, x, y);
    ll t = x;
    x = y;
    y = t - a / b * y;
    return r;
}

int main()
{
    ll z, x, y, d, u, v, x0, y0;
    while(cin >> x >> y) {
        if(x == 0 && y == 0) break;
        d = exGCD(x, y, x0, y0);
        if(d != 1) {
            cout << "Inf\n";
            continue;
        }
        z = x*y - x - y;
        cout << z << endl;
    }
    return 0;
}
    
    
    
    
