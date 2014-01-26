/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1263.html
 */
#include <stdio.h>

int main() {
	int N;
	while (scanf("%d", &N) == 1) {
		int i = 0;
		double S = 0;
		while (i++ < N)
			S += 1.0 / i;
		printf("%.12f\n", S);
	}
	return 0;
}
