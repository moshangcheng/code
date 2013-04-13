/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1258.html
 */
#include <stdio.h>

#define PI 3.1415926;

int main() {
	double D, T;
	int N, n = 0;
	while (scanf("%lf%d%lf", &D, &N, &T) == 3 && N > 0) {
		double S, V;
		n++;
		T = T / 3600;
		S = D * N / 63360 * PI;
		V = S / T;
		printf("Trip #%d: ", n);
		printf("%.2f %.2f\n", S, V);
	}
	return 0;
}

