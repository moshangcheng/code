#include <iostream.h>
#include "SparseMatrix.h"

int main() {
	SparseMatrix<int> M(100), N(100), L(100);
	cin >> M;
	M.Transpose(N);
	L = M - N;
	cout << M << endl << N << endl << L << endl;
	system("pause");
	return 0;
}
