#include <iostream>
#include <iterator>
#include <numeric>
using namespace std;

int main() {
	int A[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	const int N = sizeof(A) / sizeof(int);
	int B[N];

	cout << "A[]:         ";
	copy(A, A + N, ostream_iterator<int> (cout, " "));
	cout << endl;

	adjacent_difference(A, A + N, B);
	cout << "Differences: ";
	copy(B, B + N, ostream_iterator<int> (cout, " "));
	cout << endl;

	cout << "Reconstruct: ";
	partial_sum(B, B + N, ostream_iterator<int> (cout, " "));
	cout << endl;

	system("pause");
	return 0;
}
