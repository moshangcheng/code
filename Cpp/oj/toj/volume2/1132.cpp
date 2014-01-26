#include <iostream>
using namespace std;

struct square {
	int c, r, d;
};

int main() {
	char c1, c2;
	int r1, r2, i, j;
	bool visited[8][8];
	square begin, end, list[64], temp;
	while (cin >> c1 >> r1 >> c2 >> r2) {
		begin.c = c1 - 'a';
		begin.r = r1 - 1;
		begin.d = 0;
		end.c = c2 - 'a';
		end.r = r2 - 1;
		end.d = -1;
		for (i = 0; i < 8; i++)
			for (j = 0; j < 8; j++)
				visited[i][j] = 0;

		list[0] = begin;
		visited[list[0].c][list[0].r] = 1;
		for (i = 0, j = 1; i < j; i++) {
			if (list[i].c == end.c && list[i].r == end.r)
				break;
			temp.c = list[i].c - 1;
			temp.r = list[i].r + 2;
			temp.d = list[i].d + 1;
			if (temp.c > -1 && temp.r < 8 && visited[temp.c][temp.r] == 0) {
				list[j++] = temp;
				visited[temp.c][temp.r] = 1;
			}
			temp.c = list[i].c + 1;
			temp.r = list[i].r + 2;
			temp.d = list[i].d + 1;
			if (temp.c < 8 && temp.r < 8 && visited[temp.c][temp.r] == 0) {
				list[j++] = temp;
				visited[temp.c][temp.r] = 1;
			}
			temp.c = list[i].c + 2;
			temp.r = list[i].r + 1;
			temp.d = list[i].d + 1;
			if (temp.c < 8 && temp.r < 8 && visited[temp.c][temp.r] == 0) {
				list[j++] = temp;
				visited[temp.c][temp.r] = 1;
			}
			temp.c = list[i].c + 2;
			temp.r = list[i].r - 1;
			temp.d = list[i].d + 1;
			if (temp.c < 8 && temp.r > -1 && visited[temp.c][temp.r] == 0) {
				list[j++] = temp;
				visited[temp.c][temp.r] = 1;
			}
			temp.c = list[i].c + 1;
			temp.r = list[i].r - 2;
			temp.d = list[i].d + 1;
			if (temp.c < 8 && temp.r > -1 && visited[temp.c][temp.r] == 0) {
				list[j++] = temp;
				visited[temp.c][temp.r] = 1;
			}
			temp.c = list[i].c - 1;
			temp.r = list[i].r - 2;
			temp.d = list[i].d + 1;
			if (temp.c > -1 && temp.r > -1 && visited[temp.c][temp.r] == 0) {
				list[j++] = temp;
				visited[temp.c][temp.r] = 1;
			}
			temp.c = list[i].c - 2;
			temp.r = list[i].r - 1;
			temp.d = list[i].d + 1;
			if (temp.c > -1 && temp.r > -1 && visited[temp.c][temp.r] == 0) {
				list[j++] = temp;
				visited[temp.c][temp.r] = 1;
			}
			temp.c = list[i].c - 2;
			temp.r = list[i].r + 1;
			temp.d = list[i].d + 1;
			if (temp.c > -1 && temp.r < 8 && visited[temp.c][temp.r] == 0) {
				list[j++] = temp;
				visited[temp.c][temp.r] = 1;
			}
		}
		cout << "To get from " << c1 << r1 << " to " << c2 << r2 << " takes "
				<< list[i].d << " knight moves.\n";
	}
	return 0;
}

