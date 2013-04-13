#include <iostream>
#include <algorithm>   // Need random_shuffle()
#include <vector>      // Need vector
#include <functional>  // Need unary_function
 
using namespace std;
 
// Data to randomize
int iarray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
vector<int> v(iarray, iarray + 10);
 
// Function prototype
void Display(vector<int>& vr, const char *s);
 
// The FiboRand template function-object class
template <class Arg>
class FiboRand : public unary_function<Arg, Arg> {
  int i, j;
  Arg sequence[18];
public:
  FiboRand();
  Arg operator()(const Arg& arg);
};
 
int main()
{
  FiboRand<int> fibogen;  // Construct generator object
  cout << "Fibonacci random number generator" << endl;
  cout << "using random_shuffle and a function object" << endl;
  Display(v, "Before shuffle:");
  random_shuffle(v.begin(), v.end(), fibogen);
  Display(v, "After shuffle:");
  
  system("pause");
  return 0;
}
 
// Display contents of vector vr
void Display(vector<int>& vr, const char *s)
{
  cout << endl << s << endl;
  vector<int>::iterator ivector=vr.begin();
  while(ivector!=vr.end()){
        cout<<*ivector<<" ";
        ivector++;
    }
  cout << endl;
}
 
// FiboRand class constructor
template<class Arg>
FiboRand<Arg>::FiboRand()
{
  sequence[17] = 1;
  sequence[16] = 2;
  for (int n = 15; n > 0; n--)
    sequence[n] = sequence[n + 1] + sequence[n + 2];
  i = 17;
  j = 5;
}
 
// FiboRand class function operator
template<class Arg>
Arg FiboRand<Arg>::operator()(const Arg& arg)
{
  Arg k = sequence[i] + sequence[j];
  sequence[i] = k;
  i--;
  j--;
  if (i == 0) i = 17;
  if (j == 0) j = 17;
  return k % arg;
}
