#include <iostream>
#include <string>
#include <stack>
using namespace std;

int inline convert(char c) {
	if (c >= 'A' && c <= 'Z')
		return c - 'A' + 1;
	else if (c >= '0' && c <= '9')
		return c - '0';
	else if (c == '-')
		return -1;
	else if (c == '+')
		return -2;
}

int operation(int c1, char c2, int c3) {
	if (c2 == '+')
		return (c1 + c3 + 25) % 26 + 1;
	else if (c2 == '-')
		return (c1 - c3 + 25) % 26 + 1;
	else if (c2 == '*')
		return (c1 * c3 + 25) % 26 + 1;
	else if (c2 == '/')
		return (c1 / c3 + 25) % 26 + 1;
}

int main() {

	string s;
	int c1;
	char c2, c3;
	while (cin >> s) {
		stack<char> left, right;
		for (int i = 0; i <= s.size(); i++) {
			if (i < s.size() && s[i] != ')')
				left.push(s[i]);
			else {
				while (!left.empty() && left.top() != '(') {
					right.push(left.top());
					left.pop();
				}
				if (!left.empty())
					left.pop();
				if (!right.empty()) {
					c1 = convert(right.top());
					right.pop();
					if (c1 < 0) {
						if (c1 == -1)
							c1 = 26 - convert(right.top());
						else
							c1 = convert(right.top());
						right.pop();
					}
					while (!right.empty()) {
						c2 = right.top();
						right.pop();
						c3 = right.top();
						right.pop();
						c1 = operation(c1, c2, convert(c3));
					}
					left.push(char(c1 - 1 + 'A'));
				}
			}
		}
		cout << s << "=" << left.top() << endl;
	}
	return 0;
}

