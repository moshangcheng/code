#include <iostream.h>
#include <fstream.h>
#include "LinkedQueue.h"

struct Position {
	int row;
	int col;
};

const int MaxMazeSize = 100, NumOfNbrs = 4;
int grid[MaxMazeSize][MaxMazeSize], m;
Position offset[4];

bool FindPath(Position start, Position finish, int& Pathlen) {
	if ((start.row == finish.row) && (start.col == finish.col)) {
		Pathlen = 0;
		return true;
	}
	for (int i = 0; i <= m + 1; i++) {
		grid[0][i] = grid[m + 1][i] = 1;
		grid[i][0] = grid[i][m + 1] = 1;
	}
	Position here, nbr;
	offset[0].row = 0;
	offset[0].col = 1;
	offset[1].row = 1;
	offset[1].col = 0;
	offset[2].row = 0;
	offset[2].col = -1;
	offset[3].row = -1;
	offset[3].col = 0;
	here.row = start.row;
	here.col = start.col;
	grid[start.row][start.col] = 2;

	LinkedQueue<Position> Q;
	while (1) {
		for (int i = 0; i < NumOfNbrs; i++) {
			nbr.row = here.row + offset[i].row;
			nbr.col = here.col + offset[i].col;
			if (grid[nbr.row][nbr.col] == 0) {
				grid[nbr.row][nbr.col] = grid[here.row][here.col] + 1;
				if ((nbr.row == finish.row) && (nbr.col == finish.col))
					break;
				Q.Add(nbr);
			}
		}
		if ((nbr.row == finish.row) && (nbr.col == finish.col))
			break;
		if (Q.IsEmpty())
			return false;
		Q.Delete(here);
	}
	Pathlen = grid[finish.row][finish.col] - 2;
	return true;
}

int main() {
	ifstream in("in.txt");
	cout << "                    Welcome To RAT IN A MAZE\n";
	cout << "Enter the size of the maze at most " << MaxMazeSize << endl;
	in >> m;

	cout << "Input the maze ,please!\n";
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++)
			in >> grid[i][j];

	Position start, finish;
	cout << "Enter the position of RAT\n";
	in >> start.row >> start.col;
	cout << "Enter the position of exit\n";
	in >> finish.row >> finish.col;

	int Pathlen;
	if (FindPath(start, finish, Pathlen)) {
		cout << "Rat can escape\n";
		Position here, nbr, *path = new Position[Pathlen];
		here = finish;
		for (int j = Pathlen - 1; j > -1; j--) {
			path[j] = here;
			for (int i = 0; i < NumOfNbrs; i++) {
				nbr.row = here.row + offset[i].row;
				nbr.col = here.col + offset[i].col;
				if (grid[nbr.row][nbr.col] == j + 2)
					break;
			}
			here = nbr;
		}
		for (int i = 0; i < Pathlen; i++)
			cout << path[i].row << " " << path[i].col << endl;
		delete[] path;
	} else
		cout << "Rat will be caugth\n";
	system("pause");
	return 0;
}
