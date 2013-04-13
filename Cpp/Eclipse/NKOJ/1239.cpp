/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1239.html
 */
#include <iostream>
using namespace std;

void sort(int*c, int*flag, int n) {
	int temp;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (c[i] > c[j]) {
				temp = c[i];
				c[i] = c[j];
				c[j] = temp;
				temp = flag[i];
				flag[i] = flag[j];
				flag[j] = temp;
			}
}

int main() {
	int N;
	cin >> N;
	while (N-- > 0) {
		int n;
		cin >> n;
		char X;
		int C[52], Flag[52], S = 0;
		int m = n * 2;
		for (int j = 0; j < m; j++) {
			if (j < n)
				Flag[j] = 1;
			else
				Flag[j] = -1;
		}
		for (int i = 0; i < n; i++)
			cin >> X >> C[i] >> C[n + i];

		sort(C, Flag, m);
		for (int k = 0; k < m - 1; k++) {
			S += Flag[k];
			for (int t = C[k]; t < C[k + 1]; t++)
				if (S)
					cout << char(S + 64);
		}
		cout << endl;
	}
	return 0;
}
