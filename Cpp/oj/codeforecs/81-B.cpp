#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <map>
using namespace std;

struct Senator {
	int level, l;
	Senator(int level, int l) :
		level(level), l(l) {
	}
};

double maxP;
int n, k, A;
vector<Senator> senators;

double dfs(int n, int m, int l) {
	if (n == senators.size()) {
		if (2 * m > n) {
			return 1.0;
		} else {
			return 1.0 * A / (A + l);
		}
	}
	double p = senators[n].l * dfs(n + 1, m + 1, l) / 100 + (100
			- senators[n].l) * dfs(n + 1, m, l + senators[n].level) / 100;
	return p;
}

void solve(int n, int k) {
	if (n == senators.size()) {
		double p = dfs(0, 0, 0);
		if (p > maxP) {
			maxP = p;
		}
	}
	for (int i = k; i >= 0; i--) {
		if (senators[n].l + i * 10 > 100) {
			continue;
		}
		senators[n].l += i * 10;
		solve(n + 1, k - i);
		senators[n].l -= i * 10;
	}
}

int main() {
	while (cin >> n >> k >> A) {
		maxP = -1.0;
		senators.clear();
		for (int i = 0; i < n; i++) {
			int level, l;
			cin >> level >> l;
			senators.push_back(Senator(level, l));
		}
		solve(0, k);
		cout.setf(ios::fixed);
		cout.precision(10);
		cout << maxP << endl;
	}
	return 0;
}
