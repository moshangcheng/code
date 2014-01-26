#include <iostream>
#include <string>
using namespace std;

int main() {
	int ntest, otest = 0;
	string s;
	string::iterator cnt;
	cin >> ntest;
	while (otest < ntest) {
		cin >> s;

		cout << "URL #" << ++otest << endl;
		cout << "Protocol = ";
		for (cnt = s.begin(); *cnt != ':'; cnt++)
			cout << *cnt;

		cout << endl << "Host     = ";
		for (cnt += 3; cnt != s.end() && *cnt != ':' && *cnt != '/'; cnt++)
			cout << *cnt;

		cout << endl << "Port     = ";
		if (cnt == s.end() || *cnt != ':')
			cout << "<default>";
		else
			for (cnt++; cnt != s.end() && *cnt != '/'; cnt++)
				cout << *cnt;

		cout << endl << "Path     = ";
		if (cnt == s.end())
			cout << "<default>";
		else
			for (cnt++; cnt != s.end(); cnt++)
				cout << *cnt;
		cout << endl << endl;
	}
	return 0;
}

