#include <cstdio>
using namespace std;

const int SIZE = 50000;
int c[SIZE], d[SIZE], u[SIZE], s[SIZE];

int main()
{
   int i, j, nfloor;
   long long min_cst, cnt_cst;
   while(scanf("%d", &nfloor) == 1) {
      for(i = 0; i < nfloor; i++) scanf("%d", c+i);
      for(i = 0; i < nfloor; i++) scanf("%d%d", u+i, d+i);
      s[0] = 0;
      for(i = 0; i < nfloor; i++) s[0] += c[i]*d[i];
      for(i = 1; i < nfloor; i++) 
         s[i] = s[i-1] - c[i-1]*(u[i-1] + d[i-1]);
      cnt_cst = 0;
      for(i = 1; i < nfloor; i++) cnt_cst += i*c[i]*d[i];
      min_cst = cnt_cst;
      for(i = 1; i < nfloor; i++) {
         cnt_cst -= s[i];
         if(cnt_cst < min_cst) min_cst = cnt_cst;
      }
      printf("%lld\n", min_cst);
   }
   return 0;
}
      
      
