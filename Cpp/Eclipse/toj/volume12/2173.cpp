#include <iostream>
#include <cmath>
using namespace std;

long long exGCD(long long a, long long b, long long &x, long long &y)
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
    long long x, y;
    long long ntest, A, B, C, K, K1, K2, X1, X2, Y1, Y2, X, Y, D;
    cin >> ntest;
    while(ntest-- > 0) {
        cin >> A >> B >> C >> X1 >> X2 >> Y1 >> Y2;
        if(X1 > X2 || Y1 > Y2) {
            cout << -1 << endl;
            continue;
        }
        if(A == 0 && B == 0) {
            if(C == 0) K = (X2 - X1 + 1) * (Y2 - Y1 + 1);
            else K = 0;
        }
        else {
            D = exGCD(A, B, X, Y);
            if(C % D != 0) {
                cout << -1 << endl;
                continue;
            }
            C /= D;     A /= D;     B /= D;
            X *= C;   Y *= C;
            if(A == 0 ) {
                if(Y <= Y2 && Y >= Y1) K = X2 - X1 + 1;
                else K = 0;
            }
            else if(B == 0) {
                if(X <= X2 && X >= X1) K = Y2 - Y1 + 1;
                else K = 0;
            }
            else {
                K1 = floor((Y2-Y)/A);  K2 = floor((X-X1)/B);  
                K =  (K1 < K2)? K1: K2;
                K1 = ceil((Y1-Y)/A);   K2 = ceil((X-X2)/B);  
                K +=  1 - ((K1 > K2)? K1: K2);
            }
        }
        if(K <= 0) {
            cout << -1 << endl;
            continue;
        }
        x = 1;  y = 1;
        while(x + y <= K ) {
            x += y;
            y = x - y;
        }
        cout << y << " " << x << endl;
    }
    return 0;
}
        
        
