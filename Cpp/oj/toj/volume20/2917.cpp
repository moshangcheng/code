#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
	double S;
	while (cin >> S && S > 0) {
		cout.setf(ios::fixed);
		cout << setprecision(2) << sqrt(2 * S) << endl;
	}
	return 0;
}
