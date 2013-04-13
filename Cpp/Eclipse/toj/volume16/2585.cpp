#include <iostream>
#include <string>
using namespace std;

string dict[10000];

int yeah(const string& a, const string& b) {
	int i;
	if (a.size() == b.size() - 1) {
		for (i = 0; i < a.size() && (a[i] == b[i]); i++)
			;
		for (; i < a.size() && (a[i] == b[i + 1]); i++)
			;
		if (i == a.size())
			return 1;
	} else if (a.size() == b.size()) {
		int ad, s, sum;
		sum = s = 0;
		for (i = 0; i < a.size(); i++) {
			sum += a[i] - b[i];
			if (a[i] != b[i]) {
				s++;
				if (s == 2) {
					if (a[i - 1] == b[i] && a[i] == b[i - 1])
						ad = 1;
					else
						return -1;
				} else if (s > 2)
					return -1;
			}
		}
		if (s == 0)
			return 0;
		else if (s == 1)
			return 1;
		else if (s == 2 && sum == 0)
			return 1;
	} else if (a.size() == b.size() + 1) {
		for (i = 0; i < b.size() && (a[i] == b[i]); i++)
			;
		for (; i < b.size() && (a[i + 1] == b[i]); i++)
			;
		if (i == b.size())
			return 1;
	}
	return -1;
}

int main() {
	string tmp;
	int i, j, flag, go, nword, nqry;
	while (cin >> nword) {
		for (i = 0; i < nword; i++)
			cin >> dict[i];
		cin >> nqry;
		for (i = 0; i < nqry; i++) {
			cin >> tmp;
			flag = -1;
			for (j = 0; j < nword; j++) {
				go = yeah(tmp, dict[j]);
				if (go == 0)
					break;
				else if (go == 1 && flag == -1)
					flag = j;
			}
			if (go == 0)
				cout << tmp << " is correct\n";
			else if (flag != -1)
				cout << tmp << " is a misspelling of " << dict[flag] << endl;
			else if (flag == -1)
				cout << tmp << " is unknown\n";
		}
	}
	return 0;
}
