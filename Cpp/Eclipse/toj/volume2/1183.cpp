#include <iostream>
using namespace std;

void nb(int n, int* a) {
	if (n < 0)
		return;
	int i, j, x, m;
	for (i = 0, a[0] = m = 1; n >= m; a[0] -= m, i++, m *= 10) {
		x = n % (m * 10) / m;
		//计算0 * m ~ x-1 * m 中的各个数字的个数
		for (j = 0; j < 10; j++)
			a[j] += i * x * m / 10;
		//计算0 ~ x 中各个数字的个数
		for (j = 0; j < x; j++)
			a[j] += m;
		//计算     x * m 中的各个数字的个数
		a[x] += n % m + 1;
	}
}

int main() {
	int i, a, b, num_a[10], num_b[10];
	while (cin >> a >> b) {
		if (a == 0 && b == 0)
			break;
		if (a > b) {
			b = a ^ b;
			a = b ^ a;
			b = b ^ a;
		}
		for (i = 0; i < 10; i++)
			num_a[i] = num_b[i] = 0;
		nb(b, num_b);
		nb(a - 1, num_a);
		for (i = 0; i < 9; i++)
			cout << num_b[i] - num_a[i] << " ";
		cout << num_b[9] - num_a[9] << endl;
	}
	return 0;
}

