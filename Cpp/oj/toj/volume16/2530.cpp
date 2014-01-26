#include <iostream>
#include <string>
using namespace std;

int main() {
	string X, Y;
	int i, j, lenx, leny;
	while (cin >> lenx) {
		if (lenx > 0)
			cin >> X;
		else
			X = "";
		cin >> leny;
		if (leny > 0)
			cin >> Y;
		else
			Y = "";
		lenx = X.size();
		leny = Y.size();
		int* d_cnt = new int[leny + 1];
		int* d_prev = new int[leny + 1];
		if (lenx == 0) {
			cout << leny << endl;
			continue;
		}
		for (i = 0; i <= leny; i++)
			d_prev[i] = i;
		for (i = 1; i <= lenx; i++) {
			d_cnt[0] = d_prev[0] + 1;
			for (j = 1; j <= leny; j++) {
				if (X[i - 1] == Y[j - 1])
					d_cnt[j] = d_prev[j - 1];
				else {
					d_cnt[j] = d_cnt[j - 1];
					if (d_cnt[j] > d_prev[j])
						d_cnt[j] = d_prev[j];
					if (d_cnt[j] > d_prev[j - 1])
						d_cnt[j] = d_prev[j - 1];
					d_cnt[j]++;
				}
			}
			for (j = 0; j <= leny; j++)
				d_prev[j] = d_cnt[j];
		}
		cout << d_cnt[leny] << endl;
		delete[] d_cnt;
		delete[] d_prev;
	}
	return 0;
}

