#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int mx = 21;
const int LIM = 10001;

int a[mx], op[LIM], L, R, Test, N, M, x, y, tmp;
bool mk[LIM];

inline int gcd(int x, int y) {
	int tmp;
	while (y)
		tmp = y, y = x % y, x = tmp;
	return x;
}

int main() {
	scanf("%d", &Test);
	for (int Zeit = 1; Zeit <= Test; Zeit++) {

		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%d", &a[i]);
		sort(a, a + N);
		for (int i = 1; i < N; i++)
			a[i] /= a[0];

		fill_n(mk, LIM, 0);
		mk[op[0] = 1] = 1;

		for (L = 0, R = 1; L < R; L++)
			for (int i = 1; i < N; i++) {
				tmp = op[L] * a[i];
				if (tmp < LIM && !mk[tmp])
					mk[op[R++] = tmp] = 1;
				tmp = op[L] / a[i];
				if (tmp * a[i] == op[L] && !mk[tmp])
					mk[op[R++] = tmp] = 1;
			}

		printf("Scenario #%d:\n", Zeit);
		scanf("%d", &M);
		while (M--) {
			scanf("%d%d", &x, &y);
			printf("Gear ratio %d:%d ", x, y);

			tmp = gcd(x, y);
			x /= tmp;
			y /= tmp;

			for (int i = 2; i < mx; i++)
				if (y % i == 0)
					for (int j = i; j < mx; j += i)
						if (mk[j])
							while (y % i == 0)
								y /= i, x *= j / i;

			if (y == 1)
				for (int i = 2; LIM <= x && i < R; i++)
					while (x % op[i] == 0)
						x /= op[i];

			if (y == 1 && x < LIM && mk[x])
				printf("can be realized.\n");
			else
				printf("cannot be realized.\n");
		}
		printf("\n");
	}
	return 0;
}
