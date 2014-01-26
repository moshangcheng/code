/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1007.html
 */

#include <stdio.h>

int main() {
	int N, a, b;
	while (scanf("%d", &N) == 1) {
		a = N / 2;
		b = N % 2;
		if (b == 1) {
			while (a) {
				a--;
				if (a)
					printf("2 ");
			}
			printf("3\n");
		} else {
			while (a) {
				printf("2");
				if (a)
					printf(" ");
				a--;
			}
			printf("\n");
		}
	}
	return 0;
}
