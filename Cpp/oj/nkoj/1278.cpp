/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1278.html
 */

#include <iostream>
using namespace std;

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

int main() {
	int N;
	while (cin >> N) {
		int*Ax = new int[N];
		int*Ay = new int[N];
		for (int i = 0; i < N; i++) {
			cin >> Ax[i] >> Ay[i];
			if (Ax[i] > Ay[i])
				swap(Ax[i], Ay[i]);
		}

		for (int i1 = 0; i1 < N; i1++)
			for (int i2 = i1 + 1; i2 < N; i2++)
				if (Ay[i1] > Ay[i2]) {
					swap(Ay[i1], Ay[i2]);
					swap(Ax[i1], Ax[i2]);
				}
		int m = Ay[0], S = 1;
		for (int j = 1; j < N; j++)
			if (m < Ax[j]) {
				m = Ay[j];
				S++;
			}
		S = N - S;
		cout << S << endl;
	}
	return 0;
}
