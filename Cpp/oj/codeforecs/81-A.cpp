#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <map>
using namespace std;

map<string, int> skills;

int main() {
	int n, m;
	double k;
	while (cin >> n >> m >> k) {
		skills.clear();
		for (int i = 0; i < n; i++) {
			int exp;
			string skill;
			cin >> skill >> exp;
			double newExp = exp * k + 1e-6;
			if (newExp < 100) {
				continue;
			} else {
				skills[skill] = floor(newExp);
			}
		}
		for (int i = 0; i < m; i++) {
			string skill;
			cin >> skill;
			if (skills.find(skill) == skills.end()) {
				skills[skill] = 0;
			}
		}
		map<string, int>::iterator cnt = skills.begin();
		map<string, int>::iterator end = skills.end();
		cout << skills.size() << endl;
		for (; cnt != end; cnt++) {
			cout << (*cnt).first << " " << (*cnt).second << "\n";
		}
	}
	return 0;
}
