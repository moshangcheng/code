/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1107.html
 */

#include <iostream>
using namespace std;

int main() {
	int N, i, j, k, m;
	short Num[101][300][11], Flag[300][2];
	int Dist[101], num[101];

	for (i = 1; i < 101; i++)
		num[i] = 1;
	Dist[1] = 1;
	Num[1][0][0] = 1;

	for (i = 2; i < 101; i++) {
		int Min = 10000, I = i / 2;
		for (j = i - 1; j >= I; j--) {
			int D = i - j;
			for (m = 0; m < num[j]; m++) {
				for (k = 0; k < Dist[j]; k++)
					if (Num[j][m][k] == D) {
						if (Min > Dist[j]) {
							Min = Dist[j];
							Flag[0][1] = j;
							Flag[0][0] = m;
							num[i] = 1;
						} else if (Min == Dist[j]) {
							Flag[num[i]][1] = j;
							Flag[num[i]][0] = m;
							num[i]++;
						}
						break;
					}
			}
		}

		Dist[i] = Min + 1;
		for (m = 0; m < num[i]; m++) {
			for (k = 0; k < Min; k++)
				Num[i][m][k] = Num[Flag[m][1]][Flag[m][0]][k];
			Num[i][m][Min] = i;
		}
	}

	while (cin >> N && N) {
		for (j = 0; j < Dist[N] - 1; j++)
			cout << Num[N][0][j] << " ";
		cout << Num[N][0][Dist[N] - 1] << endl;
	}
	return 0;
}
