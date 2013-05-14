#include <cstdio>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

double calc(ll m, ll k) {
	double p = 1.0;
	for(ll i = 0; i < m; i++) {
		p /= 2.0;
	}
	for(ll i = 1; i <= k; i++) {
		p *= 1.0 * (m - k + i) / i;
	}
	return p;
}


int main() {
	ll T = 0;
	ll N, X, Y, S;
	cin >> T;
	for(ll i = 0; i < T; i++) {
		cin >> N >> X >> Y;
		S = abs(X) + abs(Y);

		ll leastDmd = S * (S - 1) / 2;
		ll mostDmd = (S + 2) * (S + 1) / 2;

		printf("Case #%d: ", i+1);

		if(N <= leastDmd + Y) {
			printf("0.0\n"); 
			continue;
		}

		if(N >= mostDmd) {
			printf("1.0\n");
			continue;
		}

		if(Y == S) {
			printf("0.0\n");
			continue;
		}

		ll R = N - leastDmd;

		if(R > S) {
			if(R > S + Y) {
				printf("1.0\n");
			} else {
				ll base = R - S;

				double p = 0;
				for(ll j = Y; j < R && j < S; j++) {
					p += calc(R - 2 * base, j+1 - base);
				}
				printf("%lf\n", p);
			}

		} else {
			double p = 0;
			for(ll j = Y; j < R; j++) {
				p += calc(R, j+1);
			}
			printf("%lf\n", p);
		}
	}
	return 0;
}