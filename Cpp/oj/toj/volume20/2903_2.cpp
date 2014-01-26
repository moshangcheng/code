#include <cstdio>
#include <string>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
typedef long long bigint;
int a,b,c,n;
bigint dig[10];
void cal_dig() {
        bigint i,j=10;
        for (i=1;i<=8;i++) {
               bigint s= j/10;
               bigint t = j-1;
               dig[i] = dig[i-1] + i*(s+t)*(t-s+1)/2;
               j *= 10;
       }
}
int main() {
        int i,j,digs;
        cal_dig();
        while (scanf("%d", &n)==1) {
               bigint bn = n;
               for (i=8;i>0;i--) {
                       if (dig[i] < bn) break;
              }
               bn -= dig[i];
               digs = i+1;
               bigint s = 1;
               for (i=2;i<=digs;i++) s *= 10;
               //bigint t = 10*s -1;
               double dt = sqrt(2.0*bn/digs + 1.0*s*s - s + 0.25) - 0.5;
               int ft = int(dt);
               int ct = int(ceil(dt));
               bn -= digs * (s+ft) * (ft-s+1) /2;
               if (bn == 0) bn = digs * ct;
               char str[10];
               sprintf(str, "%d", ct);
               printf("%c\n", str[(bn-1) % digs]);
       }
}
