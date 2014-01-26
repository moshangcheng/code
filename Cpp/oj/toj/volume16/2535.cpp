#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX = 1 << 16;

int make(int p) {
	int a = floor(sqrt(p / 4));
	int b = floor(sqrt(p - 4 * a * a));
	while (b * b + 4 * a * a != p) {
		a -= 1;
		b = floor(sqrt(p - 4 * a * a));
	}
	return (2 * a > b) ? 2 * a : b;
}

void output(int n) {
	int a, b;
	if (n % 4 == 3)
		cout << n;
	else if (n == 2 || n % 4 == 1) {
		if (n == 2)
			a = b = 1;
		else {
			b = make(n);
			a = floor(sqrt(n - b * b));
		}
		cout << a << "+";
		if (b > 1)
			cout << b;
		cout << "j, ";
		cout << a << "-";
		if (b > 1)
			cout << b;
		cout << "j";
	}
}

int main() {
	unsigned i, j, bound;
	vector<unsigned> prime;
	prime.push_back(2);
	for (i = 3; i < MAX; i++) {
		bound = floor(sqrt(i));
		for (j = 0; prime[j] <= bound; j++)
			if (i % prime[j] == 0)
				break;
		if (prime[j] > bound)
			prime.push_back(i);
	}
	int n, a, b, ntest = 0;
	while (cin >> n) {
		cout << "Case #" << ++ntest << ": ";
		if (n == 1) {
			cout << 1 << endl;
			continue;
		}
		for (i = 0; n > 1; i++) {
			if (n % prime[i] != 0) {
				if (prime[i] > sqrt(n)) {
					output(n);
					n = 1;
				}
				continue;
			}
			while (n % prime[i] == 0)
				n /= prime[i];
			output(prime[i]);
			if (n > 1)
				cout << ", ";
		}
		cout << endl;
	}
	return 0;
}

