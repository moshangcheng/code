/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=1237
 */
#include <cstdio>
using namespace std;

int main() {
	char c1, c2;
	double sum;
	double a1, a2;
	while (1) {
		scanf("%lf%c", sum, &c1);
		if (c1 == '\n') {
			if (sum < 1e-3)
				break;
		} else
			scanf("%c", &c1);
		for (; c1 != '\n'; c1 = c2) {
			scanf("%lf%c", &a1, &c2);
			if (c2 == ' ')
				scanf("%c", &c2);
			if (c1 == '*')
				sum *= a1;
			else if (c1 == '/')
				sum /= a1;
			else {
				while (c2 == '*' || c2 == '/') {
					scanf("%lf", &a2);
					if (c2 == '*')
						a1 *= a2;
					if (c2 == '/')
						a1 /= a2;
					scanf("%c", &c2);
					if (c2 == '\n')
						break;
					scanf("%c", &c2);
				}
				if (c1 == '+')
					sum += a1;
				else
					sum -= a1;
			}
		}
		printf("%.2lf\n", sum);

	}
	return 0;
}
