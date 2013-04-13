#include <iostream>
#include <numeric>
using namespace std;

int main()
{
   int i, n, ntest, a[10], b[10];
   cin >> ntest;
   while(ntest-- > 0)  {
      cin >> n;
      for(i = 0; i < n; i++) cin >> a[i];
      for(i = 0; i < n; i++) cin >> b[i];
      cout << inner_product(a, a+n, b, 0) << endl;
   }
   return 0;
}
