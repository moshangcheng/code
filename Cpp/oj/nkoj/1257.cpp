/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1257.html
 */
#include <iostream>
#include <iomanip>
using namespace std;

struct Point {
	double x;
	double y;
};

int main() {
	int N;
	cin >> N;
	while (N-- > 0) {
		Point p[7];
		for (int i = 0; i < 3; i++)
			cin >> p[i].x >> p[i].y;
		for (int j = 3; j < 6; j++) {
			int x = j % 3, y = (j + 1) % 3, z = (j + 2) % 3;
			p[j].x = p[x].x + (p[y].y - p[z].y) / 2;
			p[j].y = p[x].y + (p[z].x - p[y].x) / 2;
		}
		double a[3][2], A, B, C;
		//使用行列式求解线性方程组
		a[0][0] = p[4].x - p[3].x;
		a[0][1] = p[4].y - p[3].y;
		a[1][0] = p[0].x - p[3].x;
		a[1][1] = p[4].x - p[1].x;
		a[2][0] = p[0].y - p[3].y;
		a[2][1] = p[4].y - p[1].y;
		A = a[1][0] * a[2][1] - a[1][1] * a[2][0];
		B = a[0][0] * a[2][1] - a[0][1] * a[1][1];
		C = B / A;
		p[6].x = C * p[0].x + (1 - C) * p[3].x;
		p[6].y = C * p[0].y + (1 - C) * p[3].y;
		cout.setf(ios::fixed);
		cout << setprecision(4) << p[6].x << " " << p[6].y << endl;
	}
	return 0;
}
