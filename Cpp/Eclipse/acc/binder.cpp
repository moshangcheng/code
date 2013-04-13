#include <iostream>
#include <algorithm>
#include <functional>
#include <list>
 
using namespace std;
 
// Data
int iarray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
list<int> aList(iarray, iarray + 10);
 
int main()
{
  int k = 0;
  count_if(aList.begin(), aList.end(),
    binder1st(greater<int>(), 8), k);
  cout << "Number elements < 8 == " << k << endl;
  
  system("pause");
  return 0;
}
