#include <iostream>
using namespace std;

unsigned num(unsigned n)
{
    if(n < 0) return 0;
    int i, j, a, x, m;
    for(i = 0, a = m = 1; n >= m; a -= m, i++, m *= 10) {
        x = n % (m * 10) / m;
        a += i * x * m/10 + (x > 0) ? m: n % m + 1;
    }
    return a;
}
        
int main()
{
    unsigned m, n;
    while(cin >> m >> n) cout << num(n) - num(m-1) << endl;
    return 0;
}
         