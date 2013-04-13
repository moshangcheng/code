/*
 ID: aamosha1
 PROG: friday
 LANG: C++
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

inline bool Lpyear(int N) {
	if (N % 4 == 0 && (N % 400 == 0 || N % 100))
		return 1;
	else
		return 0;
}

int main() {
	ofstream fout("friday.out");
	ifstream fin("friday.in");

	int Num, s0 = 0;
	int a[7] = { 0, 0, 0, 0, 0, 0, 0 };
	string s[7] = { "Saturday", "Sunday", "Monday", "Thursday", "Wednessday",
			"Tuesday", "Friday" };

	fin >> Num;
	for (int n = 0; n < Num; n++) {
		int Month[] = { 3, 0, 3, 2, 3, 2, 3, 3, 2, 3, 2, 3 };
		if (Lpyear(n + 1900) == 1)
			Month[1] = 1;
		for (int i = 0; i < 12; i++) {
			a[s0]++;
			s0 = (s0 + Month[i]) % 7;
		}
	}
	for (int i = 0; i < 7; i++) {
		fout << a[i];
		if (i < 6)
			fout << " ";
	}
	fout << endl;
	return 0;
}

