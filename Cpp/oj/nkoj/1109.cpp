/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1109.html
 */

#include <iostream>
#include <string>
#include <strstream>
using namespace std;

int main() {
	char A[200], B[200];
	string a[100], b[100];
	string s[100][100][100];
	int i, j, m, n, k;
	int S[101][101];

	while (cin.getline(A, 200, '#') && cin.getline(B, 200, '#')) {
		i = 0;
		j = 0;
		istrstream C1(A);
		while (C1 >> a[i])
			i++;
		istrstream C2(B);
		while (C2 >> b[j])
			j++;

		for (m = 0; m < i; m++)
			S[m][0] = 0;
		for (n = 0; n < j; n++)
			S[0][n] = 0;

		for (m = 1; m <= i; m++) {
			for (n = 1; n <= j; n++)
				if (a[m - 1] == b[n - 1]) {
					S[m][n] = S[m - 1][n - 1] + 1;
					for (k = 0; k < S[m][n] - 1; k++)
						s[m][n][k] = s[m - 1][n - 1][k];
					s[m][n][S[m][n] - 1] = a[m - 1];
				} else {
					if (S[m - 1][n] > S[m][n - 1]) {
						S[m][n] = S[m - 1][n];
						for (k = 0; k < S[m][n]; k++)
							s[m][n][k] = s[m - 1][n][k];
					} else {
						S[m][n] = S[m][n - 1];
						for (k = 0; k < S[m][n]; k++)
							s[m][n][k] = s[m][n - 1][k];
					}
				}
		}
		for (m = 0; m < S[i][j]; m++) {
			cout << s[i][j][m];
			if (m < S[i][j] - 1)
				cout << " ";
		}
		cout << endl;
	}
	return 0;
}
