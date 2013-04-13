#include <iostream>
using namespace std;

int main()
{
    unsigned n, m;
    while(cin >> n && n > 0)    {
        m = 0;
        while(n > 0) {
            m = (m<<1) + (n&1);
            n >>= 1;
        }
        cout << m << endl;
    }
    return 0;
}
        
        
