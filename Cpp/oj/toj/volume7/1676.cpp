#include <iostream>
#include <vector>
using namespace std;

struct edge {
	int i, d;
};

int main() {
	edge t;
	bool vst[50];
	vector<edge> p[50];
	int N, M, s, e, dist, i, j, sum, d[50];
	while (cin >> N >> M) {
		for (i = 0; i < N; i++)
			p[i].clear();
		for (i = 0; i < M; i++) {
			cin >> s >> e >> dist;
			s--;
			e--;
			t.i = e;
			t.d = dist;
			p[s].push_back(t);
			t.i = s;
			p[e].push_back(t);
		}
		memset(vst, 0, sizeof(vst));
		memset(d, 0x7f, sizeof(d));
		sum = d[0] = 0;
		for (i = 0; i < N; i++) {
			int minp = -1, mind = 0x7f7f7f7f;
			for (j = 0; j < N; j++)
				if (vst[j] == 0 && d[j] < mind) {
					mind = d[j];
					minp = j;
				}
			if (minp == -1)
				break;
			vst[minp] = 1;
			sum += mind;
			for (j = 0; j < p[minp].size(); j++) {
				t = p[minp][j];
				if (vst[t.i] == 0 && d[t.i] > t.d)
					d[t.i] = t.d;
			}
		}
		cout << sum << endl;
	}
	return 0;
}

