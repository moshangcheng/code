#include <iostream>
#include <string>
using namespace std;

int main() {
	int i, j, s, t;
	string a, b;
	while (cin >> a) {
		if (a == "0")
			break;
		b.clear();
		while (!a.empty()) {
			for (s = i = 0; i < a.size(); s &= 1, i++) {
				s = s * 10 + a[i] - '0';
				a[i] = s / 2 + '0';
			}
			b.append(1, s + '0');
			for (i = 0; a[i] == '0'; i++)
				;
			a.erase(0, i);
		}
		for (i = 0; i < b.size() && b[i] != '0'; i++)
			;
		for (; i < b.size() && b[i] == 0; i++)
			;
		for (j = 0; i < b.size(); i++)
			if (b[i] == '1')
				j++;
		cout << j << endl;
	}
	return 0;
}
