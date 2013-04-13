#include <iostream>
using namespace std;

int main()
{
    long long ntest, nmove;
    cin >> ntest;
    while(ntest-- > 0) {
        cin >> nmove;
        if(nmove == 0) cout << 1 << endl;
        else if(nmove == 1) cout << 2 << endl;
        else cout << (nmove*nmove*2 - 4*nmove + 5) << endl;
    }
    return 0;
}
        
