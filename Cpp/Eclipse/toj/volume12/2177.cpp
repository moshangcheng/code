//不能使用动态规划，比如 1<=>3  2<=>3  2<=>4 是有通路的 
#include <iostream>
#include <vector>
using namespace std;

struct edge {
	int v, len;
};
vector<edge> L[1000];
bool vst[1000];
int d[1000], n[1000];

int main() {
	edge tp;
	int i, j, v1, v2, len, ntest, A, B, C;
	cin >> ntest;
	while (ntest-- > 0) {
		cin >> A >> B >> C;
		for (i = 0; i < A; i++)
			L[i].clear();
		for (i = 0; i < C; i++) {
			cin >> v1 >> v2 >> tp.len;
			v1--;
			v2--;
			tp.v = v2;
			L[v1].push_back(tp);
			tp.v = v1;
			L[v2].push_back(tp);
		}
		memset(vst, 1, sizeof(vst));
		memset(d, 0x7f, sizeof(d));
		memset(n, 0, sizeof(n));
		d[0] = 0;
		n[0] = 1;
		while (1) {
			int minp = -1, mind = 0x7f7f7f7f;
			for (i = 0; i < A; i++)
				if (vst[i] && d[i] < mind) {
					mind = d[i];
					minp = i;
				}
			if (minp < 0 || minp == B - 1)
				break;
			vst[minp] = 0;
			for (i = 0; i < L[minp].size(); i++) {
				int v = L[minp][i].v;
				len = L[minp][i].len;
				if (vst[v]) {
					if (d[v] > mind + len) {
						n[v] = n[minp];
						d[v] = mind + len;
					} else if (d[v] == mind + len)
						n[v] += n[minp];
				}
			}
		}
		if (B == 1)
			cout << 0 << endl;
		cout << n[B - 1] << endl;
	}
	return 0;
}

