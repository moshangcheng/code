#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

void convert(char c, string& s) {
	char t;
	string tp;
	switch (c) {
	case 'J':
		t = s[s.size() - 1];
		s.erase(s.size() - 1).insert(0, 1, t);
		break;
	case 'C':
		t = s[0];
		s.append(1, t).erase(0, 1);
		break;
	case 'E':
		tp.clear();
		tp.append(s, (s.size() + 1) / 2, s.size() / 2);
		if (s.size() & 1)
			tp.append(1, s[s.size() / 2]);
		tp.append(s, 0, s.size() / 2);
		s = tp;
		break;
	case 'A':
		reverse(s.begin(), s.end());
		break;
	case 'P':
		for (int i = 0; i < s.size(); i++) {
			if (s[i] >= '1' && s[i] <= '9')
				s[i]--;
			else if (s[i] == '0')
				s[i] = '9';
		}
		break;
	case 'M':
		for (int i = 0; i < s.size(); i++) {
			if (s[i] >= '0' && s[i] <= '8')
				s[i]++;
			else if (s[i] == '9')
				s[i] = '0';
		}
		break;
	}
}

int main() {
	int ntest;
	string msn, word;
	cin >> ntest;
	while (ntest-- > 0) {
		cin >> msn >> word;
		for (int i = msn.size() - 1; i >= 0; i--)
			convert(msn[i], word);
		cout << word << endl;
	}
	return 0;
}
