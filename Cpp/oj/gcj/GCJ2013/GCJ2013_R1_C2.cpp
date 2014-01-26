#include <cstdio>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

const ll MAX = 1000;

ll x, y;
ll X, Y;

char dir[MAX];

bool isPossible(ll n, ll k) {
	if(k == n + 1) {
		if(x == X && y == Y) {
			return true;
		}
		return false;
	}
	ll remain = (k + n) * ( n - k + 1) / 2;
	if( abs(X - x) > remain || abs(Y - y) > remain) {
		return false;
	}
	for(ll i = 0; i < 4; i++) {
		switch(i) {
		case 0:
			dir[k-1] = 'E';
			x += k;
			if(isPossible(n, k+1)) {
				return true;
			}
			x -= k;
			break;
		case 1:
			dir[k-1] = 'S';
			y -= k;
			if(isPossible(n, k+1)) {
				return true;
			}
			y += k;
			break;
		case 2:
			dir[k-1] = 'W';
			x -= k;
			if(isPossible(n, k+1)) {
				return true;
			}
			x += k;
			break;
		case 3:
			dir[k-1] = 'N';
			y += k;
			if(isPossible(n, k+1)) {
				return true;
			}
			y -= k;
			break;
		default:
			break;
		}
	}
	return false;
}


int main() {
	
	ll T = 0;
	scanf("%lld", &T);
	for(ll i = 0; i < T; i++) {
		scanf("%lld%lld", &X, &Y);

		ll S = abs(X) + abs(Y);
		for(ll j = 1; j < MAX; j++) {
			ll M = j * (j + 1) / 2;
			if( (M%2) != (S%2) || M < S) {
				continue;
			}
			x = y = 0;
			if(isPossible(j, 1)) {
				cout << "Case #" << (i+1) << ": " << dir << endl;
				break;
			}
		}
	}
	return 0;
}
