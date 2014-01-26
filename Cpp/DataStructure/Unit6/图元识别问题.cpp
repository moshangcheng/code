#include <iostream>
#include <fstream>
using namespace std;
#include "LinkedQueue.h"

struct Position {
	int row;
	int col;
};

const int MaxSize = 1000;
int m, pixel[MaxSize][MaxSize];

void Label() {
	for (int i = 0; i <= m + 1; i++) {
		pixel[0][i] = pixel[m + 1][i] = 0;
		pixel[i][0] = pixel[i][m + 1] = 0;
	}
	Position offset[4];
	offset[0].row = 0;
	offset[0].col = 1;
	offset[1].row = 1;
	offset[1].col = 0;
	offset[2].row = 0;
	offset[2].col = -1;
	offset[3].row = -1;
	offset[3].col = 0;

	int NumOfNbrs = 4;
	LinkedQueue<Position> Q;
	int id = 1;
	Position here, nbr;

	for (int r = 1; r <= m; r++)
		for (int c = 1; c <= m; c++)
			if (pixel[r][c] == 1) {
				pixel[r][c] = ++id;
				here.row = r;
				here.col = c;
				while (1) {
					for (int i = 0; i < NumOfNbrs; i++) {
						nbr.row = here.row + offset[i].row;
						nbr.col = here.col + offset[i].col;
						if (pixel[nbr.row][nbr.col] == 1) {
							pixel[nbr.row][nbr.col] = id;
							Q.Add(nbr);
						}
					}
					if (Q.IsEmpty())
						break;
					Q.Delete(here);
				}
			}
}

int main() {
	ifstream in("C:\\Documents and Settings\\Guest\\桌面\\in.txt");
	cout << "Enter the size of table at most " << MaxSize << endl;
	in >> m;
	cout << "Enter the table please\n";
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++)
			in >> pixel[i][j];
	Label();
	cout << "Table labeled is\n";
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= m; j++)
			cout << pixel[i][j] << " ";
		cout << endl;
	}
	system("pause");
	return 0;
}

