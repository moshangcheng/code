#include <iostream>
using namespace std;

int gcd(int m, int n)
{
    while(m) {
        int t = n%m;
        n = m;
        m = t;
    }
    return n;
}

int main()
{
    char c;
    int N, num, a, b, d, x;
    cin >> N;
    while(N-- >0) {
        cin >> a >> c >> b >> num;
        a = a*100 + b;
        b = 100;
        d = gcd(a, b);
        a = a/d;  b = b/d;
        for(int i = 0; i < num; i++) {
            cin >> x;
            if(i == 0) d = x;
            else d = gcd(d, x);
        }
        while(b % 2 == 0) b/= 2;
        while(d % 2 == 0) d/=2;
        if( a % d != 0 || b != 1) cout << "no\n";
        else cout << "yes\n";
    }
    return 0;
}
        
        
        
        
        
        
    
