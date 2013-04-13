/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1086.html
 */

#include<stdio.h>

int main() {
	int n, Max = -1000000000;
	short a[100][100], Temp[100];
	int i, j, k, b, s;
	while (scanf("%d", &n) == 1) {
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				scanf("%d", &a[i][j]);

		for (k = 0; k < n; k++) {
			for (i = 0; i < n; i++)
				Temp[i] = a[k][i];
			for (j = k; j < n; j++) {
				b = 0;
				s = -1000000000;
				if (j != k)
					for (i = 0; i < n; i++)
						Temp[i] += a[j][i];
				for (i = 0; i < n; i++) {
					if (b > 0)
						b += Temp[i];
					else
						b = Temp[i];
					if (b > s)
						s = b;
				}
				if (s > Max)
					Max = s;
			}
		}
		printf("%d\n", Max);
	}
	return 0;
}
