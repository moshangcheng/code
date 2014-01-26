/*
 ID: aamosha1
 PROG: beads
 LANG: C++
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	ofstream fout("beads.out");
	ifstream fin("beads.in");

	int Num;
	string Beads;
	fin >> Num >> Beads;

	int Maxlen = 0;
	for (int i = 0; i < Num; i++) {
		int x = 0, y = 0;
		char C1 = Beads[i];
		char C2 = Beads[(i - 1 + Num) % Num];
		bool Flag[500];
		for (int m = 0; m < 500; m++)
			Flag[m] = 1;

		for (int k = i;; k++) {
			int k1 = k % Num;
			if (Flag[k1] == 0)
				break;
			if (Beads[k1] == 'w' || Beads[k1] == C1 || C1 == 'w') {
				x++;
				Flag[k1] = 0;
				if (Beads[k1] != 'w')
					C1 = Beads[k1];
			} else
				break;
		}

		for (int j = i - 1;; j--) {
			int j1 = (j + Num) % Num;
			if (Flag[j1] == 0)
				break;
			if (Beads[j1] == 'w' || Beads[j1] == C2 || C2 == 'w') {
				y++;
				Flag[j1] = 0;
				if (Beads[j1] != 'w')
					C2 = Beads[j1];
			} else
				break;
		}
		int S = x + y;
		if (S > Maxlen)
			Maxlen = S;
	}
	fout << Maxlen << endl;
	return 0;
}

