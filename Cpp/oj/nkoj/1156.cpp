/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1156.html
 */

#include <iostream>
using namespace std;

int main() {
	int W, H, M;
	int cake[21][21][21];
	for (int i = 1; i < 21; i++)
		for (int j = 1; j < 21; j++) {
			int temp = i * j + 1;
			if (temp > 21)
				temp = 21;
			for (int k = 1; k < temp; k++) {
				cake[i][j][k] = 1000000000;
				if (i * j == k)
					cake[i][j][k] = 1;
				if (k == 1)
					cake[i][j][k] = i * j;
			}
		}

	for (int i1 = 1; i1 < 21; i1++)
		for (int j1 = 1; j1 < 21; j1++) {
			int temp = i1 * j1 + 1;
			if (temp > 21)
				temp = 21;
			for (int k1 = 2; k1 < temp; k1++) {
				int t1 = k1 / 2 + 1;
				for (int m = 1; m < i1; m++) {
					int t2 = i1 - m, t3 = k1 - (t2 * j1 + 1), t4 = j1 * m + 1;
					if (t4 > t1)
						t4 = t1;
					for (int l = 1; l < t4 && l > t3; l++) {
						int s = k1 - l;
						int x = cake[m][j1][l] >= cake[t2][j1][s] ? cake[m][j1][l]
												: cake[t2][j1][s];
						if (x < cake[i1][j1][k1])
							cake[i1][j1][k1] = x;
					}
				}
				for (int n = 1; n < j1; n++) {
					int t2 = j1 - n, t3 = k1 - (t2 * i1 + 1), t4 = n * i1 + 1;
					if (t4 > t1)
						t4 = t1;
					for (int l = 1; l < t4 && l > t3; l++) {
						int s = k1 - l;
						int
								y =
										(cake[i1][n][l] >= cake[i1][t2][s]) ? cake[i1][n][l]
												: cake[i1][t2][s];
						if (y < cake[i1][j1][k1])
							cake[i1][j1][k1] = y;
					}
				}
			}
		}
	while (cin >> W >> H >> M && (W || M || H))
		cout << cake[W][H][M] << endl;
	return 0;
}
