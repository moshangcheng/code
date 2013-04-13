#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
	int L, N;
	string sw, sr, endc, ends;

	map<string, string> S, C;
	C["sh"] = C["ch"] = C["o"] = C["s"] = C["x"] = "es";

	bool uncon[26];
	memset(uncon, 1, sizeof(uncon));
	uncon[0] = uncon[4] = uncon[8] = uncon[14] = uncon[19] = 0;

	while (cin >> L >> N) {
		S.clear();
		for (int i = 0; i < L; i++) {
			cin >> sw >> sr;
			S[sw] = sr;
		}
		for (int i = 0; i < N; i++) {
			cin >> sw;
			endc = sw.substr(sw.size() - 1);
			if (S.count(sw) > 0)
				sw = S[sw];
			else if (C.count(endc) > 0)
				sw.append(C[endc]);
			else if (sw.size() >= 2) {
				ends = sw.substr(sw.size() - 2);
				if (ends[1] == 'y' && uncon[ends[0] - 'a']) {
					sw.erase(sw.size() - 1);
					sw.append("ies");
				} else if (C.count(ends) > 0)
					sw.append(C[ends]);
				else
					sw.append("s");
			}
			cout << sw << endl;
		}
	}
	return 0;
}

