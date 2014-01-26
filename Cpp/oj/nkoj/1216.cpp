/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1216.html
 */

#include <stdio.h>

int main() {
	int Num;
	scanf("%d", &Num);
	while (Num-- > 0) {
		int L, M, N, l, m, n, x, y, s;
		scanf("%d%d%d", &L, &M, &N);
		l = L;
		m = M;
		n = N;
		while (n) {
			int t = m % n;
			m = n;
			n = t;
		}
		l = L / m;
		n = N / m;
		m = M / m;
		if (l % 2 == 0) {
			l = l / 2;
			for (y = 0; y < m; y++) {
				x = l + y * n;
				if (x % m == 0)
					break;
			}
			if (y < m) {
				x = x / m;
				s = 2 * (x + y) - 1;
				printf("%d\n", s);
			} else
				printf("no\n");
		} else
			printf("no\n");
	}
	return 0;
}
