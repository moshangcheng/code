/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1270.html
 */
#include <iostream>
using namespace std;

int A[10], Flag[1000001];

void f(const int &n, const int &S) {
	for (int i = 0; i < 2; i++) {
		if (n < 9)
			f(n + 1, S + A[n] * i);
		else
			Flag[S + A[n] * i] = 1;
	}
}

int main() {
	int N;
	A[0] = 1;
	for (int i = 1; i < 10; i++)
		A[i] = A[i - 1] * i;
	f(0, 0);
	Flag[0] = 0;
	scanf("%d", &N);
	while (N > -1) {
		if (Flag[N])
			printf("YES\n");
		else
			printf("NO\n");
		scanf("%d", &N);
	}
	return 0;
}

