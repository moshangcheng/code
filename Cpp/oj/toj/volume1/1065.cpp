#include <iostream>
using namespace std;

int main()
{
    int ntest, n, tp, n2, n5;
    cin >> ntest;
    while(ntest-- > 0) {
        cin >> n;
        for(n2 = 0, tp = n; tp > 1; n2 += tp) tp /= 2;
        for(n5 = 0, tp = n; tp > 1; n5 += tp) tp /= 5;
        if(n2 > n5) cout << n5 << endl;
        else cout << n2 << endl;
    }
    return 0;
}
