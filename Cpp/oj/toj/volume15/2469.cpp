#include <cstdio>
#include <cstring>
using namespace std;

int prt[100];
bool root[100];

int Find(int e)
{
    while(!root[e]) e=prt[e];
    return e;
}

void Union(int i, int j)
{
    if(prt[i] < prt[j]) {
        prt[j] += prt[i];
        root[i] = 0;
        prt[i] = j;
    }
    else {
        prt[i] += prt[j];
        root[j] = 0;
        prt[j] = i;
    }
}

int main()
{
    int num_test, N, M, i, a, b, fa, fb, sum;
    scanf("%d", &num_test);
    while(num_test-- > 0) {
        scanf("%d%d", &N, &M);
        sum = N;
        memset(root, 1, sizeof(root));
        for(i = 0; i < N; i++) prt[i] = 1;
        for(i = 0; i < M; i++) {
            scanf("%d%d", &a, &b);
            a--; b--;
            fa = Find(a);  fb = Find(b);
            if(fa != fb) {
                Union(Find(a), Find(b));
                sum--;
            }
        }
        printf("%d\n", sum);
    }
    return 0;
}
            
            
            
        
