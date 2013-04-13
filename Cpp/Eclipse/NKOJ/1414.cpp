/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-18 下午10:25:39
 * @brief http://acm.nankai.edu.cn/p1414.html
 */
#include <iostream>
using namespace std;

int main() {
	int m, w, h, H, W, height, width;
	while (cin >> m && m) {
		W = H = height = width = 0;
		while (1) {
			cin >> w >> h;
			if (w == -1 && h == -1) {
				H += height;
				W = (W > width) ? W : width;
				break;
			}
			if (width + w <= m) {
				width += w;
				height = (height > h) ? height : h;
			} else {
				H += height;
				W = (W > width) ? W : width;
				width = w;
				height = h;
			}
		}
		cout << W << " x " << H << endl;
	}
	return 0;
}
