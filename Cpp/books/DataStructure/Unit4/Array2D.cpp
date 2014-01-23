#include <iostream>
using namespace std;
#include "Array2D.h"

int main() {
	Array2D<int> M(3, 3), N(3, 3), L(3, 3);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			M[i][j] = (i + j);
	N = M;
	N += 1;
	N = M + N;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << M[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << N[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	L = M * N;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << L[i][j] << " ";
		cout << endl;
	}
	system("pause");
	return 0;
}
