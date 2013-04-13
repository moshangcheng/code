#include <iostream>
#include <algorithm>   // Need copy()
#include <vector>      // Need vector
 
using namespace std;
 
double darray[10] =
  {1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9};
 
vector<double> vdouble(10);
 
int main()
{
  vector<double>::iterator outputIterator = vdouble.begin();
  copy(darray, darray + 10,outputIterator);
  
  
  while (outputIterator != vdouble.end()) {
    cout << *outputIterator << "  ";
    outputIterator++;
  }
  cout<<endl;
  
  
  random_shuffle(vdouble.begin(), vdouble.end());
  outputIterator = vdouble.begin();
  while (outputIterator != vdouble.end()) {
    cout << *outputIterator << "  ";
    outputIterator++;
  }
  cout<<endl;
  
  reverse(vdouble.begin(), vdouble.end());
  outputIterator = vdouble.begin();
  while (outputIterator != vdouble.end()) {
    cout << *outputIterator << "  ";
    outputIterator++;
  }
  cout<<endl;
  
  double value=3.14159;
  replace(vdouble.begin(), vdouble.end(), 1.5, value);
  outputIterator = vdouble.begin();
  while (outputIterator != vdouble.end()) {
    cout << *outputIterator << "  ";
    outputIterator++;
  }
  cout<<endl;
  
  outputIterator= find(vdouble.begin(),vdouble.end(), value);
  if (outputIterator!= vdouble.end())
  if (outputIterator!= vdouble.end())
    cout << "Vector contains value " << *outputIterator << endl;
  else
    cout << "Vector does not contain 50" << endl;
  system("pause");
  return 0;
}
