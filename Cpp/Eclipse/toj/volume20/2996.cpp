#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const double EP = 1e-10;
const double g = 9.8;
int main()
{
    double h, v, l, H;
    while(cin >> h >> l >> v) {
        if(fabs(h) < EP && fabs(v) < EP && fabs(l) < EP) break;
        H = v*v/2/g - 0.5*g*l*l/v/v + h;
        cout.setf(ios::fixed);
        cout << setprecision(2) << H << endl;
    }
    return 0;
}
