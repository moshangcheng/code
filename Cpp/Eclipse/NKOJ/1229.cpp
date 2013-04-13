/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1229.html
 */

#include <iostream>
using namespace std;

inline int DI(int t, int C) {
	if (t == 0)
		return 0;
	else if (t > 0 && t < 11)
		return -1 * C;
	else
		return (t - 10) * (t - 10);
}

int main() {
	int N = 0, Num;
	cin >> Num;
	while (Num) {
		N++;
		int L, C, a, b[1000], s[1000], s1 = 0;
		int M = 0;
		cin >> L >> C;
		for (int i = 0; i < Num; i++) {
			scanf("%d", &a);
			if (i == 0)
				s[i] = a;
			else
				s[i] = s[i - 1] + a;
			s1 += a;
			if (s1 >= L) {
				if (L == s1) {
					b[M] = i + 1;
					s1 = 0;
				} else {
					b[M] = i;
					s1 = a;
				}
				M++;
			}
		}
		if (s1)
			b[M++] = Num;

		int S[1000][1000];
		for (int j = 0; j < b[0]; j++)
			S[0][j] = DI(L - s[j], C);

		for (int k = 1; k < M; k++) {
			for (int k1 = 0; k1 < b[k]; k1++) {
				if (k1 == 0)
					S[k][k1] = (k + 1) * DI(L, C);
				else {
					int Min = 1000000000;
					for (int k2 = (k1 < b[k - 1]) ? k1 : b[k - 1] - 1; k2 > -1; k2--) {
						if (L >= (s[k1] - s[k2])) {
							int t = S[k - 1][k2] + DI(L + s[k2] - s[k1], C);
							if (t < Min)
								Min = t;
						} else
							break;
					}
					S[k][k1] = Min;
				}
			}
		}
		cout << "Case " << N << ":\n\n";
		cout << "Minimum number of lectures: " << M << endl;
		cout << "Total dissatisfaction index: " << S[M - 1][Num - 1] << endl;
		cin >> Num;
		if (Num)
			cout << endl;
	}
	return 0;
}

