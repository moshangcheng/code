/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-8-12 下午07:57:52
 * @brief GCJ2011 R1A B
 * http://code.google.com/codejam/contest/dashboard?c=1145485#s=p0
 * http://code.google.com/codejam/contest/dashboard?c=1145485#s=a&a=0
 */
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int gcd(int a, int b) {
	while (a != 0) {
		int c = b % a;
		b = a;
		a = c;
	}
	return b;
}

bool solve(long long N, int Pd, int Pg) {
	long long minD = 100 / gcd(Pd, 100);
	long long maxD = N;
	if (Pg == 100 && Pd != 100) {
		return false;
	}
	if(Pg == 0 && Pd != 0) {
		return false;
	}
	if (minD > maxD) {
		return false;
	}
	return true;
}

int source(istream& cin, ostream& cout) {
//int main() {
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) {
		long long N;
		int Pd, Pg;
		cin >> N >> Pd >> Pg;
		cout << "Case #" << i + 1 << (solve(N, Pd, Pg) ? ": Possible" : ": Broken") << endl;
	}
	return 0;
}
