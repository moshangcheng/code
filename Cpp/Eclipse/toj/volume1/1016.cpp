#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <algorithm>
using namespace std;

vector<string> p[101][2];
list<pair<int, int> > L;
map<string, int> M;
list<pair<int, int> >::iterator cnt;
char c[26] = { '2', '2', '2', '3', '3', '3', '4', '4', '4', '5', '5', '5', '6',
		'6', '6', '7', '7', '7', '7', '8', '8', '8', '9', '9', '9', '9' };

string convert(const string& a) {
	string b;
	for (int i = 0; i < a.size(); i++)
		b += c[a[i] - 'a'];
	return b;
}

void output(int len) {
	int i, j, max;
	string tmp;
	M.clear();
	map<string, int>::iterator m_cnt, max_e;
	for (cnt = L.begin(); cnt != L.end(); cnt++)
		M[p[cnt->first][0][cnt->second].substr(0, len)] += cnt->first;
	m_cnt = max_e = M.begin();
	for (m_cnt++; m_cnt != M.end(); m_cnt++)
		if (m_cnt->second > max_e->second)
			max_e = m_cnt;
	cout << max_e->first << endl;
}

int main() {
	string s, numb;
	int ntest, otest = 0;
	int i, j, k, tmp, m, nword;
	cin >> ntest;
	while (otest++ < ntest) {
		cin >> nword;
		for (i = 0; i < 101; i++) {
			p[i][0].clear();
			p[i][1].clear();
		}
		for (i = 0; i < nword; i++) {
			cin >> s >> tmp;
			p[tmp][0].push_back(s);
			p[tmp][1].push_back(convert(s));
		}
		cout << "Scenario #" << otest << ":\n";
		cin >> m;
		for (i = 0; i < m; i++) {
			L.clear();
			cin >> numb;
			if (numb[0] == '1') {
				cout << endl;
				continue;
			}
			for (j = 100; j >= 0; j--)
				for (k = 0; k < p[j][1].size(); k++)
					if (p[j][1][k][0] == numb[0])
						L.push_back(make_pair(j, k));
			for (j = 1; j < numb.size(); j++) {
				if (L.empty())
					cout << "MANUALLY\n";
				else
					output(j);
				if (numb[j] == '1')
					break;
				for (cnt = L.begin(); cnt != L.end();)
					if (p[cnt->first][1][cnt->second][j] != numb[j])
						cnt = L.erase(cnt);
					else
						cnt++;
			}
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}
