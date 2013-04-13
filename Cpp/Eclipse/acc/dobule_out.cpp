#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
   double x;
   cout.setf(ios::fixed);
   cout.precision(0);
   while(cin >> x) cout << x << endl;
   return 0;
}
