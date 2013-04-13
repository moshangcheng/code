#include <string>
#include <set>
#include <iostream>
using namespace std;

int main()
{
  set<string,greater<string> > strset;
  set<string,greater<string> >::iterator si;
  strset.insert("cantaloupes");
  strset.insert("apple");
  strset.insert("orange");
  strset.insert("banana");
  strset.insert("grapes");
  strset.insert("grapes");  
  for (si=strset.begin(); si!=strset.end(); si++)  
  {  cout << *si << " ";  }
  cout << endl;
  system("pause");
  return 0;
}
