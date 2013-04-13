/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-18 下午10:25:39
 * @brief http://acm.nankai.edu.cn/p1215.html
 */
#include <iostream>
using namespace std;

const int SIZE = 100;
const int MAX = 100000;
bool Flag = 1, flag = 0;
int M, N, K;
int a, b, X, Y, dist, num_path;
int Cor1[SIZE][SIZE];
int Cor2[SIZE][SIZE];

int ID_Search1(int dist, int depth, int x, int y);
int ID_Search2(int dist, int depth, int x, int y);

int main() {
	int i, j;
	while (cin >> M >> N >> K) {
		for (i = 0; i < SIZE; i++)
			for (j = 0; j < SIZE; j++)
				Cor2[i][j] = Cor1[i][j] = MAX;

		for (i = 0; i < K; i++) {
			cin >> a >> b;
			Cor2[a - 1][b - 1] = Cor1[a - 1][b - 1] = 0;
		}
		cin >> a >> b >> X >> Y;
		a--;
		b--;
		X--;
		Y--;

		dist = num_path = 0;
		while (1) {
			flag = 0;
			ID_Search1(dist, 0, X, Y);
			if (flag == 0 || Flag == 0)
				break;
			flag = 0;
			ID_Search2(dist, 0, a, b);
			if (flag == 0 || Flag == 0)
				break;
			dist++;
		}
		if (flag == 0)
			cout << "No Solution!\n";
		else
			cout << dist << endl << num_path << endl;
	}
	return 0;
}

int ID_Search1(int dist, int depth, int x, int y) {
	if (dist == depth) {
		flag = 1;
		Cor1[x][y] = depth;
		if (x == a && y == b) {
			Flag = 0;
			num_path++;
		}
		return 1;
	}
	if (y > 0 && Cor1[x][y - 1] > depth)
		ID_Search1(dist, depth + 1, x, y - 1);
	if (x > 0 && Cor1[x - 1][y] > depth)
		ID_Search1(dist, depth + 1, x - 1, y);
	if (y < N - 1 && Cor1[x][y + 1] > depth)
		ID_Search1(dist, depth + 1, x, y + 1);
	if (x < M - 1 && Cor1[x + 1][y] > depth)
		ID_Search1(dist, depth + 1, x + 1, y);
}

int ID_Search2(int dist, int depth, int x, int y) {
	if (dist == depth) {
		flag = 1;
		Cor2[x][y] = depth;
		if (x == X && y == Y) {
			Flag = 0;
			num_path++;
		}
		return 1;
	}
	if (y > 0 && Cor2[x][y - 1] > depth)
		ID_Search2(dist, depth + 1, x, y - 1);
	if (x > 0 && Cor2[x - 1][y] > depth)
		ID_Search2(dist, depth + 1, x - 1, y);
	if (y < N - 1 && Cor2[x][y + 1] > depth)
		ID_Search2(dist, depth + 1, x, y + 1);
	if (x < M - 1 && Cor2[x + 1][y] > depth)
		ID_Search2(dist, depth + 1, x + 1, y);
}
