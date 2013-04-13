#include <iostream>
#include <cmath>
using namespace std;

int exGCD(int a, int b, int &x, int &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int r = exGCD(b, a % b, x, y);
    int t = x;
    x = y;
    y = t - a / b * y;
    return r;
}

int main()
{
    bool flag;
    int x, y, z, n, x0, y0, d0, z0, d, r, u, v, X, Y, Z;
    while(cin >> x >> y >> z >> n) {
        d = exGCD(x, y, x0, y0);
        r = exGCD(d, z, d0, z0);
        if(n % r != 0) {
            cout << -1 << endl;
            continue;
        }
        flag = 0;
        for(u = ceil(1.0*r*z0/d); ; u++) {
            Z = (d*u/r - z0)*n/r;
            for(v = floor(1.0*y0*(d0+z*u/r)*d/x); ; v--) {
                Y = (y0*(d0+z*u/r) - x*v/d)*n/r;
                X = (x0*(d0+z*u/r) + y*v/d)*n/r;
                if(X < 0) break;
                flag = 1;
                break;
            }
            if(flag) break;
        }
        if(flag)
        cout << X << " " << Y << " " << Z << endl;
        else cout << -1 << endl;
    }
    return 0;
}
