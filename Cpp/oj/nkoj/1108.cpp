/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-11-10 下午04:11:03
 * @brief http://acm.nankai.edu.cn/p1108.html
 */

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main() {
	int n, m;
	long long p;
	while (scanf("%d%d", &n, &m) == 2 && (n || m)) {
		if (m > n / 2) m = n - m;
		p = 1LL;
		for (int i = 1; i <= m; i++) {
			p *= (n - i + 1);
			p /= i;
		}
		printf("%lld\n", p);
	}
	return 0;
}
