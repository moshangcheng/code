/*
 ID: aamosha1
 PROG: barn1
 LANG: C++
 */
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream fin("barn1.in");
	ofstream fout("barn1.out");

	int N, S, C;
	fin >> N >> S >> C;
	int i, j, k, s;
	int Lmin, Fmin = 2000;

	int Cow[200];
	bool Flag[200];
	int Len[50][200];
	for (i = 0; i < S; i++)
		Flag[i] = 0;

	for (i = 0; i < C; i++) {
		fin >> Cow[i];
		Cow[i]--;
		Flag[Cow[i]] = 1;
	}

	if (Flag[0])
		Fmin = 0;
	for (i = 0; i < N; i++)
		Len[i][0] = Flag[0];
	for (i = 1; i < S; i++) {
		if (Flag[i]) {
			Fmin = (Fmin < i) ? Fmin : i;
			Len[0][i] = i + 1 - Fmin;
		} else
			Len[0][i] = Len[0][i - 1];
	}

	for (i = 1; i < N; i++) {
		for (j = 1; j < S; j++) {
			if (Flag[j]) {
				Lmin = 1000000000;
				for (k = 0; k < j; k++) {
					s = Len[i - 1][k] + j - k;
					if (s < Lmin)
						Lmin = s;
				}
				Len[i][j] = Lmin;
			} else
				Len[i][j] = Len[i][j - 1];
		}
	}

	fout << Len[N - 1][S - 1] << endl;
	return 0;
}
