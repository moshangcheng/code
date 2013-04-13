/*
 ID: aamosha1
 PROG: clocks
 LANG: C++
 */
#include <iostream>
#include <fstream>
using namespace std;

bool Flag = 1;
int Numb[9], S[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int Path[15];
int Plus[9][9] = { 3, 3, 0, 3, 3, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 3,
		3, 0, 3, 3, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0, 3, 0, 3, 3, 3, 0, 3,
		0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0, 3, 3, 0, 3, 3, 0, 0, 0, 0, 0, 0,
		0, 3, 3, 3, 0, 0, 0, 0, 3, 3, 0, 3, 3 };

void DFS(int n, int m) {
	int i, j;
	if (m == n) {
		for (i = 0; i < 9; i++)
			if ((S[i] + Numb[i]) % 12 != 0)
				break;
		if (i == 9)
			Flag = 0;
	} else if (m < n) {
		if (m == 0)
			i = 0;
		else
			i = Path[m - 1];
		for (; i < 9; i++) {
			Path[m] = i;
			if (m > 2 && Path[m] == Path[m - 3])
				continue;
			for (j = 0; j < 9; j++)
				S[j] += Plus[Path[m]][j];
			DFS(n, m + 1);
			if (Flag == 0)
				break;
			for (j = 0; j < 9; j++)
				S[j] -= Plus[Path[m]][j];
		}
	}
}

int main() {
	ifstream fin("clocks.in");
	ofstream fout("clocks.out");

	int i, j;
	for (i = 0; i < 9; i++)
		fin >> Numb[i];

	i = 0;
	while (++i) {
		DFS(i, 0);
		if (Flag == 0)
			break;
	}
	if (Flag == 0) {
		i--;
		for (j = 0; j < i; j++)
			fout << (Path[j] + 1) << " ";
		fout << (Path[j] + 1) << endl;
	}
	return 0;
}

