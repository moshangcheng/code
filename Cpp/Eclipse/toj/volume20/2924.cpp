#include <iostream>
using namespace std;

int main() {
	int N, P, T;
	bool flag[10];
	int n[10], s[1000], w[100], t[1000];
	while (cin >> N) {
		memset(flag, 0, sizeof(flag));
		for (int i = 0; i < N; i++) {
			cin >> n[i];
			if (flag[n[i]]) {
				i--;
				N--;
			} else
				flag[n[i]] = 1;
		}
		cin >> P >> T;

		w[0] = 1;
		memset(s, 0, sizeof(s));
		for (int j = 0; j < N; j++)
			s[n[j] % T]++;
		for (int i = 1; i < P; i++) {
			w[i] = w[i - 1] * 10 % T;
			memset(t, 0, sizeof(t));
			for (int j = 0; j < N; j++) {
				if (i == P - 1 && n[j] == 0)
					continue;
				for (int k = 0; k < T; k++)
					t[(k + w[i] * n[j]) % T] += s[k];
			}
			for (int j = 0; j < T; j++)
				t[j] %= 1000001;
			memcpy(s, t, sizeof(t));
		}
		cout << s[0] << endl;
	}
	return 0;
}
