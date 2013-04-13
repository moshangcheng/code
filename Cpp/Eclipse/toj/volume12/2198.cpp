#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 100000;
int a[MAX];

int main()
{
    int i, j, N, M;
    while(cin >> N >> M)  {
        if(N == 0 && M == 0) break;
        for(i = 0; i < M; i++) cin >> a[i];
        sort(a, a + M);
        for(j =0, i = M&1; i < M; i += 2)  j ^= a[i+1]-a[i]-1;
        if(M&1) j ^= a[0] - 1;
        if(j > 0) cout << "Win\n";
        else cout << "Lose\n";
    }
    return 0;
}
