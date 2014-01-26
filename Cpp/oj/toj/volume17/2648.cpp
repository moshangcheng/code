#include <iostream>
#include <vector>
using namespace std;

const int MAX = 10000;
bool notp[MAX];
bool vst[MAX];
int pn, pr[1500];
vector<pair<int, int> > prmpth;

int main() {
	int i, j, k;
	pn = 0;
	memset(notp, 0, sizeof(notp));
	for (pn = 0, i = 2; i < MAX; i++) {
		if (!notp[i])
			pr[pn++] = i;
		for (j = 0; j < pn && pr[j] * i < MAX; j++) {
			notp[pr[j] * i] = 1;
			if (i % pr[j] == 0)
				break;
		}
	}
	int p1, p2, ntest;
	int d, vlu, tmp1, tmp;
	cin >> ntest;
	while (ntest-- > 0) {
		prmpth.clear();
		memset(vst, 0, sizeof(vst));
		cin >> p1 >> p2;
		vst[p1] = 1;
		prmpth.push_back(make_pair(p1, 0));
		for (i = 0; i < prmpth.size(); i++) {
			d = prmpth[i].second;
			vlu = prmpth[i].first;
			if (vlu == p2)
				break;
			for (j = 1; j < 10000; j *= 10) {
				tmp1 = vlu / (j * 10) * (j * 10) + vlu % j;
				if (j == 1000)
					k = 1;
				else
					k = 0;
				for (; k < 10; k++) {
					tmp = tmp1 + k * j;
					if (notp[tmp] || vst[tmp])
						continue;
					vst[tmp] = 1;
					prmpth.push_back(make_pair(tmp, d + 1));
				}
			}
		}
		if (i == prmpth.size())
			cout << "Impossible\n";
		else
			cout << d << endl;
	}
	return 0;
}
