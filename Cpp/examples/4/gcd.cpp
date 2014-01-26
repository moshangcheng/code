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
    cout << -1/3 << ends << -1%3 << ends << 1/(-3) << ends << 1%(-3) << endl;
    cout << -4/3 << ends << -4%3 << ends << 4/(-3) << ends << 4%(-3) << endl;
    int m, n;
    while(1) {
        cout << "Please enter two integers: \n";
        cin >> m >> n;
        cout << "(" << m << "," << n <<") = " << gcd(m, n) << endl << endl;
    }
    return 0;
}
    
