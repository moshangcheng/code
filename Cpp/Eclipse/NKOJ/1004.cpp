/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1004.html
 */

#include<stdio.h>

int main() {
	int n;
	while (scanf("%d", &n) == 1)
		printf("%d\n", (n + 1) * (n + 1) / 2 - 1);
	return 0;
}
