#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;

const int MAX = 1 << 15;

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

int main() {
	int i, j, bound;
	vector<int> prime;
	prime.push_back(2);
	for (i = 3; i < MAX; i++) {
		bound = floor(sqrt(i));
		for (j = 0; prime[j] <= bound; j++)
			if (i % prime[j] == 0)
				break;
		if (prime[j] > bound)
			prime.push_back(i);
	}

	string s;
	vector<pair<int, int> > L;
	int p, m, sum;
	while (getline(cin, s)) {
		sum = 1;
		L.clear();
		if (s == "0")
			break;
		istringstream is(s);
		while (is >> p >> m)
			sum *= Power(p, m);
		sum++;
		for (i = 0; sum > 1; i++) {
			if (sum % prime[i] != 0) {
				if (prime[i] > sqrt(sum)) {
					L.push_back(pair<int, int> (sum, 1));
					break;
				}
				continue;
			}
			for (j = 0; sum % prime[i] == 0; j++)
				sum /= prime[i];
			L.push_back(pair<int, int> (prime[i], j));
		}
		for (i = L.size() - 1; i > 0; i--)
			cout << L[i].first << " " << L[i].second << " ";
		cout << L[0].first << " " << L[0].second << endl;
	}
	return 0;
}
