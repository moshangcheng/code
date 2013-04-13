#include <iostream>
#include <cstdlib>    // Need random(), srandom()
#include <algorithm>   // Need random_shuffle()
#include <vector>      // Need vector
#include <functional>  // Need ptr_fun()
 
using namespace std;
 
// Data to randomize
int iarray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
vector<int> v(iarray, iarray + 10);
 
// Function prototypes
void Display(vector<int>& vr, const char *s);
unsigned int RandInt(const unsigned int n);
 
int main()
{
  Display(v, "Before shuffle:");
 
  pointer_to_unary_function<unsigned int, unsigned int>
    ptr_RandInt = ptr_fun(RandInt);  // Pointer to RandInt()//注意这行
  random_shuffle(v.begin(), v.end(), ptr_RandInt);
 
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
 
 
// Return next random value in sequence modulo n
unsigned int RandInt(const unsigned int n)
{
  return rand() % n;
}
