/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1200.html
 */
#include <iostream>
using namespace std;

int main() {
	int M, N, T;
	while (cin >> M >> N && (M || N)) {
		int n = 0;
		while (M) {
			int k = N / M;
			if (k > 1 || M == N)
				break;
			n += k;
			T = N % M;
			N = M;
			M = T;
		}
		if (n % 2 == 0)
			cout << "Stan wins\n";
		else
			cout << "Ollie wins\n";
	}
	return 0;
}

