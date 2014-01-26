#include <iostream>
#include <string>
using namespace std;

struct PRICE {
	int ins, del;
};

int main() {
	char c;
	string a;
	PRICE p[26];
	int N, M, i, j, l;
	int s[2000][2000];
	while (cin >> N >> M >> a) {
		for (i = 0; i < N; i++) {
			cin >> c;
			cin >> p[c - 'a'].ins >> p[c - 'a'].del;
		}
		memset(s, 0, sizeof(s));
		for (l = 1; l < M; l++)
			for (i = 0; i < M - l; i++) {
				j = i + l;
				int t, minp = 1000000000;
				if (a[i] == a[j])
					minp = s[i + 1][j - 1];
				if ((t = s[i][j - 1] + p[a[j] - 'a'].del) < minp)
					minp = t;
				if ((t = s[i][j - 1] + p[a[j] - 'a'].ins) < minp)
					minp = t;
				if ((t = s[i + 1][j] + p[a[i] - 'a'].del) < minp)
					minp = t;
				if ((t = s[i + 1][j] + p[a[i] - 'a'].ins) < minp)
					minp = t;
				s[i][j] = minp;
			}
		cout << s[0][M - 1] << endl;
	}
	return 0;
}

