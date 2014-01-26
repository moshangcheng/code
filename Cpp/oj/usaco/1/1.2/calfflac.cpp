/*
 ID: aamosha1
 PROG: calfflac
 LANG: C++
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void f(int i, int m, int &z1, int &z2, int &z3, char*b1, char*b2) {
	i++;
	int x1, x2, x3 = 0, k = i / 2;
	int y1, y2, y3 = 0;
	for (int j = 0; j < k; j++) {
		if (b1[j] == b2[m - i + j]) {
			if (x3 > 0) {
				x3++;
				x2 = j;
			} else {
				x3 = 1;
				x1 = x2 = j;
			}
			if (x3 > y3) {
				y1 = x1;
				y2 = x2;
				y3 = x3;
			}
		} else
			x3 = 0;
	}
	if (y3 > z3) {
		z1 = y1;
		z2 = y2;
		z3 = y3;
	}
	if (z2 == k - 1) {
		z3 = 2 * z3 + i - 2 * k;
		z2 = z3 + z1 - 1;
	}
}

int main() {
	ifstream fin("calfflac.in");
	ofstream fout("calfflac.out");

	int i;
	int n = 0, m = 0;
	int z1, z2, z3 = 0;
	int y1, y2, y3 = 0;
	int C[20000];
	string S;
	char B1[20000], B2[20000], A[20001];

	fin.read(A, 200001);
	while (n < fin.gcount()) {
		if (A[n] <= 'Z' && A[n] >= 'A') {
			C[m] = n;
			B1[m] = A[n];
			m++;
		} else if (A[n] <= 'z' && A[n] >= 'a') {
			C[m] = n;
			B1[m] = char(A[n] + 'A' - 'a');
			m++;
		}
		n++;
	}
	for (i = 0; i < m; i++)
		B2[i] = B1[m - 1 - i];
	B2[m] = B1[m] = '\0';
	for (i = 0; i < m; i++) {
		y3 = 0;
		f(i, m, y1, y2, y3, B1, B2);
		if (y3 > z3) {
			z3 = y3;
			z2 = y2;
			z1 = y1;
		}
	}
	for (i = m - 1; i > -1; i--) {
		y3 = 0;
		f(i, m, y1, y2, y3, B2, B1);
		if (y3 > z3) {
			z3 = y3;
			z2 = m - 1 - y1;
			z1 = m - 1 - y2;
		}
	}
	if (z3 > 0) {
		fout << z3 << endl;
		z1 = C[z1];
		z2 = C[z2];
		for (i = z1; i <= z2; i++)
			fout << A[i];
		fout << endl;
	}
	return 0;
}
