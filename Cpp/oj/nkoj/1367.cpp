/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-18 下午10:25:39
 * @brief http://acm.nankai.edu.cn/p1367.html
 */
#include <iostream>
#include <math.h>
using namespace std;

const double PI = 3.1415926;

int main() {
	int T;
	double X, Y;
	while (cin >> X >> Y && (X || Y)) {
		T = int(PI * (X * X + Y * Y) / 100) + 1;
		cout << "The property will be flooded in hour " << T << ".\n";
	}
	return 0;
}
