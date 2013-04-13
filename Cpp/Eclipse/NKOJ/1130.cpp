/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1130.html
 */
#include <iostream>
using namespace std;

void Swap(int &x, int &y) {
	int temp = x;
	x = y;
	y = temp;
}

int main() {
	int N;
	while (cin >> N) {
		int Point[50];
		char Edge[50];
		for (int i = 0; i < N; i++)
			cin >> Edge[i] >> Point[i];

		int Smax[50][50], Smin[50][50];
		for (int j = 0; j < N; j++)
			Smax[j][j] = Smin[j][j] = Point[j];

		for (int k1 = 1; k1 < N; k1++) {
			for (int k2 = 0; k2 < N; k2++) {
				int Min, Max, t2 = (k2 + k1) % N;
				Min = 1000000000;
				Max = -1000000000;
				for (int k3 = 0; k3 < k1; k3++) {
					int t1 = (k3 + k2) % N, t = (t1 + 1) % N, x1, y2;
					if (Edge[t] == 't') {
						y2 = Smin[k2][t1] + Smin[t][t2];
						x1 = Smax[k2][t1] + Smax[t][t2];
					}
					if (Edge[t] == 'x') {
						x1 = Smin[k2][t1] * Smin[t][t2];
						int x2 = Smax[k2][t1] * Smax[t][t2];
						int y1 = Smin[k2][t1] * Smax[t][t2];
						y2 = Smax[k2][t1] * Smin[t][t2];
						if (x1 < x2)
							Swap(x1, x2);
						if (y1 < y2)
							Swap(y1, y2);
						if (x1 < y1)
							Swap(x1, y1);
						if (x2 < y2)
							Swap(x2, y2);
					}
					if (x1 > Max)
						Max = x1;
					if (y2 < Min)
						Min = y2;
				}
				Smin[k2][t2] = Min;
				Smax[k2][t2] = Max;
			}
		}

		int Max = -1000000000;
		int Flag[50], m = 1, x = 0;
		for (int n = 0; n < N; n++) {
			int Temp = Smax[n][(n + N - 1) % N];
			if (Temp > Max) {
				Flag[0] = n + 1;
				Max = Temp;
				m = 1;
			} else if (Temp == Max)
				Flag[m++] = n + 1;
		}
		cout << Max << endl;
		while (x < m) {
			cout << Flag[x];
			if (++x < m)
				cout << " ";
		}
		cout << endl;
	}
	return 0;
}
