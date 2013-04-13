#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct node {
	int x, y;
};

int main() {
	ifstream in("C:\\Documents and Settings\\moshangcheng\\桌面\\in.txt");
	int n, p;
	string way;
	bool table[52][52];
	node worm[20];
	while (in >> n && n != 0) {

		for (int i = 0; i < 52; i++)
			for (int j = 0; j < 52; j++)
				table[i][j] = 0;
		for (int i = 11; i < 31; i++)
			table[25][i] = 1;
		for (int i = 0; i < 20; i++) {
			worm[i].x = 25;
			worm[i].y = 30 - i;
		}
		for (int i = 0; i < 52; i++)
			table[i][0] = table[i][51] = table[0][i] = table[51][i] = 1;

		in >> way;
		for (p = 0; p < n; p++) {
			if (way[p] == 'E') {
				table[worm[19].x][worm[19].y] = 0;
				for (int i = 19; i > 0; i--)
					worm[i] = worm[i - 1];
				worm[0].y++;
				if (table[worm[0].x][worm[0].y] == 1) {
					if (worm[0].y == 51)
						cout << "The worm ran off the board on move " << p + 1
								<< ".\n";
					else
						cout << "The worm ran into itself on move " << p + 1
								<< ".\n";
					break;
				} else
					table[worm[0].x][worm[0].y] = 1;
			} else if (way[p] == 'W') {
				table[worm[19].x][worm[19].y] = 0;
				for (int i = 19; i > 0; i--)
					worm[i] = worm[i - 1];
				worm[0].y--;
				if (table[worm[0].x][worm[0].y] == 1) {
					if (worm[0].y == 0)
						cout << "The worm ran off the board on move " << p + 1
								<< ".\n";
					else
						cout << "The worm ran into itself on move " << p + 1
								<< ".\n";
					break;
				} else
					table[worm[0].x][worm[0].y] = 1;
			} else if (way[p] == 'S') {
				table[worm[19].x][worm[19].y] = 0;
				for (int i = 19; i > 0; i--)
					worm[i] = worm[i - 1];
				worm[0].x++;
				if (table[worm[0].x][worm[0].y] == 1) {
					if (worm[0].x == 51)
						cout << "The worm ran off the board on move " << p + 1
								<< ".\n";
					else
						cout << "The worm ran into itself on move " << p + 1
								<< ".\n";
					break;
				} else
					table[worm[0].x][worm[0].y] = 1;
			} else if (way[p] == 'N') {
				table[worm[19].x][worm[19].y] = 0;
				for (int i = 19; i > 0; i--)
					worm[i] = worm[i - 1];
				worm[0].x--;
				if (table[worm[0].x][worm[0].y] == 1) {
					if (worm[0].x == 0)
						cout << "The worm ran off the board on move " << p + 1
								<< ".\n";
					else
						cout << "The worm ran into itself on move " << p + 1
								<< ".\n";
					break;
				} else
					table[worm[0].x][worm[0].y] = 1;
			}
		}
		if (p == n)
			cout << "The worm successfully made all " << n << " moves.\n";
	}
	system("pause");
	return 0;
}

