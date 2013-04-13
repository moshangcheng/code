#include <iostream>
using namespace std;

int main() {
	double r;
	unsigned long long n, sum;
	while (cin >> r >> n) {
		if (r < 1e-10) {
			if (n > 0)
				sum = 2 * n;
			else
				sum = 1;
		} else if (n == 0)
			sum = 2;
		else {
			if ((n + 1) & 1)
				sum = (n + 2) / 2 * (n + 1);
			else
				sum = (n + 1) / 2 * (n + 2);
		}
		cout << sum << endl;
	}
	return 0;
}

