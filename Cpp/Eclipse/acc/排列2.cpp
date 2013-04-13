#include <iostream>
using namespace std;

int A[100], D[100], E[100];

void swap(int& a, int& b) {
	int c = a;
	a = b;
	b = c;
}

int main() {
	int i, j, k, n, p, q;
	while (1) {
		cout << "Please input the size of permutation\n";
		cin >> n;
		for (i = 1; i <= n; i++) {
			A[i] = D[i] = i;
			E[i] = -1;
		}
		while (1) {
			q = 0;
			for (i = 1; i <= n; i++)
				cout << A[i] << " ";
			cout << endl;
			for (k = n; k > 1; k--) {
				D[k] += E[k];
				p = D[k];
				if (p == k)
					E[k] = -1;
				else {
					if (p == 0) {
						E[k] = 1;
						q++;
					} else {
						p += q;
						swap(A[p], A[p + 1]);
						break;
					}
				}
			}
			if (k == 1)
				break;
		}
	}
	return 0;
}

