#include <iostream>
using namespace std;

struct nb {
	int vlu, x, y;
};

int exGCD(int a, int b, int &x, int &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	int r = exGCD(b, a % b, x, y);
	int t = x;
	x = y;
	y = t - a / b * y;

	return r;
}

int main() {
	int a, b, c, x, y, z;
	while (cin >> a >> b >> c) {
		if (a == 0 && b == 0 && c == 0) {
			cout << "No Sense\n";
			continue;
		}
		z = exGCD(a, b, x, y);
		if (c % z == 0) {
			cout << "(" << a << ")*(" << x * c / z << ") + (";
			cout << b << ")*(" << y * c / z << ") = " << c << endl;
		} else
			cout << "No solution !\n";
	}
	system("pause");
	return 0;
}

