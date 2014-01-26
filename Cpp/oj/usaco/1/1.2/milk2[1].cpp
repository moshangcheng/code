/*
 ID: aamosha1
 PROG: milk2
 LANG: C++
 */
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

struct Time {
	int Start;
	int End;
};

int comp(const void*a, const void*b) {
	Time*A = (Time*) a;
	Time*B = (Time*) b;
	if (A->Start < B->Start)
		return -1;
	else if (A->Start > B->Start)
		return 1;
	else
		return 0;
}

int main() {
	ofstream fout("milk2.out");
	ifstream fin("milk2.in");

	int N, i, j;
	Time time[5000];
	fin >> N;
	for (i = 0; i < N; i++)
		fin >> time[i].Start >> time[i].End;

	qsort(time, N, sizeof(time[0]), comp);

	int S = time[0].Start;
	int E = time[0].End;
	int Max1 = E - S, Max2 = 0;
	for (j = 1; j < N; j++) {
		if (time[j].Start > E) {
			if (Max1 < E - S)
				Max1 = E - S;
			S = time[j].Start;
			if (Max2 < S - E)
				Max2 = S - E;
			E = time[j].End;
		} else if (time[j].End > E)
			E = time[j].End;
	}
	fout << Max1 << " " << Max2 << endl;
	return 0;
}
