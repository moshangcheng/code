#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

struct NB {
	string s;
	int n;
};

bool operator <(NB a, NB b) {
	if (a.s[0] == b.s[0])
		return (a.n < b.n) ? 1 : 0;
	return (a.s[0] < b.s[0]);
}

int main() {
	NB t;
	vector<NB> L;
	int N, maxlen, num_test = 0;
	while (cin >> N && N > 0) {
		L.clear();
		maxlen = 0;
		for (int i = 0; i < N; i++) {
			cin >> t.s;
			istringstream is(t.s);
			is >> t.n;
			reverse(t.s.begin(), t.s.end());
			L.push_back(t);
			if (t.s.size() > maxlen)
				maxlen = t.s.size();
		}
		cout << "Case " << ++num_test << ":\n";
		for (int i = 0; i < maxlen; i++) {
			sort(L.begin(), L.end());
			for (int j = 0; j < L.size(); j++) {
				if (j > 0)
					cout << " ";
				cout << L[j].n;
				L[j].s.erase(L[j].s.begin());
				if (L[j].s.empty())
					L[j].s.append(1, '0');
			}
			cout << endl;
		}
	}
	return 0;
}

