#include <iostream>
using namespace std;

const int MAXSIZE = 10001;
int s[100], f[MAXSIZE], g[MAXSIZE];

int main() {
	int i, j, k, flag, n, m, vlu;
	while (cin >> k && k > 0) {
		for (i = 0; i < k; i++)
			cin >> s[i];
		memset(g, 0, sizeof(g));
		for (i = 0; i < MAXSIZE; i++) {
			for (j = 0; j < k; j++)
				if (i >= s[j])
					g[f[i - s[j]]] = i + 1;
			for (j = 0; g[j] == i + 1; j++)
				;
			f[i] = j;
		}
		cin >> n;
		while (n-- > 0) {
			cin >> m;
			for (flag = i = 0; i < m; i++) {
				cin >> vlu;
				flag ^= f[vlu];
			}
			if (flag > 0)
				cout << 'W';
			else
				cout << 'L';
		}
		cout << endl;
	}
	return 0;
}
