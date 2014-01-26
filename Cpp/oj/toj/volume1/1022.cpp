#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int i, r;
	int a[7], s[7];
	while (1) {
		for (i = 1; i < 7; i++)
			cin >> a[i];
		for (i = 1; i < 7; i++)
			if (a[i] != 0)
				break;
		if (i == 7)
			break;

		memset(s, 0, sizeof(s));
		s[6] = a[6];

		s[5] = a[5];
		a[1] -= s[5] * 11;
		if (a[1] < 0)
			a[1] = 0;

		s[4] = a[4];
		if (s[4] * 5 <= a[2])
			a[2] -= s[4] * 5;
		else {
			a[1] -= (s[4] * 20 - a[2] * 4);
			a[2] = 0;
		}

		s[3] = ceil(a[3] / 4.0);
		r = s[3] * 4 - a[3];
		if (r > 0) {
			if (a[2] >= 2 * r - 1) {
				a[2] -= 2 * r - 1;
				a[1] -= 4 + r;
			} else {
				a[1] -= (9 * r - a[2] * 4);
				a[2] = 0;
			}
		}

		s[2] = ceil(a[2] / 9.0);
		a[1] -= (s[2] * 9 - a[2]) * 4;
		if (a[1] < 0)
			a[1] = 0;
		s[1] = ceil(a[1] / 36.0);

		cout << s[1] + s[2] + s[3] + s[4] + s[5] + s[6] << endl;
	}
	return 0;
}

