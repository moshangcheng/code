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
bigint n,p[2];
bigint idx[5];
int pos[5][2];
int point[2][2];
void cal(int who) {
        idx[1] = 3*n -2;
        pos[1][0] = 0; pos[1][1] = n-1;
        idx[2] = 1;
        pos[2][0] = 0; pos[2][1] = 0;
        idx[3] = n;
        pos[3][0] = n-1; pos[3][1] = 0;
        idx[4] = n+n -1;
        pos[4][0] = n-1; pos[4][1] = n-1;
        //
        bigint i,j;
        if (n%2 && n*n==p[who]) {
               point[who][0] = point[who][1] = n/2;
               return;
       }
        for (i=n/2,j=n;i>0;i--,j-=2) {
               if (p[who] <= idx[1] +j-2) {
                       if (p[who] >= idx[1]) {
                               point[who][0] = pos[1][0];
                               point[who][1] = pos[1][1] -(p[who]-idx[1]);
                    }
                       else if (p[who] >= idx[4]) {
                               point[who][0] = pos[4][0] -(p[who]-idx[4]);
                               point[who][1] = pos[4][1];
                    }
                       else if (p[who] >= idx[3]) {
                               point[who][0] = pos[3][0];
                               point[who][1] = pos[3][1] +(p[who]-idx[3]);
                    }
                       else {
                               point[who][0] = pos[2][0] +(p[who]-idx[2]);
                               point[who][1] = pos[2][1];
                    }
                       return;
              }
               pos[1][0] ++; pos[1][1] --;
               pos[2][0] ++; pos[2][1] ++;
               pos[3][0] --; pos[3][1] ++;
               pos[4][0] --; pos[4][1] --;
               idx[2] = idx[1] +j-1;
               idx[3] = idx[2] +(j-2)-1;
               idx[4] = idx[3] +(j-2)-1;
               idx[1] = idx[4] +(j-2)-1;
       }
}
int main() {
        while (scanf("%lld %lld %lld", &n, &p[0], &p[1])==3) {
               cal(0); cal(1);
               printf("%d,%d %d,%d\n",point[0][0],point[0][1],point[1][0],point[1][1]);
               int gx = point[1][0] - point[0][0];
               int gy = point[1][1] - point[0][1];
               string ans = "";
               if (gy != 0) {
                       if (gx < 0) ans = "Upper";
                       else if (gx > 0) ans = "Lower";
              }
               else {
                       if (gx < 0) ans = "Up";
                       else if (gx > 0) ans = "Down";
              }
               if (gx != 0) {
                       if (gy < 0) ans += " left";
                       else if (gy > 0) ans += " right";
              }
               else {
                       if (gy < 0) ans = "Left";
                       else if (gy > 0) ans = "Right";
              }
               printf("%s\n", ans.c_str());
       }
}
