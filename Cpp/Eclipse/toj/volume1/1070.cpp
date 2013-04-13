#include <iostream>
using namespace std;

const unsigned MAX = 1<<15;

bool FIND, vst[MAX];
unsigned TEMP, maxn, n, m, vlu[16][MAX], edge[MAX][2];

void go(int depth, int k)
{
    if(depth == maxn) {
        FIND = 1;
        return;
    }
    unsigned a = TEMP&edge[k][0], b = TEMP&edge[k][1];
    if(!vst[a]) {
        vst[a] = 1;
        vlu[n][depth] = a;
        go(depth+1, a);
        if(FIND) return;
        vst[a]= 0;
    }
    if(!vst[b]) {
        vst[b] = 1;
        vlu[n][depth] = b;
        go(depth+1, b);
        if(FIND) return;
        vst[b] = 0;
    }
}

int main()
{
    unsigned i,j;
    for(i = 0; i < MAX; i++) 
		edge[i][1] = 1 + (edge[i][0] = (i<<1)); 
    for(n = 1; n < 16; n++) {
        maxn = 1<<n;
        TEMP = maxn - 1;
        memset(vst, 0, sizeof(vst));
        FIND = 0;  vlu[n][0] = 0;   vst[0] = 1;
        go(1, 0);
    }
    while(cin >> n >> m )    {
        if(m == 0 && n == 0) break;
        cout << vlu[n][m] << endl;
    }
    return 0;
}
            
            
        
        
        
