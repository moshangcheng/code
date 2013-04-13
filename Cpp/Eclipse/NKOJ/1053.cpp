/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1053.html
 */
#include <iostream>
using namespace std;

int main() {
	bool Flag[32768];
	int P[4000], flag = 0;
	Flag[2] = 1;
	P[0] = 2;
	for (int i = 3; i < 32768; i++) {
		int j;
		for (j = 2; j < i; j++)
			if (Flag[j] && i % j == 0) {
				Flag[i] = 0;
				break;
			}
		if (j == i) {
			Flag[i] = 1;
			P[++flag] = i;
		}
	}
	int N;
	while (cin >> N && N) {
		int temp = N / 2 + 1, s = 0;
		for (int k = 0; P[k] < temp; k++)
			if (Flag[N - P[k]])
				s++;
		cout << s << endl;
	}
	return 0;
}

