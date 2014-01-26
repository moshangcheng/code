/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1141.html
 */

#include <stdio.h>
#include <math.h>

# define PI 3.1415926535897;

int main() {
	double R, H, D1, D2, W1, W2, w, dis;
	while (scanf("%lf%lf%lf%lf%lf%lf", &R, &H, &D1, &W1, &D2, &W2) == 6) {
		w = W1 - W2;
		if (w < 0)
			w = -w;
		if (w > 180)
			w = 360 - w;
		w = w * R / sqrt(R * R + H * H) / 180 * PI;
		dis = sqrt(D1 * D1 + D2 * D2 - 2 * D1 * D2 * cos(w));
		printf("%.2f\n", dis);
	}
	return 0;
}
