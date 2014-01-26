#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;
	int i, n, any, part;
	while (1) {
		cin >> s;
		if (s == "*")
			break;
		for (i = 0; i < s.size() && s[i] == ' '; i++)
			;
		s.erase(0, i);
		for (i = s.size() - 1; i >= 0 && s[i] == ' '; i--)
			;
		s.erase(i, s.size() - 1 - i);
		any = i = n = part = 0;
		if (s[0] == '+' || s[0] == '-')
			i = 1;
		for (; i < s.size(); i++) {
			if (s[i] == '.') {
				if (any > 0 || n == 0)
					break;
				any++;
				n = 0;
			} else if (s[i] == 'e' || s[i] == 'E') {
				if (part == 0 && n > 0) {
					if (i == s.size() - 1)
						break;
					any++;
					part = 1;
					n = 0;
					if (s[i + 1] == '+' || s[i + 1] == '-')
						i++;
				} else
					break;
			} else if (s[i] <= '9' && s[i] >= '0')
				n++;
			else
				break;
		}
		cout << s << " is ";
		if (any > 0 && i == s.size() && n > 0)
			cout << "legal.\n";
		else
			cout << "illegal.\n";
	}
	return 0;
}
