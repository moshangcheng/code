/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1112.html
 */

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

struct STONE {
	int x;
	int y;
};

int main() {
	STONE stone[200];
	double Dist[200][200], dist[200];
	double temp, Dmax = -1000000000.0, newd;
	int N, i, j, k, m, Num = 0;
	while (cin >> N && N) {
		Num++;
		for (i = 0; i < N; i++) {
			cin >> stone[i].x >> stone[i].y;
			for (j = 0; j <= i; j++) {
				if (j != i)
					Dist[i][j] = Dist[j][i] = -sqrt(double((stone[i].x
							- stone[j].x) * (stone[i].x - stone[j].x)
							+ (stone[i].y - stone[j].y) * (stone[i].y
									- stone[j].y)));
				else
					Dist[i][j] = 0;
			}
		}

		for (i = 0; i < N; i++)
			dist[i] = Dist[0][i];

		for (i = 1; i < N; i++) {
			temp = Dmax;
			for (k = 1; k < N; k++) {
				if (dist[k] > temp && dist[k] < 0) {
					m = k;
					temp = dist[k];
				}

			}
			if (temp != Dmax) {
				dist[m] = -dist[m];
				for (j = 1; j < N; j++) {
					if (Dist[m][j] < 0 && dist[j] < 0) {
						newd = Dist[m][j];
						if (newd + dist[m] > 0)
							newd = -dist[m];
						if (dist[j] < newd)
							dist[j] = newd;
					}
				}
			}
		}
		cout << "Scenario #" << Num << endl << "Frog Distance = ";
		cout.setf(ios::fixed);
		cout << setprecision(3) << dist[1] << endl << endl;
	}
	return 0;
}

