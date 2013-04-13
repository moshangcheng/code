#include <iostream>
using namespace std;

int Power(int n, int p) {
	int k = 1;
	if (p == 0)
		return 1;
	while (p > 0) {
		if (p & 1 == 1)
			k *= n;
		n *= n;
		p /= 2;
	}
	return k;
}

void out(int n) {
	if (n == 0) {
		cout << '@';
		return;
	}
	out(n - 1);
	for (int i = 0, j = Power(3, n - 1); i < j; i++)
		cout << ' ';
	out(n - 1);
}
int main() {
	int n;
	while (cin >> n) {
		out(n);
		cout << endl;
	}
	return 0;
}
