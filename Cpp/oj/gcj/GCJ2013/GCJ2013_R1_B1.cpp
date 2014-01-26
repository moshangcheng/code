#include <cstdio>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

const ll MAX = 100;
ll motes[MAX];
ll bigger[MAX];





int main() {
	ll T = 0;
	ll A, N;
	cin >> T;
	for(ll i = 0; i < T; i++) {
		cin >> A >> N;
		for(ll j = 0; j < N; j++) {
			cin >> motes[j];
		}

		if(A == 1) {
			cout << "Case #" << (i+1) << ": " << N << endl;
			continue;
		}

		sort(motes, motes + N);

		ll opCount = 0, sum = A;
		for(ll j = 0; j < N; j++) {
			ll k = 0;
			while(sum <= motes[j]) {
				sum += sum - 1;
				k++;
			}
			if(N - j < k) {
				opCount += N - j;
				break;
			} else {
				sum += motes[j];
				opCount += k;
			}
		}
		if(opCount > N) {
			opCount = N;
		}
		cout << "Case #" << (i+1) << ": " << opCount << endl;
	}
	return 0;
}