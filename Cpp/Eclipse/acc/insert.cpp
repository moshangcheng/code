#include <iostream>
#include <algorithm>
#include <list>
 
using namespace std;
 
int iArray[5] = { 1, 2, 3, 4, 5 };
 
void Display(list<int>& v, const char* s);
 
int main()
{
  list<int> iList;
 
  // Copy iArray backwards into iList
  copy(iArray, iArray + 5, back_inserter(iList));
  Display(iList, "Before find and copy");
 
  // Locate value 3 in iList
  list<int>::iterator p =
    find(iList.begin(), iList.end(), 3);
 
  // Copy first two iArray values to iList ahead of p
  copy(iArray, iArray + 2, inserter(iList, p));
  Display(iList, "After find and copy");
  
  p =find(iList.begin(), iList.end(), 2);
  cout << "before: p == " << *p << endl;
  advance(p, 3);  // same as p = p + 2;
  cout << "after : p == " << *p << endl;
  int k = 0;
  //distance(p, iList.end(), k);
  cout << "k == " << k << endl;
 
  system("pause");
  return 0;
}
 
void Display(list<int>& a, const char* s)
{
  cout << s << endl;
  list<int>::iterator ilist=a.begin();
  while(ilist!=a.end()){
        cout<<*ilist<<" ";
        ilist++;
    }
  cout << endl;
}
