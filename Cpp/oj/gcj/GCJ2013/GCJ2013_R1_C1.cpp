#include <cstdio>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

const ll MAX = 1000000;

char name[MAX+1];

bool isVowel[26];


int main() {
	for(ll i = 0; i < 26; i++) {
		isVowel[i] = false;
	}
	isVowel['a'-'a'] = isVowel['e'-'a'] = isVowel['i'-'a'] = isVowel['o'-'a'] = isVowel['u'-'a'] = true;

	ll T = 0;
	ll N;
	scanf("%lld", &T);
	for(ll i = 0; i < T; i++) {
		scanf("%s%lld", name, &N);

		bool flag = false;
		ll len = strlen(name);

		ll start = 0, m = 0, acc = 0, sum = 0, num = 0;

		for(ll j = 0; name[j] != '\0'; j++) {
			if(!isVowel[name[j] - 'a']) {
				if(acc == N-1) {
					sum += j - (N-1) + 1;
					num += m - (N - 1) + 1;
					m = N - 1;
				} else {
					m++;
					sum += num;
					acc++;
				}
			} else {
				m++;
				sum += num;
				acc = 0;
			}
		}
		cout << "Case #" << (i+1) << ": " << sum << endl;
	}
	return 0;
}
