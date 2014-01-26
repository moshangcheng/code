#include <iostream>
#include <cmath>
using namespace std;

const double EP = 1e-2;

double double_gcd(double a, double b)
{
    while(a > b*EP) {
        double c = fmod(b, a);
        b = a;
        a = c;
    }
    return b;
}
        
int main()
{
    double m, n;
    while(1) {
        cout << "Please enter two real number: \n";
        cin >> m >> n;
        cout << "(" << m << "," << n <<") = " << double_gcd(m, n) << endl << endl;
    }
    return 0;
}
