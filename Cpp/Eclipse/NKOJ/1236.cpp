/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1236.html
 */

#include <stdio.h>

int main() {
	int a, b, c;
	while (scanf("%d%d", &a, &b) == 2) {
		if (a == 0 && b == 0)
			break;
		c = 1;
		a = a % 9;
		if (a == 0)
			printf("9\n");
		else if (a == 3 || a == 6) {
			if (b > 1)
				printf("9\n");
			else if (b == 1)
				printf("%d\n", a);
			else if (b == 0)
				printf("1\n");
		} else {
			b = b % 6;
			while (b-- > 0)
				c = (c * a) % 9;
			printf("%d\n", c);
		}
	}
	return 0;
}

