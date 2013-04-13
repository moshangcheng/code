#include <iostream>
#include <list>
#include <cmath>
#include <sstream>
#include <string>
using namespace std;

double dmin;
const double EP = 1E-10;
const double INF = 1E+10;
struct POINT {
	double x, y, d;
	char s[100];
};

double multi(double x1, double y1, double x2, double y2) {
	return (x1 * y2 - x2 * y1);
}

bool operator<(POINT a, POINT b) {
	double p = multi(a.x, a.y, b.x, b.y);
	if (fabs(p) < EP) {
		if (fabs(a.d - b.d) < EP && fabs(a.d - dmin) > EP)
			return (a.x * a.x + a.y * a.y > b.x * b.x + b.y * b.y) ? 1 : 0;
		else
			return (a.x * a.x + a.y * a.y < b.x * b.x + b.y * b.y) ? 1 : 0;
	} else
		return (p > 0) ? 1 : 0;
}

int main() {
	char T;
	POINT p, minp;
	list<POINT> L, temp_L;
	list<POINT>::iterator cnt, next, prev, cnt_t;
	while (1) {
		while (cin >> p.s) {
			istringstream ins(p.s);
			ins >> T >> p.x >> T >> p.y >> T;
			L.push_back(p);
			T = cin.get();
			if (T == '\n')
				break;
		}
		if (L.empty())
			break;
		for (cnt = L.begin(); cnt != L.end(); cnt++)
			if (cnt == L.begin() || cnt->y < minp.y || (fabs(cnt->y - minp.y)
					< EP && cnt->x < minp.x))
				minp = *cnt;
		dmin = INF;
		for (cnt = L.begin(); cnt != L.end(); cnt++) {
			cnt->x -= minp.x;
			cnt->y -= minp.y;
			if (fabs(cnt->x) + fabs(cnt->y) < EP)
				cnt->d = INF;
			else
				cnt->d = acos(cnt->x / sqrt(cnt->x * cnt->x + cnt->y * cnt->y));
			if (cnt->d < dmin)
				dmin = cnt->d;
		}
		L.sort();
		temp_L = L;
		if (L.size() > 3) {
			cnt = prev = L.begin();
			cnt = ++prev;
			for (next = ++cnt, next++; next != L.end(); cnt++, next++, prev++) {
				while (multi(next->x - prev->x, next->y - prev->y, cnt->x
						- prev->x, cnt->y - prev->y) > EP) {
					L.erase(cnt);
					cnt = prev--;
				}
			}
		}
		for (cnt = L.begin(); cnt != L.end(); cnt++) {
			if (cnt != L.begin())
				cout << " ";
			cout << cnt->s;
		}
		cout << endl;
		L.clear();
	}
	return 0;
}

