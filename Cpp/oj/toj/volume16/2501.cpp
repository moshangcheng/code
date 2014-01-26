#include <iostream>
#include <string>
using namespace std;

int main() {
	int ntest, i, sum, cnt;
	string s;
	cin >> ntest;
	while (ntest-- > 0) {
		cin >> s;
		for (sum = cnt = i = 0; i < s.size(); i++) {
			if (s[i] == 'O')
				sum += ++cnt;
			else
				cnt = 0;
		}
		cout << sum << endl;
	}
	return 0;
}

