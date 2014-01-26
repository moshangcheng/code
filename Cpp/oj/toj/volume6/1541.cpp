#include <iostream>
#include <string>
using namespace std;

int s[6000];

int main() {
	string str;
	int i, cnt, prev;
	while (cin >> str) {
		if (str == "0")
			break;
		s[0] = 1;
		prev = str[0] - '0';
		for (i = 1; i < str.size(); prev = cnt, i++) {
			s[i] = 0;
			cnt = str[i] - '0';
			if (prev > 0 && prev * 10 + cnt < 27) {
				if (i == 1)
					s[i]++;
				else
					s[i] += s[i - 2];
			}
			if (cnt != 0)
				s[i] += s[i - 1];
		}
		cout << s[str.size() - 1] << endl;
	}
	return 0;
}

