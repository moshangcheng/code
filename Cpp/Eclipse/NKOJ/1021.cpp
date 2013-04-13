/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1021.html
 */

#include <iostream>
using namespace std;

int main() {
	long long N;
	while (scanf("%lld", &N) == 1) {
		N--;
		long long a = 1;
		while (N) {
			bool c = N % 2;
			if (c)
				printf("%lld\n", a);
			N = N / 2;
			a *= 3;
		}
	}
	return 0;
}

