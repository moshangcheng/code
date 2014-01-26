#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const double EP = 1e-6;

int main() {
	int a, b, c, otest = 0;
	cout.setf(ios::fixed);
	cout.precision(3);
	while (cin >> a >> b >> c) {
		if (a == b && b == c && c == 0)
			break;
		cout << "Triangle #" << ++otest << endl;
		if (c == -1)
			cout << "c = " << sqrt(a * a + b * b) << endl;
		else if (a == -1) {
			if (c <= b)
				cout << "Impossible.\n";
			else
				cout << "a = " << sqrt(c * c - b * b) << endl;
		} else if (b == -1) {
			if (c <= a)
				cout << "Impossible.\n";
			else
				cout << "b = " << sqrt(c * c - a * a) << endl;
		}
		cout << endl;
	}
	return 0;
}

