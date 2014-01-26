/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1272.html
 */
#include <iostream>
using namespace std;

struct POINT {
	char c;
	int x;
	int y;
};

inline int V(int x1, int y1, int x2, int y2) {
	return (x1 * y2 - x2 * y1);
}

int main() {
	int N;
	while (cin >> N && N) {
		POINT P[15];
		for (int i = 0; i < N; i++)
			cin >> P[i].c >> P[i].x >> P[i].y;

		int Smax = 0, Flag[3];
		for (int j1 = 0; j1 < N; j1++)
			for (int j2 = 0; j2 < N; j2++)
				for (int j3 = 0; j3 < N; j3++) {
					if (j2 != j1 && j3 != j2 && j3 != j1) {
						int x1 = P[j2].x - P[j1].x;
						int x2 = P[j3].x - P[j1].x;
						int y1 = P[j2].y - P[j1].y;
						int y2 = P[j3].y - P[j1].y;
						int j = 0;
						for (; j < N; j++)
							if (j != j1 && j != j2 && j != j3) {
								int a = V(P[j].x - P[j1].x, P[j].y - P[j1].y,
										x1, y1);
								int b = V(P[j].x - P[j1].x, P[j].y - P[j1].y,
										x2, y2);
								int c = V(P[j].x - P[j2].x, P[j].y - P[j2].y,
										-x1, -y1);
								int d = V(P[j].x - P[j2].x, P[j].y - P[j2].y,
										x2 - x1, y2 - y1);
								if (a * b <= 0 && c * d <= 0)
									break;
							}
						if (j == N) {
							int S = V(x1, x2, y1, y2);
							if (S < 0)
								S = -S;
							if (S > Smax) {
								Flag[0] = j1;
								Flag[1] = j2;
								Flag[2] = j3;

								Smax = S;
							}
						}
					}
				}
		for (int j = 0; j < 3; j++)
			for (int k = j + 1; k < 3; k++)
				if (Flag[j] > Flag[k]) {
					int temp = Flag[k];
					Flag[k] = Flag[j];
					Flag[j] = temp;
				}
		for (int n = 0; n < 3; n++)
			cout << P[Flag[n]].c;
		cout << endl;
	}
	return 0;
}

