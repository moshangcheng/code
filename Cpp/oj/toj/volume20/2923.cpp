#include <iostream>
#include <string>
using namespace std;

int main() {
	int ntest;
	string a, b;
	cin >> ntest;
	while (ntest-- > 0) {
		cin >> a >> b;
		if ((a[a.size() - 1] + b[b.size() - 1]) % 2 == 0)
			cout << "MEET\n";
		else
			cout << "CANNOT\n";
	}
	return 0;
}
