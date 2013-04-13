#include <cstdio>
#include <iostream>
using namespace std;

const int MAX = 1000;
bool t[MAX + 1][MAX + 1];
int cnt[MAX + 1], prev[MAX + 1], S[MAX + 1][MAX + 1];

int main()
{
    int i, j, k, b, c, tx, ty, maxx, maxy, ntest, F, A;
    scanf("%d", &ntest);
    while(ntest-- > 0) {
        scanf("%d%d", &F, &A);
        maxx = maxy = 0;
        memset(t, 0, sizeof(t));
        memset(prev, 0, sizeof(prev));
        memset(S[0], 0, sizeof(S[0]));
        for(i = 0; i < F; i++) {
            scanf("%d%d", &tx, &ty);
            if(tx > maxx) maxx = tx;
            if(ty > maxy) maxy = ty;
            t[tx][ty] = 1;
        }
        for(i = 1; i <= maxx; i++) {
            S[i][0] = 0;
            for(j = 1; j <= maxy; j++)
            S[i][j] = t[i][j] + S[i-1][j] + S[i][j-1] - S[i-1][j-1];
        }
        for(i = 1; i <= maxx; i++)  {
            cnt[0] = 0;
            for(j = 1; j <= maxy; j++) {
                if(i * j <= A) {
                    cnt[j] = S[i][j];
                    continue;
                }
                cnt[j] = (cnt[j-1] > prev[j]) ? cnt[j-1]: prev[j];
                for(k = i - (A + j-1)/j; k > 0; k--) {
                    b = j - A / (i - k);
                    if(b == 0) continue;
                    c = S[i][j] - S[k-1][j] - S[i][b-1] + S[k-1][b-1];
                    if(c > cnt[j]) cnt[j] = c;
                }
            }
            memcpy(prev, cnt, sizeof(cnt));
        }
        printf("%d\n", cnt[maxy]);
    }
    return 0;
}
                    
                
        
        
        
        
