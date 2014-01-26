#include <iostream>
#include <cmath>
using namespace std;

const double C = ((sqrt(5.0) + 1.0) / 2);

int F(int n) {
	return floor(pow(C, n + 1.0) / sqrt(5.0) + 0.5);
}
int cpt(int n) {
	int i;
	for (i = 0; F(i + 2) <= n; i++)
		;
	return i + 1;
}

int main() {
	char a[100];
	int ntest, N, maxlen, tp;
	cin >> ntest;
	while (ntest-- > 0) {
		cin >> N;
		maxlen = cpt(N);
		memset(a, '0', sizeof(a));
		a[0] = '1';
		N -= F(maxlen);
		while (N > 0) {
			tp = cpt(N);
			a[maxlen - tp] = '1';
			N -= F(tp);
		}
		for (int i = 0; i < maxlen; i++)
			cout << a[i];
		cout << endl;
	}
	return 0;
}

