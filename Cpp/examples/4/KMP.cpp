/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-10-17 下午03:08:43
 * @brief
 */

#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

void getPreffixFunction(string str, vector<int>& pi) {
	int k = -1;
	pi[0] = -1;
	for (int i = 1; i < str.size(); i++) {
		while (k >= 0 && str[k + 1] != str[i]) {
			k = pi[k];
		}
		if (str[k + 1] == str[i]) {
			k++;
		}
		pi[i] = k;
	}
}

void KMP(string p, string t) {
	vector<int> pi(p.size());
	getPreffixFunction(p, pi);
	int q = -1;
	for (int i = 0; i < t.size(); i++) {
		while (q >= 0 && p[q + 1] != t[i]) {
			q = pi[q];
		}
		if (p[q + 1] == t[i]) {
			q++;
		}
		if (q + 1 == p.size()) {
			cout << "position " << i + 1 - p.size() << " match success\n";
			q = pi[q];
		}
	}
}

int main() {
	string text = "faabc";
	string pattern = "aabc";
	KMP(pattern, text);
	return 0;
}
