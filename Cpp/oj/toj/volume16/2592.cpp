#include <cstdio>
using namespace std;

const int MAX = 1001;
int tb[MAX][MAX];
int A[MAX], D[MAX], E[MAX];

void swap(int& a, int& b) {
	int c = a;
	a = b;
	b = c;
}

int main() {
	int i, j, k, p, q, s, s0, n;
	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				scanf("%d", &tb[i][j]);
		s0 = 0;
		for (i = 1; i <= n; i++) {
			A[i] = D[i] = i;
			E[i] = -1;
			s0 += tb[i][i];
		}
		while (1) {
			s = 0;
			for (i = 1; i <= n; i++)
				s += tb[i][A[i]];
			if (s != s0)
				break;
			q = 0;
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
		if (k == 1)
			printf("homogeneous\n");
		else
			printf("not homogeneous\n");
	}
	return 0;
}
