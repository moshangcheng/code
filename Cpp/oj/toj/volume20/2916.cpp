#include <iostream>
using namespace std;

int gcd(int a, int b)
{
    while(a != 0) {
        int c = b % a;
        b = a;
        a = c;
    }
    return b;
}

int main()
{
    unsigned X, Y;
    while(cin >> X >> Y) {
        Y /= gcd(X, Y);
        cout << Y << endl;
    }
    return 0;
}
            
    
