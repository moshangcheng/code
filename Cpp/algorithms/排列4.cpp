#include <iostream>
using namespace std;

int main() {
	int a[100], A[100];
	int i, j, n, t;
	while (cin >> n) {
		memset(a, 0, sizeof(a));
		while (1) {
			memset(A, 0, sizeof(A));
			for (i = n - 1; i > 0; i--) {
				for (t = 0, j = n - 1; t <= a[i] && j >= 0; j--)
					if (A[j] == 0)
						t++;
				A[j + 1] = i + 1;
			}
			for (i = 0; i < n; i++)
				if (A[i] == 0)
					cout << 1 << " ";
				else
					cout << A[i] << " ";
			cout << endl;
			for (i = 1; i < n; i++)
				if (a[i] < i) {
					a[i]++;
					break;
				} else
					a[i] = 0;
			if (i == n)
				break;
		}
	}
	return 0;
}

