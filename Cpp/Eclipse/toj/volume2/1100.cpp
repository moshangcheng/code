#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

short gcd(short a, short b) {
	while (a != 0) {
		short c = b % a;
		b = a;
		a = c;
	}
	return b;
}
int main() {
	double pi;
	short i, j, s, N, a[50];
	cout.setf(ios::fixed);
	cout.precision(6);
	while (cin >> N && N > 0) {
		for (i = 0; i < N; i++)
			cin >> a[i];
		s = 0;
		for (i = 0; i < N; i++)
			for (j = i + 1; j < N; j++)
				if (gcd(a[i], a[j]) == 1)
					s++;
		if (s == 0)
			cout << "No estimate for this data set.\n";
		else {
			pi = sqrt(3.0 * N * (N - 1) / s);
			cout << pi << endl;
		}
	}
	return 0;
}

