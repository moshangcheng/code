#include <iostream>
#include <cmath>
using namespace std;

const double a = 0.33267;
const double a1 = 0.4361836;
const double a2 = -0.1201676;
const double a3 = 0.9372986;
const double PI = acos(0) * 2.0;

double PHI(double x) {
	double t = 1.0 / (1 + a * abs(x));
	double value = (a1 * t + a2 * t * t + a3 * t * t * t) * exp(-x * x / 2.0)
			/ pow(2 * PI, 0.5);
	;
	if (x > 0)
		return 1 - value;
	else if (x < 0)
		return value;
	else
		return 0.5;
}

int main() {
	double x;
	while (cin >> x) {
		cout << PHI(x) << endl;
	}
	return 0;
}
