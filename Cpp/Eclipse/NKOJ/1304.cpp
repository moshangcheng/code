/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1304.html
 */

#include <iostream>
#include <math.h>
using namespace std;

int f(int n) {
	int S = 0;
	while (n) {
		S += n % 10;
		n = n / 10;
	}
	return S;
}

int main() {
	int P[10000], i, k = 1, j;
	P[0] = 2;
	for (i = 3; i < 100000; i++) {
		double temp = sqrt(double(i));
		for (j = 0; P[j] < temp; j++)
			if (i % P[j] == 0)
				break;
		if (P[j] >= temp)
			P[k++] = i;
	}

	int N;
	while (cin >> N) {
		if (N == 0)
			break;
		int n = N, S, Temp, Num;
		while (++n) {
			S = 0;
			Temp = n;
			for (i = 0; i < k && P[i] < Temp; i++) {
				Num = 0;
				while (Temp % P[i] == 0) {
					Num++;
					Temp = Temp / P[i];
				}
				if (Num)
					S += Num * f(P[i]);
			}
			if (Temp > 1)
				S += f(Temp);
			if (Temp != n && S == f(n)) {
				cout << n << endl;
				break;
			}
		}
	}
	return 0;
}
