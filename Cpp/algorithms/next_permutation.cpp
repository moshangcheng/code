#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;

int main()
{
  	int A[] = {8, 3, 6, 1, 2, 5, 7, 4};
  	const int N = sizeof(A) / sizeof(int);
  	
  	next_permutation(A, A+N);
  	copy(A, A+N, ostream_iterator<int>(cout, " "));
  	cout << endl;
  	system("pause");
  	return 0;  
}
