#include <iostream>
#include <string>
using namespace std;

int period[1000000], p[1000000];

int main() {
	string s;
	int i, j, n, sum;
	cin >> n;
	while (n-- > 0) {
		cin >> s;
		sum = 1;
		period[0] = 1;
		p[0] = -1;
		for (j = -1, i = 1; i < s.size(); i++) {
			while (j > -1 && s[j + 1] != s[i])
				j = p[j];
			if (s[j + 1] == s[i])
				j++;
			p[i] = j;
			if (j == -1)
				period[i] = i + 1;
			else if (period[i - j - 1] != period[j])
				period[i] = i + 1;
			else
				period[i] = period[j];
			sum += (i + 1) / period[i];
			sum %= 2006;
		}
		cout << sum << endl;
	}
	return 0;
}
