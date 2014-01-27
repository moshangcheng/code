#include <iostream>
#include <fstream>
using namespace std;
#include "Stack.h"

struct Position {
	int row;
	int col;
};

const int MaxMazeSize = 1000;
int m, maze[MaxMazeSize][MaxMazeSize];

bool FindPath() {
	Stack<Position>*path = new Stack<Position> (m * m - 1);
	Position offset[4];
	offset[0].row = 0;
	offset[0].col = 1;
	offset[1].row = 1;
	offset[1].col = 0;
	offset[2].row = 0;
	offset[2].col = -1;
	offset[3].row = -1;
	offset[3].col = 0;
	for (int i = 0; i <= m + 1; i++) {
		maze[0][i] = maze[m + 1][i] = 1;
		maze[i][0] = maze[i][m + 1] = 1;
	}
	Position here;
	here.row = 1;
	here.col = 1;
	maze[1][1] = 1;
	int option = 0;
	int LastOption = 4;
	while (here.row != m || here.col != m) {
		int r, c;
		while (option < LastOption) {
			r = here.row + offset[option].row;
			c = here.col + offset[option].col;
			if (maze[r][c] == 0)
				break;
			option++;
		}
		if (option < LastOption) {
			path->Add(here);
			here.row = r;
			here.col = c;
			maze[r][c] = 1;
			option = 0;
		} else {
			if (path->IsEmpty())
				return false;
			Position next;
			path->Delete(next);
			if (next.row == here.row)
				option = 2 + next.col - here.col;
			else
				option = 3 + next.row - here.row;
			here = next;
		}
	}
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
			in >> maze[i][j];
	if (FindPath())
		cout << "Rat can escape\n";
	else
		cout << "Rat will be caugth\n";
	system("pause");
	return 0;
}


