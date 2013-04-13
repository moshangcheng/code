#include <iostream>
#include <string>
using namespace std;

string s[1001];
int L[1000000][2];

int main() {
	char C;
	int a[4][2] = { -1, 0, 0, 1, 1, 0, 0, -1 };
	int i, j, k, nop, m, n, l, lm, ln, r, c, tr, tc, otest = 0;
	while (1) {
		s[0].clear();
		for (m = 0; cin >> s[m]; m++)
			if (s[m][0] < 'a' || s[m][0] > 'z') {
				for (i = 0, nop = 0; i < s[m].size(); i++)
					nop = nop * 10 + s[m][i] - '0';
				break;
			}
		if (m == 0)
			break;
		n = s[0].size();
		for (i = 0; i < nop; i++) {
			cin >> r >> c;
			r--;
			c--;
			if (r >= m || c >= n)
				continue;
			C = s[r][c];
			s[r][c] = ' ';
			if (C == ' ')
				continue;
			L[0][0] = r;
			L[0][1] = c;
			for (l = 1, j = 0; j < l; j++) {
				for (k = 0; k < 4; k++) {
					tr = L[j][0] + a[k][0];
					tc = L[j][1] + a[k][1];
					if (tr >= 0 && tr < m && tc >= 0 && tc < n)
						if (s[tr][tc] == C) {
							L[l][0] = tr;
							L[l++][1] = tc;
							s[tr][tc] = ' ';
						}
				}
			}
			for (n = lm = j = 0; j < m; j++) {
				for (ln = k = 0; k < s[j].size(); k++)
					if (s[j][k] != ' ')
						s[lm][ln++] = s[j][k];
				if (ln == 0)
					continue;
				if (ln > n)
					n = ln;
				s[lm++].erase(ln);
			}
			m = lm;
			for (j = 0; j < m; j++)
				s[j].append(n - s[j].size(), ' ');
			for (j = m - 1; j > 0; j--) {
				for (k = 0; k < n; k++)
					if (s[j][k] == ' ')
						for (int t = j - 1; t >= 0; t--)
							if (s[t][k] != ' ') {
								s[j][k] = s[t][k];
								s[t][k] = ' ';
								break;
							}
			}
		}
		cout << "Test case #" << ++otest << ":\n";
		for (j = 0; j < m; j++)
			cout << s[j] << endl;
	}
	return 0;
}
