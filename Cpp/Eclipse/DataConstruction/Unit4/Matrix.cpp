#include <iostream>
using namespace std;
#include "Matrix.h"

int main() {
	Matrix<int> M(3, 5), N(3, 5), L(5, 3);
	for (int i = 1; i < 4; i++)
		for (int j = 1; j < 6; j++)
			M(i, j) = (i + j);
	N = M;
	N += 1;
	N = M + N;
	for (int i = 1; i < 4; i++) {
		for (int j = 1; j < 6; j++)
			cout << M(i, j) << " ";
		cout << endl;
	}
	cout << endl;
	for (int i = 1; i < 4; i++) {
		for (int j = 1; j < 6; j++)
			cout << N(i, j) << " ";
		cout << endl;
	}
	cout << endl;
	M.Transpose(L);
	for (int i = 1; i < 6; i++) {
		for (int j = 1; j < 4; j++)
			cout << L(i, j) << " ";
		cout << endl;
	}
	cout << endl;
	L = M * L;
	for (int i = 1; i < 4; i++) {
		for (int j = 1; j < 4; j++)
			cout << L(i, j) << " ";
		cout << endl;
	}
	M(1, 1) = N(1, 1);
	M(1, 1) = -1;
	cout << M(1, 1) << " " << N(1, 1) << endl;
	cout << endl;
	system("pause");
	return 0;
}
