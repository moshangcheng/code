#include <iostream>
#include <string>
#include <stack>
using namespace std;

const int MAX = 1000000;
string s;
bool vst[MAX];
int power[7] = { 1, 10, 100, 1000, 10000, 100000, 1000000 };

bool go(int num, int nb, int vlu) {
	if (nb == power[num] - 1)
		return 1;
	int i, tmp;
	vst[vlu] = 1;
	for (i = 0; i < 10; i++) {
		tmp = vlu * 10 % power[num] + i;
		if (vst[tmp])
			continue;
		if (go(num, nb + 1, tmp) == 1) {
			s += i + '0';
			return 1;
		}
	}
	vst[vlu] = 0;
	return 0;
}

int main() {
	stack<pair<int, int> > vlu;
	int i, j, n, tmp, cnt_vlu;
	while (cin >> n && n > 0) {
		memset(vst, 0, sizeof(vst));
		vlu.push(make_pair(0, 0));
		while (vlu.size() < power[n]) {
			cnt_vlu = vlu.top().first;
			vst[cnt_vlu] = 1;
			for (; vlu.top().second < 10; vlu.top().second++) {
				tmp = cnt_vlu * 10 % power[n] + vlu.top().second;
				if (!vst[tmp]) {
					vlu.top().second++;
					vlu.push(make_pair(tmp, 0));
					break;
				}
			}
			if (vlu.top().first != cnt_vlu)
				continue;
			vst[cnt_vlu] = 0;
			vlu.pop();
		}
		s.clear();
		while (!vlu.empty()) {
			s += vlu.top().first % 10 + '0';
			vlu.pop();
		}
		for (i = 1; i < n; i++)
			s += '0';
		for (i = 0, j = s.size() - 1; i < j; i++, j--) {
			char c = s[i];
			s[i] = s[j];
			s[j] = c;
		}
		cout << s << endl;
	}
	return 0;
}

