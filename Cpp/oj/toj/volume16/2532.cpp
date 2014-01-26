#include <iostream>
#include <cmath>
using namespace std;

typedef long long ll;
ll gcd(ll a, ll b) {
	while (a != 0) {
		ll c = b % a;
		b = a;
		a = c;
	}
	return b;
}

ll modpower(ll n, ll p, ll b) {
	ll k = 1;
	if (p == 0)
		return 1;
	while (p > 0) {
		if (p & 1 == 1)
			k = k * n % b;
		n = n * n % b;
		p /= 2;
	}
	return k;
}

ll EulerPHI(ll n) {
	if (n == 1)
		return 1;
	ll i = 2, m = n, root = floor(sqrt(double(m)));
	for (; i <= root; i++) {
		if (m % i == 0) {
			n -= n / i;
			for (; m % i == 0; m /= i)
				;
			root = floor(sqrt(m));
		}
	}
	if (m != 1)
		n -= n / m;
	return n;
}

int main() {
	char c;
	ll len, p, q, d, i, bound, phi, otest = 0;
	while (cin >> p >> c >> q) {
		d = gcd(p, q);
		p /= d;
		q /= d;
		for (len = 0; (q & 1) == 0; len++)
			q >>= 1;
		phi = EulerPHI(q);
		bound = floor(sqrt(phi));
		for (i = 2; i <= bound; i++) {
			if (phi % i == 0) {
				while (modpower(2, phi / i, q) == 1)
					phi /= i;
				bound = floor(sqrt(phi));
			}
		}
		cout << "Case #" << ++otest << ": ";
		cout << len + 1 << "," << phi << endl;
	}
	return 0;
}

