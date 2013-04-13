#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

bool v1[100], v2[100];

int inline mod(int i, int j)
{ 
    if(i >= 0) return i%j;
    else if(i < 0) return  (j-1-i)/j*j + i;
}

int main()
{
    int i, j, vlu, N, K;
    while(scanf("%d%d", &N, &K) == 2)  {
        memset(v1, 0, sizeof(v1));
        scanf("%d", &vlu);
        vlu = mod(vlu, K);
        v1[vlu] = 1;
        for(i = 1; i < N; i++) {
            scanf("%d", &vlu);
            memset(v2, 0, sizeof(v2));
            for(j = 0; j < K; j++)
                if(v1[j]) 
                v2[mod(j+vlu, K)] = v2[mod(j-vlu, K)] = 1;
            memcpy(v1, v2, sizeof(v1));
        }
        if(v1[0]) printf("Divisible\n");
        else printf("Not divisible\n");
    }
    return 0;
}
