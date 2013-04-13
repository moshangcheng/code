#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int *maxp, *minp;
	int i, j, N, P, FIND;
	int cpl[100][100], sov[100][2];
	while (cin >> N >> P) {
		memset(sov, 0, sizeof(sov));
		for (i = 0; i < N; i++) {
			for (j = 0; j < P; j++)
				cin >> cpl[i][j];
			maxp = max_element(cpl[i], cpl[i] + P);
			minp = min_element(cpl[i], cpl[i] + P);
			for (j = 0; j < P; j++) {
				if (cpl[i][j] == *maxp)
					sov[j][0]++;
				if (cpl[i][j] == *minp)
					sov[j][1]++;
			}
		}
		FIND = 0;
		for (i = 0; i < P; i++)
			if (sov[i][0] == 0 && sov[i][1] > N / 2) {
				if (FIND)
					cout << " " << i + 1;
				else {
					cout << i + 1;
					FIND = 1;
				}
			}
		if (FIND == 0)
			cout << 0;
		cout << endl;
	}
	return 0;
}
