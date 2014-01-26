#include <iostream>
#include <cmath>
using namespace std;

long long gcd(long long a, long long b)
{
    while(a) {
        long long temp = b%a;
        b = a;
        a = temp;
    }
    return b;
}

int main()
{
    char c;
    long long N, a, b, num_test = 0, x, d;
    cin >> N;
    while(num_test++ < N){
        cin >> a >> c >> b;
        if(a <= 0) x = a/b - 1;   
        else x = (a - 1)/b;
        cout << "case " << num_test << ": ["<<x;
        a-= x*b;
        d =  gcd(a, b);  a/= d; b/= d;
        while(1) {
            if(b == 1)  {
                cout << ",1]\n";
                break;
            }
            x = (b - 1)/a;
            b-= x*a;
            a = a + b;
            b = a - b;
            a = a - b;
            cout << "," << x;
        }
    }       
    return 0;
}
