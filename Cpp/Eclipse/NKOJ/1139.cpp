/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1139.html
 */

#include <iostream>
using namespace std;

int main() {
	int I, K;
	long long int N, b[10];
	b[0] = 10;
	for (int i = 1; i < 10; i++)
		b[i] = b[i - 1] * 10;

	while (cin >> I >> K >> N) {
		int c[10][11];
		for (int j = 0; j < I; j++) {
			c[j][1] = N % b[j];
		}

		for (int i1 = 2; i1 <= K; i1++)
			for (int i2 = i1 - 1; i2 < I; i2++) {
				int max = 0;
				for (int i3 = i1 - 2; i3 < i2; i3++) {
					int s = c[i3][i1 - 1] * (N / b[i3] % (b[i2] / b[i3]));
					if (s > max)
						max = s;
				}
				c[i2][i1] = max;
			}
		cout << c[I - 1][K] << endl;
	}
	return 0;
}
