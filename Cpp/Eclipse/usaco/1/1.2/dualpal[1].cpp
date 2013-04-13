/*
 ID:	aamosha1
 PROG: dualpal
 LANG: C++
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ofstream fout("dualpal.out");
ifstream fin("dualpal.in");

bool Judge(int N, int B) {
	int temp = 0, T = N;
	while (T) {
		temp = T % B + temp * B;
		T = T / B;
	}
	if (temp == N)
		return 1;
	else
		return 0;
}

int main() {
	int N, S, Num = 0;

	fin >> N >> S;
	for (int i = S + 1;; i++) {
		if (Num == N)
			break;
		int num = 0;
		for (int j = 2; j < 11; j++) {
			if (num > 1)
				break;
			if (Judge(i, j) == 1)
				num++;
		}
		if (num > 1) {
			Num++;
			fout << i << endl;
		}
	}
	return 0;
}
