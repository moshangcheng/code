#include <cstdio>
#include <set>
using namespace std;

int exGCD(int a, int b, int &x, int &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int r = exGCD(b, a % b, x, y);
    int t = x;
    x = y;
    y = t - a / b * y;
    return r;
}

int main()
{
   set<int> S;
   long long x;
   int p1, p2, n, r, s, d;
   while(scanf("%d", &n) == 1 && n > 0) {
      S.clear();
      for(p1 = 1; p1*p1 <= n; p1++)  {
         if(n % p1 != 0) continue;
         p2 = n / p1; 
         d = exGCD(p1, p2, r, s);
         if(d > 2) continue;
         x = 1 - 2*r*p1/d;
         while(x >  0) x -= n/d;
         while(x <= 0) x += n/d;
         for(; x < n; x += n/d) {
            S.insert(x);
            if(2*x != n) S.insert(n-x);
		}
      }
      printf("%d\n", S.size());
   }
   return 0;
}
