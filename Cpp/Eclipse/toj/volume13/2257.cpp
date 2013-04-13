#include <iostream>
using namespace std;

int main() {
	char cnt[200];
	int n, k, m, s, prev, ntest;
	cin >> ntest;
	while (ntest-- > 0) {
		cin >> n >> k;
		for (prev = m = 0, s = n * k;; m++) {
			s = s + prev * n;
			cnt[m] = s % 10 + '0';
			s = s / 10;
			prev = cnt[m] - '0';
			if (prev == k && s == 0)
				break;
		}
		if (n > k) {
			cout << 0 << endl;
			continue;
		}
		for (int i = m - 1; i >= 0; i--)
			cout << cnt[i];
		cout << k << endl;
	}
	return 0;
}

