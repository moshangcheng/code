/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1254.html
 */
#include <stdio.h>
#include <math.h>

int main() {
	int Num, I = 0;
	double T = sqrt(2) - 1;
	scanf("%d", &Num);
	while (I < Num) {
		int m, n;
		I++;
		scanf("%d%d", &m, &n);
		double length;
		if (m % 2 == 0 || n % 2 == 0)
			length = m * n;
		else
			length = m * n + T;
		printf("Scenario #%d:\n%.2f\n\n", I, length);
	}
	return 0;
}

