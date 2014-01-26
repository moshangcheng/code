#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	int i;
	double a, sum;
	while (cin >> a) {
		for (sum = a, i = 0; i < 11; sum += a, i++)
			cin >> a;
		cout.setf(ios::fixed);
		cout << "$" << setprecision(2) << (sum / 12.0) << endl;
	}
	return 0;
}
