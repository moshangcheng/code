#include <iostream>
#include <bitset>
using namespace std;

int main() {
  const bitset<12> mask(2730); 
  cout << "mask =      " << mask<<" "<<mask.to_ulong() << endl;

  bitset<12> x;

  cout << "Enter a 12-bit bitset in binary: " << flush;
  if (cin >> x) {
    cout << "x =        " << x << endl;
    cout << "As ulong:  " << x.to_ulong() << endl;
    cout << "And with mask: " << (x & mask) << endl;
    cout << "Or with mask:  " << (x | mask) << endl;
  }
  
  system("pause");
}

