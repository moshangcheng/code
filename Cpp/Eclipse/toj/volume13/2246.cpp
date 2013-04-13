#include <iostream>
#include <cmath>
using namespace std; 

int main()
{
    unsigned n, p, m, b, ntest;
    cin >> ntest;
    while(ntest-- > 0)  {
        cin >> n >> m >> p;
        if(n <= 2*m+1) {
            if(p == n) cout << m - (n-1)/2 << endl;
            else cout << ((n&1) == (p&1)) << endl;
        }
        else {
            b = floor(log2(n - 2*m + 0.5));
            if(p > 2*m + (1<<b)) cout << "Thrown\n";
            else cout << 0 << endl;
        }
    }
    return 0;
}
                
