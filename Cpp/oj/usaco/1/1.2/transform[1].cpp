/*
 ID: aamosha1
 PROG: transform
 LANG: C++
 */
#include <iostream>
#include <fstream>
using namespace std;

int N, x, y;

void f(int j, int k, int flag) {
	if (flag == 0) {
		y = N - 1 - j;
		x = k;
	} else if (flag == 1) {
		x = N - 1 - j;
		y = N - 1 - k;
	} else if (flag == 2) {
		x = N - 1 - k;
		y = j;
	} else if (flag == 3) {
		x = j;
		y = N - 1 - k;
	}
}

int main() {
	ifstream fin("transform.in");
	ofstream fout("transform.out");

	int i, j, k, m, Flag = 1;
	char C1[10][10], C2[10][10];

	fin >> N;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			fin >> C1[i][j];
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			fin >> C2[i][j];

	for (i = 0; i < 6; i++) {
		if (i < 4) {
			for (j = 0; j < N && Flag; j++)
				for (k = 0; k < N && Flag; k++) {
					f(j, k, i);
					if (C1[j][k] != C2[x][y])
						Flag = 0;
				}
		} else if (i == 4) {
			for (m = 0; m < 4; m++) {
				for (j = 0; j < N && Flag; j++)
					for (k = 0; k < N && Flag; k++) {
						f(j, k, 3);
						f(x, y, m);
						if (C1[j][k] != C2[x][y])
							Flag = 0;
					}
				if (Flag)
					break;
				else if (m < 3)
					Flag = 1;
			}
		} else if (i == 5) {
			for (j = 0; j < N && Flag; j++)
				for (k = 0; k < N && Flag; k++)
					if (C1[j][k] != C2[j][k])
						Flag = 0;
		}
		if (Flag)
			break;
		Flag = 1;
	}
	fout << (i + 1) << endl;
	return 0;
}

