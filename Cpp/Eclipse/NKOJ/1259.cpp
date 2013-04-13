/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1259.html
 */
#include <iostream>
using namespace std;

int main() {
	int N;
	while (cin >> N && N) {
		int A[1000];
		for (int i = 0; i < N; i++)
			cin >> A[i];

		int n = 0, Flag;
		while (1) {
			n++;
			int temp = A[N - 1];
			for (int j = N - 1; j > 0; j--) {
				A[j] = (A[j] + A[j - 1]) / 2;
				if (A[j] % 2 == 1)
					A[j]++;
			}
			A[0] = (A[0] + temp) / 2;
			if (A[0] % 2 == 1)
				A[0]++;
			int k;
			Flag = A[0];
			for (k = 0; k < N; k++)
				if (A[k] != Flag)
					break;
			if (k == N)
				break;
		}
		cout << n << " " << Flag << endl;
	}
	return 0;
}

