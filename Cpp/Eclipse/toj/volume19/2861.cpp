#include <iostream>
#include <cmath>
using namespace std;

long long F(int n)
{
    if(n == 0) return 0;
    long long s = 0;
    int k = floor(sqrt(n));
    for(int i = 1; i <= k; i++) s += n/i;
    for(int i = 1; i < n/k; i++)  s += (n/i - n/(i+1))*i;
    return s;
}

int main()
{
    int a, b, k;
    long long sum;
    while(cin >> a >> b) {
        if(a == 0 && b == 0) break;
        cout << F(b) - F(a-1) << endl;
    }
    return 0;
}
