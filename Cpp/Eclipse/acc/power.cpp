//n^p   p = a(k)*2^k + a(k-1)*2^(k-1) + ... a(0)*2^0
//    n^p = ∏n^(a(i)*2^i)) 
#include <iostream>
using namespace std;

unsigned  Power(unsigned n, unsigned p)
{
    unsigned k = 1;
    if(p == 0) return 1;
    while( p > 0) {
        if(p & 1 == 1) k *= n;
        n *= n;
        p /= 2;
    }
    return k;
}


int main()
{
    int n, p;
    while( cin >> n >> p)
    cout << Power(n, p) << endl;
    return 0;
}
