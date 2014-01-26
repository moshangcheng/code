#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const double PI = 2*acos(0);

int main()
{
	int R;
	while(cin >> R) {
		cout.setf(ios::fixed);
		cout.precision(10);
		cout << (PI*R*R) << endl << (2.0*R*R) << endl;
	}
	return 0;
}
		
