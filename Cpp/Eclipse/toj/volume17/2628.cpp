#include <iostream>
#include <string>
using namespace std;

bool sub(const string& s1, const string& s2) {
	int i, j;
	for (i = 0, j = 0; i < s1.size() && j < s2.size(); i++)
		if (s1[i] == s2[j])
			j++;
	if (j == s2.size())
		return 1;
	return 0;
}

int main() {
	int i, j, ntest;
	cin >> ntest;
	string s1, s2;
	while (ntest-- > 0) {
		cin >> s1 >> s2;
		if (sub(s1, s2))
			cout << "YES\n";
		else {
			reverse(s2.begin(), s2.end());
			if (sub(s1, s2))
				cout << "YES\n";
			else
				cout << "NO\n";
		}
	}
	return 0;
}
