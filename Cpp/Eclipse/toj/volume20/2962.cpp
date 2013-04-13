#include <iostream>
using namespace std;

int n, vlu[50];

int cpt(int start, int res)
{
    int i, s;
    for(s = 0, i = n-1; i > start; i--) {
        s += (n-i)*(vlu[i] - vlu[i-1]);
        if(s > res) break;
    }
    if(i == start)  return ( n-start > 1) ? (res - s)%(n-start): 0;
    s -= (n-i)*(vlu[i] - vlu[i-1]);
    return vlu[i] - (res - s)/(n-i) - vlu[start];
}

int main()
{
    unsigned mind;
    int i, j, ntest, K, res;
    cin >> ntest;
    while(ntest-- > 0) {
        cin >> n >> K;
        for(i = 0; i < n; i++)   cin >> vlu[i];
        sort(vlu, vlu + n);
        mind = cpt(0, K);
        for(i = 0, res = K - vlu[0]; i < n && res >= 0; i++, res -= vlu[i]) {
            int tp = cpt(i+1, res);
            if(tp < mind) mind = tp;
        }
        cout << mind << endl;
    }
    return 0;
}
