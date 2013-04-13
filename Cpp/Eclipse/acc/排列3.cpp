#include <iostream>
#include <algorithm>
using namespace std;

int A[100], D[100], E[100];

int main() {
	int i, j, k, n, p, q;
	while (1) {
		cout << "Please input the size of permutation\n";
		cin >> n;
		for (i = 1; i <= n; i++)
			A[i] = i;
		while (1) {
			for (i = 1; i <= n; i++)
				cout << A[i] << " ";
			cout << endl;
			for (i = n; i > 1 && A[i] < A[i - 1]; i--)
				;
			if (i == 1)
				break;
			for (j = i; j <= n && A[j] > A[i - 1]; j++)
				;
			swap(A[i - 1], A[j - 1]);
			reverse(A + i, A + n + 1);
		}
	}
	return 0;
}

