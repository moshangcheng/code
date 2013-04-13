#include <iostream>
#include <string>
using namespace std;

int main() {
	int ntest;
	string s, ct("cow"), pt("ow");
	bool c[26];
	memset(c, 0, sizeof(c));
	c['a' - 'a'] = c['e' - 'a'] = c['i' - 'a'] = c['o' - 'a'] = c['u' - 'a']
			= 1;
	cin >> ntest;
	while (ntest-- > 0) {
		cin >> s;
		if (c[s[0] - 'a'])
			s.append(ct);
		else {
			char tp = s[0];
			s.erase(0, 1).append(1, tp).append(pt);
		}
		cout << s << endl;
	}
	return 0;
}
