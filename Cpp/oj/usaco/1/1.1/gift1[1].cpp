/*
 ID: aamosha1
 PROG: gift1
 LANG: C++
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int Num;
string Name[10];

int Find(string A) {
	int i;
	for (i = 0; i < Num; i++)
		if (A == Name[i])
			break;
	if (i != Num)
		return i;
	else
		return -1;
}

int main() {
	ofstream fout("gift1.out");
	ifstream fin("gift1.in");

	fin >> Num;
	for (int i = 0; i < Num; i++)
		fin >> Name[i];

	int Sum, n, Money[10];
	for (int k = 0; k < Num; k++)
		Money[k] = 0;

	string Temp, name;
	while (fin >> Temp >> Sum >> n) {
		if (Sum || n) {
			int m = Find(Temp);
			int aver = Sum / n;
			Money[m] = Money[m] + Sum % n - Sum;
			while (n-- > 0) {
				fin >> name;
				int s = Find(name);
				Money[s] += aver;
			}
		}
	}

	for (int m = 0; m < Num; m++)
		fout << Name[m] << " " << Money[m] << endl;
	return 0;
}

