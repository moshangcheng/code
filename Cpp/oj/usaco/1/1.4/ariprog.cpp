/*
 ID：aamosha1
 PROG: ariprog
 LANG: C++
 */
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream fin("ariprog.in");
	ofstream fout("ariprog.out");

	int Len, M, N, Num = 0;
	int i, j, k;
	bool Flag[125001];
	int a[62501];
	for (i = 0; i < 125001; i++)
		Flag[i] = 0;

	fin >> Len >> M;
	N = M * M * 2;
	for (i = 0; i <= M; i++)
		for (j = 0; j <= M; j++)
			Flag[i * i + j * j] = 1;
	for (i = 0, j = 0; i <= N; i++)
		if (Flag[i])
			a[j++] = i;

	for (j = 1; j <= N / (Len - 1); j++)
		for (i = 0; a[i] <= (N - j * Len + j); i++) {
			for (k = 1; k < Len; k++)
				if (Flag[a[i] + j * k] == 0)
					break;
			if (k == Len) {
				fout << a[i] << " " << j << endl;
				Num++;
			}
		}
	if (Num == 0)
		fout << "NONE\n";
	//system("pause");
	return 0;
}

