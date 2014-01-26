#include <iostream>
#include <vector>
using namespace std;

struct ROAD {
	int i, d;
};

int d[1000];
bool vst[1000];
vector<ROAD> P[1000];

int main() {
	int num_test, N, M;
	int start, end, x, y, dist;
	cin >> num_test;
	while (num_test-- > 0) {
		cin >> N >> M >> start >> end;
		memset(vst, 1, sizeof(vst));
		memset(d, 0x7f, sizeof(d));
		for (int i = 0; i < N; i++)
			P[i].clear();
		start--;
		end--;
		for (int i = 0; i < M; i++) {
			cin >> x >> y >> dist;
			x--;
			y--;
			ROAD tp = { x, dist };
			P[y].push_back(tp);
			tp.i = y;
			P[x].push_back(tp);
		}

		d[start] = 0;
		while (1) {
			int minp = -1, mind = 0x7f7f7f7f;
			for (int i = 0; i < N; i++)
				if (vst[i] && d[i] < mind) {
					minp = i;
					mind = d[i];
				}
			if (minp == -1 || minp == end)
				break;
			vst[minp] = 0;
for		(int i = 0; i < P[minp].size(); i++)
		d[ P[minp][i].i ] <?= mind + P[minp][i].d;
	}
	if(d[end] == 0x7f7f7f7f) cout << -1 << endl;
	else cout << d[end] << endl;
}
return 0;
}

