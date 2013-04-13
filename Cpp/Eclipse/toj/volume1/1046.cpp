#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAX = 5000;
vector<int> L, tp;
bool vst[MAX], flag[MAX];
string s1[MAX], s2[MAX];

bool inline notzero(const string& s) {
	return s[s.size() - 1] != '0';
}

int main() {
	int i, j, k, mod, m, N, M, a[10];
	while (cin >> N >> M) {
		for (i = 0; i < M; i++) {
			cin >> k;
			for (j = i; j > 0; j--)
				if (k < a[j - 1])
					a[j] = a[i - 1];
				else
					break;
			a[j] = k;
		}
		L.clear();
		memset(flag, 0, sizeof(flag));
		memset(vst, 0, sizeof(vst));
		for (i = 0; i < MAX; i++)
			s1[i].clear();
		for (i = 0; i < M; i++) {
			L.push_back(a[i]);
			s1[a[i]] += a[i] + '0';
			flag[a[i]] = 1;
		}
		vst[1] = 1;
		mod = 10 % N;
		while (1) {
			if (flag[0] && notzero(s[0]))
				break;
			/*if(vst[mod] == 1) {
			 for(i = N-1; i >= 0; i--)
			 if(flag[i] && N%i == 0) {
			 for(k = N/i; k > 0; k--) {
			 for(j = s1[i].size()-1; j >= 0; j--)
			 cout << s1[i][j];
			 }
			 cout << endl;
			 break;
			 }
			 if(i < 0) cout << 0 << endl;
			 break;
			 }*/
			vst[mod] = 1;
			tp.clear();
			memset(flag, 0, sizeof(flag));
			for (i = 0; i < M; i++) {
				for (j = 0; j < L.size(); j++) {
					k = (L[j] + a[i] * mod) % N;
					if (!flag[k]) {
						tp.push_back(k);
						s2[k] = s1[L[j]] + char(a[i] + '0');
						flag[k] = 1;
					}
				}
				if (flag[0] && notzero(s[0]))
					break;
			}
			L = tp;
			for (i = 0; i < L.size(); i++)
				s1[L[i]] = s2[L[i]];
			mod = mod * 10 % N;
		}
		if (flag[0]) {
			for (j = s1[0].size() - 1; j >= 0; j--)
				cout << s1[0][j];
			cout << endl;
		}
	}
	return 0;
}
