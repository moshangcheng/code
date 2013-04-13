/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1143.html
 */

#include <stdio.h>
#define Min -1000000000;

int main() {
	int M, N, P;
	int n1, n2, n3, n4, n5, Max, s, b;
	int Temp[50][50], temp[50], Value[50][50][50];

	while (scanf("%d%d%d", &M, &N, &P) == 3) {
		for (n1 = 0; n1 < M; n1++)
			for (n2 = 0; n2 < N; n2++)
				for (n3 = 0; n3 < P; n3++)
					scanf("%d", &Value[n1][n2][n3]);

		Max = Min;
		for (n1 = 0; n1 < M; n1++) {
			for (n2 = 0; n2 < N; n2++)
				for (n3 = 0; n3 < P; n3++)
					Temp[n2][n3] = 0;

			for (n2 = n1; n2 < M; n2++) {
				for (n3 = 0; n3 < N; n3++)
					for (n4 = 0; n4 < P; n4++)
						Temp[n3][n4] += Value[n2][n3][n4];

				for (n3 = 0; n3 < N; n3++) {
					for (n4 = 0; n4 < P; n4++)
						temp[n4] = 0;

					for (n4 = n3; n4 < N; n4++) {
						s = Min;
						b = 0;
						for (n5 = 0; n5 < P; n5++) {
							temp[n5] += Temp[n4][n5];
							if (b > 0)
								b += temp[n5];
							else
								b = temp[n5];
							if (b > s)
								s = b;
						}
						if (s > Max)
							Max = s;
					}
				}
			}
		}
		printf("%d\n", Max);
	}
	return 0;
}
