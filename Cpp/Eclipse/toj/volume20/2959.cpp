#include <cstdio>
#include <map>
using namespace std;

int main()
{
    map<int, int> n;
    int i, x, s, flag, N, M, sum;
    while(scanf("%d%d", &N, &M) == 2) {
        n.clear();
        flag = s = sum = 0;
        n[s] = 1;
        for(i = 0; i < N; i++)  {
            scanf("%d", &x);
            x = (x > M)? 1: ((x == M) ? 0: -1);
            s += x;
            if(x == 0) flag = 1;
            if(flag == 0) {
                n[s]++;
                continue;
            }
            sum += n[s];
        }
        printf("%d\n", sum);
    }
    return 0;
}
