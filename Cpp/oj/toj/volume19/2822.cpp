#include <stdio.h>
#define M 2002
#define N 30

int f[M][M] = { 0 };

int main() {
	int i, j, k, n, m, s;
	char a[M], st[N];
	int del[N] = { 0 }, ins[N] = { 0 };

	scanf("%d%d", &n, &m);
	scanf("%s", a);
	for (i = 0; i < n; i++) {
		scanf("%s", st);
		scanf("%d%d", &ins[st[0] - 'a'], &del[st[0] - 'a']);
	}
	for (k = 1; k < m; k++) {
		for (i = 0; i < m - k; i++) {
			j = i + k;
			s = 99999999;
			if (a[i] == a[j] && f[i + 1][j - 1] < s)
				s = f[i + 1][j - 1];
			if (f[i + 1][j] + del[a[i] - 'a'] < s)
				s = f[i + 1][j] + del[a[i] - 'a'];
			if (f[i][j - 1] + del[a[j] - 'a'] < s)
				s = f[i][j - 1] + del[a[j] - 'a'];
			if (f[i + 1][j] + ins[a[i] - 'a'] < s)
				s = f[i + 1][j] + ins[a[i] - 'a'];
			if (f[i][j - 1] + ins[a[j] - 'a'] < s)
				s = f[i][j - 1] + ins[a[j] - 'a'];
			f[i][j] = s;
		}
	}

	printf("%d\n", f[0][m - 1]);
	return 0;
}

