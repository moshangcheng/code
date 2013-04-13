#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

struct point {
	double x, y;
};
struct line {
	double a, b, c;
};
const double pi = 3.141592653589793;
const double EP = 1E-10;

line vertical(point a, point b) {
	line oc;
	oc.a = b.x - a.x;
	oc.b = b.y - a.y;
	oc.c = -(oc.a * (a.x + b.x) / 2.0 + oc.b * (a.y + b.y) / 2.0);
	return oc;
}

bool intersect(line l1, line l2, point &p) {
	double d = l1.a * l2.b - l2.a * l1.b;
	if (fabs(d) < EP)
		return false;
	p.x = -(l1.c * l2.b - l2.c * l1.b) / d;
	p.y = -(l1.a * l2.c - l2.a * l1.c) / d;
	return true;
}

int main() {
	point A, B, C, O;
	while (cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y) {
		intersect(vertical(A, B), vertical(B, C), O);
		cout.setf(ios::fixed);
		cout << setprecision(2) << 2 * pi * sqrt(((O.x - A.x) * (O.x - A.x)
				+ (O.y - A.y) * (O.y - A.y))) << endl;
	}
	return 0;
}

