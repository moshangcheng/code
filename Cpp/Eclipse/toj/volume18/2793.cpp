#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const unsigned MAX = floor(sqrt(1000000000));

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
	unsigned ntest, N, s, T;
	cin >> ntest;
	while (ntest-- > 0) {
		cin >> N;
		for (s = 1, T = N, i = 0; T > 1; i++) {
			if (T % prime[i] != 0) {
				if (prime[i] > sqrt(T))
					break;
				continue;
			}
			for (j = 0; T % prime[i] == 0; j++)
				T /= prime[i];
			s *= prime[i];
		}
		s *= T;
		cout << N / s + 1 << endl;
	}
	return 0;
}
